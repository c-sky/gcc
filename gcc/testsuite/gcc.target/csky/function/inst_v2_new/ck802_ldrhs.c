/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck802"  { csky-*-* }  { "*" }  { "-mcpu=ck802*"  }  }  */
/* { dg-options "-O2" } */

short* table;

char* bar(char* src)
{
  int code = *src;
  return src + table[code];
}

signed char* table2;
signed char* foo(signed char* src)
{
  int code = *src;
  return src + table2[code];
}

/* { dg-final { scan-assembler-not "ldr\.hs" } }*/
/* { dg-final { scan-assembler-not "ldr\.bs" } }*/
