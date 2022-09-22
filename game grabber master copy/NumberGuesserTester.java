import java.util.Scanner;

public class NumberGuesserTester {
    public static void main(String[] args) {
        System.out.println("Test 1");

        FakeRandom fr = new FakeRandom(49); // should mean a random number of 50.
        NumberGuesser ng = new NumberGuesser(fr, 72, 5);

        String input = "apple\n49\n51\n50\n";
        ng.play(new Scanner(input));

        System.out.println("TEST 1 PHASE 2");
        input = "apple\n1\n2\ndog\n4\npear\n3\n5\n";
        ng.play(new Scanner(input));

    }
}

/*
Test 1
nextInt: 72
I've picked a number 1 to 72. You get 5 guesses to guess it
Enter Your Move or 'quit' to quit> Invalid Move! try again> Too Low
Enter Your Move or 'quit' to quit> Too High
Enter Your Move or 'quit' to quit> That's it!
The number was: 50
TEST 1 PHASE 2
nextInt: 72
I've picked a number 1 to 72. You get 5 guesses to guess it
Enter Your Move or 'quit' to quit> Invalid Move! try again> Too Low
Enter Your Move or 'quit' to quit> Too Low
Enter Your Move or 'quit' to quit> Invalid Move! try again> Too Low
Enter Your Move or 'quit' to quit> Invalid Move! try again> Too Low
Enter Your Move or 'quit' to quit> Too Low
The number was: 50
 */
