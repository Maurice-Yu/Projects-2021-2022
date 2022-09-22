import java.util.Random;
import java.util.Scanner;
// abstract class Game {
//   public Random random;
//   protected int rounds;
//   protected int round=0;
//   protected String guess;
//   private String name;
//   protected String answer;
//   protected abstract String prepToPlay();

//   protected abstract boolean isOver();
//   protected abstract boolean isValid(String move);

//   protected abstract String processMove(String move);
//   protected abstract String finalMessage();
//   protected abstract String getName();
//   public void play(Scanner user)
//   { 
//     System.out.println(this.prepToPlay());
//     while(user.hasNext())
//     {
//     System.out.print("Enter Your Move or 'quit' to quit ");
//     String x;
//     x=user.next();
//     if(x!="quit")
//       {
//       System.out.print(this.processMove(x));
//       while (!this.isValid(x))
//       {
//         x=user.next();
//         System.out.print(this.processMove(x));
//       }
//       if (this.isOver())
//       {
//         System.out.println(this.finalMessage());
//         break;
//       }
//       }
    
//     else
//     {
//       System.out.println(this.finalMessage());
//     }

//     }
//   }

// }

// class NumberGuesser extends Game
// {
//   private int secret;
//   protected String getName()
//   {
//     return"NumberGuesser";
//   }
//   protected void setguess(String x)
//   {
//     guess=x;
//   }
//   protected boolean isValid(String move)
//   {
//       for (int i = 0;i<guess.length();i++)
//     {

//       if (guess.charAt(i) != '1'&& guess.charAt(i) != '2'&&guess.charAt(i) !='3'&& guess.charAt(i) != '4'&& guess.charAt(i) != '5'&& guess.charAt(i) != '6'&&guess.charAt(i) != '7'&&guess.charAt(i) != '8'&& guess.charAt(i) !='9'&& guess.charAt(i) !='0' 
//       )
//       {
//         return false;
//       }
//     }
//     return true;
//   }
//   //   protected void play(Scanner user)
//   // {
//   //   System.out.println(this.prepToPlay());
//   //   while(user.hasNext())
//   //   {
//   //   System.out.print("Enter Your Move or 'quit' to quit ");
//   //   String x;
//   //   x=user.next();
//   //   if(x!="quit")
//   //     {
//   //     System.out.print(this.processMove(x));
//   //     while (!this.isValid())
//   //     {
//   //       x=user.next();
//   //       System.out.print(this.processMove(x));
//   //     }
//   //     if (this.isOver())
//   //     {
//   //       System.out.println(this.finalMessage());
//   //       break;
//   //     }
//   //     }
    
//   //   else
//   //   {
//   //     System.out.println(this.finalMessage());
//   //   }

//   //   }
//   // }
//   protected int getsecret()
//   {
//     return secret;
//   }
//   private int maxsecret;

//   public NumberGuesser(Random rng,int maxnumber,int maxguesses)
//   {
//     random = rng;
//     rounds= maxguesses;
//     maxsecret= maxnumber;


//   }
//   protected boolean isOver()
//   {
//     if (rounds<round)
//     {
//       return true;
//     }
//     return false;

//   }
//   protected String finalMessage()
//   {
//     return "The number was: "+this.getsecret()+"\n";

//   }
//   protected String processMove(String move)
//   {
//     this.setguess(move);

//     if (this.isValid(move)==true)
//     {
       
//        int x=Integer.parseInt(move);
        

//        round+=1;
//         if (Integer.parseInt(move)>this.getsecret())
//         {
//           return("Too High"+"\n");
//         }
//         if (Integer.parseInt(move)<this.getsecret())
//         {
//           return("Too Low"+"\n");
//         }
//         if ((Integer.parseInt(move)==(this.getsecret())))
//         {
//           return("That's it!"+"\n"+this.finalMessage());
//         }
//       }
    
//       return("Invalid Move! try again");
    
//   }

//   protected String prepToPlay()
//   {
//     secret=random.nextInt(maxsecret);
//     round=1;
//     return"I’ve picked a number 1 to " +maxsecret+". You get " + rounds+" guesses to guess it";
//   }

// }

// class Hangman extends Game
// {
//   protected String word;
//   protected String currentbord="";
//   protected int min;
//   protected int max;
//   protected WordsList words;
//   protected String getName()
//   {
//     return"Hangman";
//   }
//   protected String prepToPlay()
//   {

//     answer=words.getWord(min,max);
//     round=1;
//     currentbord="";
    
//     for(int i = 0;i<answer.length();i++)
//     {
//       currentbord+="-";
//     }
//     round = 1;
//     return("I’ve picked a "+answer.length()+"letter word. Guess letters you think are in the word. You get "+rounds+"guesses.");
//   }
//    protected boolean isOver()
//   {
//     if (rounds<round)
//     {
//       return true;
//     }
//     return false;

//   }
//   protected Hangman(WordsList words,int min, int max, int maxguess)
//   {
//     this.words = words;
//     this.min = min;
//     this.max = max;
//     this.rounds = maxguess;
//   }
//   //  protected void play(Scanner user)
//   // {
//   //   System.out.println(this.prepToPlay());
//   //   while(user.hasNext())
//   //   {
//   //   System.out.print("Enter Your Move or 'quit' to quit ");
//   //   String x;
//   //   x=user.next();
//   //   if(x!="quit")
//   //     {
//   //     System.out.print(this.processMove(x));
//   //     while (!this.isValid())
//   //     {
//   //       x=user.next();
//   //       System.out.print(this.processMove(x));
//   //     }
//   //     if (this.isOver())
//   //     {
//   //       System.out.print(this.finalMessage());
//   //       break;
//   //     }
//   //     }
    
//   //   else
//   //   {
//   //     System.out.println(this.finalMessage());
//   //   }

//   //   }
//   // }
//   protected boolean isValid(String move)
//   {
//     if(this.guess.length()>1)
//     {
//       return false;
//     }
//      for (int i = 0;i<guess.length();i++)
//     {
//       if (answer.charAt(i) != 'q'&& answer.charAt(i) != 'w'&& answer.charAt(i) != 'e'&& answer.charAt(i) != 'r'&& answer.charAt(i) != 't'&&answer.charAt(i) != 'y'&& answer.charAt(i) != 'u'&& answer.charAt(i) != 'i'&& answer.charAt(i) != 'o'&& answer.charAt(i) != 'p'&& answer.charAt(i) != 'a'&& answer.charAt(i) != 's'&& answer.charAt(i) != 'd'&& answer.charAt(i) != 'f'&& answer.charAt(i) != 'g'&& answer.charAt(i) != 'h'&& answer.charAt(i) != 'j'&& answer.charAt(i) != 'k'&& answer.charAt(i) != 'l'&& answer.charAt(i) != 'z'&& answer.charAt(i) != 'x'&& answer.charAt(i) != 'c'&& answer.charAt(i) != 'v'&& answer.charAt(i) != 'b'&& answer.charAt(i) != 'n'&& answer.charAt(i) != 'm'
//       )
//       {
//         return false;
//       } 
     
//   }
//    return true;
//   }
//   protected String processMove(String move)
//     {
//    round+=1;
//   this.guess=move;
//     if (this.isValid(move)==true)
//     {
    
     
//         for(int i=0;i<answer.length();i++)
//         {
//           if(this.guess.equals(answer.substring(i,i+1)))
//           {
//             currentbord=currentbord.substring(0,i)+move+currentbord.substring(i+1,currentbord.length());
//           }
//         }
//         if(currentbord.equals(answer))
//         {

//           return(currentbord+"\n"+this.finalMessage());
//         }
//       return currentbord+"\n";
//       }
//       return("Invalid Move! try again ");
    
//   }
//   protected String finalMessage()
//   {
//     return("The word was: "+answer+"\n");
//   }
  
// }
// // class wordjumbler extends Game
// // {
// //   String word;
// //   String currentbord;

// //    protected void play(Scanner user)
// //   {
// //     System.out.println(this.prepToPlay());
// //     while(user.hasNext())
// //     {
// //     String x;
// //     x=user.next();
// //     if(x!="quit")
// //     {
// //       System.out.print("Enter Your Move or 'quit' to quit");
// //     System.out.println(this.processMove(x));
  
// //     }
// //     else
// //     {
// //       System.out.println(this.finalMessage());
// //     }

// //     }
// //   }
// //   protected boolean isValid()
// //   {
// //      for (int i = 0;i<guess.length();i++)
// //     {
// //       if (answer.charAt(i) != 'q'&& answer.charAt(i) != 'w'&& answer.charAt(i) != 'e'&& answer.charAt(i) != 'r'&& answer.charAt(i) != 't'&&answer.charAt(i) != 'y'&& answer.charAt(i) != 'u'&& answer.charAt(i) != 'i'&& answer.charAt(i) != 'o'&& answer.charAt(i) != 'p'&& answer.charAt(i) != 'a'&& answer.charAt(i) != 's'&& answer.charAt(i) != 'd'&& answer.charAt(i) != 'f'&& answer.charAt(i) != 'g'&& answer.charAt(i) != 'h'&& answer.charAt(i) != 'j'&& answer.charAt(i) != 'k'&& answer.charAt(i) != 'l'&& answer.charAt(i) != 'z'&& answer.charAt(i) != 'x'&& answer.charAt(i) != 'c'&& answer.charAt(i) != 'v'&& answer.charAt(i) != 'b'&& answer.charAt(i) != 'n'&& answer.charAt(i) != 'm'
// //       )
// //       {
// //         return false;
// //       } 
// //   }
// //   }
// //   protected String processMove(String move)
// //     {
// //     this.guess=move;
  
// //     if (this.isValid()==true)
// //     {
// //         round+=1;
        
// //       if (!this.isOver())
// //       {
    
// //       }
// //       else
// //     {
// //       return(this.finalMessage());
// //     }
// //     }
// //       return("Invalid Move! try again");
    
// //   }
  
// // }
class Main
{
  public static void main(String[] args) {
        // TEST 1: this expects exact matches.


        String input = "-10\n2\nvalid\nwin\n1\nquit\n7\n3\n";
        // 10
        // 2
        // valid
        // win
        // 1
        // quit
        // 7
        // 3

        // System.out.println("Test 1");
        // // setting this one aside so I can check if it's been played
        // DummyGame special = new DummyGame("Special");

        // System.out.println("special.isOver: "+special.isOver());


        // Game[] games = new Game[]{new DummyGame("apples"),
        //                    new DummyGame("Bananas"),
        //                    special};
        // Scanner scan = new Scanner(input);
        // GameGrabber gg = new GameGrabber(games, scan);
        // gg.doMenu();

        // System.out.println("special.isOver: "+special.isOver());

        // System.out.println("Test 2");
        // System.out.println("This requires manual validation and input");
        // System.out.println("Check for a well-formatted menu with at least 4 options, one for each game.");
        // // in case you didn't know -- you can call main directly. While it is a _special_ static method,
        // it is, ultimately, just a static method
        GameGrabber.main(new String[0]);
    }

  //   public static void main(String[] args)
  // {
  //    Scanner x= new Scanner(System.in);
  //   Random y = new Random();
  //   WordsList words= new WordsList(y);
  //   Game[] games = new Game[4];
  //   {
  //     games[0]=new Hangman(words,2,5,5);
  //     games[1]=new NumberGuesser(y,5,5);
  //     games[2]= new RPS(y,5,5);
  //     games[3]= new WordJumble(words,y,1,5,5);
  //   }
  //   GameGrabber game=new GameGrabber(games,x);
  //   game.doMenu();
  // }
  // public static void main(String[] args) {
  //       // TEST 1: this expects exact matches.


  //       String input = "-10\n2\nvalid\nwin\n1\nquit\n7\n3\n";
  //       // 10
  //       // 2
  //       // valid
  //       // win
  //       // 1
  //       // quit
  //       // 7
  //       // 3

  //       System.out.println("Test 1");
  //       // setting this one aside so I can check if it's been played
  //       DummyGame special = new DummyGame("Special");

  //       System.out.println("special.isOver: "+special.isOver());


  //       Game[] games = new Game[]{new DummyGame("apples"),
  //                          new DummyGame("Bananas"),
  //                          special};
  //       Scanner scan = new Scanner(input);
  //       GameGrabber gg = new GameGrabber(games, scan);
  //       gg.doMenu();

  //       System.out.println("special.isOver: "+special.isOver());

  //       System.out.println("Test 2");
  //       System.out.println("This requires manual validation and input");
  //       System.out.println("Check for a well-formatted menu with at least 4 options, one for each game.");
  //       // in case you didn't know -- you can call main directly. While it is a _special_ static method,
  //       // it is, ultimately, just a static method
  //       GameGrabber.main(new String[0]);
  //   }
  // public static void main(String[] args) {
  //       System.out.println("Test 1");

  //       FakeRandom fr = new FakeRandom(50); // should mean a random number of 50.
  //       NumberGuesser ng = new NumberGuesser(fr, 72, 5);

  //       String input = "apple\n49\n51\n50\n";
  //       ng.play(new Scanner(input));
  //       System.out.println("TEST 1 PHASE 2");
  //       input = "apple\n1\n2\ndog\n4\npear\n3\n5\n";
  //       ng.play(new Scanner(input));

  //   }
    // public static void main(String[] args) {

    //     FakeWordList fwl = new FakeWordList("aardvark");
    //     Hangman hw = new Hangman(fwl, 4, 9, 10);

    //     System.out.println("TEST 1");
    //     String input = "r\nd\na\nq\nk\na\naardvark\nv\n";
    //     hw.play(new Scanner(input));

    //     System.out.println("TEST 1 part 2");
    //     input = "";
    //     for (int i = 0; i < 10; i++) {
    //         input += "a\n";
    //     }
        // hw.play(new Scanner(input));
    // }
    //     public static void main(String[] args) {
    //     Random rand = new Random();
    //     FakeWordList fwl = new FakeWordList("abcdefghijklmnopqrstuvwxyz");
    //     WordJumble wordJumble = new WordJumble(fwl, rand, 2, 10, 3);

    //     System.out.println("TEST 1");
    //     System.out.println("YOU will need to manually verify that the alphabet seems scrambled.");
    //     String input = "abcdefghijklmnopqrstuvwxyz\n";
    //     Scanner scan = new Scanner(input);
    //     wordJumble.play(scan);

    //     // re-using the same wordJumble
    //     System.out.println("TEST 1 PHASE 2");
    //     System.out.println("you will need to manual verify that the alphabet is scrambled, and scrambled differently than in phase1.");
    //     input = "apple\npear\nbanana\n";
    //     scan = new Scanner(input);
    //     wordJumble.play(scan);
    // }
    //  public static void main(String[] args) {
    //     // testing RPS in an automated way is quite hard.
    //     // there's no good way to fully automatically test it.
    //     // therefore this file (and the autograder question based on it) will require manual verification.

    //     System.out.println("TEST 1");
    //     System.out.println("manually verify that ai moves look random, and that win/ lose looks right");
    //     RPS rps = new RPS(new Random(0), 10, 10);
    //     String input = "";
    //     for (int i = 0; i < 1000; i++) {
    //         input += "rock\npaper\nscissors\nspock\n";
    //     }
    //     rps.play(new Scanner(input));
    // }
}