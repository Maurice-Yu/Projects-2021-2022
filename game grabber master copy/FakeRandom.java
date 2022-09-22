import java.util.Random;

public class FakeRandom extends Random {
    private int random;

    public FakeRandom(int random) {
        this.random = random;
    }

    @Override
    public int nextInt(int bound) {
        System.out.println("nextInt: "+bound);
        return random;
    }
}
