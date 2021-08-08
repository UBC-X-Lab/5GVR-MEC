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

public class PositionServer : MonoBehaviour
{
    //Control fields
    private static int controlPort = 3490;

    Thread focalControl;
    Thread focalTransmit;
    Mutex mut = new Mutex();
    //mut must be locked to read or write any of the below values
    private bool send = false;
    private bool active = false; 
    TimeSpan transmitFrequency = TimeSpan.FromMilliseconds(33);
    DateTime timeout;
    public IPAddress destination = IPAddress.Parse("0.0.0.0");
    public int destinationPort = 3491;
    float transformx;
    float transformy;
    float transformz;


    //Temp?
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
        focalTransmit.Abort();
        focalControl.Abort();
        print("[Position Server] Killed all threads.");
    }

    public void connect(System.Object obj)
    {
        TcpListener control;
        try
        {
            control = new TcpListener(IPAddress.Any, controlPort);
            control.Start();
            while (true)
            {
                print("[Position Server] Waiting for connection.");
                TcpClient client = control.AcceptTcpClient();
                timeout = DateTime.Now.AddSeconds(2);
                mut.WaitOne();
                destination = ((IPEndPoint)(client.Client.RemoteEndPoint)).Address;
                mut.ReleaseMutex();
                print("[Position Server] Connection established with " + destination.ToString());
                NetworkStream stream = client.GetStream();
                focalTransmit = new Thread(new ParameterizedThreadStart(transmit));
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
                    if (send && !active && !focalTransmit.IsAlive)
                    {
                        focalTransmit.Start();
                        Thread.Yield();
                    }
                }
                focalTransmit.Abort();
                client.Close();
                send = false;
                print("[Position Server] Connection timed out.");
            }
        }
        catch (Exception e)
        {
            
        }
    }

    public void transmit(System.Object obj)
    {
        mut.WaitOne();
        active = true;
        mut.ReleaseMutex();
        UdpClient transmitClient = new UdpClient();
        try {
            print("[Position Server] Initializing data transmission to: " + destination.ToString() + ":" + destinationPort + ".");
            transmitClient.Connect(destination, destinationPort);
            print("[Position Server] Started data transmission every " + transmitFrequency.TotalMilliseconds + " milliseconds.");
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
                transmitClient.Send(outData, outData.Length);
                Thread.Sleep(transmitFrequency);
            }
        }catch(ThreadAbortException e)
        {
            print("[Position Server] Stopping data transmission.");
            transmitClient.Close();
            mut.WaitOne();
            active = false;
            mut.ReleaseMutex();
        }
        catch (Exception e)
        {
            print("[Position Server] Server exception: " + e.ToString() + e.StackTrace);
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
        }else if (command.Contains("p"))
        {
            mut.WaitOne();
            destinationPort = num;
            mut.ReleaseMutex();
            send = true;
        }
        else
        {
            print("[Position Server] Unexpected command: " + command);
        }
    }
}
