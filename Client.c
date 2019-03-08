/************************       P2_Client.c       ********************************* 
*
* Programmer: Joel Godinez
* 
* Course: CSCI 4354
*
* Date: 7 Mar 2019       
*
* Assignment: Homework 5 (client)
*
* Environment: C with VIM
*
* Files Included: P2_Client.c
*
* Purpose: Create an inter-process communication (IPC) using FIFOS to pass information *back and forth in a multiple client to single server architecture. 
*
* Input: Each client will send a job name, an integer array’s size, and contents, and the client’s private FIFO to the common FIFO.  
*
* Preconditions/ Assumptions: User will use integers array
*
* Output: The calculated result from user’s input received from the server 
*
* Postconditions: Calculation must be accurate
*
* Algorithm:
*		Declare file descriptor variable for writing to server
*		Declare file descriptor variable for read from server
*                        Open the Common_FIFO in WRITE mode 
*                        If Common_FIFO not in WRITE mode
*              	    Print error message
*		Create job name		
*                        Prompt integers and populate the integer array
*		Save user’s inputs
*		Write user’s data, job name, and id as a 1 byte struct to Common_FIFO
*		Read the response from the server from Private_FIFO
If Private_FIFO not in READ mode
*                         	Print error message
*		Display server’s data to the console.
*		Close link to Private_FIFO
*                        Close link to Common_FIFO 
* **************************************************************************************/ 

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

// Client struct
typedef struct Client1{
	char jobName[10];
	char FIFO_Name[15];
    int values[50];
	int arrayLength;
} ClientReq;

//void showResult(CLIENTREQ[1], int);
 
main (void)
{
  int fda,i;    // to write to server
  int fdb;    // to read response from server
  int clientID;  // get client's unique ID
  int finish;
  int total;
//   int intbuff[1];    // buffer holds an int
//   int outint[1];    // server puts string here
//   int result[1];
//   //int arrayToSend[10];    // fill this array 
//   memset(intbuff,0,sizeof(int)); 
//   memset(outint,0,sizeof(int)); 
  
ClientReq c1req;

clientID = getpid();
// get process id and produce string
sprintf(c1req.FIFO_Name, "FIFO_%d", clientID);
printf("\nFIFO name: %s", c1req.FIFO_Name);

// Open Common_FIFO in READ
if((fda=open("Common_FIFO", O_WRONLY))<0)
    printf("cant open fifo to write");

// create Private_FIFO
if ((mkfifo(("%s",c1req.FIFO_Name), 0666)<0 && errno != EEXIST))
    {
    perror("cant create Private_FIFO");
    exit(-1);
    }
 
 
// Open Private_FIFO
if((fdb=open("Private_FIFO", O_RDONLY))<0)
     printf("cant open fifo to read");

printf("Please enter an array length: ");
scanf("%d",&c1req.arrayLength);
fflush(stdin);
printf("This is array length: %d",c1req.arrayLength);

printf("Please enter a job name: ");
scanf("%s",&c1req.jobName);


for(i =0;i<c1req.arrayLength;i++){
printf("Please enter an array value: ");
scanf("%d",&c1req.values[i]);
}
 
 
write(fda, &c1req, sizeof(c1req));
//   printf("\nClient: Got the integer sent, now waiting for response ");
//   read(fdb, &result, sizeof(int));
//   printf("\nClient: received from the server %d", result[0]);

//finish= read(fdb,&total, sizeof(int));
 
  close(fda);
  close(fdb);
 
  printf ("\nall done!\n");
   
}   // end main()
 
 



