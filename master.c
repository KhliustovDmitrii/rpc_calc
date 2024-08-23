/*********************************************\
 * MASTER part of program
 * Works with client and calc hosts
 * 1. CREATE passive socket for new connections
 * 2. CREATE calc_host list
 * 3. ACCEPT connection. 
 * 4. Call processing procedure
\*********************************************/

#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server_proc.c"

#define QLEN 32 //Length of request queue

void TCP_process_request(int);
void reaper(int);

int main(int argc, char **argv)
{
   printf("------------------------------- SERVER PROGRAM STARTED -------------------------------\n");
   struct sockaddr_in fsin;
   int msock, ssock;
   unsigned int alen;
   
   (void) signal(SIGCHLD, reaper);
   
   //+++++++ 1
   msock = passiveTCP(QLEN);
   if(msock < 0)
   {
      fprintf(stderr, "Could not create passive socket\n");
      exit(1);
   }
   else
      printf("Passive socket create - complete\n\n\n");
      
   alen = sizeof(fsin);
   
   //+++++++ 2
   create_host_list();
   
   while(1)
   {  
      //+++++++ 3
      ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
      if(ssock < 0)
      {
         fprintf(stderr, "Could not accept connection\n");
         exit(1);
      }
      else
         printf("Connection accept - complete\n\n\n");
         
      //+++++++ 4
      TCP_process_request(ssock);
      (void) close(ssock);
   }
   
   return 0;
}

//------------------------------- BOTTOM OF THE FILE -------------------------------
