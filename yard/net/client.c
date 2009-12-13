#include "../include/yard.h"

const int MAX_CLIENT_CONNECTIONS = 128;

static SOCKET * connections = NULL;
static YARD_VM_CONNECTION_SETTINGS * settings = NULL;
static YARD_VM_CONNECTION_SETTINGS * master_settings = NULL;

/*
    Practically does nothing. Just saves the connection settings array to be referenced
    later.
    
    YARD_VM_CONNECTION_SETTINGS * cs: settings to save.
*/
void yard_net_configure(YARD_VM_CONNECTION_SETTINGS * cs, int count) {
  int i = 0;
  
  settings = (YARD_VM_CONNECTION_SETTINGS *)malloc(sizeof(YARD_VM_CONNECTION_SETTINGS) * MAX_CLIENT_CONNECTIONS);
  memset(settings, 0, sizeof(YARD_VM_CONNECTION_SETTINGS) * MAX_CLIENT_CONNECTIONS);
  
  for(i = 0; i < count; i++) {
    memcpy(&settings[cs[i].cookie], &cs[i], sizeof(YARD_VM_CONNECTION_SETTINGS));
    
    if (settings[cs[i].cookie].master) {
      // store the master for easier reference
      master_settings = &settings[cs[i].cookie];
    }
  }
  
  if (!master_settings) {
    printf("Master VM not set.\n");
    exit(1);
  }
}


/*
    Takes care of reconnecting to the computer.
    
    int cookie: Cookie of the machine to reconnect to.
*/
static int __yard_net_reconnect(int cookie) {
  SOCKET soket = socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in * sin = make_sockaddr_in(yard_settings_by_cookie(cookie)->host, yard_settings_by_cookie(cookie)->port);
  
  connect(soket, (struct sockaddr *)sin, sizeof(struct sockaddr_in));
  
  connections[cookie] = soket;
}

/*
    Performs an attempt to send the packet to the socket given. 
    If doesn't succeed, re-estabilishes the connection and retries.
*/
static int __yard_net_do_send(int cookie, void * data, int size) {
  int result = 0;
  SOCKET socket = 0;
  
  while (result != size) {
    if (result < 0 || socket <= 0) {
      __yard_net_reconnect(cookie);  
    }
    
    socket = connections[cookie];
    result = send(socket, data, size, 0);
  }
}

/*
    Fetches connection settings from global config array being provided
    a cookie to refer.
    
    int cookie: cookie to fetch settings by.
*/
YARD_VM_CONNECTION_SETTINGS * yard_settings_by_cookie(int cookie) {
  return &settings[cookie];
}

/*
    Returns a cookie to refer to master.
*/
int yard_master_cookie() {
  return master_settings->cookie;  
}

/*
    Sends out a message in (non)blocking way. Also assigns the ref_id to the message
    to keep track on what's going on.
*/
YARD_NET_MESSAGE * yard_net_send_message(void * data, int size, int cookie, int flags, int ref_id, int operation, int send_flags) {
  long result_size = sizeof(YARD_NET_MESSAGE) + size;
  YARD_NET_MESSAGE * message = (YARD_NET_MESSAGE *)malloc(result_size), * result = 0;
  
  message->flags = flags;
  message->size = result_size;
  memcpy((char *)message + sizeof(YARD_NET_MESSAGE), data, size);
  message->ref_id = ref_id;
  message->from = yard_local_cookie();
  message->operation = operation;
  message->id = yard_net_next_id();
  
  if (send_flags & YARD_NET_BLOCKING == YARD_NET_BLOCKING) {
    yard_net_pause_receiver();
  }
  
  __yard_net_do_send(cookie, message, message->size);  
  
  if (send_flags & YARD_NET_BLOCKING == YARD_NET_BLOCKING) {
    result = yard_net_process_until_reply(message->id, 0);
    yard_net_resume_receiver();
  }
  
  return result;
}

/*
    Initialzies the client's variables, sets the neccessary values, allocates memory for
    some structures.
*/
void yard_net_initialize_clients() {
  connections = (SOCKET *)malloc(sizeof(SOCKET) * MAX_CLIENT_CONNECTIONS);
  memset(connections, 0, sizeof(SOCKET) * MAX_CLIENT_CONNECTIONS);
}
