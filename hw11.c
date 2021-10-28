#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int rand_num() {
  int fd = open("/dev/urandom", O_RDONLY);
  if (fd < 0) {
    return 0;
  }

  int buff;
  read(fd, &buff, sizeof(int));

  return buff;
}

int main(){
  int arr[10];
  int i;
  printf("Array of random values:\n{ ");
  for (i = 0; i < 10; i++) {
    arr[i] = rand_num();
    printf("%d ", arr[i]);
  }
  printf("}\n");

  int fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
  if (fd < 0) {
    return -1;
  }
  write(fd, arr, sizeof(arr));

  int new_arr[10];
  fd = open("test.txt", O_RDONLY);
  if (fd < 0) {
    return -1;
  }

  read(fd, new_arr, sizeof(new_arr));

  printf("Array of random values in the copy:\n{ ");
  for (i = 0; i < 10; i++) {
    printf("%d ", new_arr[i]);
  }
  printf(" }\n");

  return 0;
}
