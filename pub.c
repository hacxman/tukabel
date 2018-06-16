#include <czmq.h>

int main(int argc, char *argv[]) {
  char *addr = "tcp://0.0.0.0:5560";

  if (argc > 1 && strncmp(argv[1], "--help", 6) == 0) {
    fprintf(stderr, "Usage: %s IP_TO_BIND_TO\n"
        "IP_TO_BIND_TO format: tcp://name:port\n"
        "                      tcp://0.0.0.0:5560   means bind to all available adapters on port 5560\n"
        , argv[0]);
    return EXIT_SUCCESS;
  };

  if (argc > 1) {
    addr = argv[1];
  }

  char *fulladdr = (char*)calloc(strlen(addr) + 2, 1);
  sprintf(fulladdr, "@%s", addr);
//  fprintf(stderr, "'%s'\n", fulladdr);

  zsock_t *writer = zsock_new_push(fulladdr); assert(write);
  //zsock_t *writer = zsock_new_push("@tcp://0.0.0.0:5560"); assert(write);

  zsock_resolve(writer);

  while (1) {
    char *input = NULL;
    size_t ln = 0;
    getline(&input, &ln, stdin);
    zstr_send(writer, input);
    free(input);
  }
}
