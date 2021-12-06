import javax.swing.*;  
import java.awt.*;  
import java.awt.event.*;  
import java.lang.Exception;  
  
class CreateLoginForm extends JFrame
{  
    JButton b1;  
    JPanel newPanel;  
    JLabel userLabel, passLabel;  
    final JTextField  textField1, textField2;  
      
    CreateLoginForm()  
    {     
        newPanel = new JPanel(new GridLayout(3, 1));  
          
        userLabel = new JLabel();  
        userLabel.setText("Username");
        newPanel.add(userLabel);     

        textField1 = new JTextField(15); 
        newPanel.add(textField1);  
  
        passLabel = new JLabel();  
        passLabel.setText("Password");    
        newPanel.add(passLabel);    

        textField2 = new JPasswordField(15);
        newPanel.add(textField2);
          
        b1 = new JButton("SUBMIT");
        b1.addActionListener(new ActionListener() {
            // handle button event
            public void actionPerformed( ActionEvent event )
            {
                String userValue = textField1.getText();
                String passValue = textField2.getText();
    
                if (userValue.equals("netflix") && passValue.equals("tudum")) { 
                    JOptionPane.showMessageDialog(CreateLoginForm.this, 
                        String.format("Welcome " + userValue));
                }  
                else{  
                    JOptionPane.showMessageDialog(CreateLoginForm.this, 
                        String.format("Enter valid credentials! "));
                }
            } // end method actionPerformed
        }); 
        // b1.addActionListener(handler); // inner class
        newPanel.add(b1);           
        
        //set border to panel   
        add(newPanel, BorderLayout.CENTER);  
          
        // b1.addActionListener(this); function !!
        setTitle("Enter Credentials!!");
    }  

    // inner class for button event handling
    // private class ButtonHandler implements ActionListener
    // {
    //     // handle button event
    //     public void actionPerformed( ActionEvent event )
    //     {
    //         String userValue = textField1.getText();
    //         String passValue = textField2.getText();

    //         if (userValue.equals("netflix") && passValue.equals("tudum")) { 
    //             JOptionPane.showMessageDialog(CreateLoginForm.this, 
    //                 String.format("Welcome " + userValue));
    //         }  
    //         else{  
    //             JOptionPane.showMessageDialog(CreateLoginForm.this, 
    //                 String.format("Enter valid credentials! "));
    //         }
    //     } // end method actionPerformed
    // }
}  

class LoginFormDemo  
{  
    public static void main(String arg[])  
    {  
        CreateLoginForm form = new CreateLoginForm();  
        form.setSize(400, 200);
        form.setVisible(true);  
        form.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }  
}  