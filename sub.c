#include <czmq.h>

int main(int argc, char *argv[]) {
  FILE *fout = NULL;
  char *addr = NULL;
  if (argc > 1 && strncmp(argv[1], "--help", 6) == 0) {
    fprintf(stderr, "Usage: %s SERVER_IP [OUTFILE]\n"
        "SERVER_IP format: tcp://name:port\n"
        , argv[0]);
    return EXIT_SUCCESS;
  };
  
  if (argc > 1) {
    addr = argv[1];
  };
  
  if (argc > 2) {
    fout = fopen(argv[2], "w");
  } else {
    fout = stdout; 
  }

  char *fulladdr = (char*)calloc(strlen(addr) + 2, 1);
  sprintf(fulladdr, ">%s", addr);
//  fprintf(stderr, "'%s'\n", fulladdr);

  zsock_t *reader = zsock_new_pull(fulladdr); //">tcp://0.0.0.0:5560");
  assert(reader);
  zsock_resolve(reader);

  while (1) {
    zmsg_t *msg = zmsg_recv(reader);
    assert(msg);
    char *string = zmsg_popstr(msg);
    fprintf(fout, "%s", string);
    if (fout != stdout) {
      fprintf(stderr, "%s", string);
      fflush(stderr);
    }
    fflush(fout);
    free(string);
    zmsg_destroy(&msg);
  }
}
