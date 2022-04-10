using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using UnityEngine;
using System.Threading;

public class TCP_connection : MonoBehaviour
{
   // Socket tcpServer = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
    static List<Client> clientList = new List<Client>();
    TcpListener listener;
    IPAddress localAdd;
    public static string dataReceived;
    public string IP = "192.168.31.140";
    public int Port = 8899;
    // Start is called before the first frame update
    void Start()
    {
        //tcpServer.Bind(new IPEndPoint(IPAddress.Parse("192.168.31.161"), 6000));
        //tcpServer.Listen(10);
        localAdd = IPAddress.Parse(IP);
        listener = new TcpListener(IPAddress.Any,Port);
        listener.Start();
        print("Sever Running");
    }

    // Update is called once per frame
    void Update()
    {
        if (!listener.Pending())
        {
        }
        else
        {
            Socket clientSocket = listener.AcceptSocket();
            print("A client is connected");
            Client client = new Client(clientSocket);
            clientList.Add(client);
        }
    }

    class Client {
        private Socket clientSocket;
        private Thread t;
        private byte[] data = new byte[1024];
        public Client(Socket s) {
            clientSocket = s;
            t = new Thread(ReceiveMessage);
            t.Start();
        }

        private void ReceiveMessage() {

            while (true)
            {
                int length = clientSocket.Receive(data);
                dataReceived = Encoding.UTF8.GetString(data, 0, length);
                if (dataReceived == "b")
                {
                    print("Connection Break");
                    break;
                }
                
                print("Received Message:" + dataReceived);
                System.Threading.Thread.Sleep(1000);
                dataReceived="";
            }
        }
    }
}


