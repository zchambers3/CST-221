//Zack Chambers
//CST-221
//Producer and Consumer
//December 23, 2018

//The approach to this project was to create a project that manages processes
//and threads. The two process in this program are "Producer" and "Consumer".
//To solve the multi-process synchronization problem in which the producer
//and consumer processes share a common fixed-zise bufferused as a queue, I 
//implemented a program that allows the producer to produce data until the
//buffer is full, and then allows the consumer to remove the data until the
//buffer is empty and continue this process in an infinite loop.  To do this,
//I first defined a max for the buffer. After this, I declared the product
//that will be passed into the "insert" variable using the "put" method to
//be incremented until MAX buffer reached. The "signal" method will increment
//the value of the semaphore while the "wait" method will decrement the value.
//The "get" method is called to retrieve the product at the "retreive"
//variable. The "produce" method increments the product forever, or in this
//case until it reaches MAX buffer. The "consume" methods prints the product
//that was consumed. The producer method produces the product to be put in the
//buffer and while loop is used to state that while the buffer is empty
//and mutex equals 1, then produce the product. Once the producer reaches full
//buffer, the "consumer" method steps in and uses a while loop to state that
//while the buffer is full and mutex equals 1, remove the product until the
//buffer is empty.  This cycle is then repeated forever on an infinite loop.

#include <stdio.h>
#include <stdlib.h>

//Max size buffer
#define MAX 100

//Semaphores
int mutex=1, full=0, empty=MAX;

//Product
int theProduct=0;
int insert=0;
int retrieve=0;

//Buffer array
int buffer[MAX];

//Producer and consumer methods declared
void producer();
void consumer();

//Wait decrements value of semaphore
int wait(int semaphore){
return semaphore - 1;
}

//Signal will increment value of semaphore
int signal(int semaphore){
return semaphore + 1;
}

//put will pass in product
void put(int product){
buffer[insert] = product;
insert = (insert + 1) % MAX;
}

//get will return the product
int get(){
int product = buffer[retrieve];
retrieve = (retrieve + 1) %MAX;
return product;
}

//produce will increment the product forever or until it reaches the max.
int produce(){
theProduct++;
return theProduct;
}

//consume will print the product passed in and consumed.
void consume(int product){
printf("Consumed: %d\n", product);
}

//method will produce products and put them into the buffer.
void producer(){
int product;
//While the buffer is empy and mutex equals 1, the method will produce.
while(empty != 0 && mutex == 1){
	product = produce();
	empty = wait(empty);
	mutex = wait(mutex);

	put(product);
	printf("Produced: %d\n", product);

	mutex = signal(mutex);
	full = signal(full);
}

printf("Buffer is full!\n");
theProduct = 0;
consumer();
}

//Method will consume products once buffer is full.
void consumer(){

int product;

while(full != 0 && mutex ==1){

full = wait(full);
mutex = wait(mutex);
product = get();
mutex = signal(mutex);
empty = signal(empty);
consume(product);
}

printf("Buffer is empty!\n");
producer();
;}

//Producer and Consumer begins with the call of the producer function.
int main(){
producer();
return 0;
}
