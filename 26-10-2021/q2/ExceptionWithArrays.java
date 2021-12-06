
class MyArray {
    private int[] arr;

    public MyArray(int... numbers) {
        arr = new int[10];
        int validcnt = 0;

        try{
            for(int i = 0; i < 10; i++){
                arr[i] = numbers[i];
                validcnt++;
            }
        }
        catch(ArrayIndexOutOfBoundsException e){
            System.err.printf("%s\n", e);
        }
        catch(NumberFormatException e){
            System.err.printf("%s\n", e);
        }
        finally{
            System.out.printf("First %d elements passed set in the array!\n", validcnt);
        }
    }

    public void printArray(){
        int validcnt = 0;

        System.out.print("[");
        try{
            for(int i = 0; i < 10; i++){
                System.out.printf("%d ", arr[i]);
                validcnt++;
            }
        }
        catch(ArrayIndexOutOfBoundsException e){
            System.out.printf("First %d elements are valid in the array!\n", validcnt);
        }
        finally{
            System.out.print("]\n");
        }
    }

    public void setArray(int... numbers){
        int validcnt = 0;

        try{
            for(int i = 0; i < 10; i++){
                arr[i] = numbers[i];
                validcnt++;
            }
        }
        catch(ArrayIndexOutOfBoundsException e){
            System.out.printf("%s\n", e);
        }
        catch(NumberFormatException e){
            System.out.printf("%s\n", e);
        }
        finally{
            System.out.printf("First %d elements passed set in the array!\n", validcnt);
        }
    }
    
    public void setStringToIntValue(String val, int index){
        try{
            arr[index] = Integer.parseInt(val);
            System.out.printf("Index %d value set to %s\n", index, val);
        }
        catch(NumberFormatException e){
            System.out.printf("%s\n", e);
        }
        catch(ArrayIndexOutOfBoundsException e){
            System.out.printf("%s\n", e);
        }
    }
}

public class ExceptionWithArrays {
    public static void main(String[] args) {
        MyArray m1 = new MyArray(1,2,3,4,5);
        m1.printArray();
        System.out.println("");
        
        m1.setArray(1,2,3,4,5,6,7,8,9);
        m1.printArray();
        System.out.println("");
        
        m1.setStringToIntValue("100", 0);
        m1.printArray();
        System.out.println("");

        m1.setStringToIntValue("error", 11);
        m1.printArray();
        System.out.println("");

        m1.setStringToIntValue("23", 11);
        m1.printArray();
        System.out.println("");
        
        m1.setArray(1,2,3,4,5,6,7,8,9,10);
        m1.printArray();
        System.out.println("");
    }
}
