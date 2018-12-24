//Zack Chambers
//CST-221
//Monitors and Semaphores
//December 23, 2018

//Synchronization mechanisms are needed in a program to ensure that two 
//or more concurrent processes or threads do not simultaneously execute in the
//critical section. The reason that semaphores and monitors are needed is
//because multi-threaded applications must control how threads access shared
//resources and ensure that threads work well together. If applications do
//not control the threads, then it can result in corruption of data and other
//problems. Monitors and semaphores are both use to accomplish thread
//synchronization. Monitors contain a set of multiple routines that are
//protected by a mutex or mutual exclusion lock. None of the routines in
//in the monitor can be executed by a thread until that thread acquires the
//lock. This allows one thread to be executed at a time. A semaphore is a
//simpler contruct because it is a lock that protects a shared resource rather
//than a set of routines. The application must acquire the lock before using
//the shred resource that is protected by a semaphore.  When deciding which to
//use, it depends on the application and the language being used. Normally a
//desktop application would use monitors since monitors leave less
//possibilities for mistakes.  However, the downside is that monitors would
//leave a larger structure. Semaphores are often used in OS's since they are
//a lightweight structure. However, semaphores provide more room for mistakes
//since every routine accessing a shared resource has to explicitly acquire
//a lock before using the resource which can easily be forgotten when coding
//the routines.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

//Max Buffer
#define BufferSize 10

//Methods to procedure and consume numbers
void *Producer();
void *Consumer();

//First position of the number increment
int BufferIndex=0;
char *BUFFER;

//Condition Variable initialize
pthread_cond_t Buffer_Not_Full=PTHREAD_COND_INITIALIZER;
pthread_cond_t Buffer_Not_Empty=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mVar=PTHREAD_MUTEX_INITIALIZER;

int main(){

	//Create thread variables
	pthread_t ptid,ctid;

	//Allocates the requested memory and returns a pointer to it.
	BUFFER=(char *) malloc(sizeof(char) * BufferSize);

	//Thread creation
	pthread_create(&ptid,NULL,Producer,NULL);
	pthread_create(&ctid,NULL,Consumer,NULL);

	//Suspend execution of the calling thread until the target thread
	//terminates, unless target thread is already terminated.
	pthread_join(ptid,NULL);
	pthread_join(ctid,NULL);

	return 0;
}

//Producer method to produce products for the buffer

void *Producer(){

	//Infinite loop
	for(;;){

		//The mutex object is locked, if the mutex is alread locked,
		//the calling thread blocks until the mutex becomes available.
		pthread_mutex_lock(&mVar);
		if(BufferIndex==BufferSize){

		pthread_cond_wait(&Buffer_Not_Full,&mVar);

		}

		BUFFER[BufferIndex++]='@';
		printf("Produce : %d \n",BufferIndex);
		pthread_mutex_unlock(&mVar);
		pthread_cond_signal(&Buffer_Not_Empty);
	}
}

//Consumer method to consume the producer
void *Consumer(){

	//Infinite loop
	for(;;){

		//Mutex lock until the mutex becomes available
		pthread_mutex_lock(&mVar);
		if(BufferIndex==-1){

		pthread_cond_wait(&Buffer_Not_Empty,&mVar);

	}

		printf("Consume : %d \n",BufferIndex--);
		pthread_mutex_unlock(&mVar);
		pthread_cond_signal(&Buffer_Not_Full);

	}

}
