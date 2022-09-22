import java.util.Random;
import java.util.Scanner;
public class NumberGuesser extends Game
{
  private int secret;
  public String getName()
  {
    return"NumberGuesser";
  }
  protected void setguess(String x)
  {
    guess=x;
  }
  protected boolean isValid(String move)
  {
     if(this.guess.equals("quit"))
    {
      return true;
    }
      for (int i = 0;i<guess.length();i++)
    {

      if (guess.charAt(i) != '1'&& guess.charAt(i) != '2'&&guess.charAt(i) !='3'&& guess.charAt(i) != '4'&& guess.charAt(i) != '5'&& guess.charAt(i) != '6'&&guess.charAt(i) != '7'&&guess.charAt(i) != '8'&& guess.charAt(i) !='9'&& guess.charAt(i) !='0' 
      )
      {
        return false;
      }
    }
    return true;
  }
  //   protected void play(Scanner user)
  // {
  //   System.out.println(this.prepToPlay());
  //   while(user.hasNext())
  //   {
  //   System.out.print("Enter Your Move or 'quit' to quit ");
  //   String x;
  //   x=user.next();
  //   if(x!="quit")
  //     {
  //     System.out.print(this.processMove(x));
  //     while (!this.isValid())
  //     {
  //       x=user.next();
  //       System.out.print(this.processMove(x));
  //     }
  //     if (this.isOver())
  //     {
  //       System.out.println(this.finalMessage());
  //       break;
  //     }
  //     }
    
  //   else
  //   {
  //     System.out.println(this.finalMessage());
  //   }

  //   }
  // }
  protected int getsecret()
  {
    return secret;
  }
  private int maxsecret;

  public NumberGuesser(Random rng,int maxnumber,int maxguesses)
  {
    random = rng;
    rounds= maxguesses;
    maxsecret= maxnumber;


  }
  protected boolean isOver()
  {
    if (this.guess.equals("quit"))
    {
      return true;
    }
     if ((Integer.parseInt(guess)==(this.getsecret())))
        {
          return true;
        }
    if (rounds<round)
    {
      return true;
    }
    
    return false;

  }
  protected String finalMessage()
  {
    return "The number was: "+this.getsecret()+"\n";

  }
  protected String processMove(String move)
  {
    this.setguess(move);

    if (this.isValid(move)==true)
    {
      if (this.guess.equals("quit"))
    {
      return ("bye");
    }
       int x=Integer.parseInt(move);
        

       round+=1;
        if (Integer.parseInt(move)>this.getsecret())
        {
          return("Too High"+"\n");
        }
        if (Integer.parseInt(move)<this.getsecret())
        {
          return("Too Low"+"\n");
        }
        if ((Integer.parseInt(move)==(this.getsecret())))
        {

          return("That's it!"+"\n"+this.finalMessage());
  
        }
      }
    
      return("Invalid Move! try again> ");
    
  }

  protected String prepToPlay()
  {
    secret=random.nextInt(maxsecret)+1;
    round=1;
    return"I've picked a number 1 to " +maxsecret+". You get " + rounds+" guesses to guess it";
  }

}