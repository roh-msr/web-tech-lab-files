import java.util.Scanner;

public class HelloWorld {
    public static void main(String[] args) {
        System.out.println("Hello World!!");

        Scanner reader = new Scanner(System.in);

        int num = reader.nextInt();

        System.out.print("You entered: " + num);
    }
}