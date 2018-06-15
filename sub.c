#include <czmq.h>

int main(int argc, char *argv[]) {
  FILE *fout = NULL;
  if (argc > 1 && strncmp(argv[1], "--help", 6) == 0) {
    fprintf(stderr, "Usage: %s [OUTFILE]\n", argv[0]);
    return EXIT_SUCCESS;
  } else if (argc > 1) {
    fout = fopen(argv[1], "w");
  } else {
    fout = stdout; 
  }

  zsock_t *reader = zsock_new_pull(">tcp://0.0.0.0:5560");
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
