/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-options "-O0" } */
/* { dg-final { scan-assembler-times "q2h_uv.*\[ |\t\]ld\.b.*q2h_uv" 1 } } */
/* { dg-final { scan-assembler-times "q2h_sv.*\[ |\t\]ld\.bs.*q2h_sv" 1 } } */
/* { dg-final { scan-assembler-times "q2s_uv.*\[ |\t\]ld\.b.*q2s_uv" 1 } } */
/* { dg-final { scan-assembler-times "q2s_sv.*\[ |\t\]ld\.bs.*q2s_sv" 1 } } */
/* { dg-final { scan-assembler-times "q2d_uv.*\[ |\t\]ld\.b.*q2d_uv" 1 } } */
/* { dg-final { scan-assembler-times "q2d_sv.*\[ |\t\]ld\.bs.*q2d_sv" 1 } } */
/* { dg-final { scan-assembler-times "h2s_uv.*\[ |\t\]ld\.h.*h2s_uv" 1 } } */
/* { dg-final { scan-assembler-times "h2s_sv.*\[ |\t\]ld\.hs.*h2s_sv" 1 } } */
/* { dg-final { scan-assembler-times "h2d_uv.*\[ |\t\]ld\.h.*h2d_uv" 1 } } */
/* { dg-final { scan-assembler-times "h2d_sv.*\[ |\t\]ld\.hs.*h2d_sv" 1 } } */
/* { dg-final { scan-assembler-times "s2d_uv.*\[ |\t\]ldw.*s2d_uv" 1 } } */
/* { dg-final { scan-assembler-times "s2d_sv.*\[ |\t\]ldw.*s2d_sv" 1 } } */


/* { dg-final { scan-assembler-times "q2h_u.*\[ |\t\]zextb.*q2h_u" 1 } } */
/* { dg-final { scan-assembler-times "q2h_s.*\[ |\t\]sextb.*q2h_s" 1 } } */
/* { dg-final { scan-assembler-times "q2s_u.*\[ |\t\]zextb.*q2s_u" 1 } } */
/* { dg-final { scan-assembler-times "q2s_s.*\[ |\t\]sextb.*q2s_s" 1 } } */
/* { dg-final { scan-assembler-times "q2d_u.*\[ |\t\]zextb.*q2d_u" 1 } } */
/* { dg-final { scan-assembler-times "q2d_s.*\[ |\t\]sextb.*q2d_s" 1 } } */
/* { dg-final { scan-assembler-times "h2s_u.*\[ |\t\]zexth.*h2s_u" 1 } } */
/* { dg-final { scan-assembler-times "h2s_s.*\[ |\t\]sexth.*h2s_s" 1 } } */
/* { dg-final { scan-assembler-times "h2d_u.*\[ |\t\]zexth.*h2d_u" 1 } } */
/* { dg-final { scan-assembler-times "h2d_s.*\[ |\t\]sexth.*h2d_s" 1 } } */
/* { dg-final { scan-assembler-times "s2d_u.*\[ |\t\]mov.*s2d_u" 1 } } */
/* { dg-final { scan-assembler-times "s2d_s.*\[ |\t\]mov.*s2d_s" 1 } } */

#define TEST1(n,T1,T2) signed   T1 test_##n##_s (){signed T2 v=-1;            T1 d=(T1)v; return d;}
#define TEST2(n,T1,T2) unsigned T1 test_##n##_u (){unsigned T2 v=-1;          T1 d=(T1)v; return d;}
#define TEST3(n,T1,T2) signed   T1 test_##n##_sv(){volatile signed T2 v=-1;   T1 d=(T1)v; return d;}
#define TEST4(n,T1,T2) unsigned T1 test_##n##_uv(){volatile unsigned T2 v=-1; T1 d=(T1)v; return d;}

#define TEST(n,A,B) TEST1(n,A,B) TEST2(n,A,B) TEST3(n,A,B) TEST4(n,A,B)

#define RUN(A,B,v) RESULT1(A,B,v)  RESULT2(A,B,v) RESULT3(A,B,v) RESULT4(A,B,v)

TEST(q2h, short    , char)
TEST(q2s, int      , char)
TEST(q2d, long long, char)
TEST(h2s, int      , short)
TEST(h2d, long long, short)
TEST(s2d, long long, int)

