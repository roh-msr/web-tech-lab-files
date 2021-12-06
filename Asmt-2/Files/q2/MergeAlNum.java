import java.util.*;
import java.io.*;

class UnknownCharacterException extends Exception  
{  
    public UnknownCharacterException (String str)  
    {
        super(str);  
    }  
}

class FileOp {
    private File f1;

    public void createNewFile(String fileName) {
        try {
            f1 = new File(fileName);

            if (f1.createNewFile()) {
                System.out.println("File " + f1.getName() + " created successfully.");
            } else {
                System.out.println("File already exists in the directory.");
            }
        } catch (IOException e) {
            System.out.println("An unexpected error has occurred.");
            e.printStackTrace();
        }
    }

    public String readFromFile() {
        String s = "";
        try {  
            FileReader fr = new FileReader(f1);
            BufferedReader br = new BufferedReader(fr);   

            int c = 0;             
            while((c = br.read()) != -1)         //Read char by Char
            {
                char symbol = (char) c;

                if(!Character.isLetter(symbol) 
                && !Character.isDigit(symbol) 
                && !Character.isWhitespace(symbol)){
                    throw new UnknownCharacterException("Invalid character found!!");
                }
                else{
                    s += symbol;
                    continue;
                }                
            }

            return s;
        }
        catch(UnknownCharacterException e){
            System.out.println("Invalid character found!!");  
            e.printStackTrace();
        }
        catch (FileNotFoundException exception) {  
            System.out.println("Unexcpected error occurred!");  
            exception.printStackTrace();  
        }
        catch(Exception e){
            System.out.println("Unexcpected error occurred!");  
            e.printStackTrace();
        } 
        
        return s;
    }

    public void writeToFile(String content) {
        try {
            FileWriter fwrite = new FileWriter(f1.getName());
            fwrite.write(content);
            fwrite.close();

            System.out.println("Content successfully written to the file.");
        } catch (FileNotFoundException e) {  
            System.out.println("File Not found!");  
            e.printStackTrace();  
        } catch (IOException e) {
            System.out.println("Unexpected error has occurred");
            e.printStackTrace();
        }
    }

    public static void mergeFiles(FileOp dest, FileOp source1, FileOp source2){
        String str1 = source1.readFromFile();
        String str2 = source2.readFromFile();
        String res = "";

        int c1 = 0;
        int c2 = 0;

        while(c1 < str1.length() && c2 < str2.length()){
            res += str1.charAt(c1++);
            res += str2.charAt(c2++);
        }
        
        while(c1 < str1.length()){
            res += str1.charAt(c1++);
        }
        
        while(c2 < str2.length()){
            res += str2.charAt(c2++);
        }

        dest.writeToFile(res);
    }

    public void deleteFile(){
        if (f1.delete()) {
            System.out.println("File " + f1.getName() + " is deleted successfully.");
        } else {
            System.out.println("File does not exist in the directory.");
        }
    }
}

public class MergeAlNum {
    public static void main(String args[]) {
        FileOp fn = new FileOp();
        fn.createNewFile("numbers.txt");
        fn.writeToFile("12345 6789");
        String s = fn.readFromFile();
        System.out.println("numbers.txt : " + s);
        System.out.println();
        
        FileOp fa = new FileOp();
        fa.createNewFile("alphabets.txt");
        fa.writeToFile("abcde efghijkl");
        s = fa.readFromFile();
        System.out.println("alphabets.txt : " + s);
        System.out.println();
        
        FileOp dest = new FileOp();
        dest.createNewFile("mergedText.txt");
        FileOp.mergeFiles(dest, fn, fa);
        System.out.println("mergedText.txt : " + dest.readFromFile());
        System.out.println();
    }
}
