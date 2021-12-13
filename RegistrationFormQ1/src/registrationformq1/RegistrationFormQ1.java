package registrationformq1;

import java.awt.EventQueue;
import javax.swing.JFrame;

/**
 *
 * @author Rohith M S R
 */

public class RegistrationFormQ1 extends JFrame {
    public void initUI(){
        EventQueue.invokeLater(() -> {
            FormPage frame = new FormPage();
            frame.setVisible(true);
        });
    }
    
    public static void main(String[] args) {
        var reg = new RegistrationFormQ1();
        reg.initUI();
    }
}
