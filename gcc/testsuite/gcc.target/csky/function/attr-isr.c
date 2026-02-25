/* { dg-do assemble } */
/* { dg-options "--save-temps" } */

__attribute__((isr)) void func(void)
{
}

/* { dg-final { cleanup-saved-temps } } */
