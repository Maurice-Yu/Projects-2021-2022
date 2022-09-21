import java.util.Random;
import java.util.Scanner;

public class WordJumbleTester {
    public static void main(String[] args) {
        Random rand = new Random();
        FakeWordList fwl = new FakeWordList("abcdefghijklmnopqrstuvwxyz");
        WordJumble wordJumble = new WordJumble(fwl, rand, 2, 10, 3);

        System.out.println("TEST 1");
        System.out.println("YOU will need to manually verify that the alphabet seems scrambled.");
        String input = "abcdefghijklmnopqrstuvwxyz\n";
        Scanner scan = new Scanner(input);
        wordJumble.play(scan);

        // re-using the same wordJumble
        System.out.println("TEST 1 PHASE 2");
        System.out.println("you will need to manual verify that the alphabet is scrambled, and scrambled differently than in phase1.");
        input = "apple\npear\nbanana\n";
        scan = new Scanner(input);
        wordJumble.play(scan);
    }
}
/*
TEST 1
YOU will need to manually verify that the alphabet seems scrambled.
getWord 2 to 10
The following is a jumbled up word: ckxsfignlrvubzhajmwyqtdpeo You get 3 guesses to guess it
Enter Your Move or 'quit' to quit> The word was abcdefghijklmnopqrstuvwxyz
TEST 1 PHASE 2
you will need to manual verify that the alphabet is scrambled, and scrambled differently than in phase1.
getWord 2 to 10
The following is a jumbled up word: zethcmsvjrfoyxkpbuawldignq You get 3 guesses to guess it
Enter Your Move or 'quit' to quit> That's not it
Enter Your Move or 'quit' to quit> That's not it
Enter Your Move or 'quit' to quit> That's not it
The word was abcdefghijklmnopqrstuvwxyz
 */
