#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>  //default includes for the socket
#include <cstring>
using namespace std;

int main() {
    // 1. Creating the socket for connection 
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET means IPv4 (it is the code for IPv4)
    // SOCK_STREAM is the indication of TCP as we are using tcp type of transportation 

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(server_fd);
        return 1;
    }
    //writing the server address 
    sockaddr_in address{};//variable or container that stores the elements of an address
    address.sin_family = AF_INET; //this is the type of address I am using(AF_INET means Address family IPv4) 
    address.sin_addr.s_addr = INADDR_ANY; //this is the IP address of the incoming connection, here I have put any IP address so all the IPs can communicate
    address.sin_port = htons(8080);       //this is the port throught which communication is done, here 8080 port

    //the bind fucntion
    if(::bind(server_fd, (struct sockaddr*)&address, sizeof(address))<0){
        perror("bind failed");
        close(server_fd);
        return 1;
    }
    // Now server is attached to port 8080

    //the listen function 
    if(listen(server_fd, 3)<0){
        perror("Listen failed");
        close(server_fd);
        return 1;
    }
    cout << "Server is listening on port 8080,active to receive messages\n";
    //now server is ready to accept the messages incoming

    //the accept function  
    socklen_t addr_len = sizeof(address);  //this is passed so that message size does not exceed limit of the memory in the address
    int client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addr_len);
    if(client_socket < 0){
        perror("Accept failed");
        close(server_fd);
        return 1 ;
    }
    cout << "Client connected!\n";

    //receive the message
    char buffer[1024] = {0}; //stores the message
    int bytes_read=(client_socket, buffer, 1024); //this function reads the message and stores in buffer variable
    if(bytes_read<0){
        perror("Read failed");
    }else{
        buffer[bytes_read]= '\0' ;
        cout << "Received: " << buffer << endl;  // print the message on the terminal 
    }
    // Close sockets
    close(client_socket);
    close(server_fd);

    return 0;
};