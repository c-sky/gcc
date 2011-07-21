/* { dg-do compile  { target i?86-*-linux* x86_64-*-linux* } } */
/* { dg-options "-O2 -fdump-tree-optimized -fdisable-tree-einline=foo2 -fdisable-ipa-inline -Wno-attributes" } */
int g;
__attribute__((always_inline)) void bar (void)
{
  g++;
}

int foo (void)
{
  bar ();
  return g;
}

int foo2 (void)
{
  bar();
  return g + 1;
}

/* { dg-final { scan-tree-dump-times "bar" 4 "optimized" } } */
/* { dg-final { cleanup-tree-dump "optimized" } } */
