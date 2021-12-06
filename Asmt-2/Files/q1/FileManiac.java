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
    public int digits = 0;
    public int letters = 0;

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

    public void readFromFile() {
        try {  
            FileReader fr = new FileReader(f1);
            BufferedReader br = new BufferedReader(fr);   

            int c = 0;             
            while((c = br.read()) != -1)         //Read char by Char
            {
                char symbol = (char) c;

                if(Character.isLetter(symbol)){
                    letters++;
                }
                else if(Character.isDigit(symbol)){
                    digits++;
                }
                else if(Character.isWhitespace(symbol)){
                    continue;
                }
                else{
                    throw new UnknownCharacterException("Invalid character found!!");
                }                
            }
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

    public void deleteFile(){
        if (f1.delete()) {
            digits = 0;
            letters = 0;
            System.out.println("File " + f1.getName() + " is deleted successfully.");
        } else {
            System.out.println("File does not exist in the directory.");
        }
    }
}

public class FileManiac {
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        String s;

        System.out.print("Enter a sentence!: ");
        s = in.nextLine();

        FileOp fobj = new FileOp();

        fobj.createNewFile("sample.txt");
        fobj.writeToFile(s);
        fobj.readFromFile();

        System.out.printf("Digits : %d , Letters : %d\n", fobj.digits, fobj.letters);
    }
}
