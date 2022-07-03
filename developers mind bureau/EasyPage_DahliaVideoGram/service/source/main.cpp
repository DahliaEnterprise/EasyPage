
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>


#include "/root/dahliavideogram/baseline_and_supposedly_static_biditectional_communication/service/source/tcp/tcp_start_service.h"
#include "/root/dahliavideogram/baseline_and_supposedly_static_biditectional_communication/service/source/tcp/client_management/list_of_clients.h"


#include "/root/dahliavideogram/baseline_and_supposedly_static_biditectional_communication/service/source/tcp/tcp_start_service.c"
#include "/root/dahliavideogram/baseline_and_supposedly_static_biditectional_communication/service/source/tcp/client_management/list_of_clients.c"


int main()
{
	tcp_start_service();
	
	tcp_list_of_clients_initialize();

	//Main loop(manager loop(?))
	int keep_running = 1;
	while(keep_running == 1)
  {
		
		//manage a new client connection
	tcp_list_of_clients_handle_new_client();
		
		//execute actions pushed to the actions item list
		//todo
		
		//read from list of client sockets into their respective buffers
		tcp_list_of_clients_handle_incoming_transmission();
		
		//write to list of client sockets from their respective buffers.
	
	}
	
	
  return 0;
}
