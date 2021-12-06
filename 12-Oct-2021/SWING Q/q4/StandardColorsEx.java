import javax.swing.*;
import java.awt.*;
import java.util.*;

class MyLabel extends JLabel {
    public MyLabel() {
        super("", null, LEADING);
    }

    @Override
    public boolean isOpaque() {
        return true;
    }
}

public class StandardColorsEx extends JFrame {
    public StandardColorsEx() {
        initUI();
    }

    private void initUI() {
        Color[] stdCols = { Color.black, Color.blue, Color.cyan, Color.darkGray, Color.gray, Color.green,
                Color.lightGray, Color.magenta, Color.orange, Color.pink, Color.red, Color.white, Color.yellow };
        var labels = new ArrayList<JLabel>();
        for (var col : stdCols) {
            var lbl = createColouredLabel(col);
            labels.add(lbl);
        }
        createLayout(labels.toArray(new JLabel[0]));
        setTitle("Standard colours");
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    private JLabel createColouredLabel(Color col) {
        var lbl = new MyLabel();
        lbl.setMinimumSize(new Dimension(90, 40));
        lbl.setBackground(col);
        return lbl;
    }

    private void createLayout(JLabel[] labels) {
        var pane = (JPanel) getContentPane();
        var gl = new GroupLayout(pane);
        pane.setLayout(gl);
        pane.setToolTipText("Content pane");
        gl.setAutoCreateContainerGaps(true);
        gl.setAutoCreateGaps(true);
        gl.setHorizontalGroup(gl.createParallelGroup()
                .addGroup(gl.createSequentialGroup().addComponent(labels[0]).addComponent(labels[1])
                        .addComponent(labels[2]).addComponent(labels[3]))
                .addGroup(gl.createSequentialGroup().addComponent(labels[4]).addComponent(labels[5])
                        .addComponent(labels[6]).addComponent(labels[7]))
                .addGroup(gl.createSequentialGroup().addComponent(labels[8]).addComponent(labels[9])
                        .addComponent(labels[10]).addComponent(labels[11]))
                .addComponent(labels[12]));
        gl.setVerticalGroup(gl.createSequentialGroup()
                .addGroup(gl.createParallelGroup().addComponent(labels[0]).addComponent(labels[1])
                        .addComponent(labels[2]).addComponent(labels[3]))
                .addGroup(gl.createParallelGroup().addComponent(labels[4]).addComponent(labels[5])
                        .addComponent(labels[6]).addComponent(labels[7]))
                .addGroup(gl.createParallelGroup().addComponent(labels[8]).addComponent(labels[9])
                        .addComponent(labels[10]).addComponent(labels[11]))
                .addComponent(labels[12]));
        pack();
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            var ex = new StandardColorsEx();
            ex.setVisible(true);
        });
    }
}