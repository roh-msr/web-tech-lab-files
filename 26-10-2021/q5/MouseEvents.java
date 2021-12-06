import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class MouseEvents implements MouseListener {
    static JLabel label;
    static JFrame frame;

    public void mouseClicked(MouseEvent e) {
        label.setText("Mouse Click !");
    }  
    
    public void mouseEntered(MouseEvent e) {
        label.setText("Mouse Entered !");
    }  
    
    public void mouseExited(MouseEvent e) {
        label.setText("Mouse Exited !");
    }  
    
    public void mousePressed(MouseEvent e) {
        label.setText("Mouse Press !");
    }
    
    public void mouseReleased(MouseEvent e) {
        label.setText("Mouse Released !");
        System.out.println("Mouse Release");
    } 
    
    public MouseEvents() {
        frame = new JFrame("Mouse Events");  
        frame.addMouseListener(this);

        label = new JLabel("Fire a mouse event dude!!");  
        label.setBounds(100, 30, 200, 200);  
        
        frame.add(label);  
        frame.setSize(400,300);  
        frame.setLayout(null);  
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.setVisible(true);
    }
    
    public static void main(String[] args) {  
        new MouseEvents();
    } 
}