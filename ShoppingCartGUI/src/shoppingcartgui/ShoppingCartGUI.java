package shoppingcartgui;

import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.SwingUtilities;

class Item {
    public final JPanel panel;
    
    private final JLabel name;
    private final JLabel price;
    private final JLabel stock;
    private final JLabel quantity;
    private final JComboBox product_quantity_wanted;
    private final JLabel product_name;
    private final JLabel product_price;
    private final JLabel product_stock;
    
    Item(String item_name, int item_price, int item_stock) {
        panel = new JPanel(new GridLayout(4, 2, 10, 10)); // 4 rows, 2 cols
        name = new JLabel("NAME");
        price = new JLabel("PRICE");
        stock = new JLabel("AVAILABILITY");
        quantity = new JLabel("QUANTITY");
        
        product_name = new JLabel(item_name);
        product_price = new JLabel(Integer.toString(item_price));
        product_stock = new JLabel(Integer.toString(item_stock));
        
        List<Integer> quanlist = new ArrayList<>();
        for (int i = 0; i <= item_stock; ++i) {
            quanlist.add(i);
        }
        product_quantity_wanted = new JComboBox(quanlist.toArray());
        
        panel.add(name);
        panel.add(product_name);
        panel.add(price);
        panel.add(product_price);
        panel.add(stock);
        panel.add(product_stock);
        panel.add(quantity);
        panel.add(product_quantity_wanted);
        
        panel.setVisible(true);
        panel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
    }
}

public class ShoppingCartGUI {
    private final JFrame frame;
    private final JPanel itemList;
    private final JScrollPane scrollPane;
    private final JButton buy;
    private final JButton refresh;
    
    public void initUI() {
        frame.setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        
        itemList.setLayout(new GridLayout(5, 2));
        
        for(int i = 0; i < 10; ++i){
            if(i % 2 == 0){  
                Item it = new Item("Apples", 23, 5);
                it.panel.setBackground(Color.WHITE);
                itemList.add(it.panel);
            }
            else{
                Item it = new Item("Banana", 56, 6);
//                it.panel.setBackground(new Color((int)(Math.random() * 0x1000000)));
                it.panel.setBackground(Color.LIGHT_GRAY);
                itemList.add(it.panel);
            }
        }
        
        gbc.fill = GridBagConstraints.VERTICAL;
        gbc.gridwidth = 2;
        gbc.ipadx = 750;
        gbc.ipady = 500;
        gbc.gridx = 0;
        gbc.gridy = 0;
        frame.add(scrollPane, gbc);
        
        gbc.gridwidth = 1;
        gbc.ipadx = 100;
        gbc.ipady = 50;
        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.insets = new Insets(10,0,0,0);
        frame.add(buy, gbc);
        
        refresh.addActionListener((ActionEvent e) -> { 
            frame.dispose();
            ShoppingCartGUI sg = new ShoppingCartGUI();
        });  
        
        gbc.gridwidth = 1;
        gbc.ipadx = 100;
        gbc.ipady = 50;
        gbc.gridx = 1;
        gbc.gridy = 1;
        gbc.insets = new Insets(10,0,0,0);
        frame.add(refresh, gbc);
        
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
        frame.setSize(800, 800);
    }
    
    public ShoppingCartGUI() {
        frame = new JFrame("Rohith M S R's House of Gadgets");
        itemList = new JPanel();
        scrollPane = new JScrollPane(itemList);
        buy = new JButton("BUY");
        refresh = new JButton("REFRESH");
        initUI();
    }
    
    public static void main(String[] args) {
        ShoppingCartGUI sg = new ShoppingCartGUI();
    }
}
