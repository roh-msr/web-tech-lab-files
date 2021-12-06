import java.util.*;

public class DuplicateWordsExtracter { 
    public static void printDuplicateWords(String s){
        Map<String, Integer> map = new HashMap<String, Integer>();
        String[] words = s.replaceAll("[^a-zA-Z ]", "").toLowerCase().split("\\s+");

        System.out.println("Words: " + Arrays.toString(words));

        int count;
        for(String word : words){
            count = map.containsKey(word) ? map.get(word) : 0;
            map.put(word, count + 1); 
        }

        count = 0;
        for(String word : map.keySet()){
            if(map.get(word) > 1){
                count += 1;
            }
        }

        System.out.println("No. of. duplicates: " + count);
    }

    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        String s;

        System.out.print("Enter a sentence!: ");
        s = in.nextLine();

        printDuplicateWords(s);
    }
}
