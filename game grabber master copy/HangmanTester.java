// import java.util.Scanner;

// public class HangmanTester {
//     public static void main(String[] args) {

//         FakeWordList fwl = new FakeWordList("aardvark");
//         Hangman hw = new Hangman(fwl, 4, 9, 10);

//         System.out.println("TEST 1");
//         String input = "r\nd\na\nq\nk\na\naardvark\nv\n";
//         hw.play(new Scanner(input));

//         System.out.println("TEST 1 part 2");
//         input = "";
//         for (int i = 0; i < 10; i++) {
//             input += "a\n";
//         }
//         hw.play(new Scanner(input));
//     }
// }
/*
TEST 1
getWord 4 to 9
I've picked a 8 letter word. Guess letters you think are in the word. You get 10 guesses.
Enter Your Move or 'quit' to quit> __r___r_
Enter Your Move or 'quit' to quit> __rd__r_
Enter Your Move or 'quit' to quit> aard_ar_
Enter Your Move or 'quit' to quit> aard_ar_
Enter Your Move or 'quit' to quit> aard_ark
Enter Your Move or 'quit' to quit> aard_ark
Enter Your Move or 'quit' to quit> Invalid Move! try again> aardvark
The word was: aardvark
TEST 1 part 2
getWord 4 to 9
I've picked a 8 letter word. Guess letters you think are in the word. You get 10 guesses.
Enter Your Move or 'quit' to quit> aa___a__
Enter Your Move or 'quit' to quit> aa___a__
Enter Your Move or 'quit' to quit> aa___a__
Enter Your Move or 'quit' to quit> aa___a__
Enter Your Move or 'quit' to quit> aa___a__
Enter Your Move or 'quit' to quit> aa___a__
Enter Your Move or 'quit' to quit> aa___a__
Enter Your Move or 'quit' to quit> aa___a__
Enter Your Move or 'quit' to quit> aa___a__
Enter Your Move or 'quit' to quit> aa___a__
The word was: aardvark
 */