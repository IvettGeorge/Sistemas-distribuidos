#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>

#define SERVER_ADDRESS  "10.0.2.15"     /* server IP */
#define PORT            40002

/* Test sequences */
                  /* receive buffer */
 
 
/* This clients connects, sends a text and disconnects */
int main() 
{ 
    int sockfd; 
    struct sockaddr_in servaddr; 
    int lon;
    int n;
    char buf_rx[100]; 
    char buf_txt[100];     
      
    /* Socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    { 
        printf("CLIENT: socket creation failed...\n"); 
        return -1;  
    } 
    else
    {
        printf("Conexion correcta \n"); 
    }
    
    
    memset(&servaddr, 0, sizeof(servaddr));

    /* assign IP, PORT */
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr( SERVER_ADDRESS ); 
    servaddr.sin_port = htons(PORT); 
  
    /* try to connect the client socket to server socket */
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) 
    { 
        printf("connection with the server failed...\n");  
        return -1;
    } 
   
    
    printf("Longitud de la cadena: "); 
    scanf("%i",&lon);
    n=htonl(lon);
    printf("Cadena: ");
    scanf("%s",&buf_txt);
    
    write(sockfd, (char *)&n, sizeof(buf_txt)); 
    write(sockfd, buf_txt, sizeof(buf_txt)); 
 
  
    read(sockfd, (char *)&n,  sizeof(buf_txt));
    int lon2=ntohl(n);
     printf("El servidor dice: %i",lon);
     
     
    read(sockfd, buf_rx, sizeof(buf_rx));
     printf( "%s",buf_rx); 
    
   
       
    /* close the socket */
    close(sockfd); 
} 
