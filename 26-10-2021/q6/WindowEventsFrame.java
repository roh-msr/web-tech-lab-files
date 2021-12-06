import java.awt.*;    
import java.awt.event.*;
  
public class WindowEventsFrame extends Frame implements WindowListener {    
    public WindowEventsFrame() {   
        addWindowListener(this);       
        setSize (400, 400);    
        setLayout (null);    
        setVisible (true);    
    }       
    
    public void windowActivated (WindowEvent arg0) {    
        System.out.println("Activated");    
    }    
    
    public void windowClosed (WindowEvent arg0) {    
        System.out.println("Closed");    
    }    
    
    public void windowClosing (WindowEvent arg0) {    
        System.out.println("Closing");    
        dispose();    
    }    
    
    public void windowDeactivated (WindowEvent arg0) {    
        System.out.println("Deactivated");    
    }    
    
    public void windowDeiconified (WindowEvent arg0) {    
        System.out.println("De-iconified");    
    }    
    
    public void windowIconified(WindowEvent arg0) {    
        System.out.println("Iconified");    
    }    
    
    public void windowOpened(WindowEvent arg0) {    
        System.out.println("Opened");    
    }

    public static void main(String[] args) {    
        new WindowEventsFrame();    
    }
}    