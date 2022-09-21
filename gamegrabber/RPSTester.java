import java.util.Random;
import java.util.Scanner;

public class RPSTester {
    public static void main(String[] args) {
        // testing RPS in an automated way is quite hard.
        // there's no good way to fully automatically test it.
        // therefore this file (and the autograder question based on it) will require manual verification.

        System.out.println("TEST 1");
        System.out.println("manually verify that ai moves look random, and that win/ lose looks right");
        RPS rps = new RPS(new Random(0), 10, 10);
        String input = "";
        for (int i = 0; i < 1000; i++) {
            input += "rock\npaper\nscissors\nspock\n";
        }
        rps.play(new Scanner(input));
    }
}

/*
This is what one random run of my games looked like.
Yours should look kind of like this, but not exactly the same (as the random moves may be different)

manually verify that ai moves look random, and that win/ lose looks right
Enter rock, paper, or scissors. Beat me 10 times before I win 10 times!
Enter Your Move or 'quit' to quit> rock vs. rock We Tie
Enter Your Move or 'quit' to quit> paper vs. paper We Tie
Enter Your Move or 'quit' to quit> paper vs. scissors you Win
Enter Your Move or 'quit' to quit> Invalid Move! try again> scissors vs. rock you Win
Enter Your Move or 'quit' to quit> scissors vs. paper you lose
Enter Your Move or 'quit' to quit> scissors vs. scissors We Tie
Enter Your Move or 'quit' to quit> Invalid Move! try again> scissors vs. rock you Win
Enter Your Move or 'quit' to quit> rock vs. paper you Win
Enter Your Move or 'quit' to quit> rock vs. scissors you lose
Enter Your Move or 'quit' to quit> Invalid Move! try again> scissors vs. rock you Win
Enter Your Move or 'quit' to quit> scissors vs. paper you lose
Enter Your Move or 'quit' to quit> scissors vs. scissors We Tie
Enter Your Move or 'quit' to quit> Invalid Move! try again> scissors vs. rock you Win
Enter Your Move or 'quit' to quit> paper vs. paper We Tie
Enter Your Move or 'quit' to quit> scissors vs. scissors We Tie
Enter Your Move or 'quit' to quit> Invalid Move! try again> scissors vs. rock you Win
Enter Your Move or 'quit' to quit> paper vs. paper We Tie
Enter Your Move or 'quit' to quit> rock vs. scissors you lose
Enter Your Move or 'quit' to quit> Invalid Move! try again> scissors vs. rock you Win
Enter Your Move or 'quit' to quit> scissors vs. paper you lose
Enter Your Move or 'quit' to quit> paper vs. scissors you Win
Enter Your Move or 'quit' to quit> Invalid Move! try again> rock vs. rock We Tie
Enter Your Move or 'quit' to quit> scissors vs. paper you lose
Enter Your Move or 'quit' to quit> scissors vs. scissors We Tie
Enter Your Move or 'quit' to quit> Invalid Move! try again> scissors vs. rock you Win
You win the set
 */