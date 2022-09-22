import java.util.Random;
import java.util.Scanner;

public class RPS extends Game
{
  protected int wins;
  protected int wins1;
  protected String ai;
  public String getName()
  {
    return"RPS";
  }
  protected String prepToPlay()
  {
    round=1;
    return("Enter rock , paper , or scissors. Beat me "+wins1+" times before I win "+wins1+"times!");
  }
  protected boolean isOver()
  {
    if (rounds<round)
    {
      return true;
    }
    if (wins==wins1)
    {
      return true;
    }
    if (this.guess.equals("quit"))
    {
      return true;
    }
    return false;
 
  }
  protected boolean isValid(String move)
  {
    
     if(this.guess.equals("quit"))
    {
      return true;
    }
    if ((!this.guess.equals("rock"))&&!this.guess.equals(("paper"))&&(!this.guess.equals(("scissors"))))
    {
      return false;
    }
    return true;
  }
  public RPS(Random rng,int wins,int rounds)
  {
    this.rounds=rounds;
    this.wins1 = wins;
    this.random=rng;
  }
  protected String processMove(String move)
  {
    
    this.guess=move;
    if (this.guess.equals("quit"))
    {
      return ("bye");
    }
    int x=random.nextInt(3);
    if(x==0)
    {
      this.ai="scissors";
    }
    if(x==2)
    {
      this.ai="paper";
    }
    if(x==1)
    {
      this.ai="rock";
    }
    this.guess=move;
    if(this.isValid(move))
    {
    if (move.equals("rock")&&ai.equals("scissors"))
    {
      this.wins+=1;
      return"rock vs scissors "+"you win"+"\n";
    }
    else if(move.equals("paper")&&ai.equals("rock"))
    {
      this.wins+=1;
      return"paper vs rock"+" you win"+"\n";
    }
    else if(move.equals("scissors")&&ai.equals("paper"+"\n"))
    {
          this.wins+=1;
          return"scissors vs paper"+"+ you win"+"\n";
    }
    else if(move.equals(ai))
    {
      return move+" vs "+ai+" we tie"+"\n";
    }
    else
    {
      round+=1;
      return move+" vs "+ai+"you lose"+"\n";
    }
    }
    else
    {
         return("Invalid Move! try again> ");
    }
  }
  protected String finalMessage()
  {
    if(wins==wins1)
    {
      return"You win the set"+"\n";
    }
    return"You lose the set"+"\n";
  }
}