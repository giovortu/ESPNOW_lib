/*
Etienne Arlaud
*/

#include <stdint.h>
#include <stdio.h>

#include <assert.h>
#include <unistd.h>
#include <sys/time.h>

#include <thread>

#include "ESPNOW_manager.h"
#include "ESPNOW_types.h"


#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

using namespace std;

static uint8_t my_mac[6] = {0x84, 0xC9, 0xB2, 0x81, 0xE3, 0xAF};
static uint8_t broadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

ESPNOW_manager *handler;

uint8_t payload[127];

void callback(uint8_t src_mac[6], uint8_t *data, int len) 
{
    handler->mypacket.wlan.actionframe.content.length = 127 + 5;
    char buffer[250];
    memset( buffer, '\0', 250 );
    memcpy( buffer , data, len);
    printf("%s\n", buffer );
}

void *myThreadFunction(void *arg) {
    printf("Starting\n");


    handler = new ESPNOW_manager((char*)arg, DATARATE_24Mbps, CHANNEL_freq_1, my_mac, broadcast, false);
    //handler->set_filter(ESP_mac, dest_mac);
    handler->set_recv_callback(&callback);
    handler->start();

    while(1 ) sleep(1);
}



int main(int argc, char **argv) 
{

    int value = 42; 
    pthread_t myThread;

    // Create a thread and run myThreadFunction
    if (pthread_create(&myThread, NULL, myThreadFunction, (void *)argv[1]  ) ) {
        perror("Thread creation failed");
        return 1;
    }

    // Code running in the main thread while the other thread is running
    printf("Main thread is running\n");

    // Wait for the thread to finish
    if (pthread_join(myThread, NULL) != 0) {
        perror("Thread join failed");
        return 1;
    }

    printf("Thread has finished\n");

    return 0;

    handler->end();
}


