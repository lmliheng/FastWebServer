import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class WebServer {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            System.out.println("New client connected");

            // 创建一个新的线程来处理每个客户端的请求
            new Thread(new ClientHandler(clientSocket)).start();
        }
    }

    static class ClientHandler implements Runnable {
        private final Socket clientSocket;

        public ClientHandler(Socket socket) {
            this.clientSocket = socket;
        }

        @Override
        public void run() {
            try (
                    InputStream input = clientSocket.getInputStream();
                    OutputStream output = clientSocket.getOutputStream();
            )
             {
                // 读取请求行
                BufferedReader in = new BufferedReader(new InputStreamReader(input));
                String requestLine = in.readLine();

                // 简单处理，直接返回一个HTML响应
                if (requestLine != null && requestLine.startsWith("GET")) {
                    String fileName = "./index.html";
                    Path filePath = Paths.get(fileName);
                    if (Files.exists(filePath)) {
                        String httpResponse = "HTTP/1.1 200 OK\r\n" +
                                "Content-Type: text/html; charset=UTF-8\r\n" +
                                "\r\n";
                        output.write(httpResponse.getBytes("UTF-8"));

                        // 读取HTML文件并写入响应
                        Files.copy(filePath, output);
                    } else {
                        String httpResponse = "HTTP/1.1 404 Not Found\r\n" +
                                "Content-Type: text/html; charset=UTF-8\r\n" +
                                "\r\n" +
                                "<!DOCTYPE html>\n" +
                                "<html>\n" +
                                "<head>\n" +
                                "<title>404 Not Found</title>\n" +
                        "</head>\n" +
                                "<body>\n" +
                                "<h1>404 Not Found</h1>\n" +
                                "</body>\n" +
                                "</html>";
                        output.write(httpResponse.getBytes("UTF-8"));
                    }
                }

                output.flush();
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}