/***********************    P2_Server    **************************************
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
*               Write calculation to Pr ivate_FIFO
*               Close link to Private_FIFO
*               Unlink Private_FIFO
*          Close link to Common_FIFO
*          Unlink Common_FIFO
*
*
*
*
*/
