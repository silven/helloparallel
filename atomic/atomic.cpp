#include <stdio.h>
#include <unistd.h>
#include <thread>

void producer() {
	printf("I am the producer\n");
}

void consumer() {
	printf("I am the consumer\n");
}


int main(void) {
    printf("Hello atomic\n");
    
    std::thread pThread(producer);
    std::thread cThread(consumer);
    
    pThread.join();
    cThread.join();
    return 0;
}

