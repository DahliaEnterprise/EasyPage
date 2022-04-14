
//prerequisite
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <time.h>

//nanosleep requires implicit header delcaration.
int nanosleep(const struct timespec *req, struct timespec *rem);

//shasta exchange headers

//shasta exchanbe definitions
#include "./produce_available_index_of_list_of_client_connection_slots/produce_available_index_of_list_of_client_connection_slots.c"

//global variables
  //service connection
  int server_socket_filedescriptor;
  
  //framed message segment
  char framed_message_segment[1023]; //setting to 1024 is presumed to allocate within ram the amount of 1023+minimum next ram slot available. its probly just 1023 plus 8 bytes on a 64 bit ram configuration.

  //flag of whole message completed.
  char whole_message_transmitted_flag[41];

  //constant time period
  struct timespec time_to_suspend_shasta_exchange_iteration_remaining;
  struct timespec time_to_suspend_shasta_exchange_iteration_request;


//entry to program.
int main()
{
  //initate socket
  server_socket_filedescriptor = -1;
  server_socket_filedescriptor = socket(AF_INET, SOCK_STREAM, 0);
    //determine socket is handable by variable.
    if(server_socket_filedescriptor == -1)
    {
      printf("socket() problems. \n");
      return -1;
    }
    
    //define server socket as non blocking.
    fcntl(server_socket_filedescriptor, F_SETFL, O_NONBLOCK);
    
  //initiate the server address details (majority)ram location storage.
  struct sockaddr_in server_address;
    //zero the server address sockadd_in structure.
    memset(&server_address, 0, sizeof(server_address));
    
    //define parameters pertaining to "server_address".
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(3456);
    memset(server_address.sin_zero, 0, 8);
   
  //bind (network inout)file with server address information. (alert the network card with what to do with this file)
  int bind_return_code = bind(server_socket_filedescriptor, (struct sockaddr *)&server_address, sizeof(struct sockaddr));
  if(bind_return_code != 0)
  {
   printf("bind() %s \n", strerror(errno));
   return -2;
  }
  
  //enable listening functioning.
  int listen_return_code = listen(server_socket_filedescriptor, 5);
  if(listen_return_code != 0)
  {
    printf("listen() \n");
    return -3;
  }
  
  //zero the framed message segment.
  memset(framed_message_segment, 0, 1024);
  
  //zero the whole_message_transmitted_flag
  memset(whole_message_transmitted_flag, 0, 32);
  
  //define the whole message transmitted flag.
  whole_message_transmitted_flag[0] = '1';
  whole_message_transmitted_flag[1] = 'B';
  whole_message_transmitted_flag[2] = '4';
  whole_message_transmitted_flag[3] = '8';
  whole_message_transmitted_flag[4] = '0';
  whole_message_transmitted_flag[5] = '1';
  whole_message_transmitted_flag[6] = '5';
  whole_message_transmitted_flag[7] = '8';
  whole_message_transmitted_flag[8] = 'E';
  whole_message_transmitted_flag[9] = '1';
  whole_message_transmitted_flag[10] = 'F';
  whole_message_transmitted_flag[11] = '3';
  whole_message_transmitted_flag[12] = '0';
  whole_message_transmitted_flag[13] = 'E';
  whole_message_transmitted_flag[14] = '0';
  whole_message_transmitted_flag[15] = 'B';
  whole_message_transmitted_flag[16] = '6';
  whole_message_transmitted_flag[17] = 'C';
  whole_message_transmitted_flag[18] = 'E';
  whole_message_transmitted_flag[19] = 'E';
  whole_message_transmitted_flag[20] = '7';
  whole_message_transmitted_flag[21] = '8';
  whole_message_transmitted_flag[22] = '1';
  whole_message_transmitted_flag[23] = '3';
  whole_message_transmitted_flag[24] = 'E';
  whole_message_transmitted_flag[25] = '9';
  whole_message_transmitted_flag[26] = 'E'; 
  whole_message_transmitted_flag[27] = 'C';
  whole_message_transmitted_flag[28] = 'F';
  whole_message_transmitted_flag[29] = '0';
  whole_message_transmitted_flag[30] = '9';
  whole_message_transmitted_flag[31] = '4';
  whole_message_transmitted_flag[32] = 'B';
  whole_message_transmitted_flag[33] = 'D';
  whole_message_transmitted_flag[34] = '6';
  whole_message_transmitted_flag[35] = 'B';
  whole_message_transmitted_flag[36] = '3';
  whole_message_transmitted_flag[37] = '7';
  whole_message_transmitted_flag[38] = '4';
  whole_message_transmitted_flag[39] = '5';
  whole_message_transmitted_flag[40] = '\0';
  
  //begin shasta exchange iteration of trigger based automated work.
    //initialize temporary array to account for connections and their associated states.
      //define a number to be used within a manner consensus pertaining to concurrent connections
      unsigned short int size_of_concurrent_connections = 1024;
      
      //initialize and zero an array of client socket file descriptors.
      int * list_of_client_socket_file_descriptors = (int *)malloc(size_of_concurrent_connections * sizeof(int));
      memset(list_of_client_socket_file_descriptors, 0, size_of_concurrent_connections);
    
      //initialize and zero an array of client address info.(this/these address infor handles signal the network card that the program has not let go)
      struct sockaddr_in * list_of_client_address_info = (struct sockaddr_in *)malloc(size_of_concurrent_connections * sizeof(struct sockaddr_in));
      memset(list_of_client_address_info, 0, size_of_concurrent_connections);
      
      //initialize and zero an array of flags that indicate which associated data slots are being used by the program or are available.
      unsigned short int * list_of_flags_indicating_active_clients = (unsigned short int *)malloc(size_of_concurrent_connections * sizeof(unsigned short int));
      memset(list_of_flags_indicating_active_clients, 0, size_of_concurrent_connections);
      
      //initialize and set count of active clients. (this reduces a need for counting every check, necessary efficiency).
      unsigned short int current_total_active_clients = 0;
    
    //initialize temporary holder for newly accepted connections.
    int temporary_socket_file_descriptor = -1;
    struct sockaddr_in client_address_information;
    socklen_t length = 0;
    
    //do begin while loop
    printf("Shasta Exchange\n");
    time_to_suspend_shasta_exchange_iteration_request.tv_nsec = 10000000; //ten miliseconds.
    
    int shasta_exchange_iteration_continue_loop = 1;
    while(shasta_exchange_iteration_continue_loop == 1)
    {
     //determine if a connection is awaiting to be accepted.
     temporary_socket_file_descriptor = accept(server_socket_filedescriptor, (struct sockaddr *)&client_address_information, &length);
     if(temporary_socket_file_descriptor < 0)
     {
      // printf("accept() %s \n", strerror(errno));
       
     }else{
       //set this client socket as not blocking immediately, as to not be required to do so just before the accept command.
       fcntl(temporary_socket_file_descriptor, F_SETFL, O_NONBLOCK);
    
       
       //Has the maximum amount of concurrent users been reached?
       if(current_total_active_clients >= size_of_concurrent_connections)
       {
         //tell the (presumably php script) that the total concurrent connections has been reached.
         framed_message_segment[0] = 'm';
         framed_message_segment[1] = 'a';
         framed_message_segment[2] = 'x';
         framed_message_segment[3] = ' ';
         framed_message_segment[4] = 'c'; 
         framed_message_segment[5] = 'o';
         framed_message_segment[6] = 'n';
         framed_message_segment[7] = 'n';
         framed_message_segment[8] = 'e';
         framed_message_segment[9] = 'c';
         framed_message_segment[10] = 't';
         framed_message_segment[11] = 'i';
         framed_message_segment[12] = 'o';
         framed_message_segment[13] = 'n';
         framed_message_segment[14] = 's';
         framed_message_segment[15] = '.';
         framed_message_segment[16] = '\0'; //null is presumbly set previously, it' best to influence the network card to include it with the message.
         
         //copy framed message segment to the network card with the attached signal to send over the network.
         write(temporary_socket_file_descriptor, framed_message_segment, 17);
         
         //copy whole_message_transmitted_flag to the network card with the attached signal to send over the network.
         write(temporary_socket_file_descriptor, whole_message_transmitted_flag, 40);
         write(temporary_socket_file_descriptor, '\0', 1);
         
         //clear framed message segment memory. (this reset' the state for reuse)
         memset(framed_message_segment, '\0', 17);
          
         //shutdown and drop connection. (frees network card resources)
         shutdown(temporary_socket_file_descriptor, SHUT_RDWR);
         close(temporary_socket_file_descriptor);
         
         //reset temporary socket file descriptor.
         temporary_socket_file_descriptor = -1;
         
       }else if(current_total_active_clients < size_of_concurrent_connections)
       {
       printf("new active client\n");
         //increase total active clients count by one.
         current_total_active_clients = current_total_active_clients + 1;
         
         //find a slot by index available for client management.
         unsigned short int empty_slot_by_index = produce_available_index_of_list_of_client_connection_slots(list_of_flags_indicating_active_clients, size_of_concurrent_connections);
         
         //assign temporary socket file descriptor to the respective associated slot.
         list_of_client_socket_file_descriptors[empty_slot_by_index] = temporary_socket_file_descriptor;
         
         //prevent handle loss of client address information.
         list_of_client_address_info[empty_slot_by_index] = client_address_information;
         
         //flag slot is not available.
         list_of_flags_indicating_active_clients[empty_slot_by_index] = 1;
         
         //transmit ready to accept request
         framed_message_segment[0] = 'r';
         framed_message_segment[1] = 'e';
         framed_message_segment[2] = 'a';
         framed_message_segment[3] = 'd';
         framed_message_segment[4] = 'y';
         framed_message_segment[5] = ' ';
         framed_message_segment[6] = 't';
         framed_message_segment[7] = 'o';
         framed_message_segment[8] = ' ';
         framed_message_segment[9] = 'a';
         framed_message_segment[10] = 'c';
         framed_message_segment[11] = 'c';
         framed_message_segment[12] = 'e';
         framed_message_segment[13] = 'p';
         framed_message_segment[14] = 't';
         framed_message_segment[15] = ' ';
         framed_message_segment[16] = 'r';
         framed_message_segment[17] = 'e';
         framed_message_segment[18] = 'q';
         framed_message_segment[19] = 'u';
         framed_message_segment[20] = 'e';
         framed_message_segment[21] = 's';
         framed_message_segment[22] = 't';
         framed_message_segment[23] = '\0';
         printf("%s \n", framed_message_segment);
         write(temporary_socket_file_descriptor, framed_message_segment, 24);
         
         
         //copy whole_message_transmitted_flag to the network card with the attached signal to send over the network.
         write(temporary_socket_file_descriptor, whole_message_transmitted_flag, 41);
     
     
         //shutdown and drop connection. (frees network card resources)
         shutdown(temporary_socket_file_descriptor, SHUT_RDWR);
         close(temporary_socket_file_descriptor);
         
         
         //reset temporary socket file descriptor.
         temporary_socket_file_descriptor = -1;
         
       }
     }
       
     //cpu gets hot during while-loops with zero computation being commited due to no resistance during proverbial pathway finding amongst transistors, this will signal cool down time during high heat.
     nanosleep(&time_to_suspend_shasta_exchange_iteration_request, &time_to_suspend_shasta_exchange_iteration_remaining);
    }
    
  return 0;
}




