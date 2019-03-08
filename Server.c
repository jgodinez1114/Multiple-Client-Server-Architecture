/***************************    P2_Server    **************************************
* Programmer: Joel Godinez
*
* Course: CSCI 4354
*
* Date: 7 Mar 2019
*
* Assignment: Program 2
*
* Environment: C with Vim
*
* File: Server.c
*
* Purpose: Create an inter-process communication (IPC) using FIFOS to pass information **back and forth in a multiple client to single server architecture
*
* Input: Request from client with a job name, an array size, an array and a private FIFO name from a client through a FIFO named Common_FIFO
*
* Preconditions/ Assumptions: Client will send integers array, and process id.
*
* Ouput: n/a
*
* Postconditions: Client must send FIFOs in Write Mode
*
* Algorithm:
*           Create the Common_FIFO
*           Prompt user for number of expected clients
*           Open Common_FIFO in READ mode
*           If Common_FIFO not in READ mode
*               Print error message
*           For each client
*               Read job name, array size, array contents
*               Create Private_FIFO
*               Open Private_FIFO
*               Calculate sum of array contents
*               Write calculation to Private_FIFO
*               Close link to Private_FIFO
*               Unlink Private_FIFO
*          Close link to Common_FIFO
*          Unlink Common_FIFO*
*
*/


#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

// Client 1
typedef struct Client1{
	char jobName[10];
	int values[50];
	int totalSum;
    int arrayLength;
} Client1req;

 
main (void)
{
  int fda;    // to read from client
  int fdb;    // to write to client
  int finish;    // lets me know that client is done
  int i;    // because C needs this defined as int
  int clientAmount; // hold client amount
  double result;
  int clients; 

// Structure instances
Client1req c1req;


/* Create the Common_FIFO    */
if ((mkfifo("Common_FIFO",0666)<0 && errno != EEXIST))
    {
    perror("cant create Common_FIFO");
    exit(-1);
    }
wait(NULL);
// Prompt user for number of expected clients
printf("How many clients will communicate today?");
scanf("%d\n",&clientAmount);
fflush(stdin);
printf("%d",clientAmount);
for(i= 0;i<clientAmount;i++){
    // Open Common_FIFO in READ mode
    if((fda=open("Common_FIFO", O_RDONLY))<0)
        printf("cant open fifo to write");

    // read struct
    finish=read(fda, &c1req, sizeof(c1req)); 

    // Open Private_FIFO
    if((fdb=open("Private_FIFO", O_WRONLY))<0)
        printf("cant open fifo to read");

    // calculate sum of array contents
    int total=0; // store the sum value of array contents 
        for (i = 0;i<c1req.arrayLength;i++){
            total += c1req.values[i];
        }
    result = (double) total/c1req.arrayLength;
    
    printf("Your total: %d\n", total);
    // Write sum to Private_FIFO
    write(fdb, &total, sizeof(&total));
    printf("\nServer: Got the result sent");

    // close link to Private_FIFO
    

        
    // if((fda=open("Common_FIFO", O_RDONLY))<0)
    //     printf("cant open fifo to write");
    
    // if((fdb=open("Private_FIFO", O_WRONLY))<0)
    //     printf("cant open fifo to read");
    
   
    close(fdb);    
    unlink("Private_FIFO");
    close(fda);
}
close(fda);
unlink("Common_FIFO");
 
}
 