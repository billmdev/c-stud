
// defines in_addr structure 
#include <arpa/inet.h> 
  
// contains constants and structures 
// needed for internet domain addresses 
#include <netinet/in.h> 
  
// standard input and output library 
#include <stdio.h> 
  
// contains string functions 
#include <string.h> 
  
// for socket creation 
#include <sys/socket.h> 
  
// contains constructs that facilitate getting 
// information about files attributes. 
#include <sys/stat.h> 
  
// contains a number of basic derived types 
// that should be used whenever appropriate 
#include <sys/types.h> 
  
main() 
{ 
    struct sockaddr_in client, server; 
    int s, n, sock, g, j, left, right, flag; 
    char b1[20], b2[10], b3[10], b4[10]; 
  
    // creating socket 
    s = socket(AF_INET, SOCK_STREAM, 0); 
  
    // assign IP, PORT 
    server.sin_family = AF_INET; 
  
    // this is the port number of running server 
    server.sin_port = 2000; 
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
  
    // Binding newly created socket 
    // to given IP and verification 
    bind(s, (struct sockaddr*)&server, sizeof server); 
    listen(s, 1); 
    n = sizeof client; 
  
    sock = accept(s, (struct sockaddr*)&client, &n); 
    for (;;) { 
        recv(sock, b1, sizeof(b1), 0); 
  
        // whenever a request from a client came. 
        // It will be processed here. 
        printf("\nThe string received is:%s\n", b1); 
        if (strlen(b1) == 0) 
            flag = 1; 
        else { 
            left = 0; 
            right = strlen(b1) - 1; 
            flag = 1; 
            while (left < right && flag) { 
                if (b1[left] != b1[right]) 
                    flag = 0; 
                else { 
                    left++; 
                    right--; 
                } 
            } 
        } 
        send(sock, &flag, sizeof(int), 0); 
        break; 
    } 
    close(sock); 
  
    // close the socket 
    close(s); 
} 

