
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "networking.h"

int main() {
  struct sockaddr_in addr = create_server_address(1337);

  int s = socket(addr.sin_family, SOCK_STREAM, 0);
  if (s == -1) {
    perror("Failed to create socket.");
    exit(1);
  }

  int b = bind(s, (const struct sockaddr *)&addr, sizeof(addr));
  if (b == -1) {
    perror("Failed to bind socket.");
    close(s);
    exit(1);
  }

  int l = listen(s, 3);
  if (l == -1) {
    perror("Failed to listen socket.");
    close(s);
    exit(1);
  }

  int a = accept(s, (struct sockaddr *)&addr, (socklen_t *)sizeof(addr));
  if (a == -1) {
    perror("Failed to accept from client.");
    close(s);
    exit(1);
  }

  char buffer[1024] = {0};
  ssize_t r = read(a, buffer, sizeof(buffer) - 1);
  if (a == -1) {
    perror("Failed to read client data.");
    close(s);
    close(a);
    exit(1);
  }

  printf("Client data: %s\n", buffer);

  close(s);
  close(a);
  return 0;
}
