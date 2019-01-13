//Zack Chambers
//CST 221
//January 13, 2019
//John Zupan

//To avoid a deadlock, we must implement certain precautions before a process
//can simply request a recourse. In this program a timer is implemented so
//that the process can request the recourse and wait a certain amount of time,
//in this case a millisecond.  The program will attempt to do this up to four
//time before it is either accepted by the recourse or terminated and forced
//to begin the entire process again.  I wanted to create checkpoints, or
//recourses that need to be requested before the final recourse becomes
//available but was unable to accomplish this task. The same timer would be
//implemented for each checkpoint but when the timeout occurs it would not
//send it to the back of the line but rather that recourse that caused the
//timeout.

#include <pthread.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>

#define MILLION 1000000

void err_abort(int status, char* message) {
	fprintf(stderr, " %s \n ", message);
}

void errno_abort(char* message) {
	perror(message);
	exit(EXIT_FAILURE);
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int counter = 0;

void timer_thread(union sigval arg) {
	int status;

	status = pthread_mutex_lock(&mutex);
	if (status != 0)
		err_abort(status, "Lock Mutex");

	if (++counter >= 5) {
		status = pthread_cond_signal(&cond);

	if (status != 0)
		err_abort(status, "Signal condition");
	}

	status = pthread_mutex_unlock(&mutex);
	if (status != 0)
		err_abort(status, "Unlock mutex");

	printf( "Timer %d \n ", counter);
}

void create_timer(unsigned i) {
	timer_t timer_id;
	int status;
	struct itimerspec ts;
	struct sigevent se;
	long long nanosecs = MILLION * 100 * i * i;

	se.sigev_notify = SIGEV_THREAD;
	se.sigev_value.sival_ptr = &timer_id;
	se.sigev_notify_function = timer_thread;
	se.sigev_notify_attributes = NULL;

	ts.it_value.tv_sec = nanosecs / 1000000000;
	ts.it_value.tv_nsec = nanosecs % 1000000000;
	ts.it_interval.tv_sec = 0;
	ts.it_interval.tv_nsec = 0;

	status = timer_create(CLOCK_REALTIME, &se, &timer_id);
	if (status == -1)
		errno_abort( "Create timer");

	status = timer_settime(timer_id, 0, &ts, 0);
	if (status == -1)
		errno_abort( "Set timer");
}

int main() {
	int status;
	unsigned i = 1;

	for(; i < 6; i++)
		create_timer(i);

	status = pthread_mutex_lock(&mutex);
	if (status != 0)
		err_abort(status, "Lock mutex");

	while (counter < 5) {
		printf( " \tBlocked!\n ");
		status = pthread_cond_wait(&cond, &mutex);
	if (status != 0)
		err_abort(status, "Wait on condition");
		printf( " \tUnblocked!\n ");
	}
	status = pthread_mutex_unlock(&mutex);
	if (status != 0)
		err_abort(status, "Unlock mutex");

	return 0;
}

if(fork() == 0) {
	printf("\nI am in pipe\n");
	execlp("/bin/ls","ls",NULL);
	printf("\nStill in the pipe\n");
}
else {
	fprintf(stderr, "Writing to pipe now\n");
	write(status, buffer, BUFFER_SIZE);
	fprintf(stderr, "Wrote to pipe!");
}
