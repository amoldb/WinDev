// crt_fgets.c
// This program uses fgets to display
// the first line from a file.

#include <stdio.h>

int main( void )
{
   FILE *stream;
   char line[100];

   if( fopen_s( &stream, "StringVector.c", "r" ) == 0 )
   {
      while(fgets(line, 100, stream) != NULL)
         printf( "%s", line);
      fclose( stream );
   }
}