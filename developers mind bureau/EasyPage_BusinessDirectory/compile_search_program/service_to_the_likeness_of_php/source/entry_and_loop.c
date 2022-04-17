
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
#include <sys/types.h>
#include <dirent.h>

//nanosleep requires implicit header delcaration.
int nanosleep(const struct timespec *req, struct timespec *rem);

//shasta exchange
  //shasta exchange headers
    //independent structure(s)
    #include "./structure_string/structure_string.h"
    
    //major functions
    #include "./produce_available_index_of_list_of_client_connection_slots/produce_available_index_of_list_of_client_connection_slots.h"
    #include "./client_routine_stage_one/client_routine_stage_one.h"
  
  //shasta exchange definitions
    //independent structure(s)
    #include "./structure_string/structure_string.c"
    
    //major functions
    #include "./extract_list_of_business_filenames_to_parseable_ram/extract_list_of_business_filenames_to_parseable_ram.c"
    #include "./produce_available_index_of_list_of_client_connection_slots/produce_available_index_of_list_of_client_connection_slots.c"
    #include "./client_routine_stage_one/client_routine_stage_one.c"

//global variables
  //service connection
  int server_socket_filedescriptor;
  
  //framed message segment
  char framed_message_segment[1023]; //setting to 1024 is presumed to allocate within ram the amount of 1023+minimum next ram slot available. its probly just 1023 plus 8 bytes on a 64 bit ram configuration. some say it does what mysql does which is times two or the base number plus a minimum large number such as 128

  //flag of whole message completed.
  char whole_message_transmitted_flag[41];

  //constant time period
  struct timespec time_to_suspend_shasta_exchange_iteration_remaining;
  struct timespec time_to_suspend_shasta_exchange_iteration_request;

  //receive buffer string size.
  unsigned int send_string_max_size;
  
  //send buffer string size.
  unsigned int receive_string_max_size;
  
  //temporary receive buffer.
  char * temporary_receive_buffer;

//entry to program.
int main()
{
  //define root directory to transmit content.
  //root_directory_of_content "/var/www/business_directory_content/";
  //"/var/www/business_directory_content/list_of_businesses/";


  //extract text file style list(characters) into a c style array of string names that which make it parseable.
    //initialize nessecsary memory spaces.
    struct string * list_of_business_records = 0;
    
    //do extract and convert to ram parseabme list.
    int extract_business_name_list_return_code = extract_list_of_business_filenames_to_parseable_ram(list_of_business_records);
    
    if(extract_business_name_list_return_code < 1)
    {
      return -1;
    }


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
  unsigned short int frame_message_segment_index = 0;
  while(frame_message_segment_index < 1024)
  {
    framed_message_segment[frame_message_segment_index] = '\0';
    
    //next character slot.
    frame_message_segment_index = frame_message_segment_index + 1;
  }
  
  //define the whole message transmitted flag.
  strcat(whole_message_transmitted_flag, "1B480158E1F30E0B6CEE7813E9ECF094BD6B3745");
  
  //begin shasta exchange iteration of trigger based automated work.
    //initialize temporary array to account for connections and their associated states.
      //define a number to be used within a manner consensus pertaining to concurrent connections
      unsigned short int size_of_concurrent_connections = 1024;
      
      //initialize and zero an array of client socket file descriptors.
      int * list_of_client_socket_file_descriptors = 0;
      while(list_of_client_socket_file_descriptors == 0){ list_of_client_socket_file_descriptors = (int *)malloc(size_of_concurrent_connections * sizeof(int)); }
      memset(list_of_client_socket_file_descriptors, 0, size_of_concurrent_connections);
    
      //initialize and zero an array of client address info.(this/these address infor handles signal the network card that the program has not let go)
      struct sockaddr_in * list_of_client_address_info = 0;
      while(list_of_client_address_info == 0){ list_of_client_address_info = (struct sockaddr_in *)malloc(size_of_concurrent_connections * sizeof(struct sockaddr_in)); }
      //memset(list_of_client_address_info, 0, size_of_concurrent_connections);
      
      //initialize and zero an array of flags that indicate which associated data slots are being used by the program or are available.
      unsigned short int * list_of_flags_indicating_active_clients = 0;
      while(list_of_flags_indicating_active_clients == 0){ list_of_flags_indicating_active_clients = (unsigned short int *)malloc(size_of_concurrent_connections * sizeof(unsigned short int)); }
      memset(list_of_flags_indicating_active_clients, 0, size_of_concurrent_connections);
      unsigned short int list_of_flags_indicating_active_clients_index = 0;
      while(list_of_flags_indicating_active_clients_index < size_of_concurrent_connections)
      {
        //this step appears nessecary as memset is a (void)zero and or NULL, where as an equal(set) zero is a integer zero.
        list_of_flags_indicating_active_clients[list_of_flags_indicating_active_clients_index] = 0;
        
        list_of_flags_indicating_active_clients_index = list_of_flags_indicating_active_clients_index + 1;
      }
      
      //initialize and zero an array of eqch respective clients current stage within the request response stage.
      /*
        every client gets one response(non delisional, to be clear: not a literal-technical one); 
        if events are required to occur beyond one response the database event system will create and manage changes, and the client can submit a second request after the first request has been commited for the database event changes to occur.
      */
      unsigned short int * list_of_current_stage = 0;
      while(list_of_current_stage == 0){ list_of_current_stage = (unsigned short int *)malloc(size_of_concurrent_connections * sizeof(unsigned short int)); }
      
    
      //initialize send "ring buffer".
      struct string * list_of_send_buffer = 0;
      while(list_of_send_buffer == 0){ list_of_send_buffer = (struct string *)malloc(size_of_concurrent_connections * sizeof(struct string)); }
      
      send_string_max_size = 32000;
      unsigned short int index_of_list_of_send_buffer = 0;
      while(index_of_list_of_send_buffer < size_of_concurrent_connections)
      {
        list_of_send_buffer[index_of_list_of_send_buffer].string_buffer = 0;
        while(list_of_send_buffer[index_of_list_of_send_buffer].string_buffer == 0){ list_of_send_buffer[index_of_list_of_send_buffer].string_buffer = (char *)malloc(send_string_max_size * sizeof(char)); }
        list_of_send_buffer[index_of_list_of_send_buffer].string_buffer_memory_size = send_string_max_size;
        
        index_of_list_of_send_buffer = index_of_list_of_send_buffer + 1;
      }
      
   
      //initialize receive "ring buffer".
      struct string * list_of_receive_buffer = 0;
      while(list_of_receive_buffer == 0){ list_of_receive_buffer = (struct string *)malloc(size_of_concurrent_connections * sizeof(struct string)); }
      
      receive_string_max_size = 32000;
      unsigned short int index_of_list_of_receive_buffer = 0;
      while(index_of_list_of_receive_buffer < size_of_concurrent_connections)
      {
        list_of_receive_buffer[index_of_list_of_receive_buffer].string_buffer = 0;
        while(list_of_receive_buffer[index_of_list_of_receive_buffer].string_buffer == 0){ list_of_receive_buffer[index_of_list_of_receive_buffer].string_buffer = (char *)malloc(receive_string_max_size * sizeof(char)); }
        list_of_receive_buffer[index_of_list_of_receive_buffer].string_buffer_memory_size = receive_string_max_size;
        
        index_of_list_of_receive_buffer = index_of_list_of_receive_buffer + 1;
      }
   
      //initialize and set count of active clients. (this reduces a need for counting every check, necessary efficiency).
      unsigned short int current_total_active_clients = 0;
    
    
    //initialize temporary holder for newly accepted connections.
    int temporary_socket_file_descriptor = -1;
    struct sockaddr_in client_address_information;
    socklen_t length = 0;
    
    char * temporary_receive_buffer = 0;
    while(temporary_receive_buffer == 0){ temporary_receive_buffer = (char *)malloc(receive_string_max_size * sizeof(char)); }
    
    memset(temporary_receive_buffer, 0, receive_string_max_size);
    
    
    //do begin while loop
    printf("Shasta Exchange\n");
    time_to_suspend_shasta_exchange_iteration_request.tv_nsec = 100000000; //one hundred miliseconds.
    
    int shasta_exchange_iteration_continue_loop = 1;
    while(shasta_exchange_iteration_continue_loop == 1)
    {
     /*
        Multithread on a single thread.
        
        1) Accept one new connection.
           a) drop if max concurrent connections accepted.
           b) allocate client associations to proceed with the
              one time request then respond paradigm.
        
        2) Iterate through each client connection.
           a) if stage is zero then wait for request.
              note: this is a local connection so we can
                    trust the server is not hacked or being
                    infiltrated, thus no need to enforce timeout.
           a.1) while receiving partially or all of the request
                append to the receive buffer associated with the client.
                change stage to one when the entire message is received.
               
           b) if stage is one,
              then a response has not yet
              been calculated and or determined. calculate or
              determine response and place the whole response
              within the send ring buffer associated with the client.
              change stage to two, indicating that parts of the 
              response will transmitted per turn.
              
           c) if stage is two,
              transmit part of the response then break away
              for the next client connected to the service
              to be attended to.
              if the entire response has been transmitted, 
              close the connection and delete the associated
              client  variables.
              
     */
    
     /* Route 1) Accept one connection */
     //determine if a connection is awaiting to be accepted.
     temporary_socket_file_descriptor = accept(server_socket_filedescriptor, (struct sockaddr *)&client_address_information, &length);
     if(temporary_socket_file_descriptor < 0)
     {
      // printf("accept() %s \n", strerror(errno));
      //error occurrd.
     }else{
       //Has the maximum amount of concurrent users been reached?
       if(current_total_active_clients >= size_of_concurrent_connections)
       {
         /*
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
         
         //set this client socket as not blocking immediately.
         //fcntl(temporary_socket_file_descriptor, F_SETFL, O_NONBLOCK);
    
         //copy framed message segment to the network card with the attached signal to send over the network.
         write(temporary_socket_file_descriptor, framed_message_segment, 17);
         
         //copy whole_message_transmitted_flag to the network card with the attached signal to send over the network.
         write(temporary_socket_file_descriptor, whole_message_transmitted_flag, 40);
         write(temporary_socket_file_descriptor, '\0', 1);
         
         //clear framed message segment memory. (this reset' the state for reuse)
         memset(framed_message_segment, '\0', 17);
          
         //shutdown and drop connection. (frees network card resources)
         //shutdown(temporary_socket_file_descriptor, SHUT_RDWR);
         close(temporary_socket_file_descriptor);
         
         //reset temporary socket file descriptor.
         temporary_socket_file_descriptor = -1;
         */
       }else if(current_total_active_clients < size_of_concurrent_connections)
       {
         printf("new active client\n");
        
         //increase total active clients count by one.
         current_total_active_clients = current_total_active_clients + 1;
         
         //find a slot by index available for client management.
         unsigned short int empty_slot_by_index = produce_available_index_of_list_of_client_connection_slots(list_of_flags_indicating_active_clients, size_of_concurrent_connections);
         
         //assign temporary socket file descriptor to the respective associated slot.
         list_of_client_socket_file_descriptors[empty_slot_by_index] = temporary_socket_file_descriptor;
         fcntl(list_of_client_socket_file_descriptors[empty_slot_by_index], F_SETFL, O_NONBLOCK);
         
         //prevent handle loss of client address information.
         list_of_client_address_info[empty_slot_by_index] = client_address_information;
         
         //flag slot is not available.
         list_of_flags_indicating_active_clients[empty_slot_by_index] = 1;
         
         //define current stage of the connection.
         list_of_current_stage[empty_slot_by_index] = 0;
         
         //zero send message buffer.
         unsigned short int list_of_send_buffer_index = 0;
         while(list_of_send_buffer_index < send_string_max_size)
         {
           list_of_send_buffer[empty_slot_by_index].string_buffer[list_of_send_buffer_index] = '\0';
         
           //next character slot.
           list_of_send_buffer_index = list_of_send_buffer_index + 1;
         }
        
         //zero receive message buffer.
         unsigned short int list_of_receive_buffer_index = 0;
         while(list_of_receive_buffer_index < receive_string_max_size)
         {
           list_of_receive_buffer[empty_slot_by_index].string_buffer[list_of_receive_buffer_index] = '\0';
         
           //next character slot.
           list_of_receive_buffer_index = list_of_receive_buffer_index + 1;
         }
       }
     }
     
     
     /* Route 2) Iterate through each connection within the list. */
     if(current_total_active_clients > 0)
     {
       unsigned short int index_of_client_connections = 0;
       while(index_of_client_connections < size_of_concurrent_connections)
       {
         //ensure a connection is active before applying connection logic.
         if(list_of_flags_indicating_active_clients[index_of_client_connections] == 1)
         {
           //take action based on what the current stage is.
           if(list_of_current_stage[index_of_client_connections] == 0)
           {
             client_routine_stage_one(temporary_receive_buffer, 
                                      receive_string_max_size, 
                                      list_of_client_socket_file_descriptors[index_of_client_connections], 
                                      list_of_receive_buffer[index_of_client_connections].string_buffer,
                                      whole_message_transmitted_flag,
                                      & list_of_current_stage[index_of_client_connections]);
           }else if(list_of_current_stage[index_of_client_connections] == 1)
           {
             //determine what the request is by being able to ignore the whole meassge received flag segment.
             unsigned int end_of_string_character_position = strlen(list_of_receive_buffer[index_of_client_connections].string_buffer) - 40; //exact position before begining of whole mesaage received flag segment.
             
             //isolate the "request" message.
             char * request_message = 0;
             while(request_message == 0){ request_message = (char *)malloc((end_of_string_character_position * sizeof(char))+1); }
             memset(request_message, '\0', (end_of_string_character_position+1)); //how to set as null instead of (void)zero.... c is like putting together a puzzle while blind. but its still the best.
             unsigned int request_message_index = 0;
             while(request_message_index < end_of_string_character_position)
             {
               request_message[request_message_index] = list_of_receive_buffer[index_of_client_connections].string_buffer[request_message_index];
             
               //next character position.
               request_message_index = request_message_index + 1;
             }
             
             
             
             printf("%s\n", request_message);
             free(request_message);
           }
         }
           
         //next client to attend to...
         index_of_client_connections = index_of_client_connections + 1;
       }
     }
       
     //cpu gets hot during while-loops with zero computation being commited due to no resistance during proverbial pathway finding amongst transistors, this will signal cool down time during high heat.
     nanosleep(&time_to_suspend_shasta_exchange_iteration_request, &time_to_suspend_shasta_exchange_iteration_remaining);
    }
   
  return 0;
}







