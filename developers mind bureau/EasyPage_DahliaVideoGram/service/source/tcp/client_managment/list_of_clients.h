int tcp_list_of_clients_total_clients_memory;
int tcp_list_of_clients_total_clients_memory_available;
int * tcp_list_of_clients_slot_available;
int client_address_length;
struct list_of_clients
{
	struct sockaddr_in * client_address;
	int client_file_descriptor;
	char * message_received;
	int message_received_max_length;
};
struct list_of_clients * tcp_concurrent_clients;

char * tcp_list_of_clients_incoming_transmission_buffer;

void tcp_list_of_clients_initialize();

int tcp_list_of_clients_get_available_index();

void tcp_list_of_clients_handle_new_client();

void tcp_list_of_clients_handle_incoming_transmission();
