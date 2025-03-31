#include <stdio.h>

char s[]="Esto es una prueba";
char i;
char *p;

int main (void)
{
for (i=0 ; i<15 ; i++)
putchar( s[i] ); //s[i]==*(s+i)
p=s;
for (i=0 ; i<15 ; i++)
putchar(*p++); //p se modifica

return 0;
}