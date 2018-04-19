/* Check the __CSKYBE__ and __CSKYLE__ macros are accurate.  */
/* { dg-do run } */
extern void abort (void);
extern void exit (int);

short foo = 1;
int main ()
{
  char *p = (char *) &foo;

#ifdef __CSKYBE__
  if (p[0] != 0 || p[1] != 1)
#else
  if (p[0] != 1 || p[1] != 0)
#endif
    abort ();
  exit (0);
}
