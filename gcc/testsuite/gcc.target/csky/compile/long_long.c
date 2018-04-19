/* { dg-do compile } */
/* { dg-skip-if  ""  { csky-*-* }  { "-march=ck801" }  { ""  }  }  */
/* { dg-final { scan-assembler "\[ |\t\]addi\[ |\t\].*\n\[ |\t\]cmpnei.*\n\[ |\t\]incf.*" } } */

#include <stdio.h>

int main()
{
    long long int i=0;
    for(;i<100;i++)
    {
        printf("%lld\n",i);
    }
    return 0;
}
