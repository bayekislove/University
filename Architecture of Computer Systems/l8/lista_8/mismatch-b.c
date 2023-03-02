/* mismatch-b.c */
#include <stdio.h>

char main;

void p2() {
  main = 'a';
  printf("0x%x\n", main);
}
