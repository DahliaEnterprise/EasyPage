//prerequisite
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>


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
      printf("socket() problems.");
      return;
    }
    
  //initiate the server address details (majority)ram location storage.
  struct sockaddr_in server_address;
    //zero the server address sockadd_in structure.
    
}
