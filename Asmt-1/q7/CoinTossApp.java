import java.util.Scanner;
import java.util.Random;

enum Coin { 
    HEADS, TAILS, INVALID;

    public static Coin getSide(int i){
        if(i == 0){
            return Coin.HEADS;
        }
        if(i == 1){
            return Coin.TAILS;
        }
        return Coin.INVALID;
    } 
};

class CoinToss {
    private int h = 0;
    private int t = 0;
    private static Random gen = new Random();

    public void display() {
        System.out.printf("Heads = %d, Tails = %d\n", h, t);
    }

    public void flip() {
        int rand = gen.nextInt(2);

        if(rand == 0){
            h++;
        }
        else if(rand == 1){
            t++;
        }

        System.out.println("Side = " + Coin.getSide(rand));
    }
}

public class CoinTossApp {
    public static void main(String[] args){
        CoinToss app1 = new CoinToss();
        Scanner sc = new Scanner(System.in);
        boolean flag = true;

        do{
            System.out.println("Press 1 to Toss Coin");
            System.out.println("Press 2 for results");
            System.out.println("Press 0 to exit!!");
            System.out.print("Enter an option: ");
            int opt = sc.nextInt();

            switch(opt){
                case 1:
                    app1.flip();
                    break;
                case 2:
                    app1.display();
                    break;
                case 0:
                    flag = false;
                    break;
                default:
                    System.out.println("Enter a valid option!");
            }
        }
        while(flag);
    }
}