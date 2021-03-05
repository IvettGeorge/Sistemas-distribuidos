#include <unistd.h>  

/* sockets */
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h> 
#include <string.h> 

/* server parameters */
#define SERV_PORT       40002             
#define SERV_HOST_ADDR "10.0.2.15"     
#define BUF_SIZE        100           
#define BACKLOG         5             

int main(int argc, char* argv[])          /* input arguments are not used */
{ 
    int sockfd, connfd ;  /* listening socket and connection socket file descriptors */
    unsigned int len;     /* length of client address */
    struct sockaddr_in servaddr, client; 
    int n, lon;
    int  len_rx, len_tx = 0;                     /* received and sent length, in bytes */
    char buff_tx[BUF_SIZE] = "Servidor conectado";
    char buff_rx[BUF_SIZE];   /* buffers for reception  */
    
     
    /* socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    { 
        fprintf(stderr, "Fallo la conexion %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
       // printf("[SERVER]: Socket successfully created..\n"); 
    }
    
    /* clear structure */
    memset(&servaddr, 0, sizeof(servaddr));
  
    /* assign IP, SERV_PORT, IPV4 */
    servaddr.sin_family      = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR); 
    servaddr.sin_port        = htons(SERV_PORT); 
    
    
    /* Bind socket */
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) 
    { 
        fprintf(stderr, "[SERVER-error]: socket bind failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
        //printf("[SERVER]: Socket successfully binded \n");
    }
  
    /* Listen */
    if ((listen(sockfd, BACKLOG)) != 0) 
    { 
        fprintf(stderr, "[SERVER-error]: socket listen failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
       printf("Conectado al puerto: %d \n\n", ntohs(servaddr.sin_port) ); 
    }
    
    len = sizeof(client); 
  
      /* Accept the data from incoming sockets in a iterative way */
      while(1)
      {
        connfd = accept(sockfd, (struct sockaddr *)&client, &len); 
        if (connfd < 0) 
        { 
           // fprintf(stderr, "[SERVER-error]: connection not accepted. %d: %s \n", errno, strerror( errno ));
            return -1;
        } 
        else
        {              
           
                /* read client message, copy it into buffer */
                read(connfd, (char *)&n, sizeof(buff_tx));
                len_rx = (read(connfd, buff_rx, sizeof(buff_rx)));
                lon=ntohl(n);  
                lon=lon+1;
                
                printf("ingrse %i caracteres: ",lon ); 
                scanf("%s",&buff_rx);
                
                n=htonl(lon);
                write(connfd, (char *)&n, sizeof(buff_tx));
                write(connfd, buff_rx, sizeof(buff_rx));
                  
                  
                close(connfd);
                  
                
                }            
             
        }                      
       
} 
