#include <czmq.h>

int main(int argc, char *argv[]) {
  zsock_t *writer = zsock_new_push("@tcp://0.0.0.0:5560"); assert(write);

  zsock_resolve(writer);

  while (1) {
    char *input = NULL;
    size_t ln = 0;
    getline(&input, &ln, stdin);
    zstr_send(writer, input);
    free(input);
  }
}
