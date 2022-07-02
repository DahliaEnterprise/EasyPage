int tcp_list_of_clients_total_clients_memory;
int tcp_list_of_clients_total_clients_memory_available;
int * tcp_list_of_clients_slot_available;
int client_address_length;
struct list_of_clients
{
	struct sockaddr_in * client_address;
	int client_file_descriptor;
};
struct list_of_clients * tcp_concurrent_clients;
struct sockaddr_in * new_client_address;

void tcp_list_of_clients_initialize();

int tcp_list_of_clients_get_available_index();

void tcp_list_of_clients_handle_new_client();
