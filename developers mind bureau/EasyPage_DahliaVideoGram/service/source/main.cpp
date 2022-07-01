
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <unistd.h>

int  main()
{
	int service_socket_filedescriptor;
	service_socket_filedescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if(service_socket_filedescriptor == -1)
	{
		return -1;
	}
	
	struct sockaddr_in server_address;
	bzero(&server_address, sizeof(server_address)); 
	server_address.sin_family = AF_INET; 
  server_address.sin_addr.s_addr = htonl(INADDR_ANY); 
  server_address.sin_port = htons(8080); 

	int bind_success = bind(service_socket_filedescriptor, (struct sockaddr *)&server_address, sizeof(server_address));
	if(bind_success != 0)
	{
		return -2;
	}
	
	int listen_success = listen(service_socket_filedescriptor, 5);
	
	struct sockaddr_in client_address;
	int client_address_length = sizeof(client_address);
	
	int client_file_descriptor = accept(service_socket_filedescriptor, (struct sockaddr *)&client_address, &client_address_length); 
  char buffer[4095];
	int keep_running = 1;
	while(keep_running == 1)
	{
		printf("reading\n");
		bzero(buffer, 2);
		read(client_file_descriptor, buffer, 1);
		buffer[1] = '\0';
		printf(buffer);
		printf("\n");
	}
	
	
  return 0;
}
