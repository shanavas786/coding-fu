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
  char buff2[65536];
  fgets(buff, sizeof(buff), file);
  int len = strlen(buff) - 1; // strip new line
  strcpy(buff2, buff);

  int fwd_id = 0;
  int bwd_id = (len - 1) / 2;
  int idx = 0;
  int fwd_ptr = 0;
  int bwd_ptr = len - 1;
  int blocks;

  while (fwd_id < bwd_id) {
    blocks = buff[fwd_ptr] - '0';
    while (blocks) {
      /* printf("%d %d\n", idx, fwd_id); */
      checksum = checksum + (fwd_id * idx);
      blocks--;
      idx++;
    }
    fwd_id++;
    fwd_ptr++;

    blocks = buff[fwd_ptr] - '0';
    while (blocks && (fwd_id < bwd_id)) {
      if (buff[bwd_ptr] == '0') {
        // move to next memory block
        bwd_ptr -= 2;
        bwd_id--;
      }
      checksum = checksum + (bwd_id * idx);
      /* printf("%d %d\n", idx, bwd_id); */
      idx++;
      blocks--;
      buff[bwd_ptr] -= 1;
    }
    fwd_ptr++;
  }

  blocks = buff[fwd_ptr] - '0';
  while (blocks) {
    /* printf("%d %d\n", idx, bwd_id); */
    checksum = checksum + (fwd_id * idx);
    blocks--;
    idx++;
  }

  printf("\nchecksum: %lld\n", checksum);

  int file_sizes[65536]; // fileid to file size
  int file_idxs[65536];  // file id to start idx
  int total_memory = 0;
  checksum = 0;

  for (int i = 0; i < len; i++) {
    total_memory += buff2[i] - '0';
  }

  int *free_blocks = calloc(total_memory, sizeof(int));
  idx = 0;
  int fid = 0;
  for (int i = 0; i < len - 1; i += 2) {
    blocks = buff2[i] - '0';
    file_sizes[fid] = blocks;
    file_idxs[fid] = idx;
    idx += blocks;

    fid++;
    blocks = buff2[i + 1] - '0';
    free_blocks[idx] = blocks;
    idx += blocks;
  }

  blocks = buff2[len - 1] - '0';
  file_sizes[fid] = blocks;
  file_idxs[fid] = idx;
  idx += blocks;

  for (int fid = (len - 1) / 2; fid > 0; fid--) {
    blocks = file_sizes[fid];
    // search for free block that fits
    for (int free_idx = 0; free_idx < file_idxs[fid]; free_idx++) {
      if (blocks <= free_blocks[free_idx]) {
        int rem_blocks = free_blocks[free_idx] - blocks;
        // found one
        for (int i = 0; i < blocks; i++) {
          free_blocks[free_idx + i] = 0;
        }
        free_blocks[free_idx + blocks] = rem_blocks;
        file_idxs[fid] = free_idx;
        break;
      }
    }
  }

  for (int fid = 0; fid <= (len - 1) / 2; fid++) {
    idx = file_idxs[fid];
    blocks = file_sizes[fid];
    for (int i = 0; i < blocks; i++) {
      checksum += (idx + i) * fid;
    }
  }

  free(free_blocks);
  fclose(file);
  printf("\nchecksum: %lld\n", checksum);
}
