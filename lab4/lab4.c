#define _DEFAULT_SOURCE
#define BUF_SIZE 128
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  // if (len < 0) {
  //  handle_error("snprintf");
  //}
  write(STDOUT_FILENO, buf, len);
}

struct header {
  uint64_t size;
  struct header *next;
};

int main() {
  // Increase heap size by 256 bytes
  void *newptr = sbrk(256);
  void *ptr2 = newptr + 128;

  // Create memory block 1
  struct header *block1 = (struct header *)newptr;
  block1->next = NULL;
  block1->size = 128;
  // Initialize data of this memory block after header to 0
  memset(newptr + sizeof(struct header), 0, 128 - sizeof(struct header));

  // Create memory block 2
  struct header *block2 = (struct header *)ptr2;
  block2->next = block1;
  block2->size = 128;
  // Initialize data of memory block after header to 1
  memset(ptr2 + sizeof(struct header), 1, 128 - sizeof(struct header));

  // Print starting address
  print_out("Block 1 Starting Address: %p\n", &block1, sizeof(&block1));
  print_out("Block 2 Starting Address: %p\n", &block2, sizeof(&block2));

  // Print size
  print_out("Block 1 .size: %d\n", &block1->size, sizeof(&block1->size));
  print_out("Block 2 .size: %d\n", &block2->size, sizeof(&block2->size));

  // print next
  print_out("Block 1 .next: %p\n", &block1->next, sizeof(&block1->next));
  print_out("Block 2 .next: %p\n", &block2->next, sizeof(&block2->next));

  // print each byte (excluding header)
  print_out("Block 1 each byte:\n", newptr, 0);
  for (void *i = newptr + sizeof(struct header); i < newptr - sizeof(struct header) + 128; i++) {
    // Need %hhu not %d
    print_out("%hhu\n", i, 1);
  }
  print_out("Block 2 each byte:\n", ptr2, 0);
  for (void *i = ptr2 + sizeof(struct header); i < ptr2 - sizeof(struct header) + 128; i++) {
    print_out("%hhu\n", i, 1);
  }
}
