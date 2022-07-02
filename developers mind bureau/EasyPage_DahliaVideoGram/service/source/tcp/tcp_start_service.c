void tcp_start_service()
{
	service_socket_filedescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if(service_socket_filedescriptor == -1)
	{
		
	}
	
	bzero(&server_address, sizeof(server_address)); 
	server_address.sin_family = AF_INET; 
  server_address.sin_addr.s_addr = htonl(INADDR_ANY); 
  server_address.sin_port = htons(8080); 

	int bind_success = bind(service_socket_filedescriptor, (struct sockaddr *)&server_address, sizeof(server_address));
	if(bind_success != 0)
	{
		
	}
	
	int listen_success = listen(service_socket_filedescriptor, 5);
	
	//make the service socket non blocking(intended for the accept command to be non blocking)
	fcntl(service_socket_filedescriptor, F_SETFL, O_NONBLOCK);
	
}

