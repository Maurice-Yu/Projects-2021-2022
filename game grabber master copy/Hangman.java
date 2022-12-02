import java.util.Random;
import java.util.Scanner;
public class Hangman extends Game
{
  protected String word;
  protected String currentbord="";
  protected int min;
  protected int max;
  protected WordsList words;
  public String getName()
  {
    return"Hangman";
  }
  protected String prepToPlay()
  {

    answer=words.getWord(min,max);
    round=1;
    currentbord="";
    
    for(int i = 0;i<answer.length();i++)
    {
      currentbord+="_";
    }
    round = 1;
    return("I've picked a "+answer.length()+" letter word. Guess letters you think are in the word. You get "+rounds+" guesses.");
  }
   protected boolean isOver()
  {
    if (this.guess.equals("quit"))
    {
      return true;
    }
       if(currentbord.equals(answer))
        {

          return true;
        }
    if (rounds<round)
    {
      return true;
    }
    return false;

  }
  public Hangman(WordsList words,int min, int max, int maxguess)
  {
    this.words = words;
    this.min = min;
    this.max = max;
    this.rounds = maxguess;
  }
  
  protected boolean isValid(String move)
  {
    if(this.guess.equals("quit"))
    {
      return true;
    }
    if(this.guess.length()>1)
    {
      return false;
    }
     for (int i = 0;i<guess.length();i++)
    {
      if (answer.charAt(i) != 'q'&& answer.charAt(i) != 'w'&& answer.charAt(i) != 'e'&& answer.charAt(i) != 'r'&& answer.charAt(i) != 't'&&answer.charAt(i) != 'y'&& answer.charAt(i) != 'u'&& answer.charAt(i) != 'i'&& answer.charAt(i) != 'o'&& answer.charAt(i) != 'p'&& answer.charAt(i) != 'a'&& answer.charAt(i) != 's'&& answer.charAt(i) != 'd'&& answer.charAt(i) != 'f'&& answer.charAt(i) != 'g'&& answer.charAt(i) != 'h'&& answer.charAt(i) != 'j'&& answer.charAt(i) != 'k'&& answer.charAt(i) != 'l'&& answer.charAt(i) != 'z'&& answer.charAt(i) != 'x'&& answer.charAt(i) != 'c'&& answer.charAt(i) != 'v'&& answer.charAt(i) != 'b'&& answer.charAt(i) != 'n'&& answer.charAt(i) != 'm'
      )
      {
        return false;
      } 
     
  }
   return true;
  }
  protected String processMove(String move)
    {

   round+=1;
  this.guess=move;
      if (this.guess.equals("quit"))
    {
      return ("bye");
    }
      if (this.isValid(move)==true)
    {
    
     
        for(int i=0;i<answer.length();i++)
        {
          if(this.guess.equals(answer.substring(i,i+1)))
          {
            currentbord=currentbord.substring(0,i)+move+currentbord.substring(i+1,currentbord.length());
          }
        }
        if(currentbord.equals(answer))
        {
          round = rounds;
          return(currentbord+"\n"+this.finalMessage());
        }
      return currentbord+"\n";
      }
      return("Invalid Move! try again> ");
    
  }
  protected String finalMessage()
  {
    return("The word was: "+answer+"\n");
  }
  
}