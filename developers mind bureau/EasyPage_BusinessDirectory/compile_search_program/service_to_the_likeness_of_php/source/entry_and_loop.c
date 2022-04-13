
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

//global variables
int server_socket_filedescriptor;

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
    //fcntl(server_socket_filedescriptor, F_SETFL, O_NONBLOCK);
    
  //initiate the server address details (majority)ram location storage.
  struct sockaddr_in server_address;
    //zero the server address sockadd_in structure.
    memset(&server_address, 0, sizeof(server_address));
    
    //define parameters pertaining to "server_address".
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(3456);
    memset(server_address.sin_zero, 0, 8);
   
  //bind (network inout)file with server address information. (alert the network card what to do with this file)
  //struct sockaddr * general_server_address_sizeof = (struct sockaddr*)malloc(sizeof(struct sockaddr));
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
  
  //begin shasta exchange iteration of trigger based automated work.
    //initialize temporary holder for newly accepted connections.
    int temporary_socket_file_descriptor = -1;
    socklen_t length = 0;
    temporary_socket_file_descriptor = accept(server_socket_filedescriptor, (struct sockaddr *)&server_address, &length);
     
    
    struct sockaddr_in client_address_info;
    
    //do begin while loop
    time_to_suspend_shasta_exchange_iteration_request.tv_nsec = 10000000;
    
    int shasta_exchange_iteration_continue_loop = 1;
    while(shasta_exchange_iteration_continue_loop == 1)
    {
     //determine if a connection is awaiting to be accepted.
     temporary_socket_file_descriptor = accept(server_socket_filedescriptor, (struct sockaddr *)&server_address, &length);
     if(temporary_socket_file_descriptor < 0)
     {
      // printf("accept() %s \n", strerror(errno));
       
     }else{
       printf("client detected. \n");
     }
       
     //cpu gets hot during while loops with zero load.
     nanosleep(&time_to_suspend_shasta_exchange_iteration_request, &time_to_suspend_shasta_exchange_iteration_remaining);
    }
    
  return 0;
}


