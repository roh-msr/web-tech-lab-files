import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Q1Oct12 extends JFrame implements ActionListener {
    JButton b1, b2, b3;
    JFrame frame = new JFrame();
    JLabel l1 = new JLabel();
    JPanel panel = new JPanel();
    int count = 0;

    public Q1Oct12() {
        initUI();
    }

    private void initUI() {
        panel.setLayout(new FlowLayout(FlowLayout.CENTER));

        b1 = new JButton("Increment");
        b1.setFocusable(false);
        b1.addActionListener(this);
        b1.setPreferredSize(new Dimension(200, 50));
        
        b2 = new JButton("Decrement");
        b2.setFocusable(false);
        b2.addActionListener(this);
        b2.setPreferredSize(new Dimension(200, 50));
        
        b3 = new JButton("Reset");
        b3.setFocusable(false);
        b3.addActionListener(this);
        b3.setPreferredSize(new Dimension(200, 50));
        
        panel.add(b1);
        panel.add(b2);
        panel.add(b3);
        
        l1.setVisible(true);
        l1.setPreferredSize(new Dimension(200, 50));
        l1.setVerticalAlignment(JLabel.TOP);
		l1.setHorizontalAlignment(JLabel.CENTER);
        l1.setFont(new Font("Times New Roman", Font.BOLD, 24));

        panel.add(l1);

        frame.getContentPane().add(panel);
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.setSize(new Dimension(420, 250));
        // frame.pack();

        frame.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
		if(e.getSource() == b1) {
            ++count;
            l1.setText(Integer.toString(count));
		}	
        else if(e.getSource() == b2) {
            --count;
            l1.setText(Integer.toString(count));
        }
        else{
            count = 0;
            l1.setText(Integer.toString(count));
        }
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            var ex = new Q1Oct12();
            ex.setVisible(true);
        });
    }
}
