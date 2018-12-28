#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
using namespace std;

struct buf
{
	long mtype;
	int data;
};

// Receiver 1 - Receives random multiples of 251 or 997 from the message queue

int main()
{
    cout << "Receiver 1: PID = " << getpid() << endl;

    // Create queue
    int qid = msgget(ftok(".",'u'),IPC_CREAT|0600);

    buf msg;
    int size = sizeof(msg)-sizeof(long);
    bool terminate997 = false;
    bool terminate251 = false;

    while(!terminate251 || !terminate997)
	{
        // Receive messages from queue
		msgrcv(qid, (struct msgbuf *)&msg, size, 111, 0);

		if(msg.data == 0) // Check for Sender 251's acknowledgment of termination
		{
            cout << "Sender 251 has terminated" << endl;
		   terminate251 = true;
        }
		else if(msg.data == 1) // Check for Sender 997's acknowledgment of termination
		{
            // Let Sender 997 know that it's acknowledgement of termination was received
            msg.mtype = 117;
            msg.data = 2;
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);

            cout << "Sender 997 has terminated" << endl;
		   terminate997 = true;
        }
		else if(msg.data == 101) // If we encounter Receiver 2's acknowledgement of termination, send it back.
		{
		    msg.mtype = 111;
		    msgsnd(qid, (struct msgbuf *)&msg, size, 0);
		}
		else if(msg.data % 251 == 0)
			cout << "Received from Sender 251 : " << msg.data << endl;
		else if(msg.data % 997 == 0)
			cout << "Received from Sender 997 : " << msg.data << endl;

	}

    cout << "Receiver 1: terminating..."<<endl;

    // Delete queue
    msgctl(qid,IPC_RMID,NULL);

    exit(0);
}

