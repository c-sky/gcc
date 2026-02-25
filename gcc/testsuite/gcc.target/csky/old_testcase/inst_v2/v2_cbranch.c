/* { dg-do compile } */
/* { dg-options "-O0" } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler-times "test1.*\[ |\t\]jbhz.*test1" 1 } } */
/* { dg-final { scan-assembler-times "test2.*\[ |\t\]jblz.*test2" 1 } } */
/* { dg-final { scan-assembler-times "test3.*\[ |\t\]jbhsz.*test3" 1 } } */
/* { dg-final { scan-assembler-times "test4.*\[ |\t\]jblsz.*test4" 1 } } */
/* { dg-final { scan-assembler-times "test5.*\[ |\t\]jbez.*test5" 1 } } */
/* { dg-final { scan-assembler-times "test6.*\[ |\t\]jbnez.*test6" 1 } } */
/* { dg-final { scan-assembler-times "test7.*\[ |\t\]cmpne.*jbf.*test7" 1 } } */
/* { dg-final { scan-assembler-times "test8.*\[ |\t\]cmpne.*jbt.*test8*" 1 } } */
/* { dg-final { scan-assembler-times "test9.*\[ |\t\]jb\[tf\].*test9" 1 } } */
/* { dg-final { scan-assembler-times "test10.*\[ |\t\]jb\[tf\].*test10" 1 } } */
/* { dg-final { scan-assembler-times "test11.*\[ |\t\]jb\[tf\].*test11" 1 } } */
/* { dg-final { scan-assembler-times "test12.*\[ |\t\]jb\[tf\]" 1 } } */

#define TEST(n,c) int test##n(int a) \
{                      \
    if(c)goto l##n;    \
    a+=2;              \
l##n:                  \
    return a;          \
}

int b=1;

TEST(1,a >0)
TEST(2,a <0)
TEST(3,a>=0)
TEST(4,a<=0)
TEST(5,a==0)
TEST(6,a!=0)
TEST(7,a==b)
TEST(8,a!=b)
TEST(9,a >b)
TEST(10,a <b)
TEST(11,a>=b)
TEST(12,a<=b)

