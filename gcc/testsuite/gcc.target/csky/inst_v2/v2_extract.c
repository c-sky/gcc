/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-options "-O2" } */
/* { dg-final { scan-assembler-times "test_sext:.*\[ |\t\]sext.*test_sext" 1 } } */
/* { dg-final { scan-assembler-times "test_zext:.*\[ |\t\]zext.*test_zext" 1 } } */
/* { dg-final { scan-assembler-times "test_ins:.*\[ |\t\]ins.*test_ins" 1 } } */

signed int test_sext(int v)
{
    signed char  c;
    c= (v>>16) & 0xff;
    return (signed int)c;
}


unsigned int test_zext(unsigned int v)
{
    unsigned char c;
    c = (v>>16) & 0xff;
    return c;
}

unsigned int test_ins(unsigned int u,unsigned int v)
{
    return (u&0xff00ffff) | ((v&0xff)<<16);
}

int main()
{
    if(test_sext(0x11812222)!=0xFFFFFF81)return 1;
    if(test_zext(0x11812222)!=0x00000081)return 1;
    if(test_ins(0x00110000,0x22)!=0x00220000)return 1;
    return 0;
}

