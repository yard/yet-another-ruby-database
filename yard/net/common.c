#include "../include/yard.h"

YardNetReceiveCallback yard_net_on_data = NULL;

static int __id_counter = 1;

void FD_COPY(fd_set * from, fd_set * to) {
  to->fd_count = from->fd_count;
  memcpy(to->fd_array, from->fd_array, from->fd_count * sizeof(SOCKET));
};

void FD_SET2(int fd, fd_set * fds) {
  fds->fd_array[fds->fd_count++] = fd;
}

/*
    Returns a new message id to be assigned.
    Seems to be thread-safe (I hope at least).
*/
int yard_net_next_id() {
  return __id_counter++;
}

/*
    Creates and populates a sockaddr_in structure being given a hostname and a port.
    
    const char * hostname: hostname to fill int the sockaddr.
    int port: port to assign.
*/
struct sockaddr_in * make_sockaddr_in(const char * hostname, int port)
{
  struct sockaddr_in * addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
  memset(addr, 0, sizeof(struct sockaddr_in));
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = inet_addr(hostname);
  addr->sin_port = htons(port);
  
  return addr;
}

/*
    Initializes the winsock library (needed on windows only).
*/
void initialize_winsock()
{
  WSADATA wsaData;
  WORD version = MAKEWORD( 2, 0 );
  WSAStartup(version, &wsaData);
}

/*
    Receives some data from the client and takes care of re-assembling the message.
    Return EINVAL is some error has occured in such a way that the socket should be dropped.
    
    SOCKET client: a socket fd to perform the operation on.
*/
int process_message_from_socket(SOCKET client, YARD_NET_MESSAGE ** out_message) {
  long size = 0;
  int error = 0;
  long result = 0;
  int error_length = sizeof(error);
  YARD_NET_MESSAGE * message = 0;
  
  result = recv(client, &size, sizeof(size), MSG_PEEK);
  
  *out_message = 0;
  
  if (result < 0) {
    getsockopt(client, SOL_SOCKET, SO_ERROR, (char *)&error, &error_length);
    
    if (error == EWOULDBLOCK) {
      return 0;
    } else {
      return EINVAL;
    }
  }    
  
  message = (YARD_NET_MESSAGE *)malloc(size);
 
  result = recv(client, message, size, MSG_PEEK); 
  
  if (result < 0) {
    free(message);
    getsockopt(client, SOL_SOCKET, SO_ERROR, (char *)&error, &error_length);
    
    if (error == EWOULDBLOCK) {
      return 0;
    } else {
      return EINVAL;
    }
  }  
  
  if (result == size) {  
    // we received exactly what we wanted to receive
    // just remove the message from the queue and get out of there
    recv(client, message, size, 0); 
    message->data = (YARD_NET_MESSAGE *)(((char *)message) + sizeof(YARD_NET_MESSAGE));
    
    *out_message = message;
    yard_net_on_data(message);
  } else {
    // we don't have enough data... will wait
    free(message);
  }   
  
  return 0;
}