/* CSCI-4061 Fall 2022
 * Group Member #1: Maurice Yu yu000464
 * Group Member #2: Demond Counce counc012
 * Group Member #3: Yibeltal Wattero watte094
 */

#include "wrapper.h"
#include "util.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <gtk/gtk.h>
#include <signal.h>

#define MAX_TABS 100  // this gives us 99 tabs, 0 is reserved for the controller
#define MAX_BAD 1000
#define MAX_URL 100
#define MAX_FAV 100
#define MAX_LABELS 100


comm_channel comm[MAX_TABS];         // Communication pipes
char favorites[MAX_FAV][MAX_URL];    // Maximum char length of a url allowed
int num_fav = 0;                     // # favorites

typedef struct tab_list {
  int free;
  int pid; // may or may not be useful
} tab_list;

// Tab bookkeeping
tab_list TABS[MAX_TABS];


/************************/
/* Simple tab functions */
/************************/

// return total number of tabs
int get_num_tabs () {
  // Loop and count the number of used tabs
  int count = 0;
  for (int i = 0; i < MAX_TABS; i++) {
    // Increment count if the tab is not free
    if (TABS[i].free == 0) {
      count++;
    }
  }
  return count;
}

// get next free tab index
int get_free_tab () {
  // Loop until a free tab is found
  for (int i = 0; i < MAX_TABS; i++) {
    // Return index of first available tab
    if(TABS[i].free == 1) {
      return i;
    }
  }
  // Return -1 if no tab is free
  return -1;
}

// init TABS data structure
void init_tabs () {
  int i;

  for (i=1; i<MAX_TABS; i++)
    TABS[i].free = 1;
  TABS[0].free = 0;
}

/***********************************/
/* Favorite manipulation functions */
/***********************************/

// return 0 if favorite is ok, -1 otherwise
// both max limit, already a favorite (Hint: see util.h) return -1
int fav_ok (char *uri) {
  // Check if uri on favorites array
  if (on_favorites(uri) == 1) {
    return -1;
  }
  // Check if max amount of favorites is in the array
  else if (num_fav >= MAX_FAV) {
    return -1;
  }

  return 0;
}


// Add uri to favorites file and update favorites array with the new favorite
void update_favorites_file (char *uri) {
  //Checks if favorites constraints were broken
  if (fav_ok(uri) == -1) {
    alert("Favorites");
    return;
  }
  // Add uri to favorites file
  FILE* fp;
  if ((fp = fopen("./.favorites", "a")) == NULL) {
    perror("favorites open failed");
    exit(-1);
  }
  // Write to the favorites file
  else if (fprintf(fp, "%s\n", uri) < 0) {
    perror("favorites write failed");
    exit(-1);
  }
  // Close the fp to favorites file
  else if (fclose(fp)) {
    perror("favorites close failed");
    exit(-1);
  }
  // Update favorites array with the new favorite
  // char ch = '\0';
  // strncat(uri,&ch,1);
  strcpy(favorites[num_fav], uri);
  //printf("%s\n", favorites[num_fav]);
  num_fav++;
}

// Set up favorites array
void init_favorites (char *fname) {
  // Open file
  FILE* fp;
  if((fp = fopen(fname, "r+")) == NULL) {
    perror("favorites init open failed");
    exit(-1);
  }
  int i = 0;
  // Loop through file and add it to the favorites array
  while (fgets(favorites[i], MAX_URL, fp) != NULL) {
    favorites[i][strlen(favorites[i])-1]='\0';
    i++;
    
  }
  
  // strset("\n", "\0");
  // Increment total amount of favorites in array
  num_fav += i;
  // Close the fp to the fname file
  if (fclose(fp)) {
    perror("favorites init close failed");
    exit(-1);
  }
}

// Make fd non-blocking just as in class!
// Return 0 if ok, -1 otherwise
// Really a util but I want you to do it :-)
int non_block_pipe (int fd) {
  if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1) {
    return -1;
  }

  return 0;
}

/***********************************/
/* Functions involving commands    */
/***********************************/

// Checks if tab is bad and url violates constraints; if so, return.
// Otherwise, send NEW_URI_ENTERED command to the tab on inbound pipe
void handle_uri (char *uri, int tab_index) {
  // Checks if uri passed is good format
  if (bad_format(uri) == 1) {
    alert("Bad Format");
    return;
  }
  //Checks if uri is on the blacklist
  else if (on_blacklist(uri) == 1) {
    alert("Blacklist");
    return;
  }
  else {
    // Set req_t attributes to send command
    req_t msg;
    msg.type = NEW_URI_ENTERED;
    msg.tab_index = tab_index;
    sprintf(msg.uri, "%s", uri);

    // Write the command to the inbound pipe of tab_index
    if (write(comm[tab_index].inbound[1], &msg, sizeof(req_t)) == -1) {
      perror("uri write failed");
      exit(-1);
    }
    // Write url to the terminal
    printf("URL selected is %s\n", msg.uri);
  }
}


// A URI has been typed in, and the associated tab index is determined
// If everything checks out, a NEW_URI_ENTERED command is sent (see Hint)
// Short function
void uri_entered_cb (GtkWidget* entry, gpointer data) {

  if(data == NULL) {
    return;
  }

  // Get the tab (hint: wrapper.h)
  int tab_index = query_tab_id_for_request(entry, data);


  // Get the URL (hint: wrapper.h)
  char* uri = get_entered_uri(entry);


  // Hint: now you are ready to handle_the_uri
  handle_uri(uri, tab_index);

}


// Called when + tab is hit
// Check tab limit ... if ok then do some heavy lifting (see comments)
// Create new tab process with pipes
// Long function
void new_tab_created_cb (GtkButton *button, gpointer data) {

  if (data == NULL) {
    return;
  }

  // at tab limit?
  if (get_num_tabs() >= MAX_TABS) {
    alert("Max Tabs Reached");
    return;
  }

  // Get a free tab
  int tab_index = get_free_tab();

  // Create communication pipes for this tab
  if (pipe(comm[tab_index].inbound) == -1) {
    perror("New tab inbound pipe failed");
    exit(-1);
  }

  if (pipe(comm[tab_index].outbound) == -1) {
    perror("New tab outbound pipe failed");
    exit(-1);
  }

  // Make the read ends non-blocking
  if (non_block_pipe(comm[tab_index].inbound[0]) == -1) {
    perror("Render non-block failed");
    exit(-1);
  }
  if (non_block_pipe(comm[tab_index].outbound[0]) == -1) {
    perror("Render non-block failed");
    exit(-1);
  }

  // fork and create new render tab
  pid_t pidnum;
  if ((pidnum = fork()) == -1) {
    perror("Render tab fork failed");
    exit(-1);
  }

  else if (pidnum == 0) {
    // Note: render has different arguments now: tab_index, both pairs of pipe fd's
    // (inbound then outbound) -- this last argument will be 4 integers "a b c d"
    // Hint: stringify args
    char pipe_str[40];
    char tabnum[2];
    sprintf(tabnum, "%d", tab_index);
    sprintf(pipe_str, "%d %d %d %d", comm[tab_index].inbound[0], comm[tab_index].inbound[1], comm[tab_index].outbound[0], comm[tab_index].outbound[1]);

    if(execl("./render", "render", tabnum, pipe_str, NULL) == -1) {
      perror("Render tab execl failed");
      exit(-1);
    }
  }

  else {
    // Controller parent just does some TABS bookkeeping
    TABS[tab_index].free = 0;
  }
}

// This is called when a favorite is selected for rendering in a tab
// Hint: you will use handle_uri ...
// However: you will need to first add "https://" to the uri so it can be rendered
// as favorites strip this off for a nicer looking menu
// Short
void menu_item_selected_cb (GtkWidget *menu_item, gpointer data) {

  if (data == NULL) {
    return;
  }

  // Note: For simplicity, currently we assume that the label of the menu_item is a valid url
  // get basic uri
  char *basic_uri = (char *)gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item));

  // append "https://" for rendering
  char uri[MAX_URL];
  sprintf(uri, "https://%s", basic_uri);

  // Get the tab (hint: wrapper.h)
  int tab_index = query_tab_id_for_request(menu_item, data);

  // Hint: now you are ready to handle_the_uri
  handle_uri(uri, tab_index);

  return;
}

// BIG CHANGE: the controller now runs an loop so it can check all pipes
// Long function
int run_control() {
  browser_window * b_window = NULL;
  int i, nRead, status;
  req_t req;

  //Create controller window
  create_browser(CONTROLLER_TAB, 0, G_CALLBACK(new_tab_created_cb),
		 G_CALLBACK(uri_entered_cb), &b_window, comm[0]);

  // Create favorites menu
  create_browser_menu(&b_window, &favorites, num_fav);

  while (1) {
    process_single_gtk_event();

    // Read from all tab pipes including private pipe (index 0)
    // to handle commands:
    // PLEASE_DIE (controller should die, self-sent): send PLEASE_DIE to all tabs
    // From any tab:
    //    IS_FAV: add uri to favorite menu (Hint: see wrapper.h), and update .favorites
    //    TAB_IS_DEAD: tab has exited, what should you do?

    // Loop across all pipes from VALID tabs -- starting from 0
    for (i=0; i<MAX_TABS; i++) {
      if (TABS[i].free) continue;
      nRead = read(comm[i].outbound[0], &req, sizeof(req_t));

      // Check that nRead returned something before handling cases
      if (nRead == -1) {
        continue;
      }

      // Case 1: PLEASE_DIE
      if (req.type == PLEASE_DIE && i == 0) {
        for (int j = 1; j < MAX_TABS; j++) {
          if (TABS[j].free == 0) {
            if (write(comm[j].inbound[1], &req, sizeof(req_t)) == -1) {
              perror("PLEASE_DIE command write failed");
              exit(-1);
            }
          }
        }
        for (int k = 1; k < get_num_tabs(); k++) {
          if (waitpid(TABS[k].pid, &status, 0) == -1) {
            perror("PLEASE_DIE command wait failed");
            exit(-1);
          }
        }
        return 0;
      }

      // Case 2: TAB_IS_DEAD
      if (req.type == TAB_IS_DEAD && TABS[i].free == 0) {
        if (waitpid(TABS[i].pid, &status, 0) == -1) {
          perror("TAB_IS_DEAD wait failed");
          exit(-1);
        }
        TABS[i].free = 1;
      }

      // Case 3: IS_FAV
      if (req.type == IS_FAV && TABS[i].free == 0) {
        update_favorites_file(req.uri);
        if (fav_ok(req.uri) == 0)  {
          add_uri_to_favorite_menu(b_window, req.uri);
        }
        continue;
      }
    }
    usleep(1000);
  }
  return 0;
}


int main(int argc, char **argv)
{

  if (argc != 1) {
    fprintf (stderr, "browser <no_args>\n");
    exit (0);
  }

  init_tabs ();
  // init blacklist (see util.h), and favorites (write this, see above)
  init_blacklist("./.blacklist");
  init_favorites("./.favorites");


  // Fork controller
  pid_t pidnum;
  if ((pidnum = fork()) == -1) {
    perror("Controller fork failed");
    exit(-1);
  }
  // Child process
  else if (pidnum == 0) {
    // Child creates a pipe for itself comm[0]
    if (pipe(comm[0].inbound) == -1) {
      perror("Controller inbound pipe failed");
      exit(-1);
    }

    if (pipe(comm[0].outbound) == -1) {
      perror("Controller outbound pipe failed");
      exit(-1);
    }
    // Non-block the reading ends of the controller
    if (non_block_pipe(comm[0].inbound[0]) == -1 ) {
      perror("Controller non-block failed");
      exit(-1);
    }
    if (non_block_pipe(comm[0].outbound[0]) == -1) {
      perror("Controller non-block failed");
      exit(-1);
    }

    // then calls run_control ()
    run_control();
  }
  // Parent waits ...
  else {
    if (wait(NULL) == -1) {
      perror("Parent wait failed");
      exit(-1);
    }
  }

  return 0;
}
