import java.util.Scanner;

public class reverseNum {
    public static int revNum(int n){
        int rn = 0;

        while(n > 0){
            int digit = n % 10;
            n /= 10;
            rn = rn * 10 + digit;
        }

        return rn;
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Enter a positive int: ");
        int n = sc.nextInt();

        if(n < 0){
            System.out.print("Please enter a positive number !");
        }
        else{
            System.out.print("Reversed Num = " + revNum(n));
        }

    }
}