import java.util.Scanner;
import java.util.Random;
public class GameGrabber
{
  Game[] Games;
  Scanner user;
  int game;
 public GameGrabber(Game[] Games,Scanner user)
  {
    this.Games=Games;
    this.user=user;
  }
  public void doMenu()
  {
    for(int i=0;i<Games.length;i++)
    {
      System.out.println(i+") "+Games[i].getName());
    }
    int x=-1;
    System.out.println(Games.length+") Quit");
    boolean ended=false;
    while(!ended)
    {
    while (x>Games.length||x<0)
    {
      
      System.out.println("Pick a game (0-"+Games.length+") ");
      x=user.nextInt();
    }
    if (x==Games.length)
    {
      ended=true;
      System.out.println("goodbye");
    }
    else
    {
      Games[x].play(user);
       }
  
  }
  }
  public static void main(String[] args)
  {
    Scanner x= new Scanner(System.in);
    Random y = new Random();
    WordsList words= new WordsList(y);
    Game[] games = new Game[4];
    {
      games[0]=new Hangman(words,2,5,5);
      games[1]=new NumberGuesser(y,5,5);
      games[2]= new RPS(y,5,5);
      games[3]= new WordJumble(words,y,1,5,5);
    }
    GameGrabber game=new GameGrabber(games,x);
    game.doMenu();
  }
  
}