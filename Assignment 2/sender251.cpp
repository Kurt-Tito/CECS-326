#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>g
#include <string.h>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include "get_info.h"
using namespace std;

 struct buf
{
    long mtype;
    int data;
};

// Sender 251 sends random multiples of 251 to the message queue

int main()
{
    cout << "Sender 251: PID = " << getpid() << endl;

    // Message queue
    int qid = msgget(ftok(".",'u'),0);

    buf msg;
    int size = sizeof(msg)-sizeof(long);
    srand(time(NULL));
    bool terminate251 = false;
    
    msg.data = 0;
    msg.mtype = 111;

    // Call get_info method from get_info.h file
    get_info(qid, (struct msgbuf *)&msg, size, 111);
    
    //msg.mtype = 25;

    // Terminates by 'kill' command
    //for(;;)
    while(!terminate251)
    {
        // Continuosly generate numbers until we get a number divisble by 251
        msg.data = rand();

        if(msg.data%251 == 0)
        {
        cout << "251 Sent: " << msg.data << endl;

        // Send message to queue
        msgsnd(qid, (struct msgbuf *)&msg, size, 0);
        }
    }

    cout << "Sender 251 Terminated." << endl;

    exit(0);
}

