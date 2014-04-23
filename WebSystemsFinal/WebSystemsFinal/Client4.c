// Tania Nsouli
// Jian Tang
// PA4
// April 17, 2014
//
// Compile with gcc client4.c -o <execute word>

////////////*** UDP ***/////////////
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#define IP "127.0.0.1"
#define PORT 12345

// function to handle notifying the user of errors
//with the sockets
void err_quit(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(-1); 
}

int main(int argc, char**argv)
{
   int sockfd,n;
   struct sockaddr_in servaddr,cliaddr;
   char sendline[1000];
   char recvline[1000];
   
   sockfd=socket(AF_INET,SOCK_DGRAM,0);  // opens socket
   // if it returns a -1 then it failed to open 
   if (sockfd == -1)
   {   perror("opening socket");
       exit(-1);
   }
   
   // setting up the socket
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=inet_addr(IP);
   servaddr.sin_port=htons(PORT);

   printf("Enter Search Key: ");  // asks the user for a search key
   if(fgets(sendline, 10000,stdin) != NULL)
   {   
      printf("\n\n");
      sendto(sockfd,sendline,strlen(sendline),0,   // send the search key 
             (struct sockaddr *)&servaddr,sizeof(servaddr)); // to the server
      n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);  // then waits for the server
      if(n == -1)				// to find a match for the search key
      {  // if receive returns a -1 then it failed to receive the message
	  err_quit("Nothing Received\n");
      }else{  //otherwise it will print the result found 
          printf("Received from Server %s: \n", IP);
          printf("%s\n\n", recvline);
      }
      recvline[n]=0;
      printf ("Client is done\n");
      close(sockfd);  // then we close the socket and the client is done
   }else{
	printf("Null Argument\n");
   }
   
}