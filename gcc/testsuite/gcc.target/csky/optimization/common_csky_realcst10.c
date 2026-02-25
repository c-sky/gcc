/* { dg-do compile } */

/* { dg-options "-O2  -fdump-tree-original -freal-cst" } */
/* { dg-final { scan-tree-dump "a > 1100" "original" } } */

#define THRESHOLD  1000.6
#define HYSTERISIS (0.1*THRESHOLD)
int foo(int a){
  int sum = 0;
  if(a >= (THRESHOLD + HYSTERISIS))
    sum+=100;
  return sum;
}
