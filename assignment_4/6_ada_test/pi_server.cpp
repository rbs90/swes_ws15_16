#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = 20001;
	std::cout << "Binding socket..."  << std::endl;

	int status = bind ( create_socket, (struct sockaddr *) &address, sizeof (address)) == 0);
	if (status == -1) {
	  std::cout << "bind error" << std::endl;
	  return status;
    } else { // Connection successfull
    
    
    }
    
    
	return 0; 
}
