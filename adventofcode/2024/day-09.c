#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 1) {
    exit(1);
  }

  char *file_path = argv[1];
  FILE *file = fopen(file_path, "r");

  if (file == NULL) {
    exit(1);
  }

  long long checksum = 0;
  char buff[65536];
  fgets(buff, sizeof(buff), file);
  int len = strlen(buff) - 1; // strip new line

  int fwd_id = 0;
  int bwd_id = (len - 1) / 2;
  int idx = 0;
  int fwd_ptr = 0;
  int bwd_ptr = len - 1;
  int blocks;
  int free_blocks;

  int z;
  while (fwd_id < bwd_id) {
    blocks = buff[fwd_ptr] - '0';
    while (blocks) {
      printf("%d %d\n", idx, fwd_id);
      checksum = checksum + (fwd_id * idx);
      blocks--;
      idx++;
    }
    fwd_id++;
    fwd_ptr++;
    /* z = getchar(); */

    free_blocks = buff[fwd_ptr] - '0';
    while (free_blocks && (fwd_id < bwd_id)) {
      if (buff[bwd_ptr] == '0') {
        // move to next memory block
        bwd_ptr -= 2;
        bwd_id--;
      }
      checksum = checksum + (bwd_id * idx);
      printf("%d %d\n", idx, bwd_id);
      idx++;
      free_blocks--;
      buff[bwd_ptr] -= 1;
    }
    fwd_ptr++;
    /* z = getchar(); */
  }

  blocks = buff[fwd_ptr] - '0';
  while (blocks) {
    printf("%d %d\n", idx, bwd_id);
    checksum = checksum + (fwd_id * idx);
    blocks--;
    idx++;
  }

  printf("\nchecksum: %lld\n", checksum);
}
