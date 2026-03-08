#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"

using namespace ns3;

void ReceiveData(Ptr<Socket> socket)
{
    Ptr<Packet> packet;
    while ((packet = socket->Recv()))
    {
        std::cout << "UDP Server received "
                  << packet->GetSize()
                  << " bytes at time "
                  << Simulator::Now().GetSeconds()
                  << " seconds" << std::endl;
    }
}

void SendData(Ptr<Socket> socket, uint32_t size, uint32_t count, Time interval)
{
    if (count > 0)
    {
        socket->Send(Create<Packet>(size));

        Simulator::Schedule(interval,
                            &SendData,
                            socket,
                            size,
                            count - 1,
                            interval);
    }
    else
    {
        socket->Close();
    }
}

int main(int argc, char *argv[])
{
    Time::SetResolution(Time::NS);

    NodeContainer nodes;
    nodes.Create(2);

    PointToPointHelper link;
    link.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    link.SetChannelAttribute("Delay", StringValue("3ms"));

    NetDeviceContainer devices = link.Install(nodes);

    InternetStackHelper stack;
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.2.2.0", "255.255.255.0");

    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    uint16_t port = 9000;

    Ptr<Socket> serverSocket =
        Socket::CreateSocket(nodes.Get(1), UdpSocketFactory::GetTypeId());

    InetSocketAddress local =
        InetSocketAddress(Ipv4Address::GetAny(), port);

    serverSocket->Bind(local);
    serverSocket->SetRecvCallback(MakeCallback(&ReceiveData));

    Ptr<Socket> clientSocket =
        Socket::CreateSocket(nodes.Get(0), UdpSocketFactory::GetTypeId());

    InetSocketAddress remote =
        InetSocketAddress(interfaces.GetAddress(1), port);

    clientSocket->Connect(remote);

    Simulator::Schedule(Seconds(1.5),
                        &SendData,
                        clientSocket,
                        512,
                        8,
                        Seconds(0.8));

    Simulator::Stop(Seconds(12.0));

    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
