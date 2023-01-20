#include <unistd.h>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>

#include "functions.cpp"

int main(int argc, char** argv) {
  
  signed char* option = (signed char*)malloc(sizeof(signed char));

  bool sizeopt = false;

  char* filepath = NULL;

  long double filesize = 0;
  char* filesizeunits = (char*)malloc(3*sizeof(char));

  opterr = 0;

  while ((*option = getopt(argc, argv, ":?sf:hv")) != -1) {
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
      case 'f': {
                  if (filepath != NULL) {
                    free(filepath);
                    filepath = NULL;
                  }
                  filepath = (char*)malloc((strlen(optarg)+1)*sizeof(char*));
                  if (filepath == NULL) {
                    fprintf(stderr, "Could not allocate memory.\n");
                  }
                  memcpy(filepath, optarg, strlen(optarg));
                  filepath[strlen(optarg)] = '\0';
                  break;
                } 
      case 's': {
                  sizeopt = true;
                }
    }
  }
  
  free(option);

  if (sizeopt == true) {
    filesize = getfilesize(filepath, filesizeunits);
    if (filesize == -1) {
      fprintf(stderr, "Could not open %s.\n", filepath);
      exit(EXIT_FAILURE);
    }
    if (filesize == -2 || filesize == -3) {
      fprintf(stderr, "Could not work with file %s.\n", filepath);
      exit(EXIT_FAILURE);
    }
    printf("Size of %s is %Lf%s\n", filepath, filesize, filesizeunits);
  }

  return EXIT_SUCCESS;

}
