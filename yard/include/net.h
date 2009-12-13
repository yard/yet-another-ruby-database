#ifndef _NET_H_
#define _NET_H_

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "advapi32.lib")

#include <winsock.h>
#include <time.h>

#include "threads.h"

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
  // whether the VM is a master one
  int master;
};

typedef struct __vm_connection_settings YARD_VM_CONNECTION_SETTINGS;

/*
    Represents a connection instance.
    Contains a socket used with the connection, reference to connection settings etc.
*/
struct __vm_connection {
  // connection settings to restore in case of something bad happens
  YARD_VM_CONNECTION_SETTINGS * connection_settings;
  int socket;
};

typedef struct __vm_connection YARD_VM_CONNECTION;

#define YARD_NET_DEFINE_GLOBAL_VARIABLE 1
#define YARD_NET_UPDATE_OBJECT 2
#define YARD_NET_FETCH_OBJECT 3
#define YARD_NET_FETCH_GLOBAL_VARIABLE 4

#define YARD_NET_FETCH_OBJECT_SUCCESS 5

/*
    A network message.
    To work with it, just allocate the neccessary amount of data into "data" field and set the size 
    field to MessageSize + sizeof(YARD_NET_MESSAGE) (in bytes). 
*/
struct __net_message {
  long size;
  long id;
  long ref_id;
  long flags;
  int from;
  int operation;
  
  void * data;
};

typedef struct __net_message YARD_NET_MESSAGE;

#define YARD_NET_ANY_SOURCE -1
#define YARD_NET_ANY_TARGET -1

#define YARD_NET_BLOCKING 1
#define YARD_NET_GENERAL 0

/*
    Initializes server listener.
    
    Just creates and binds the server socket and allocates some memory for internal structures (like connection lists).
*/
int yard_net_initialize_server_listener();

/*
    Configures the VM to use certain endpoints to send data to.
    
    YARD_VM_CONNECTION_SETTINGS * settings: an array of settings to utilize.
*/
void yard_net_configure(YARD_VM_CONNECTION_SETTINGS *, int);

/*
    Initialzies client subsystem.
*/
void yard_net_initialize_clients();

/*
    Passes the message to the specified receiver. If the receiver cookie is less than zero,
    sends the message to every VM.
    If any of the target connections is dead, and "force" is non-zero, refreshes it to ensure the data has been sent.
*/
YARD_NET_MESSAGE * yard_net_send_message(void *, int, int, int, int, int, int);

/*
    Callback type specification: is used by YARD engine as invokation point in case some
    message has been received; is invoked by yard_net_try_receive only.
*/
typedef void (*YardNetReceiveCallback)(YARD_NET_MESSAGE *);

/*
    Fetches connection settings being given a cookie.
*/
YARD_VM_CONNECTION_SETTINGS * yard_settings_by_cookie(int cookie);

/*
    Returns a new, unique across all this VM message id.
*/
int yard_net_next_id();

/*
    Basically just processes the messages from server connections unless
    it meets the ID specified.
*/
YARD_NET_MESSAGE * yard_net_process_until_reply(int, THREAD_LOCK *);

/*
    Pauses the receiving thread in order to stop any message processing 
    that may occur. May block for some time.
*/
void yard_net_pause_receiver();

/*
    Resumes the receiving thread.
*/
void yard_net_resume_receiver();

/*
    Forwarding data handler declaration.
*/
YardNetReceiveCallback yard_net_on_data;

/*
    Returns a cookie to refer to master.
*/
int yard_master_cookie();

/*
    We also have to maintain a few common methods in order to make things reusable and easier.
*/

/*    
    Fills the newly created sockaddr_in structure with the given host name and port.
*/
struct sockaddr_in * make_sockaddr_in(const char *, int);

/*
    Initializes the winsock library (needed on windows only).
*/
void initialize_winsock();

/*
    Processes the messages available on the passed socket.
*/
int process_message_from_socket(SOCKET, YARD_NET_MESSAGE **);

/*
    A really simple macros for copying between fd_sets.
*/
void FD_COPY(fd_set *, fd_set *);
void FD_SET2(int, fd_set *);

/*
    Dispatches a global variable definition message.
*/
void yard_net_dispatch_global_variable_definition(YARD_NET_MESSAGE *);

/*
    Dispatches an object fetch request.
*/
void yard_net_dispatch_object_fetch(YARD_NET_MESSAGE *);

#endif
