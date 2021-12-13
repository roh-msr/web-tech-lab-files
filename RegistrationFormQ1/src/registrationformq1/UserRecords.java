package registrationformq1;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.List;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTable;

/**
 *
 * @author Rohith M S R
 */
public class UserRecords {    
    public JFrame f; 
    public boolean isFrameOpen = false;
    private final String[] columns;
    private final String[][] records;
    
    public void initUI(){
        isFrameOpen = true;
        JTable jt = new JTable(records, columns);
        jt.setBounds(100, 100, 400, 400);  
        
        JScrollPane sp = new JScrollPane(jt);
        
        f.add(sp);
        f.setSize(500, 500);
        f.setVisible(true);
        
        f.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosed(WindowEvent e) {
               isFrameOpen = false;
            }
            
            @Override
            public void windowClosing(WindowEvent e) {
               isFrameOpen = false;
            }
        });
    }
    
    UserRecords(List<String[]> data, List<String> head){    
        f = new JFrame();
        columns = new String[head.size()];
        records = new String[data.size()][];
        
        for (int i = 0; i < head.size(); i++) {
            columns[i] = head.get(i);
        }
        
        for (int i = 0; i < data.size(); i++) {
            String[] row = data.get(i);
            records[i] = row;
        }  
    }     
}
