import javax.swing.*;

public class Q5Oct12 extends JFrame {
    JFrame f;

    Q5Oct12() {
        f = new JFrame("Select your birth month!!");

        String country[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

        JComboBox cb = new JComboBox(country);
        cb.setBounds(50, 50, 90, 20);

        f.add(cb);
        f.setLayout(null);
        f.setSize(400, 500);
        f.setVisible(true); 
        f.setLocationRelativeTo(null);
        f.setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    public static void main(String[] args) {
        new Q5Oct12();
    }
}