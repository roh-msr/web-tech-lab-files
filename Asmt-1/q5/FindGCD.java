import java.util.Scanner;

public class FindGCD {
    public static int gcd(int n1, int n2){
        int num = Math.min(n1, n2);

        while(num > 1){
            if(n1 % num == 0 && n2 % num == 0){
                return num;
            }
            num--;
        }

        return 1;
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Enter num 1: ");
        int n1 = sc.nextInt();
        System.out.print("Enter num 2: ");
        int n2 = sc.nextInt();

        System.out.printf("GCD of %d and %d = %d\n", n1, n2, gcd(n1, n2));
    }
}