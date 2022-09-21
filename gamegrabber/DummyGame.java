import java.util.Scanner;

/**
 * This class is written in a weird sort of way. A lot of the "weirdness" is the
 * fact that this is designed for TESTING not for actually playing with.
 * I WOULD NOT recommend using this as a template for designing your own games off of.
 */
public class DummyGame extends Game {
    private boolean isOver;
    private String dummy_name;

    public DummyGame() {
        dummy_name = "dummy game";
        isOver = false;
    }

    public DummyGame(String dummy_name) {
        this.dummy_name = dummy_name;
        isOver = false;
    }

    // @Override
    public boolean isOver() {
        return isOver;
    }

    // @Override
    public boolean isValid(String move) {
        return !(move.equals("invalid"));
    }

    public static final String PROCESS_STRING = "good move";
    // @Override
    public String processMove(String move) {
        isOver = "win".equals(move);
        if ("skip".equals(move)) {
            return null;
        } else {
            return PROCESS_STRING;
        }
    }

    public static final String FINAL_STRING = "GoodBye!";
    // @Override
    public String finalMessage() {
        return FINAL_STRING;
    }

    public static final String PREP_STRING = "Dummy Game is for dummies.";
    // @Override
    public String prepToPlay() {
        isOver = false;
        return PREP_STRING;
    }

    // @Override
    public String getName() {
        return dummy_name;
    }

    public static void main(String[] args) {
        DummyGame dg = new DummyGame();
        dg.play(new Scanner(System.in));
    }
}
