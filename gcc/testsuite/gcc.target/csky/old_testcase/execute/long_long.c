/* { dg-do run } */
/* { dg-skip-if  ""  { csky-*-* }  { "-march=ck801" }  { ""  }  }  */

#include <stdio.h>

int main()
{
    long long int i=0;
    for(;i<100;i++)
    {
        printf("%lld\n",i);
    }
    if ( i==100 )
    {
        return 0;
    }
    else
        return 1;
}
