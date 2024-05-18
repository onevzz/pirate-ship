import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.geom.Ellipse2D;
import javax.swing.JComponent;

public class LightComponent extends JComponent {
    public void paintComponent(Graphics ink) {
        Graphics2D canvas = (Graphics2D) ink; // create canvas
        Rectangle box = new Rectangle(50, 50, 100, 200); // drawing box to contain lights
        canvas.draw(box);
        
        Ellipse2D.Double redLight = new Ellipse2D.Double(75, 60, 50, 50); // create red light
        canvas.setColor(Color.RED);
        canvas.fill(redLight);
        
        Ellipse2D.Double yellowLight = new Ellipse2D.Double(75, 125, 50, 50); // create yellow light
        canvas.setColor(Color.YELLOW);
        canvas.fill(yellowLight);

        Ellipse2D.Double greenLight = new Ellipse2D.Double(75, 190, 50, 50); // create green light
        canvas.setColor(Color.GREEN);
        canvas.fill(greenLight);
    }
}