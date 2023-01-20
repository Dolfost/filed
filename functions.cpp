#include "functions.hpp"

long double getfilesize(const char* filename, char* units) {
  FILE* file = fopen(filename, "rb");

  if (file == NULL) {
    return -1;
  }
  
  if (fseek(file, 0L, SEEK_END) != 0) 
    return -2;

  long int b = ftell(file);
  if (b == -1L)
    return -3;

  long int kb = 0, mb = 0, gb = 0, tb = 0;
  long double result;

  if (b >= 1024) {
    kb = b/1024;
    b = b%1024;
  }
  if  (kb >= 1024) {
    mb = kb/1024;
    kb = kb%1024;
  }
  if (mb >= 1024) {
    gb = mb/1024;
    mb = mb%1024;
  }
  if (gb >= 1024) {
    tb = gb/1024;
    gb = gb%1024;
  }

  if (tb != 0) {
    strcpy(units, "TB");
    result = (long double)tb + (long double)gb/1024 + (long double)mb/2048 + (long double)kb/4096 + (long double)b/8192;
  }
  else if (gb != 0) {
    strcpy(units, "GB");
    result = (long double)gb + (long double)mb/1024 + (long double)kb/2048 + (long double)b/4096;

  }
  else if (mb != 0) {
    strcpy(units, "MB");
    result = (long double)mb + (long double)kb/1024 + (long double)b/2048;
  }
  else if (kb != 0) {
    strcpy(units, "KB");
    result = (long double)kb + (long double)b/1024;
  }
  else {
    strcpy(units, "B");
    result = (long double)b;
  }

  return result;
}

