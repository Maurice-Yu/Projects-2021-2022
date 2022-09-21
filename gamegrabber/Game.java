import java.util.Random;
import java.util.Scanner;
public abstract class Game {
  public Random random;
  protected int rounds;
  protected int round=0;
  protected String guess;
  private String name;
  protected String answer;
  protected abstract String prepToPlay();

  protected abstract boolean isOver();
  protected abstract boolean isValid(String move);

  protected abstract String processMove(String move);
  protected abstract String finalMessage();
  public abstract String getName();
  public void play(Scanner user)
  { 
    System.out.println(this.prepToPlay());
    while(user.hasNext())
    {
    System.out.print("Enter Your Move or 'quit' to quit> ");
    String x;
    x=user.next();
    if(x!="quit")
      {
      System.out.print(this.processMove(x));
      while (!this.isValid(x))
      {
        x=user.next();
        System.out.print(this.processMove(x));
      }
      if (this.isOver())
      {
        System.out.println(this.finalMessage());
        break;
      }
      }
    
    else
    {
      System.out.println(this.finalMessage());
    }

    }
  }

}