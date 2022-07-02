/*#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <unistd.h>
 #include <fcntl.h>
*/

int service_socket_filedescriptor;
struct sockaddr_in server_address;

void tcp_start_service();
