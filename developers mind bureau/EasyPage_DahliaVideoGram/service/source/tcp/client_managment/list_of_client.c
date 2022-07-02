void tcp_list_of_clients_initialize()
{
	client_address_length = sizeof(struct sockaddr_in);
	
	tcp_list_of_clients_total_clients_memory = 127;
	tcp_list_of_clients_total_clients_memory_available = tcp_list_of_clients_total_clients_memory;
	
	tcp_list_of_clients_slot_available = (int *)malloc(tcp_list_of_clients_total_clients_memory_available * sizeof(int));
	memset(tcp_list_of_clients_slot_available, 0, tcp_list_of_clients_total_clients_memory_available);
	
	tcp_concurrent_clients = (struct list_of_clients *)malloc(tcp_list_of_clients_total_clients_memory_available * sizeof(struct list_of_clients ) );
	
}

int tcp_list_of_clients_get_available_index()
{
	int output = -1;
	int index = 0;
	while(index < tcp_list_of_clients_total_clients_memory)
	{
		if(tcp_list_of_clients_slot_available[index] == 0)
		{
			output = index;
			
			index = tcp_list_of_clients_total_clients_memory;
		}else{
			index = index + 1;
		}
	}
	
	return output;
}


void tcp_list_of_clients_handle_new_client()
{
	int new_client_file_descriptor = accept(service_socket_filedescriptor, (struct sockaddr *)&new_client_address, &client_address_length); 
	if(new_client_file_descriptor > -1)
	{
		//immediatly set the client socket to non blocking.
		fcntl(new_client_file_descriptor, F_SETFL, O_NONBLOCK);
			
		//determine if there is a concurrent client slot available.
		if(tcp_list_of_clients_total_clients_memory_available > 0)
		{
			//client accepted
			//tell the client they have been accepted.
			write(new_client_file_descriptor, "accepted\n", 9);
				
			//move the client to list of clients management list.
				//find available slot index
				int available_slot_index = tcp_list_of_clients_get_available_index();
				
				//place client within the list of clients array.
				tcp_list_of_clients_slot_available[available_slot_index] = 1;
				tcp_concurrent_clients[available_slot_index].client_address = (struct sockaddr *)new_client_address;
				tcp_concurrent_clients[available_slot_index].client_file_descriptor = (int)new_client_file_descriptor;
				
		}else if(tcp_list_of_clients_total_clients_memory_available <= 0)
		{
			//client not accepted, send "rejected" message.
			write(new_client_file_descriptor, "rejected\n", 9);
				
			//stop transmission and recieve at the tcp network level.
			shutdown(new_client_file_descriptor, SHUT_RDWR);
				
			//release the file descriptor resources
			close(new_client_file_descriptor);
		}
	}
}

