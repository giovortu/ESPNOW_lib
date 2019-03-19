/*
Etienne Arlaud
*/

#include <stdint.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/time.h>

#include "ESPNOW_handler.h"
#include "ESPNOW_types.h"
						
static uint8_t my_mac[6] = {0xF8, 0x1A, 0x67, 0xb7, 0xEB, 0x0B};
static uint8_t dest_mac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static uint8_t ESP_mac[6] = {0xB4,0xE6,0x2D,0xB5,0x9F,0x85};

ESPNOW_handler *handler;

ESPNOW_packet mypacket;

void callback(uint8_t src_mac[6], uint8_t *data, int len) {
	memcpy(mypacket.wlan.actionframe.content.payload, data, 4);
	handler->send(mypacket);
}

int main(int argc, char **argv) {

	for(int i=0;i<250;i++) {
		mypacket.wlan.actionframe.content.payload[i] = 0x15;
	}
	
	mypacket.wlan.actionframe.content.length = 0xff;

	mypacket.set_channel(CHANNEL_freq_11);
	mypacket.set_datarate(DATARATE_54Mbps);
	mypacket.set_dst_mac(dest_mac);
	
	handler = new ESPNOW_handler("wlp5s0", dest_mac);

	handler->set_filter(ESP_mac, dest_mac);

	handler->set_recv_callback(&callback);

	handler->start();

	while(1) {
		sleep(1);
	}

	handler->end();
}
