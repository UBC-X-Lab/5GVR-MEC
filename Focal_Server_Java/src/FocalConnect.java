import java.io.*;
import java.net.*;
import java.time.Clock;
import java.time.Duration;

import static java.lang.Thread.yield;

public class FocalConnect {
    private static int controlPort = 3490;
    private static Clock clock = Clock.systemDefaultZone();
    private static boolean send = false;

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(controlPort)) {
            System.out.println("Server started. Socket on port: " + controlPort);
            while (true) {
                Socket socket = serverSocket.accept();
                System.out.println("Accepted control connection from: " + socket.getInetAddress().toString() + " on port: " + socket.getPort());
                FocalTransmit dataStream = new FocalTransmit(Duration.ofMillis(33), clock.instant().plus(Duration.ofSeconds(2)), socket.getInetAddress(), 3491);
                InputStream inputStream = socket.getInputStream();
                BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
                while (dataStream.getTimeout().isAfter(clock.instant())) {
                    while (inputStream.available() > 0) {
                        handleInput(reader.readLine(), dataStream);
                        dataStream.updateTimeout(clock.instant().plus(Duration.ofSeconds(2)));
                    }
                    if (send) {
                        if (!dataStream.active && !dataStream.isAlive()) {
                            dataStream.start();
                            yield();
                        }
                    }
                }
                System.out.println("control connection timed out.");
                //Reset parameters to default
                send = false;
            }

        } catch (IOException ex) {
            System.out.println("Server exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    }

    private static void handleInput(String input, FocalTransmit dataStream) {
        // If message contains "r" update the rate
        if (input.contains("r")) {
            String num = input.replaceAll("[^0-9]", "");
            dataStream.setRate(Duration.ofMillis(Integer.decode(num)));
            //If message contains "p" update the port and set send to true
        } else if (input.contains("p")) {
            String num = input.replaceAll("[^0-9]", "");
            dataStream.setPort(Integer.decode(num));
            send = true;
        } else {
            System.out.println("FocalConnect: Unexpected message: " + input);
        }
    }
}
