import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class TrafficLights extends JFrame {
    final JFrame frame = new JFrame("Radio Buttom Messages!");
    final ButtonGroup group = new ButtonGroup();
    JRadioButton optRED, optYELLOW, optGREEN;

    // implement ItemListener interface
    class MyItemListener implements ItemListener {
        public void itemStateChanged(ItemEvent ev) {
            boolean selected = (ev.getStateChange() == ItemEvent.SELECTED);
            AbstractButton button = (AbstractButton) ev.getItemSelectable();
            String command = button.getActionCommand();

            // build message
            String message = "None";
            if (selected) {
                if (command.equals("STOP")) {
                    message = "STOP";
                } else if (command.equals("READY")) {
                    message = "READY";
                } else if (command.equals("GO")) {
                    message = "GO";
                }

                // show dialog
                JOptionPane.showMessageDialog(frame, message);
            } 
        }
    }

    private void initUI() {
        optRED = new JRadioButton("RED");
        optRED.setActionCommand("STOP");

        optYELLOW = new JRadioButton("YELLOW");
        optYELLOW.setActionCommand("READY");

        optGREEN = new JRadioButton("GREEN");
        optGREEN.setActionCommand("GO");

        // add event handler
        MyItemListener myItemListener = new MyItemListener();
        optRED.addItemListener(myItemListener);
        optYELLOW.addItemListener(myItemListener);
        optGREEN.addItemListener(myItemListener);

        // add radio buttons to a ButtonGroup
        group.add(optRED);
        group.add(optYELLOW);
        group.add(optGREEN);

        
        Container cont = frame.getContentPane();
        cont.setLayout(new GridLayout(0, 1));
        cont.add(optRED);
        cont.add(optYELLOW);
        cont.add(optGREEN);

        frame.setLayout (new GridLayout(0,1));
        frame.setSize(300, 300);
        frame.setResizable(false);
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
        frame.setVisible(true);
    }

    public TrafficLights() {
        initUI();
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            var ex = new TrafficLights();
            ex.setVisible(true);
        });
    }
}
