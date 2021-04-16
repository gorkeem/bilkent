import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.Scanner;
import java.util.ArrayList;
import javax.imageio.ImageIO;
import java.util.Arrays;
import java.util.List;
import java.awt.*;
import java.awt.image.BufferedImage;
import javax.imageio.*;


public class TaxonomySearcher {

    final static String CR = "\r";
    final static String LF = "\n";
    public static String messageType;
    //public static String response;
    static Socket clientSocket;
    static DataOutputStream outToServer;
    static InputStreamReader inputStreamReader;
    static BufferedReader fromServer;
    static DataInputStream ReaderImage;
    public static List<String> curFilesDirs = new ArrayList<String>();
    public static List<String> dirStack = new ArrayList<String>();
    public static List<String> goals = new ArrayList<String>();
    public static boolean isExit = false;

    // Default Constructor
    public TaxonomySearcher(int controlPort, String host) throws IOException {
        clientSocket = new Socket(host, controlPort);
        outToServer = new DataOutputStream(clientSocket.getOutputStream());
        inputStreamReader = new InputStreamReader(clientSocket.getInputStream());
        fromServer = new BufferedReader(inputStreamReader);
        ReaderImage = new DataInputStream(clientSocket.getInputStream());
    }

    public static void sendAuthentication() throws IOException{
        final String username = "bilkentstu";
        final String password = "cs421f2020";
        messageType = "USER";
        sendCommand(messageType,username);
        printResponse(messageType);
        messageType = "PASS";
        sendCommand(messageType,password);
        printResponse(messageType);
    }
    public static void printResponse(String mesage_type) throws IOException{
        String serverResp =  fromServer.readLine();
        //System.out.println((mesage_type.equals("NLST")));
        String[] contents = serverResp.split("\\s");
        //System.out.println(contents[0]);
        //System.out.println(Arrays.toString(contents));
        if(contents.length > 1 && !(contents[0].equals("INVALID"))){
            //System.out.println("nlst response mesage length>1");
            String[] statusText = Arrays.copyOfRange(contents, 1, contents.length);
            if(mesage_type.equals("OBJ")) {
                goals = new ArrayList<>(Arrays.asList(statusText));
                System.out.println("goals: " + goals);
            }
            else if(mesage_type.equals("NLST")){
                curFilesDirs = new ArrayList<>(Arrays.asList(statusText));
                System.out.println("current dirs and files: " + curFilesDirs);
            }
        }
        else if((mesage_type.equals("NLST")) && (contents[0].equals("OK") )){
            System.out.println("empty folder");
            curFilesDirs.clear();
            System.out.println("current dirs and files: " + curFilesDirs);
        }
        System.out.println(serverResp);
        if(contents[0].equals("INVALID")){
            sendCommand("EXIT","");
            isExit = true;
        }
    }
    public static void sendCommand(String mesage_type,String argument) throws IOException{
        String command;
        if(argument != ""){
            command = mesage_type + " " + argument + CR + LF;
        }
        else{
            command = mesage_type + CR + LF;
        }
        System.out.print("Sending: " + command);
        outToServer.writeBytes(command);
    }
    public static void findFile() throws IOException{
        messageType = "OBJ";
        sendCommand(messageType,"");
        printResponse(messageType);
        depthFirstSearch();
    }
    public static boolean isFile(String obj) throws IOException{
        if(obj.contains(".")){
            System.out.println("name of the file:" + obj);
            /*
            for(int i = 0;i < goals.size();i++){
                if(obj.equals(goals.get(i))){
                    sendCommand("GET",obj);
                    readImage(obj);
                    goals.remove(i);
                    System.out.println("goals: " + goals);
                    System.out.println("Goal image"+obj);
                    break;
                }
            }*/
            return true;
        }
        return false;
    }
    public static void isGoalFile(String obj) throws IOException{
        for(int i = 0;i < goals.size();i++){
            if(obj.equals(goals.get(i))){
                sendCommand("GET",obj);
                readImage(obj);
                goals.remove(i);
                System.out.println("goals: " + goals);
                System.out.println("Goal image"+obj);
                break;
            }
        }
    }
    public static boolean isAleaf()throws IOException{
        if(curFilesDirs.isEmpty()){
            return true;
        }
        int noElements = curFilesDirs.size();
        int count = 0;
        for(int i=0;i<noElements;i++){
            if(isFile(curFilesDirs.get(i))){
                count++;
            }
        }
        if(count == noElements){
            System.out.println("it is a leaf");
            return true;
        }
        return false;
    }
    public static void depthFirstSearch() throws IOException{
        //ArrayList<String> tempElements = new ArrayList<String>();
        messageType = "NLST";
        sendCommand(messageType,"");
        printResponse(messageType);
        addDirectory();
        boolean isUp = false;
        while(!( goals.isEmpty() || dirStack.isEmpty())){
            while(!isAleaf()){
                String childDir = dirStack.remove(dirStack.size() - 1);
                sendCommand("CWDR", childDir);
                printResponse("CWDR");
                sendCommand("NLST", "");
                printResponse("NLST");
                addDirectory();
            }
            String parentDir = dirStack.get(dirStack.size() - 1);
            isUp = true;
            while(!(curFilesDirs.contains(parentDir) || goals.isEmpty())) {
                sendCommand("CDUP", "");
                printResponse("CDUP");
                sendCommand("NLST","");
                printResponse("NLST");
            }
        }
        sendCommand("EXIT","");
        isExit = true;
    }
    public static void addDirectory() throws IOException{
        for(int i=0;i<curFilesDirs.size();i++){
            if(!isFile(curFilesDirs.get(i))){
                dirStack.add(curFilesDirs.get(i));
                //System.out.println("directory: " + dirStack);
            }
            //new
            else{
                //System.out.println("it is a goal file" + curFilesDirs.get(i));
                isGoalFile(curFilesDirs.get(i));
            }
        }
        System.out.println("Directory Stack: " + dirStack);

    }
    public static void readImage(String argument)throws IOException{
        byte[] imStatusCode = new byte[4];
        byte[] imSize = new byte[4];
        ReaderImage.readFully(imStatusCode,0,4);
        ReaderImage.readFully(imSize,1,3);
        String stausIm = new String(imStatusCode, Charset.forName("US-ASCII"));
        int imageSize =  ByteBuffer.wrap(imSize).getInt();
        byte[] image = new byte[imageSize];
        ReaderImage.readFully(image, 0, imageSize);
        FileOutputStream outputFile = new FileOutputStream(argument);
        outputFile.write(image);
        System.out.println(stausIm);
    }

    public static void main(String[] args) throws IOException{
        System.out.println("-----------------------------------------------------");
        String host = args[0];
        int port = Integer.parseInt(args[1]);
        TaxonomySearcher connection = new TaxonomySearcher(port, host);
        try
        {
            connection.sendAuthentication();
            while(!isExit){
                connection.findFile();
            }
        }
        catch (Exception ioe)
        {
            System.out.println("Connection Failure");
        }
    }
}