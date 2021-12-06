import javax.swing.*;
import java.awt.*;

public class Q4Oct12 extends JFrame {
    public Q4Oct12() {
        JLabel redLabel = new JLabel("Red");
        redLabel.setVisible(true);
        redLabel.setForeground(Color.RED);
        
        JLabel blueLabel = new JLabel("Blue");
        blueLabel.setVisible(true);
        blueLabel.setForeground(Color.BLUE);
        
        JLabel greenLabel = new JLabel("Green");
        greenLabel.setVisible(true);
        greenLabel.setForeground(Color.GREEN);

        add(redLabel);
        add(blueLabel);
        add(greenLabel);

        setLayout(new GridLayout(1, 1, 100, 100));
        setVisible(true);
        setSize(400, 400);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            var ex = new Q4Oct12();
            ex.setVisible(true);
        });
    }
}
