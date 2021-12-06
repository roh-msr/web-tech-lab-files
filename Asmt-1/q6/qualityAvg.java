import java.util.Scanner;
public class qualityAvg {
    public static int qualityPoints(double n){
        if(n >= 90 && n <= 100){
            return 4;
        }
        else if(n >= 80 && n <= 89){
            return 3;
        }
        else if(n >= 70 && n <= 79){
            return 2;
        }
        else if(n >= 60 && n <= 60){
            return 1;
        }
        else{
            return 0;
        }
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Enter number of subjects: ");
        int n = sc.nextInt();

        if(n < 0){
            System.out.print("Please enter a valid number!");
        }
        else{
            int sum = 0;
            for(int i = 0; i < n; i++){
                System.out.printf("Enter subject %d marks: ", i + 1);
                sum += sc.nextInt();
            }

            double avg = sum / (n * 1.0);
            System.out.print("Points = " + qualityPoints(avg));
        }
    }
}