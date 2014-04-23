// Tania Nsouli
// Jian Tang
// PA4
// April 17, 2014
//
// Compile with gcc server4.c -o <execute word>

////////////*** UDP ***/////////////
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define filename "movie.txt"
#define MAXLINE 4096
#define LINEMAX 200
#define PORT 12345

// Error message used for when an error 
// occurs with the sockets
void err_quit(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(-1); 
}

int main(int argc, char**argv)
{
   int sockfd,n;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t len;
   char mesg[1000] = {'\0'};
   FILE* infile;
   char buf[MAXLINE] = {'\0'};
   char msg[LINEMAX] = {'\0'};
   char connect[LINEMAX] = {'\0'};
   //char* convELC;
   int i = 0;

   sockfd=socket(AF_INET,SOCK_DGRAM,0); // opens socket
   if (sockfd == -1) // checks for any errors that may 
   {			// occurred when opening socket
   	perror("opening socket");  // returns -1 if failed
   	exit(-1);
   }
   
   // sets up socket
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(PORT);
   bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

   for (;;) // inifnitely loops to handle multiple clients
   {
      len = sizeof(cliaddr);
      // waits for a client to connect so it may receive data from it (them)
      n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
      printf("Packet received from client\n"); 
      printf("Search Request: %s", mesg); // Prints out the search request sent 
      for(i=0;i<LINEMAX; i++)		    // sent from the server
      {  // looks for a '\n' character and replaces it with a '\0' character
          if(mesg[i] == '\n')    // so that it may match a word in the file
      		mesg[i] = '\0';
      }
      infile = fopen(filename,"r");   //opens file, filename = "movie.txt"
      while(fgets(buf, LINEMAX, infile) != NULL){  // reads the file line by line
	  if(strstr(buf,mesg) != NULL){   //compares the search request with each line 
		strcpy(msg, buf);      // in the file. If match then copies it into an
	 	break;		    // empty char array and breaks from the loop
	  }else{
		strcpy(msg,"No Match found");  //else says there was no match
	  }
      }
      fclose(infile);  //closes the file because we're done
      // then we send to the client and get ready to handle another client
      sendto(sockfd,msg,LINEMAX,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
   }
}