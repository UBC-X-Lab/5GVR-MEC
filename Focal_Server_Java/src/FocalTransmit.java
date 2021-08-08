import java.io.IOException;
import java.net.*;
import java.time.Clock;
import java.time.Duration;
import java.time.Instant;

public class FocalTransmit extends Thread {
    private InputWindow window = new InputWindow();
    private Duration rate;
    private Instant timeout;
    private InetAddress IPAddress;
    private int PORT;
    boolean active = false;

    FocalTransmit(Duration rate, Instant timeout, InetAddress address, int port) {
        try {
            this.rate = rate;
            this.timeout = timeout;
            this.IPAddress = InetAddress.getByName("192.168.0.115");//address;
            this.PORT = port;
        }catch(UnknownHostException e){
            System.out.println("unknown host");
        }
    }

    public void run() {
        active = true;
        try {
            System.out.println("data transmission started on ip: " + IPAddress.toString() + " port: " + PORT + " every " + rate.toMillis() + "ms.");
            DatagramSocket serverSocket = new DatagramSocket();
            byte[] sendData;
            while (Clock.systemDefaultZone().instant().isBefore(timeout)) {

                String outData = (int) window.getCursorPos().getX() + ", " + (int) window.getCursorPos().getY();
                sendData = outData.getBytes();
                DatagramPacket sendPacket = new DatagramPacket(sendData,0 ,sendData.length, IPAddress, PORT);
                serverSocket.send(sendPacket);
                try {
                    Thread.sleep(rate.toMillis());
                } catch (InterruptedException e) {
                    System.out.println("Transmit InterruptException: " + e.getMessage());
                }
            }
            serverSocket.close();
        } catch (SocketException e) {
            System.out.println("Transmit SocketException: " + e.getMessage());
            e.printStackTrace();
        } catch (IOException e) {
            System.out.println("Transmit IOException: " + e.getMessage());
            e.printStackTrace();
        }
        System.out.println("data transmission stopped.");
        active = false;
    }

    public Instant getTimeout() {
        return timeout;
    }

    void updateTimeout(Instant timeout) {
        this.timeout = timeout;
    }

    void setRate(Duration rate) {
        this.rate = rate;
    }

    void setPort(int PORT) {
        this.PORT = PORT;
    }
}
