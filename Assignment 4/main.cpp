/*
	References: 
		http://users.cs.cf.ac.uk/Dave.Marshall/C/node27.html
		http://shaunramsey.com/class/resources/450.shm.cpp.txt
*/

#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 

#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include <unistd.h>
#include <iostream>
#include <time.h>

#include <algorithm>   
#include "semaphore.h"
#include "semaphore.cpp"

using namespace std;

/* 4 Semaphores for the 4 variables */
enum {SAVING, CHECKING, PENDING, CURRENT}; 

struct account {
	float savings;
	float checking;
	float pendingBalance;
	float currentBalance;
};

void doChildProcess(SEMAPHORE &sem,account* ptr, int inchoice);
void parentCleanUp(SEMAPHORE &sem, int shmid);

int main()
{	
	int shmid;
		
	/* Allocate shared memory segment */ 
	shmid = shmget(IPC_PRIVATE, sizeof(account), PERMS);	
	
	/* Attach to shared memory segment */
	account* ptr = (account*) shmat(shmid, NULL, 0);

    /* Initialize semaphores to 1 */
    SEMAPHORE sem(4);
	sem.V(SAVING);
	sem.V(CHECKING);
	sem.V(PENDING);
    sem.V(CURRENT);
    
    /* Initialize variables to some non-zero value */
    ptr->savings = 4258.25;
	ptr->checking = 2478.50;
	ptr->pendingBalance = 5696.75;
	ptr->currentBalance = 1243.99;
	
    pid_t pid;

    /* Spawn 10 child processes */
    for (int i = 0; i < 10; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            // ------------ CHILD PROCESS ----------- //

            /* Create unique seed using Child's PID and j count to vary RNG*/
            time_t t;
            srand((int)time(&t) % getpid() * i);

            /* Create and randomize array to vary choice  */
            int nums[4] = {1, 2, 3, 4};
            random_shuffle(nums, nums + 4);
            
            /* Loop Child's Task a finite amount of times */
            for (int j = 0; j < 4; j++)
            {   
                /* Do task */ 
                doChildProcess(sem, ptr, nums[j]);
            }
            
            cout << "Child " << getpid() << " is now exiting... " << endl;
            exit(0);
        }
        else if (pid > 0)
        {
            /* Child has been forked, we are in the parent */

            //--------------- CLEAN-UP SHARED MEMORY & SEMAPHORE -----------------------//    
        
            parentCleanUp(sem, shmid);

            printf("Savings: %f\nChecking: %f\nPending Balance: %f\nCurrent Balance: %f\n", 
                ptr->savings, ptr->checking, ptr->pendingBalance, ptr->currentBalance); 
        }
        else
        {
            /* Error on forking child */
            cout << "Error: Could not fork child. " << endl;
        }
    }

	/* Detach shared memory segment */
	    //shmdt(ptr);
	
	/* Remove shared memory segment */
	    //shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

void doChildProcess(SEMAPHORE &sem, account *ptr, int inchoice)
{

    int choice; float beta;

    //choice = rand() % 4 + 1;
    choice = inchoice;
        
    cout << "Child " << getpid() << " choice is " << choice << endl;

    beta = ((float(rand()) / float(RAND_MAX)) * (0.5 - (-0.5)) + -0.5);
    cout << "Child " << getpid() << " beta value is " << beta << endl;

    switch(choice)
    {
        case 1: /* Access and Modify "Savings" */
                sem.P(SAVING);
                ptr->savings += ptr->savings*beta; // critical section
                sem.V(SAVING);
                break;
        case 2: /* Access and Modify "Checking" */
                sem.P(CHECKING);
                ptr->checking += ptr->checking*beta; // critical section
                sem.V(CHECKING);
                break;
        case 3: /* Access and Modify "Pending Balance" */
                sem.P(PENDING);
                ptr->pendingBalance += ptr->pendingBalance*beta; // critical section
                sem.V(CURRENT);
                break;
        case 4: /* Access and Modify "Current Balance" */  
                sem.P(CURRENT);
                ptr->currentBalance += ptr->currentBalance*beta; // critical section
                sem.V(CURRENT);
                break;
        default: printf("Invalid Choice");
                break;
    }
}

void parentCleanUp(SEMAPHORE &sem, int shmid) 
{
    int status;                     /* child status */
    wait(0);                        /* Wait for child to exit */
    shmctl(shmid, IPC_RMID, NULL);  /* Remove shared memory segment */
    sem.remove();                   /* Remove semaphores */
} 

