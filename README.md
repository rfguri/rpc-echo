# rpc-echo
[RPC](http://en.wikipedia.org/wiki/Remote_procedure_call) echo server implementation.

## rpcgen usage guide

First of all run [`rpcgen`](http://en.wikipedia.org/wiki/RPCGEN) tool to generate all the files needed:

```
$ rpcgen -a msg.x
```

Then edit [`msg_server.c`](https://github.com/rfguri/rpc-echo/blob/master/msg_server.c) and [`msg_client.c`](https://github.com/rfguri/rpc-echo/blob/master/msg_client.c) to code your own functions.

### msg_server.c

Holds the server code. Including includes, prototypes and implementation of the server as follows: 

```c
#include "msg.h"

int * write_1_svc(char **msg, struct svc_req *req) {
  static int result;
  printf ("%s", *msg);
  result = 1;
  return (&result);
}
```
> **Note**: `rpcgen` ask to write functions that return pointers to their integer results, not the integers themselves.

### msg_client.c

Holds the client code. Opens a connection to a machine specified on the command line and asks the server to echo the message typed.

```c
#include "msg.h"

int * echo (char *host, char *msg) {
  CLIENT *clnt;
  int  *result;
  clnt = clnt_create (host, ECHO, ECHO_V1, "udp");
  if (clnt == NULL) {
    clnt_pcreateerror (host);
    exit (1);
  }
  result = write_1(&msg, clnt);
  if (result == (int *) NULL) {
    clnt_perror (clnt, "call failed");
  }
  return (result);
}

int main (int argc, char *argv[]) {
  int *result;
  char *host, *msg, buff[2048];
  if (argc < 2) {
    printf ("Usage: %s server_host\n", argv[0]);
    exit (1);
  }
  host = argv[1];
  do {
    bzero (buff, 2048);
    read (0, buff, sizeof (buff));
    msg = strdup(buff);
    result = echo (host, msg);
  } while (result != (int *)NULL);
  exit (0);
}
```

> **Note**: Notice the RPC library call "clnt_create()", which opens a connection. It address the server by hostname, program ID, and version number. It can also specify "tcp" or "udp" transport modes.

## Compilation

```
  make -f Makefile.msg
```

## Running

On one terminal run `server` and wait to see echo messages:

```
$ ./msg_server
```

And on another one run `client` and start typing your messages:

```
$ ./msg_client <remote_server>
```

> **Note**: Remember to always start the `server` before starting the `client`.

## Example

```
$ ./msg_server
Hello, RPC!

$ ./msg_client localhost
Hello, RPC!
```

