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
