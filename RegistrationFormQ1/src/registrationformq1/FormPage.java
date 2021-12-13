package registrationformq1;

import java.awt.event.ActionEvent;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;

/**
 *
 * @author Rohith M S R
 */
public final class FormPage extends JFrame {
    UserRecords table;
    private final JPanel contentPane;
    private final JTextField name;
    private final JTextField email;
    private final JTextField phone;
    private final JPasswordField password;
    private final JButton btnAddUser;
    private final JButton btnGetUsers;
    
    public void initUI(){
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setBounds(450, 190, 1014, 597);
        setResizable(false);
        
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        contentPane.setLayout(null);
        
        JLabel labelNewUserRegister = new JLabel("REGISTER NEW USER!");
        labelNewUserRegister.setBounds(362, 52, 325, 50);
        contentPane.add(labelNewUserRegister);
        
        JLabel labelName = new JLabel("Name");
        labelName.setBounds(58, 152, 99, 43);
        contentPane.add(labelName);
        
        JLabel labelPassword = new JLabel("Password");
        labelPassword.setBounds(58, 243, 110, 29);
        contentPane.add(labelPassword);
        
        JLabel labelEmail = new JLabel("E-mail ID");
        labelEmail.setBounds(542, 159, 99, 29);
        contentPane.add(labelEmail);

        JLabel labelPhone = new JLabel("Phone");
        labelPhone.setBounds(542, 245, 99, 24);
        contentPane.add(labelPhone);
        
        name.setBounds(214, 151, 228, 50);
        contentPane.add(name);
        name.setColumns(10);

        password.setBounds(214, 235, 228, 50);
        contentPane.add(password);
        password.setColumns(10);
        
        email.setBounds(707, 151, 228, 50);
        contentPane.add(email);
        email.setColumns(10);
        
        phone.setBounds(707, 235, 228, 50);
        contentPane.add(phone);
        phone.setColumns(10);
        
        btnAddUser.setBounds(259, 427, 100, 50);
        contentPane.add(btnAddUser);
        
        btnGetUsers.setBounds(500, 427, 200, 50);
        contentPane.add(btnGetUsers);
    }
    
    public FormPage() {
        contentPane = new JPanel();
        name = new JTextField();
        password = new JPasswordField();
        email = new JTextField();
        phone = new JTextField();
        btnAddUser = new JButton("Register");
        btnGetUsers = new JButton("Get All Users!");
        
        initUI();
        
        btnGetUsers.addActionListener((ActionEvent e) -> {
            if(table != null && table.isFrameOpen == true){
                return;
            }
            
            try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/testdb","jdbcuser","")) {
                List<String> columns = new ArrayList<>();
                List<String[]> data = new ArrayList<>();
                String q2;
                Class.forName("com.mysql.cj.jdbc.Driver");
                Statement st = conn.createStatement();
                
                q2 = "SELECT id, name, email FROM user";
                ResultSet rs = st.executeQuery(q2);
                
                int nCol = rs.getMetaData().getColumnCount();
                for(int i = 1; i <= nCol; ++i){
                    columns.add(rs.getMetaData().getColumnName(i));
                }
                
                while(rs.next()) {
                    String[] row = new String[nCol];
                    for(int i = 1; i <= nCol; i++ ){
                        Object obj = rs.getObject(i);
                        row[i - 1] = (obj == null) ? null : obj.toString();
                    }
                    data.add(row);
                }
                
                table = new UserRecords(data, columns);
                table.initUI();
            }
            catch (SQLException ex) {
                System.out.println("ERROR = " + ex.getMessage());
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(FormPage.class.getName()).log(Level.SEVERE, null, ex);
            }
        });
        
        btnAddUser.addActionListener((var e) -> {
            String user_name = name.getText();
            String email_id = email.getText();
            String mobile_number = phone.getText();
            String user_password = password.getText();
            
            int len = mobile_number.length();
            if (len != 10) {
                JOptionPane.showMessageDialog(btnAddUser, "Enter a valid mobile number");
                return;
            }
            
            try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/testdb","jdbcuser","")) {
                Class.forName("com.mysql.cj.jdbc.Driver");
                String query = "INSERT INTO user(name, password, email, phone_number) VALUES('" + user_name + "','" + user_password + "','" + email_id + "','" + mobile_number + "')";

                Statement sta = conn.createStatement();
                int x1 = sta.executeUpdate(query);
                if (x1 == 0) {
                    JOptionPane.showMessageDialog(btnAddUser, "User already exists");
                }
                else {
                    JOptionPane.showMessageDialog(btnAddUser,
                            "Welcome, " + user_name + " !!\nYour details are successfully added");
                }
            }
            catch (SQLException ex) {
                System.out.println("ERROR = " + ex.getMessage());
                JOptionPane.showMessageDialog(btnAddUser, ex.getMessage());
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(FormPage.class.getName()).log(Level.SEVERE, null, ex);
            }
        });
    }
}
