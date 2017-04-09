/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v1"  { csky-*-* }  { "-march=*" }  { "-march=ck\[56\]*"  }  }  */
/* { dg-options "-O0" } */
/* { dg-final { scan-assembler-times "jb\[tf\]" 12 } } */

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

