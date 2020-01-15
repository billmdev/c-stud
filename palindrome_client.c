
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
    struct sockaddr_in client; 
    int s, flag; 
    char buffer[20]; 
  
    // socket create 
    s = socket(AF_INET, SOCK_STREAM, 0); 
  
    // assign IP, PORT 
    client.sin_family = AF_INET; 
    client.sin_port = 2000; 
    client.sin_addr.s_addr = inet_addr("127.0.0.1"); 
  
    // connect the client socket to server socket 
    connect(s, (struct sockaddr*)&client, sizeof client); 
  
    for (;;) { 
        printf("\nEnter a string to check palindrome: "); 
        scanf("%s", buffer); 
  
        printf("\nClient: %s", buffer); 
        send(s, buffer, sizeof(buffer), 0); 
        recv(s, &flag, sizeof(int), 0); 
  
        if (flag == 1) { 
            printf("\nServer: The string is a Palindrome.\n"); 
            break; 
        } 
        else { 
            printf("\nServer: The string is not a palindrome.\n"); 
            break; 
        } 
    } 
  
    // close the socket 
    close(s); 
} 

