# Single Client Chatting using TCP and UDP in ns-3

## Overview
This project demonstrates single client-server communication using TCP and UDP protocols in the ns-3 network simulator.

Two nodes are created and connected using a point-to-point link. One node acts as a client and the other as a server. The client sends packets to the server and the server receives them during the simulation.

## Technologies Used
- Network Simulator: ns-3
- Programming Language: C++
- Operating System: Linux

## Files Included
- `tcp-client-server.cc` – Implementation of client-server communication using TCP.
- `udp-client-server.cc` – Implementation of client-server communication using UDP.

## Network Configuration
- Number of nodes: 2
- Link type: Point-to-Point
- Data rate: 5–10 Mbps
- Channel delay: 2–3 ms
- Packet size: 512–1024 bytes
- Simulation time: ~10 seconds

## How to Run

Navigate to the ns-3 directory and run the following commands:
