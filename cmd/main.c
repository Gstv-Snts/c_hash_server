#include <stdio.h>
#include <stdlib.h>

int main() {
  int* arr = malloc(sizeof(int*) * 5);
  arr[0] = 10;
  arr[1] = 20;
  arr[2] = 30;
  arr[3] = 40;
  arr[4] = 50;

  for (int i = 0; i < 5; i++) {
    printf("%d: %d\n", i, arr[i]);
  }

  arr = realloc(arr, sizeof(int*) * 10);

  printf("#######\n");
  for (int i = 0; i < 10; i++) {
    printf("%d: %d\n", i, arr[i]);
  }

  return 0;
}
