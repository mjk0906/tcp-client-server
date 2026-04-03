#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <cstring>
using namespace std;

int main() {
    //creating the same socket in client also
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock<0){
        perror("Socket creation failed");
        return 1;
    }
    //again give the address of the server
    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_len = sizeof(serv_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    //internet presentation to network(inet_pton) , (domain,ip of the server in string form,variable to store ip in string form)
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){
        perror("Invalid address/Address connection failed");
        close(sock);
        return 1;
    }
    // 127.0.0.1 = localhost

    //connect function to connect with the server,again size is given for the memory limit
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    //message and send function to send the message 
    string msg = "Hello Server";
    ssize_t bytes_sent = send(sock, msg.c_str(), msg.size(), 0);
    if(bytes_sent<0){
        perror("Send failed");
    }else{
        cout << "Message sent!\n";  //prints the message sent statement
    }
    //Close socket
    close(sock); //as there is only single socket here,it is only closed

    return 0;
};