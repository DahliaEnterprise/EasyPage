//prerequisite
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>

//global variables
int server_socket_filedescriptor;

//entry to program.
void main()
{
  //initate socket
  server_socket_filedescriptor = -1;
  server_socket_filedescriptor = socket(AF_INET, SOCK_STREAM, 0);
    //determine socket is handable by variable.
    if(server_socket_filedescriptor == -1)
    {
      printf("socket() problems. \n");
      return;
    }
    
  //initiate the server address details (majority)ram location storage.
  struct sockaddr_in server_address;
    //zero the server address sockadd_in structure.
    memset(&server_address, 0, sizeof(server_address));
    
    //define parameters pertaining to "server_address".
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(8080);
    
  //bind (network inout)file with server address information. (alert the network card what to do with this file)
  struct sockaddr * general_server_address_sizeof = (struct sockaddr*)malloc(sizeof(struct sockaddr));
  int bind_return_code = bind(server_socket_filedescriptor, general_server_address_sizeof, sizeof(general_server_address_sizeof));
  if(bind_return_code != 0)
  {
   printf("bind() \n");
   return;
  }
  
  //enable listening functioning.
  int listen_return_code = listen(server_socket_filedescriptor, 5);
  if(listen_return_code != 0)
  {
    printf("listen() \n");
    return;
  }
  
  
}
