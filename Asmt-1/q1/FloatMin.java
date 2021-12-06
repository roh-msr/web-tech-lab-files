import java.util.Scanner;

public class FloatMin {
    private static float minimum3(float x, float y, float z){
        return Math.min(x, Math.min(y, z));
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        float f1, f2, f3;

        System.out.print("Enter a floating point number 1 : ");
        f1 = sc.nextFloat();
        System.out.print("Enter a floating point number 2 : ");
        f2 = sc.nextFloat();
        System.out.print("Enter a floating point number 3 : ");
        f3 = sc.nextFloat();

        System.out.print("Minimum of three floating point numbers : " + minimum3(f1, f2, f3));
    }
}