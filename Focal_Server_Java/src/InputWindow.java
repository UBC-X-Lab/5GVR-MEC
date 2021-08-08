import java.awt.*;
import javax.swing.*;

public class InputWindow {
    private static void openWindow(){
        JFrame window = new JFrame("Hover Mouse here");
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setLocationRelativeTo(null);
        window.pack();
        window.setVisible(true);
    }
    public Point getCursorPos(){
        PointerInfo pi = MouseInfo.getPointerInfo();
        return pi.getLocation();
    }
}
