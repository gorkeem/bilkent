import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;

public class Sender {

    // Ack that we are waiting for
    public static int waitingForAck = 1;
    static Semaphore mutex = new Semaphore(1);

    public static byte[] getFile(String path) {
        try {
            byte[] fileToSend = Files.readAllBytes(Paths.get(path));
            return fileToSend;
        } catch (IOException e) {
            System.out.println("Cannot find or read file");
        }
        return null;
    }

    public static List<DatagramPacket> getPackets(byte[] file, int receiverPort) throws UnknownHostException {

        // Divide file array into udp packets of size 1024 bytes, first two bytes is
        // header with big endian
        int packetsize = 1024;
        int datasize = packetsize - 2;

        List<DatagramPacket> packets = new ArrayList<DatagramPacket>();

        int start = 0;
        int counter = 1;

        while (start < file.length) {
            int end = Math.min(file.length, start + datasize);
            byte[] temp = new byte[end - start + 2];
            // Add header
            ByteBuffer b = ByteBuffer.allocate(4);
            b.putInt(counter);
            byte[] result = b.array();
            temp[0] = result[2];
            temp[1] = result[3];
            // Get packet data
            byte[] data = Arrays.copyOfRange(file, start, end); // Has length 1022
            // Add data to temp
            for (int i = 0; i < data.length; i++) {
                temp[i + 2] = data[i];
            }
            // Update start index
            start = start + datasize;
            // Create a datagram packet to add packets
            DatagramPacket tempPacket = new DatagramPacket(temp, temp.length, InetAddress.getByName("localhost"),
                    receiverPort);
            // System.out.println("temp packet size ==> " + tempPacket.getLength());
            packets.add(tempPacket);
            // Update counter for creating headers
            counter++;

        }
        return packets;
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        // Get path to file, receiver port, window size and timeout for retransmission
        String filePath = args[0];
        int receiverPort = Integer.parseInt(args[1]);
        final int WINDOWSIZE = Integer.parseInt(args[2]);
        final int TIMEOUT = Integer.parseInt(args[3]);

        // Create a UDP Socket
        // DatagramSocket socket;
        // Get the file from input path
        byte[] file = getFile(filePath);

        List<DatagramPacket> packets = getPackets(file, receiverPort);
        DatagramSocket socket = new DatagramSocket();

        // Define finishpackage
        byte[] finishpackageArr = new byte[2];
        ByteBuffer b = ByteBuffer.allocate(4);
        b.putInt(0);
        byte[] result = b.array();
        finishpackageArr[0] = result[2];
        finishpackageArr[1] = result[3];
        DatagramPacket finishpackage = new DatagramPacket(finishpackageArr, finishpackageArr.length,
                InetAddress.getByName("localhost"), receiverPort);

        // Last packet sequence number
        int lastSeq = packets.size();
        // Sequence number of the last packet sent (rcvbase)
        int lastSent = 1;

        // Listener thread
        Thread listenerThread = new Thread(new Runnable() {
            int lastSeq = packets.size();
            public void run() {
                try {
                    while (true) {
                        try {
                            socket.setSoTimeout(TIMEOUT);
                            byte[] receiveData = new byte[2];
                            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                            socket.receive(receivePacket);
                            byte[] receiveArr = receivePacket.getData();
                            int ack = ((receiveArr[0] & 0xff) << 8) | (receiveArr[1] & 0xff);
                            mutex.acquire();
                            waitingForAck = Math.max(waitingForAck, ack);
                            mutex.release();
                        }catch (SocketTimeoutException e){
                            for (int i = waitingForAck; i <= Math.min(waitingForAck+ WINDOWSIZE,lastSeq); i++) {
                                socket.send(packets.get(i - 1));
                            }
                        }
                    }
                } catch (Exception e) {
                    return;
                }
            }
        });

        listenerThread.start();

        // SENDER
        try {
            while (true) {
                // First, send all packages in the windows and update lastsent information
                //try {
                    mutex.acquire();
                    while (lastSent - waitingForAck < WINDOWSIZE && lastSent <= lastSeq) {
                        try {
                            socket.send(packets.get(lastSent - 1));
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        lastSent++;
                    }
                    mutex.release();

                    // If every package is sent, send 2 bytes of zeros to tell receiver all packages sent
                    if (waitingForAck == lastSeq) {
                        listenerThread.interrupt();
                        break;
                    }
            }
        } 
        catch (Exception e) {
            return;
        }

        socket.send(finishpackage);
        System.exit(0);
    }
}
