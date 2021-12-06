class PrimeClass {
    public static boolean isPrime(int n){
        if(n < 2){
            return false;
        }

        int ub = (int)Math.sqrt(n);

        for (int i = 2; i <= ub; ++i) {
            if (n % i == 0) {
                return false;
            }
        }

        return true;
    }

    public static void printPrimesInRange(int start, int end){
       System.out.printf("Let's get prime numbers from %d to %d !\n", start, end);

        for(int i = start; i <= end; ++i){
            if(isPrime(i)){
                System.out.printf("%d ", i);
            }
        }
    }
}

public class GetPrimes{
    public static void main(String[] args){
        PrimeClass.printPrimesInRange(1, 10000);
    }
}