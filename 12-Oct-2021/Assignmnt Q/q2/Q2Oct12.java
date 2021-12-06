import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Q2Oct12 extends JFrame {
    final JFrame frame = new JFrame("Radio Buttom Messages!");
    final ButtonGroup group = new ButtonGroup();
    JRadioButton rdbCEG, rdbMIT, rdbACT;

    // implement ItemListener interface
    class MyItemListener implements ItemListener {
        public void itemStateChanged(ItemEvent ev) {
            boolean selected = (ev.getStateChange() == ItemEvent.SELECTED);
            AbstractButton button = (AbstractButton) ev.getItemSelectable();
            String command = button.getActionCommand();

            // build message
            String message = "None";
            if (selected) {
                if (command.equals("CEG")) {
                    message = "CEG has been selected";
                } else if (command.equals("MIT")) {
                    message = "MIT has been selected";
                } else if (command.equals("ACT")) {
                    message = "ACT has been selected";
                }

                // show dialog
                JOptionPane.showMessageDialog(frame, message);
            } 
        }
    }

    private void initUI() {
        rdbCEG = new JRadioButton("CEG");
        rdbCEG.setActionCommand("CEG");

        rdbMIT = new JRadioButton("MIT");
        rdbMIT.setActionCommand("MIT");

        rdbACT = new JRadioButton("ACT");
        rdbACT.setActionCommand("ACT");

        // add event handler
        MyItemListener myItemListener = new MyItemListener();
        rdbCEG.addItemListener(myItemListener);
        rdbMIT.addItemListener(myItemListener);
        rdbACT.addItemListener(myItemListener);
        // add radio buttons to a ButtonGroup
        group.add(rdbCEG);
        group.add(rdbMIT);
        group.add(rdbACT);

        
        Container cont = frame.getContentPane();
        cont.setLayout(new GridLayout(0, 1));
        cont.add(new JLabel("Select your campus: "));
        cont.add(rdbCEG);
        cont.add(rdbMIT);
        cont.add(rdbACT);

        frame.setLayout (new GridLayout(0,1));
        frame.setSize(300, 300);
        frame.setResizable(false);
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
        frame.setVisible(true);
    }

    public Q2Oct12() {
        initUI();
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            var ex = new Q2Oct12();
            ex.setVisible(true);
        });
    }
}
