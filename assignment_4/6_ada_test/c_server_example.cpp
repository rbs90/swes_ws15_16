#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define BUF 2

using namespace std;

int main (void) {
  int create_socket, new_socket;
  socklen_t addrlen;

  char *buffer = (char*) malloc (BUF);

  ssize_t size;
  struct sockaddr_in address;
  const int y = 1;

  int led_pins[] = {2,3,4,7,8,9,10,11}; 

  if ((create_socket = socket (AF_INET, SOCK_STREAM, 0)) > 0)
    cout << "socket created..." << endl;

  setsockopt( create_socket, SOL_SOCKET,
              SO_REUSEADDR, &y, sizeof(int));

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons (20001);

  if (bind ( create_socket,
             (struct sockaddr *) &address,
             sizeof (address)) != 0) {
    cout << "Port is in use. Exiting!" << endl;
	return -1;
  }

  listen (create_socket, 5);

  addrlen = sizeof (struct sockaddr_in);
  new_socket = accept ( create_socket,
               (struct sockaddr *) &address,
               &addrlen );

  if (new_socket > 0) {
  	cout << "client connected: " << inet_ntoa (address.sin_addr) << endl;
	for (int i = 0; i < 10; i++) {
 	    size = recv (new_socket, buffer, 2, 0);
		int data = buffer[1] + (buffer[0] << 8);	    
		bool leds[10];

		for(int k = 0; k < 8; k++)
		{
		    leds[k] = (buffer[0] >> k) & 1;
		}

		leds[8] = buffer[1] & 1;
		leds[9] = (buffer[1] >> 1) & 1;
	 } 
	 close (new_socket);
  }
  return EXIT_SUCCESS;
}
