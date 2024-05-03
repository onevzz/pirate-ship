import javax.swing.JFrame;

public class Main {
    public static void main(String[] args) {
        // init window
        JFrame frame = new JFrame(); // create JFrame object
        frame.setSize(300, 400); // set size of window
        frame.setTitle("Traffic Light"); // set title of window
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // exit when close window

        LightComponent component = new LightComponent(); // drawing object
        frame.add(component);
        frame.setVisible(true); // set to visible on window
    }
}