public class PerfectNum {
    public static boolean isPerfect(int n, int display){
        int sum = 0;
        boolean[] factors = new boolean[n + 1];

        for (int i = 1; i < n; ++i) {
            if (n % i == 0) {
                sum += i;
                factors[i] = true;
            }
        }

        if(sum == n){
            if(display == 1){
                System.out.print("Factors of " + n + " = ");
                for(int i = 1; i < n; ++i){
                    if(factors[i]){
                        System.out.printf("%d ", i);
                    }
                }
                System.out.println();
            }

            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        System.out.println("isPerfect(6) = " + isPerfect(6, 1));
        System.out.println("isPerfect(8) = " + isPerfect(8, 1));
        System.out.println("isPerfect(100000) = " + isPerfect(100000, 1));

        for(int i = 1; i < 1000; ++i){
            if(isPerfect(i, 1)){
                System.out.printf("Num = %d\n", i);
            }
        }
    }
}