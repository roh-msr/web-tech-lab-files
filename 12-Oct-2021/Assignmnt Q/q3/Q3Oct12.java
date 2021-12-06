public class Q3Oct12 {
    final static int MAX_NUMBERS = 10;

    public static void main(String[] args) {
        // shared object
        Q3Oct12 obj = new Q3Oct12();
        // Creating 3 threads
        Thread t1 = new Thread(new NumberRunnable(obj, 0), "T1");
        Thread t2 = new Thread(new NumberRunnable(obj, 1), "T2");
        Thread t3 = new Thread(new NumberRunnable(obj, 2), "T3");
        t1.start();
        t2.start();
        t3.start();
    }
}

 class NumberRunnable implements static Runnable {
    Q3Oct12 obj;
    int threadNumber;
    static volatile int number = 0;

    NumberRunnable(Q3Oct12 obj, int result) {
        this.obj = obj;
        this.threadNumber = result;
    }

    // @Override
    // public void run() {
    //     synchronized (obj) {
    //         while (number < Q3Oct12.MAX_NUMBERS - 2) {
    //             while (number % 3 != threadNumber) {
    //                 try {
    //                     Thread.sleep(600);
    //                     obj.wait();
    //                 } catch (InterruptedException e) {
    //                     e.printStackTrace();
    //                 }
    //             }
    //             System.out.println(Thread.currentThread().getName() + " - " + ++number);
    //             obj.notifyAll();
    //         }
    //     }
    // }
}