import java.applet.Applet;
import java.awt.event.*;
import java.awt.*;

/* <applet code="Fact" width="500" height="400"></applet> */

public class Fact extends Applet implements ActionListener{
	
	Button calculate;
	Label ip, result;
	TextField T1,T2;
	
	public void init(){

		setLayout(new GridBagLayout());
		GridBagConstraints c = new GridBagConstraints();

		ip = new Label("Enter a number:");
		c.fill = GridBagConstraints.HORIZONTAL;
		c.weightx = 0.0;
		c.gridwidth = 3;
		c.gridx = 0;
		c.gridy = 0;
		add(ip);

		T1 = new TextField(20);
		c.fill = GridBagConstraints.HORIZONTAL;
		c.weightx = 0.0;
		c.gridwidth = 3;
		c.gridx = 1;
		c.gridy = 0;
		T1.setSize(new Dimension(50, 30));
		add(T1);
		
		T2 = new TextField(20);
		T2.setSize(new Dimension(100, 30));
		T2.setEditable(false);
		c.fill = GridBagConstraints.HORIZONTAL;
		c.weightx = 0.0;
		c.gridwidth = 3;
		c.gridx = 0;
		c.gridy = 2;
		add(T2);
		
		calculate = new Button("Calculate Factorial");
		calculate.addActionListener(this);
		c.fill = GridBagConstraints.HORIZONTAL;
		c.anchor = GridBagConstraints.PAGE_END; //bottom of space
		c.insets = new Insets(10,0,0,0);  //top padding
		c.gridx = 1;       //aligned with button 2
		c.gridy = 2;       //third row
		add(calculate, c);

		
		setVisible(true);
		setSize(new Dimension(420, 250));

	}
	
	public void actionPerformed(ActionEvent A){
		
		String num = T1.getText();
		
		long fact = 1, i = 1, n;
		
		n = Integer.parseInt(num);
		
		for(i = 1, fact = 1; i <= n; i++){
			fact *= i;
		}
		
		T2.setText(Long.toString(fact));
		repaint();
	}
}