# tcp-client-server
this is part of my app,Heuristics and Networks guild IITM 

This project demonstrates a simple TCP client-server communication using sockets in C++.

## Features
- Server binds to port 8080
- Server listens for incoming connections
- Client connects to localhost (127.0.0.1)
- Client sends "Hello Server"
- Server receives and prints the message

## How to Run

1. Compile:
   g++ server.cpp -o server
   g++ client.cpp -o client

2. Run server:
   ./server

3. Run client in another terminal:
   ./client

## Output
Server:
Client connected!
Received: Hello Server

Client:
Message sent!
