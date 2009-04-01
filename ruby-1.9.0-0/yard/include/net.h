#ifndef _NET_H_
#define _NET_H_

/*
    The stucture holds connection settings for one remote VM.
    The net API may receive several structures to be able to create multiple connections.
    
    The configuration provided is required to contain host, port and cookie for each connection.
 */
struct __vm_connection_settings {
  // hostname to connect to
  char host[255];
  // port to use
  short port;  
  // field holding cookie of the connection
  long cookie;
};

typedef struct __vm_connection_settings YARD_VM_CONNECTION_SETTINGS;

/*
    Represents a connection instance.
    Contains a socket used with the connection, reference to connection settings etc.
*/
struct __vm_connection {
  // connection settings to restore in case of something bad happens
  VM_CONNECTION_SETTINGS * connection_settings;
  int socket;
};

typedef struct __vm_connection YARD_VM_CONNECTION;

/*
    A network message.
    To work with it, just allocate the neccessary amount of data into "data" field and set the size 
    field to MessageSize + sizeof(YARD_NET_MESSAGE) (in bytes). 
*/
struct __net_message {
  long size;
  long id;
  long ref_id;
  
  void * data;
}

typedef struct __net_message YARD_NET_MESSAGE;

/*
    Initializes server listener.
    
    Just creates and binds the server socket and allocates some memory for internal structures (like connection lists).
*/
int yard_net_initialize_server_listener();

/*
    Passes the message to the specified receiver. If the receiver cookie is less than zero,
    sends the message to every VM.
    If any of the target connections is dead, and "force" is non-zero, refreshes it to ensure the data has been sent.
*/
int yard_net_send_message(YARD_NET_MESSAGE *, int, int);

/*
    Deals with accepting connections. This function is blocking; the invoking side should take care
    of executing everything in a thread or so.
*/
int yard_net_accept_connections();

/*
    Performs a non-blocking attempt to receive some data from every conneciton.
    If conneciton is a dead one, doesn't refresh it; if any data has been received,
    attempts to invoke a special callback.  
*/
int yard_net_try_receive();

/*
    Performs a block message receival. If "force" argument is set to non-zero value, will refresh
    connections any number of times until it gets some data from the destination. 
    
    If cookie is set to negative value, works pretty much the same as try_receive, but doesn't return
    unless the data has been retrieved from any VM.
    
    Please note that this function doesn't invoke any callbacks: its main use is to be called during 
    handshake process or while some blocking update is being performed.
*/
YARD_NET_MESSAGE * yard_net_do_receive(int, int);

/*
    Callback type specification: is used by YARD engine as invokation point in case some
    message has been received; is invoked by yard_net_try_receive only.
*/
typedef struct void (*YardNetReceiveCallback)(YARD_NET_MESSAGE *);

#endif
