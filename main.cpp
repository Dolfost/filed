#include <unistd.h>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>

#include "functions.cpp"

int main(int argc, char** argv) {
  
  signed char* option = (signed char*)malloc(sizeof(signed char));

  while ((*option = getopt(argc, argv, ":?hvi")) != -1) {
    switch (*option) {
      case 'h': {
                  printf("This is a help.\n");
                  exit(EXIT_SUCCESS);
                }
      case 'v': {
                  printf("program v0.1,\n2022, Ukraine.\n");
                  exit(EXIT_SUCCESS);
                }
      case ':': {
                  fprintf(stderr, "No argument provided for %s option.\n", argv[optind-2]);
                  exit(EXIT_FAILURE);
                }
      case '?': {
                  fprintf(stderr, "Unknown option %s found.\n", argv[optind-1]);
                  exit(EXIT_FAILURE);
                }
    }

  }

  return EXIT_SUCCESS;

}
