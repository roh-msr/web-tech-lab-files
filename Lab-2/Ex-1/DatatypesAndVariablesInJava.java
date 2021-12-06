public class DatatypesAndVariablesInJava {
    public static void main(String[] args) {
        Boolean isHuman = false;
        char modelName = 'Q';
        byte bitNum = 1;
        short rollNum = 5000;
        int batchNum = 1090990;
        long fullNum = 150001090990L;
        float weightInKg = 234.5f;
        double powerSupply = 12.3;

        System.out.println("A program to demonstrate different datatypes and variables!!\n");
        System.out.println("Boolean isHuman = " + isHuman);
        System.out.println("char modelName = " + modelName);
        System.out.println("byte bitNum = " + bitNum);
        System.out.println("short rollNum = " + rollNum);
        System.out.println("int batchNum = " + batchNum);
        System.out.println("long fullNum = " + fullNum);
        System.out.println("float weightInKg = " + weightInKg);
        System.out.println("double powerSupply = " + powerSupply);

        System.out.println("Let's play with some concepts in variables!!\n");
        System.out.println("Typecasting float to int -> weightInKg = " + (int)weightInKg);
        System.out.println("Widening byte to int -> bitNum = " + (int)bitNum);
        System.out.println("Overflow when cast from int to byte -> batchNum = " + (byte)batchNum);
    }
}
