#include "server.h"
#define PERM 0644


//Global Variables [Values Set in main()]
int queue_len           = INVALID;                              //Global integer to indicate the length of the queue
int cache_len           = INVALID;                              //Global integer to indicate the length or # of entries in the cache
int num_worker          = INVALID;                              //Global integer to indicate the number of worker threads
int num_dispatcher      = INVALID;                              //Global integer to indicate the number of dispatcher threads
FILE *logfile;
int numreqs             = 0;                                    //Global file pointer for writing to log file in worker


/* ************************ Global Hints **********************************/

int cacheIndex = 0;                            //[Cache]           --> When using cache, how will you track which cache entry to evict from array?
int workerIndex = 0;                            //[worker()]        --> How will you track which index in the request queue to remove next?
int dispatcherIndex = 0;                        //[dispatcher()]    --> How will you know where to insert the next request received into the request queue?
int curequest= 0;                               //[multiple funct]  --> How will you update and utilize the current number of requests in the request queue?

pthread_t worker_thread[MAX_THREADS];           //[multiple funct]  --> How will you track the p_thread's that you create for workers?
pthread_t dispatcher_thread[MAX_THREADS];       //[multiple funct]  --> How will you track the p_thread's that you create for dispatchers?
int threadID[MAX_THREADS];                      //[multiple funct]  --> Might be helpful to track the ID's of your threads in a global array

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;        //What kind of locks will you need to make everything thread safe? [Hint you need multiple]
pthread_mutex_t log_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cache_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t some_content = PTHREAD_COND_INITIALIZER;  //What kind of CVs will you need  (i.e. queue full, queue empty) [Hint you need multiple]
pthread_cond_t free_space = PTHREAD_COND_INITIALIZER;
request_t req_entries[MAX_QUEUE_LEN];                    //How will you track the requests globally between threads? How will you ensure this is thread safe?

cache_entry_t* cacheReq;                                  //[Cache]  --> How will you read from, add to, etc. the cache? Likely want this to be global

/**********************************************************************************/



/*
  THE CODE STRUCTURE GIVEN BELOW IS JUST A SUGGESTION. FEEL FREE TO MODIFY AS NEEDED
*/


/* ******************************** Cache Code  ***********************************/

// Function to check whether the given request is present in cache
int getCacheIndex(char *request) { //loops through the cache struct and checks if it is not null and a match else it returns invalid
  /* TODO (GET CACHE INDEX)
  *    Description:      return the index if the request is present in the cache otherwise return INVALID
  */
  for (int x = 0; x < cache_len; x++) {
    if (cacheReq[x].request != NULL && strcmp(cacheReq[x].request, request) == 0) {
      return x;
    }
  }

  return INVALID;
}

// Function to add the request and its file content into the cache
void addIntoCache(char *mybuf, char *memory , int memory_size) {  // frees the cache at index cacheIndex then mallocs space and string copys the request and memcopys the data into the cache
  /* TODO (ADD CACHE)
  *    Description:      It should add the request at an index according to the cache replacement policy
  *                      Make sure to allocate/free memory when adding or replacing cache entries
  */
  if (cacheReq[cacheIndex].request != NULL) {
  	free(cacheReq[cacheIndex].request);
  }

  if ((cacheReq[cacheIndex].request = malloc(strlen(mybuf) + 1)) == NULL) {
    perror("add into cache request malloc failed");
    return;
  }

  if (cacheReq[cacheIndex].content != NULL) {
    free(cacheReq[cacheIndex].content);
  }

  if ((cacheReq[cacheIndex].content = malloc(memory_size)) == NULL) {
    perror("add into cache content malloc failed");
    return;
  }

  cacheReq[cacheIndex].len = memory_size;

  strcpy(cacheReq[cacheIndex].request, mybuf);
  memcpy(cacheReq[cacheIndex].content, memory, memory_size);

  cacheIndex = (cacheIndex + 1) % cache_len;
  // check .re and .content != NULL so free
  // go into cacheindex
  //malloc space for content and req
  //memcpy --> content
  // strcpy --> req
  //cache
}

// Function to clear the memory allocated to the cache
void deleteCache() { //frees the cache at all locations
  /* TODO (CACHE)
  *    Description:      De-allocate/free the cache memory
  */
  for (int x = 0; x < cache_len; x++) {
     if (cacheReq[x].content != NULL) {
    	free(cacheReq[x].content);
    }

     if (cacheReq[x].request != NULL) {
    	free(cacheReq[x].request);
    }
  }

  free(cacheReq);
}

// Function to initialize the cache
void initCache() {//mallocs the cache struct
  /* TODO (CACHE)
  *    Description:      Allocate and initialize an array of cache entries of length cache size
  */

  if ((cacheReq = malloc(sizeof(cache_entry_t)*cache_len)) == NULL) {
    perror("init cache malloc failed");
    exit(-1);
  }

  for (int x = 0; x < cache_len; x++) {
    cacheReq[x].len = 0;
    cacheReq[x].content= NULL;
    cacheReq[x].request = NULL;
  }
}

/**********************************************************************************/

/* ************************************ Utilities ********************************/
// Function to get the content type from the request
char* getContentType(char *mybuf) {//gets the content type by checking if the string of the request matches certain file types
  /* TODO (Get Content Type)
  *    Description:      Should return the content type based on the file type in the request
  *                      (See Section 5 in Project description for more details)
  *    Hint:             Need to check the end of the string passed in to check for .html, .jpg, .gif, etc.
  */
  char* conType;


  if (strstr(mybuf, ".html") != NULL) {
    conType = "text/html";
  }

  else if (strstr(mybuf, ".jpg") != NULL) {
    conType = "image/jepg";
  }

  else if (strstr(mybuf, ".gif") != NULL) {
    conType = "image/gif";
  }

  else if (strstr(mybuf, ".gif") != NULL) {
    conType = "image/gif";
  }

  else {
    conType = "text/plain";
  }

  //TODO remove this line and return the actual content type
  return conType;
}

// Function to open and read the file from the disk into the memory. Add necessary arguments as needed
// Hint: caller must malloc the memory space
int readFromDisk(int fd, char *mybuf, void **memory) {//opens the file given by the request then dynamically mallocs memory then copys the contents of the file into memory
  //    Description: Try and open requested file, return INVALID if you cannot meaning error

  FILE *fp;

  if ((fp = fopen(&mybuf[1], "r")) == NULL) {
    perror("readFromDisk open failed");
    return INVALID;
  }

  struct stat buf;
  if (stat(&mybuf[1], &buf) == -1) {
    perror("readFromDisk stat failed");
    return INVALID;
  }

  int size = buf.st_size;
  if ((*memory = malloc(size)) == NULL) {
    perror("readFromDisk memory malloc failed");
    return INVALID;
  }

  fread(*memory, size, size, fp);

  if (fclose(fp)) {
    perror("readFromDisk close failed");
    return INVALID;
  }

  fprintf (stderr, "Closed: %s\n", mybuf);
  /* TODO
  *    Description:      Find the size of the file you need to read, read all of the contents into a memory location and return the file size
  *    Hint:             Using fstat or fseek could be helpful here
  *                      What do we do with files after we open them?
  */
 

  //TODO remove this line and follow directions above
  return size;
}

/**********************************************************************************/

// Function to receive the path)request from the client and add to the queue
void * dispatch(void *arg) { //1 of many puts the fd into reqfd and the web request into webReq

  /********************* DO NOT REMOVE SECTION - TOP     *********************/

  /* TODO (B.I)
  *    Description:      Get the id as an input argument from arg, set it to ID
  */
  int ID = *(int *) arg;

  while (1) {


	int reqFd;
  char webReq[BUFF_SIZE];
  reqFd = accept_connection();

  if (get_request(reqFd, webReq)) {
    perror("dispatch get request failed");
    return NULL;
  }

	
    /* TODO (FOR INTERMEDIATE SUBMISSION)
    *    Description:      Receive a single request and print the conents of that request
    *                      The TODO's below are for the full submission, you do not have to use a
    *                      buffer to receive a single request
    *    Hint:             Helpful Functions: int accept_connection(void) | int get_request(int fd, char *filename
    *                      Recommend using the request_t structure from server.h to store the request. (Refer section 15 on the project write up)
    */

    /* TODO (B.II)
    *    Description:      Accept client connection
    *    Utility Function: int accept_connection(void) //utils.h => Line 24
    */

    /* TODO (B.III)
    *    Description:      Get request from the client
    *    Utility Function: int get_request(int fd, char *filename); //utils.h => Line 41
    */

    //fprintf(stderr, "Dispatcher Received Request: fd[%d] request[%s]\n", tempreq.fd, tempreq.request);
    /* TODO (B.IV)
    *    Description:      Add the request into the queue
    */

        //(1) Copy the filename from get_request into allocated memory to put on request queue

        //(2) Request thread safe access to the request queue

        //(3) Check for a full queue... wait for an empty one which is signaled from req_queue_notfull

        //(4) Insert the request into the queue

        //(5) Update the queue index in a circular fashion

        //(6) Release the lock on the request queue and signal that the queue is not empty anymore

    if (pthread_mutex_lock(&lock)) {   //2 of many: if curequest is equal to the que length then it will wait until it is not full
      perror("dispatch lock failed");
      return NULL;
    }

    while(curequest == queue_len ){
      if (pthread_cond_wait(&free_space, &lock)) {
        perror("dispatch wait condition failed");
        return NULL;
      }
    }
    req_entries[dispatcherIndex].fd = reqFd;

    if ((req_entries[dispatcherIndex].request = malloc(strlen(webReq) + 1)) == NULL) {
      perror("dispatch queue malloc failed");
      return NULL;
    }
//3 of many: sets the datastructure req_entries at the index dispatcherIndex. dispatcherIndex is circular so when it reaches the end it will go back to the first index 
    strcpy(req_entries[dispatcherIndex].request, webReq);
    dispatcherIndex = (dispatcherIndex + 1) % queue_len;
    curequest++;


    if (pthread_cond_signal(&some_content)) {
      perror("dispatch condition signal failed");
      return NULL;
    }

    if (pthread_mutex_unlock(&lock)) {
      perror("dispatch unlock failed");
      return NULL;
    }
  }

  return NULL;
}

/**********************************************************************************/
// Function to retrieve the request from the queue, process it and then return a result to the client
void * worker(void *arg) {//checks to see if there is work to do then retrives information from the global datastrcture containing the fd and reqinfo into the local variables
	//then checks to see if it is in the cache and services the request in a circular fashion
  /********************* DO NOT REMOVE SECTION - BOTTOM      *********************/

  #pragma GCC diagnostic ignored "-Wunused-variable"      //TODO --> Remove these before submission and fix warnings
  #pragma GCC diagnostic push                             //TODO --> Remove these before submission and fix warnings

  // Helpful/Suggested Declarations
  int num_request = 0;                                    //Integer for tracking each request for printing into the log
  bool cache_hit  = false;                                //Boolean flag for tracking cache hits or misses if doing
  int filesize    = 0;                                    //Integer for holding the file size returned from readFromDisk or the cache
  void *memory    = NULL;                                 //memory pointer where contents being requested are read and stored
  int fd          = INVALID;                              //Integer to hold the file descriptor of incoming request
  char mybuf[BUFF_SIZE];                                  //String to hold the file path from the request

  #pragma GCC diagnostic pop                              //TODO --> Remove these before submission and fix warnings

  /* TODO (C.I)
  *    Description:      Get the id as an input argument from arg, set it to ID
  */
  int ID = *(int *) arg;

  while (1) {
    /* TODO (C.II)
    *    Description:      Get the request from the queue and do as follows
    */
          //(1) Request thread safe access to the request queue by getting the req_queue_mutex lock

          //(2) While the request queue is empty conditionally wait for the request queue lock once the not empty signal is raised

          //(3) Now that you have the lock AND the queue is not empty, read from the request queue

          //(4) Update the request queue remove index in a circular fashion

          //(5) Check for a path with only a "/" if that is the case add index.html to it

          //(6) Fire the request queue not full signal to indicate the queue has a slot opened up and release the request queue lock

      if (pthread_mutex_lock(&lock)) {
        perror("worker request lock failed");
        exit(-1);
      }

      while(curequest == 0) {
        if (pthread_cond_wait(&some_content, &lock)) {
          perror("worker request wait condition failed");
          exit(-1);
        }
      }
      fd = req_entries[workerIndex].fd;
      strcpy(mybuf, req_entries[workerIndex].request);

      filesize = readFromDisk(fd, req_entries[workerIndex].request, &memory);

      curequest--;
      workerIndex = (workerIndex + 1) % queue_len;
      num_request++;
      if (strcmp(mybuf, "/") == 0) {
        strcpy(mybuf, "/index.html");
      }

      if (pthread_cond_signal(&free_space)) {
        perror("worker request condition signal failed");
        exit(-1);
      }

      if (pthread_mutex_unlock(&lock)) {
        perror("worker request unlock failed");
        exit(-1);
      }

    
      if (pthread_mutex_lock(&cache_lock)) {
        perror("worker cache lock failed");
        exit(-1);
      }

	    if (getCacheIndex(mybuf) == INVALID) {
	      addIntoCache(mybuf, memory, filesize);
	      cache_hit = false;
	    }

    	else {
    	   int cacheNum = getCacheIndex(mybuf);
    	 	 filesize = cacheReq[cacheNum].len;
    	 	 memory = cacheReq[cacheNum].content;
    	 	 cache_hit = true;
    	}

      if (pthread_mutex_unlock(&cache_lock)) {
        perror("worker cache unlock failed");
        exit(-1);
      }

      
      if (pthread_mutex_lock(&log_lock)) {
        perror("worker print lock failed");
        exit(-1);
      }

      LogPrettyPrint(logfile, ID, numreqs, fd, mybuf, filesize, cache_hit);
      LogPrettyPrint(NULL, ID, numreqs, fd, mybuf, filesize, cache_hit);
      numreqs ++;

      if (pthread_mutex_unlock(&log_lock)) {
        perror("worker print unlock failed");
        exit(-1);
      }

      //cache stuff
    /* TODO (C.III)
    *    Description:      Get the data from the disk or the cache
    *    Local Function:   int readFromDisk(//necessary arguments//);
    *                      int getCacheIndex(char *request);
    *                      void addIntoCache(char *mybuf, char *memory , int memory_size);
    */


	
    /* TODO (C.IV)
    *    Description:      Log the request into the file and terminal
    *    Utility Function: LogPrettyPrint(FILE* to_write, int threadId, int requestNumber, int file_descriptor, char* request_str, int num_bytes_or_error, bool cache_hit);
    *    Hint:             Call LogPrettyPrint with to_write = NULL which will print to the terminal
    *                      You will need to lock and unlock the logfile to write to it in a thread safe manor
    */

    /* TODO (C.V)
    *    Description:      Get the content type and return the result or error
    *    Utility Function: (1) int return_result(int fd, char *content_type, char *buf, int numbytes); //look in utils.h
    *                      (2) int return_error(int fd, char *buf); //look in utils.h
    */
    char *conT = getContentType(mybuf);
    if (filesize == INVALID) {
      if (return_error(fd, mybuf)) {
        perror("worker return error failed");
        exit(-1);
      }
    }

    else {
      if (return_result(fd, conT, memory, filesize)) {
        perror("worker return result failed");
        exit(-1);
      }
    }
  }

  return NULL;
}

/**********************************************************************************/

int main(int argc, char **argv) {//initializes server and threads then joins the threads to prevent program from finishing

  /********************* Dreturn resulfO NOT REMOVE SECTION - TOP     *********************/
  // Error check on number of arguments
  if(argc != 7){
    printf("usage: %s port path num_dispatcher num_workers queue_length cache_size\n", argv[0]);
    return -1;
  }


  int port            = -1;
  char path[PATH_MAX] = "no path set\0";
  num_dispatcher      = -1;                               //global variable
  num_worker          = -1;                               //global variable
  queue_len           = -1;                               //global variable
  cache_len           = -1;                               //global variable


  /********************* DO NOT REMOVE SECTION - BOTTOM  *********************/
  /* TODO (A.I)
  *    Description:      Get the input args --> (1) port (2) path (3) num_dispatcher (4) num_workers  (5) queue_length (6) cache_size
  */
  port = atoi(argv[1]);
  strcpy(path,argv[2]);
  num_dispatcher = atoi(argv[3]);
  num_worker = atoi(argv[4]);
  queue_len = atoi(argv[5]);
  cache_len = atoi(argv[6]);




  /* TODO (A.II)
  *    Description:     Perform error checks on the input arguments
  *    Hints:           (1) port: {Should be >= MIN_PORT and <= MAX_PORT} | (2) path: {Consider checking if path exists (or will be caught later)}
  *                     (3) num_dispatcher: {Should be >= 1 and <= MAX_THREADS} | (4) num_workers: {Should be >= 1 and <= MAX_THREADS}
  *                     (5) queue_length: {Should be >= 1 and <= MAX_QUEUE_LEN} | (6) cache_size: {Should be >= 1 and <= MAX_CE}
  */

  // (1) port: {Should be >= MIN_PORT and <= MAX_PORT}
  if( port > MAX_THREADS && port < MIN_PORT){
    perror("Invalid port number");
 	  exit(-1);
  }

  // (2) path: {Consider checking if path exists
  FILE* check = fopen(path, "r");

  if(check == NULL){
    perror("Failed to open path");
  	exit(-1);
  }

  // (3) num_dispatcher: {Should be >= 1 and <= MAX_THREADS}
  if (num_dispatcher < 1 || num_dispatcher > MAX_THREADS){
    perror("Invalid number of dispatcher threads");
  	exit(-1);
  }

  // (4) num_workers: {Should be >= 1 and <= MAX_THREADS}
  if (num_worker < 1 || num_worker > MAX_THREADS){
    perror("Invalid number of worker threads");
  	exit(-1);
  }

  // (5) queue_length: {Should be >= 1 and <= MAX_QUEUE_LEN}
  if (queue_len < 1 || queue_len > MAX_QUEUE_LEN){
    perror("Invalid queue length");
  	exit(-1);
  }

  // (6) cache_size: {Should be >= 1 and <= MAX_CE}
  if (cache_len < 1 || cache_len > MAX_CE){
    perror("Invalid cache length");
  	exit(-1);
  }

  /********************* DO NOT REMOVE SECTION - TOP    *********************/
  printf("Arguments Verified:\n\
    Port:           [%d]\n\
    Path:           [%s]\n\
    num_dispatcher: [%d]\n\
    num_workers:    [%d]\n\
    queue_length:   [%d]\n\
    cache_size:     [%d]\n\n", port, path, num_dispatcher, num_worker, queue_len, cache_len);
  /********************* DO NOT REMOVE SECTION - BOTTOM  *********************/

  /* TODO (A.III)
  *    Description:      Open log file
  *    Hint:             Use Global "File* logfile", use "web_server_log" as the name, what open flags do you want?
  */
  logfile = fopen("web_server_log", "w");
  if (logfile == NULL){
    perror("Failed to open web server log");
  	exit(-1);
  }

  /* TODO (A.IV)
  *    Description:      Change the current working directory to server root directory
  *    Hint:             Check for error!
  */
  if (chdir(path) == -1) {
    perror("Change directory failed");
    exit(-1);
  }

  /* TODO (A.V)
  *    Description:      Initialize cache
  *    Local Function:   void    initCache();
  */
	initCache();


  /* TODO (A.VI)
  *    Description:      Start the server
  *    Utility Function: void init(int port); //look in utils.h
  */
  init(port);

  /* TODO (A.VII)
  *    Description:      Create dispatcher and worker threads
  *    Hints:            Use pthread_create, you will want to store pthread's globally
  *                      You will want to initialize some kind of global array to pass in thread ID's
  *                      How should you track this p_thread so you can terminate it later? [global]
  */
  int x = 0;
  int dispatchArr[MAX_THREADS];
  for (x = 0; x < MAX_THREADS; x++) {
      dispatchArr[x] = x;
  }

  int workerArr[MAX_THREADS];
  for (x = 0; x < MAX_THREADS; x++) {
      workerArr[x] = x;
  }

  for (x = 0; x < num_dispatcher; x++) {
    if(pthread_create(&(dispatcher_thread[x]), NULL, dispatch, (void*) &dispatchArr[x]) != 0) {
      printf("Thread %d failed to create\n", x);
    }
    printf("Dispatcher\t\t\t\t\t\t\t[%4d] Started\n", x);
  }

  for (x = 0; x < num_worker; x++) {
    if(pthread_create(&(worker_thread[x]), NULL, worker, (void*) &workerArr[x]) != 0) {
      printf("Thread %d failed to create\n", x);
    }
    printf("Worker\t\t\t\t\t\t\t\t[%4d] Started\n", x);
  }
  // Wait for each of the threads to complete their work
  // Threads (if created) will not exit (see while loop), but this keeps main from exiting
  int i;
  for (i = 0; i < num_worker; i++) {
    if ((pthread_join(worker_thread[i], NULL)) != 0) {
      printf("ERROR : Fail to join worker thread %d.\n", i);
    }
  }

  for(i = 0; i < num_dispatcher; i++){
    fprintf(stderr, "JOINING DISPATCHER %d \n", i);
    if((pthread_join(dispatcher_thread[i], NULL)) != 0) {
      printf("ERROR : Fail to join dispatcher thread %d.\n", i);
    }
  }
  fprintf(stderr, "SERVER DONE \n");  // will never be reached in SOLUTION
}
