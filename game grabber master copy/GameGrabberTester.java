import java.util.Scanner;

public class GameGrabberTester {
    // public static void main(String[] args) {
    //     // TEST 1: this expects exact matches.


    //     String input = "-10\n2\nvalid\nwin\n1\nquit\n7\n3\n";
    //     // 10
    //     // 2
    //     // valid
    //     // win
    //     // 1
    //     // quit
    //     // 7
    //     // 3

    //     System.out.println("Test 1");
    //     // setting this one aside so I can check if it's been played
    //     DummyGame special = new DummyGame("Special");

    //     System.out.println("special.isOver: "+special.isOver());


    //     Game[] games = new Game[]{new DummyGame("apples"),
    //                        new DummyGame("Bananas"),
    //                        special};
    //     Scanner scan = new Scanner(input);
    //     GameGrabber gg = new GameGrabber(games, scan);
    //     gg.doMenu();

    //     System.out.println("special.isOver: "+special.isOver());

    //     System.out.println("Test 2");
    //     System.out.println("This requires manual validation and input");
    //     System.out.println("Check for a well-formatted menu with at least 4 options, one for each game.");
    //     // in case you didn't know -- you can call main directly. While it is a _special_ static method,
    //     // it is, ultimately, just a static method
    //     GameGrabber.main(new String[0]);
    // }

}

/*
Test 1
special.isOver: false
0) apples
1) Bananas
2) Special
3) Quit
Pick a game (0-3) Pick a game (0-3) Dummy Game is for dummies.
Enter Your Move or 'quit' to quit> good move
Enter Your Move or 'quit' to quit> good move
GoodBye!
0) apples
1) Bananas
2) Special
3) Quit
Pick a game (0-3) Dummy Game is for dummies.
Enter Your Move or 'quit' to quit> GoodBye!
0) apples
1) Bananas
2) Special
3) Quit
Pick a game (0-3) Pick a game (0-3) goodbye
special.isOver: true
 */