import java.util.*;

public class FirstName {
    public static void main(String[] args) {
        int opt;
        String s;
        Scanner in = new Scanner(System.in);
        Scanner string_in = new Scanner(System.in);
        Set<String> names = new HashSet<String>();

        while(true){
            System.out.print("Enter 1 for insert, 2 for search, 0 to exit!! : ");
            opt = in.nextInt();

            switch(opt){
                case 1:
                    System.out.print("Enter the first name to insert: ");
                    s = string_in.nextLine();
                    
                    names.add(s);
                    
                    break;
                case 2:
                    System.out.print("Enter the first name to search: ");
                    s = string_in.nextLine();

                    if(names.contains(s)){
                        System.out.println("Name found!!");
                    }
                    else{
                        System.out.println("Name NOT FOUND!!");
                    }

                    break;
                case 0:
                    System.out.println("EXITING....");
                    
                    break;
                default:
                    System.out.println("Enter a valid option!!");
            }

            if(opt == 0){
                break;
            }
        }
    }
}
