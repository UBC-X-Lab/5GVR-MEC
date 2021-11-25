using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Text;
using OVR.OpenVR;
using System.Xml;
using System.Text.RegularExpressions;

public class PositionSender : MonoBehaviour
{
    
    Thread focalControl;
    Thread focalTransmit;
    Mutex mut = new Mutex();
    //mut must be locked to read or write any of the below values
    private bool send = false;
    private bool active = false;
    public String ServerAddrAsString = "10.249.146.111";
    private IPAddress serverAddr = IPAddress.Parse("10.249.146.111");
    public int controlPort = 27870;

    TimeSpan transmitFrequency = TimeSpan.FromMilliseconds(33);
    DateTime timeout;
    
    public IPAddress destination = IPAddress.Parse("0.0.0.0");
    public int StreamPort = 27871;
    public bool isTCP = false;
    float transformx;
    float transformy;
    float transformz;
    
    static Encoding enc8 = Encoding.UTF8;

    // Start is called before the first frame update
    void Start()
    {
        focalControl = new Thread(new ParameterizedThreadStart(connect));
        focalControl.Start();
    }

    // Update is called once per frame
    void Update()
    {
        mut.WaitOne();
        transformx = transform.forward.x;
        transformy = transform.forward.y;
        transformz = transform.forward.z;
        mut.ReleaseMutex();
        //print("x " + transform.forward.x);
        //print("y " + transform.forward.y);
        //print("z " + transform.forward.z);
    }

    private void OnDestroy()
    {
        if (active) {
            focalTransmit.Abort();
        }
        if (send) {
            focalControl.Abort();
        }
        print("[Position Sender] Killed all threads.");
    }

    public void connect(System.Object obj) {
        TcpClient client;
        while(true) {
            try {
                // This constructor automatically attempts connection for us
                serverAddr = IPAddress.Parse(ServerAddrAsString);
                print("[Position Sender] Connecting to " + serverAddr.ToString() + ":" + controlPort);
                client = new TcpClient(serverAddr.ToString(), controlPort);
                print("[Position Sender] Connection established");

                NetworkStream stream = client.GetStream();

                /* Check to see if the stream is actually working.
                If this is e.g. a SSH tunnel that fails to connect to the backend, this will crash. */
                stream.Write(new byte[] { 0 }, 0, 1);
                stream.Flush();
                {
                    byte[] command = new byte[1024];
                    int size = stream.Read(command, 0, command.Length);
                    print("[Position Sender] Connection appears live: " + size);
                }

                mut.WaitOne();
                // update address for upd connection (could just use serverAddr, but want to reduce refactoring
                destination = serverAddr;
                mut.ReleaseMutex();

                Thread.Sleep(500);

                focalTransmit = new Thread(new ParameterizedThreadStart(transmit));
                focalTransmit.Start();

                timeout = DateTime.Now.AddSeconds(2);
                
                while (client.Connected && DateTime.Now < timeout)
                {
                    while (stream.CanRead && stream.DataAvailable)
                    {
                        mut.WaitOne();
                        timeout = DateTime.Now.AddSeconds(2);
                        mut.ReleaseMutex();
                        byte[] command = new byte[1024];
                        stream.Read(command, 0, command.Length);
                        handleInput(enc8.GetString(command));
                    }
                    //if (send && !active && !focalTransmit.IsAlive)
                    //{
                    //focalTransmit.Start();
                    //Thread.Yield();
                    //}
                }
                // close connection
                focalTransmit.Abort();
                client.Close();
                send = false;
                print("[Position Sender] Connection timed out.");
                break;
            } catch (Exception e) {
                print("[Position Sender] connection was not established: " + e);
                Thread.Sleep(500);
                print("[Position Sender] retrying");
            }
        }
    }

    public void transmit(System.Object obj)
    {
        mut.WaitOne();
        active = true;
        mut.ReleaseMutex();
        // cant find an abstract class to use a single object so creating two and then only connet one
        TcpClient transmitClientTCP = new TcpClient(destination.ToString(), StreamPort);
        UdpClient transmitClientUDP = new UdpClient();
        NetworkStream TCPStream = null;
        
        try
        {
            print("[Position Sender] Initializing data transmission to: " + destination.ToString() + ":" + StreamPort + ".");
            if (isTCP) {
                TCPStream= transmitClientTCP.GetStream();
            } else {
                transmitClientUDP.Connect(destination, StreamPort);
            }
            print("[Position Sender] Started data transmission every " + transmitFrequency.TotalMilliseconds + " milliseconds.");
            while (true)
            {
                mut.WaitOne();
                float rotx = transformx;
                float roty = transformy;
                float rotz = transformz;
                mut.ReleaseMutex();
                byte[] out1 = BitConverter.GetBytes(rotx);
                byte[] out2 = BitConverter.GetBytes(roty);
                byte[] out3 = BitConverter.GetBytes(rotz);
                Byte[] outData = new byte[out1.Length + out2.Length + out3.Length];
                Buffer.BlockCopy(out1, 0, outData, 0, out1.Length);
                Buffer.BlockCopy(out2, 0, outData, out1.Length, out2.Length);
                Buffer.BlockCopy(out3, 0, outData, out1.Length + out2.Length, out3.Length);
                if (isTCP) {
                    TCPStream.Write(outData, 0, outData.Length);
                } else {
                    transmitClientUDP.Send(outData, outData.Length);
                }
                Thread.Sleep(transmitFrequency);
            }
        }

        catch (ThreadAbortException e)
        {
            print("[Position Sender] Stopping data transmission.");
            transmitClientTCP.Close();
            transmitClientUDP.Close();
            mut.WaitOne();
            active = false;
            mut.ReleaseMutex();
        }
        catch (Exception e)
        {
            print("[Position Sender] Sender exception: " + e.ToString() + e.StackTrace);
        }
    }

    public void handleInput(String command)
    {
        int num = Int32.Parse(Regex.Match(command, @"\d+").Value);
        if (command.Contains("r"))
        {
            mut.WaitOne();
            transmitFrequency = TimeSpan.FromMilliseconds(num);
            mut.ReleaseMutex();
        }
        else if (command.Contains("p"))
        {
            // mut.WaitOne();
            // StreamPort = num;
            // mut.ReleaseMutex();
            // send = true;
        }
        else
        {
            print("[Position Sender] Unexpected command: " + command);
        }
    }
}