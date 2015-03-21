#include "msg.h"

int * write_1_svc (char **msg, struct svc_req *req) {
  static int result;
  printf ("%s", *msg);
  result = 1;
  return (&result);
}
