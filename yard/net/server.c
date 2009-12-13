#include "../include/yard.h"


const int MAX_CONNECTIONS = 128;
const int RECV_BUFFER_SIZE = 1024 * 1024 * 32;

static SOCKET serverListener = 0;
struct timeval SELECT_TIMEOUT;

const fd_set read_fd_set;

static THREAD_LOCK * server_receiver_lock = 0;

/*
    Accepts connections from the server listener.
*/
static void __thread_acceptor(void * data) {
  struct sockaddr_in remote_address;
  int address_size = sizeof(remote_address);
  int one = 1;
  SOCKET client = 0;
  
  while(1) {
    client = accept(serverListener, (struct sockaddr *)&remote_address, &address_size);
    
    if (client == INVALID_SOCKET) {
      continue;
    }
    
    ioctlsocket(client, FIONBIO, &one);
    setsockopt(client, SOL_SOCKET, SO_RCVBUF, &RECV_BUFFER_SIZE, sizeof(RECV_BUFFER_SIZE));
    
    
    FD_SET2(client, &read_fd_set);
  }
}

/*
    Receives and processes the packets until the one marked as +ref_id+.
    
    int ref_id: when to stop the loop.
    THREAD_LOCK * lock: mutex to use; applied to stop the thread in an appropriate place.
*/
YARD_NET_MESSAGE * yard_net_process_until_reply(int ref_id, THREAD_LOCK * lock) {
  SOCKET client = 0;
  int i = 0;
  YARD_NET_MESSAGE * message = 0;
  fd_set current_read_fd_set, error_fd_set;
  
  while (1) {
    FD_COPY(&read_fd_set, &current_read_fd_set);
    FD_COPY(&read_fd_set, &error_fd_set);
    
    if (lock) {
      yard_thread_lock_start(lock);
    }
    
    if (select(0, &current_read_fd_set, (fd_set *)0, &error_fd_set, &SELECT_TIMEOUT) > 0) {

      // remove broken sockets from the set we are listening to.
      for(i = 0; i < error_fd_set.fd_count; i++) {
        FD_CLR(error_fd_set.fd_array[i], &read_fd_set);
      }
      
      // read something from places we may actually read from.
      for(i = 0; i < current_read_fd_set.fd_count; i++) {
        client = current_read_fd_set.fd_array[i];
        // try to receive the full message
        if (process_message_from_socket(client, &message) == EINVAL) {
          // drop the socket in case of error
          FD_CLR(client, &read_fd_set);
        } else {
          if (message && message->ref_id == ref_id) {
            return message;
          }
        }
      }                   
    }
    
    if (lock) {
      yard_thread_lock_end(lock);
    }
     
    yard_thread_sleep(1);
  }  
  
  return 0;
}

/*
    Pauses the receiving thread in order to stop any message processing 
    that may occur. May block for some time.
*/
void yard_net_pause_receiver() {
  yard_thread_lock_start(server_receiver_lock);  
}

/*
    Resumes the receiving thread.
*/
void yard_net_resume_receiver() {
  yard_thread_lock_end(server_receiver_lock);  
}

/*
    Accepts connections from the server listener.
*/
static void __thread_receiver(void * data) {
  yard_net_process_until_reply(-1, 0);
}

static void __bind_server_socket() {
  YARD_VM_CONNECTION_SETTINGS * settings = NULL;
  struct sockaddr_in * sin = NULL;
  
  settings = yard_settings_by_cookie(yard_local_cookie());
  
  if (!settings) {
    printf("Missing own settings\n");
    exit(1);
  } 
  
  sin = make_sockaddr_in(settings->host, settings->port);
  serverListener = socket(AF_INET, SOCK_STREAM, 0);

  if (serverListener == INVALID_SOCKET) {
    printf("Socket creation error");
    exit(1);
  }

  if (bind(serverListener, (struct sockaddr *)sin, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
    printf("Socket binding error");
    exit(1);
  };

  printf("Server started\n");

  listen(serverListener, MAX_CONNECTIONS);
}

static void __start_accepting_thread() {
  yard_create_thread(0, __thread_acceptor, 0);
}

static void __start_receiving_thread() {
  yard_create_thread(0, __thread_receiver, 0);
}

static void __initialize_variables() {
  FD_ZERO(&read_fd_set);
  
  SELECT_TIMEOUT.tv_sec = 1;
  SELECT_TIMEOUT.tv_usec = 0;
  
  server_receiver_lock = (THREAD_LOCK *)malloc(sizeof(THREAD_LOCK));
  yard_create_thread_lock(server_receiver_lock);
}

/*
    Creates a listening socket and starts a thread which accepts the connections.
*/
int yard_net_initialize_server_listener() {
  initialize_winsock();  
  __initialize_variables();
  __bind_server_socket();  
  __start_accepting_thread();
  __start_receiving_thread();
}
