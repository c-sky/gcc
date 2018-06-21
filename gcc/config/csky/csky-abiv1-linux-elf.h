/******************************************************************
 *               Run-time Target Specification                    *
 ******************************************************************/

#undef STARTFILE_SPEC
#define STARTFILE_SPEC                                                        \
  "%{!shared: %{pg|p|profile:gcrt1.o%s;pie:Scrt1.o%s;:crt1.o%s}}              \
  crti.o%s %{static:crtbeginT.o%s;shared|pie:crtbeginS.o%s;:crtbegin.o%s}"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC \
  "%{shared|pie:crtendS.o%s;:crtend.o%s} crtn.o%s"

#undef CC1_SPEC
#define CC1_SPEC  \
  "%{EB:-EB}      \
   %{EL:-EL}      \
  "

#undef ASM_SPEC
#define ASM_SPEC                \
  "%{mbig-endian:-mbig-endian}  \
  %{EB:-EB}                     \
  %{EL:-EL}                     \
  %{fpic|fPIC:-pic}             \
  %{mcpu=*:-mcpu=%*}            \
  %{march=*:-march=%*}          \
  %{mhard-float:-mhard-float}   \
  %{mfloat-abi=hard:-mhard-float}   \
  %{mdsp:-mdsp}                 \
  %{mmac:-mmac}                 \
  %{manchor:-manchor}           \
  %{mkstq:-mkstq}               \
  %{mkstq2:-mkstq2}             \
  %{mkstq3:-mkstq3}             \
  "

#define GLIBC_DYNAMIC_LINKER  "/lib/ld.so.1"

#define LINUX_TARGET_LINK_SPEC  "%{h*} %{version:-v}            \
   %{b}                                                         \
   %{static:-Bstatic}                                           \
   %{shared:-shared}                                            \
   %{symbolic:-Bsymbolic}                                       \
   %{!static:                                                   \
     %{rdynamic:-export-dynamic}                                \
     %{!shared:-dynamic-linker " GNU_USER_DYNAMIC_LINKER "}}    \
   -X                                                           \
   %{mbig-endian:-EB} %{mlittle-endian:-EL}                     \
   %{EB:-EB} %{EL:-EL}"


#undef  LINK_SPEC
#define LINK_SPEC LINUX_TARGET_LINK_SPEC


#undef  LIB_SPEC
#define LIB_SPEC \
  "%{pthread:-lpthread} -lc"
/* FIXME add this to LIB_SPEC when need */
/*   %{!shared:%{profile:-lc_p}%{!profile:-lc}}" */

#define LIBGCC_SPEC "%{mccrt: -lcc-rt;!mccrt: -lgcc}"

#define TARGET_OS_CPP_BUILTINS()            \
  do                                        \
    {                                       \
    GNU_USER_TARGET_OS_CPP_BUILTINS();      \
    }                                       \
  while (0)

/* In crtstuff.c to control section in where code resides.
   We have to write it as asm code.  */
#ifdef __PIC__
#ifdef __CSKYABIV2__
#define CRT_CALL_STATIC_FUNCTION(SECTION_OP, FUNC)  \
  asm (SECTION_OP "\n"                              \
       "\tgrs\tr3, .Lgetpc_"#FUNC"\n\t"             \
       ".Lgetpc_"#FUNC":\n\t"                       \
       "\tlrw\tr2,\t.Lgetpc_"#FUNC"@GOTPC\n\t"      \
       "\taddu\tr3, r2\n\t"                         \
       "\tlrw\tr2, "#FUNC"@GOTOFF\n\t"              \
       "\taddu\tr2, r3\n\t"                         \
       "\tjsr\tr2\n\t");                            \
       FORCE_CODE_SECTION_ALIGN                     \
       asm( TEXT_SECTION_ASM_OP);
#else
#define CRT_CALL_STATIC_FUNCTION(SECTION_OP, FUNC)  \
  asm (SECTION_OP "\n"                              \
       "\tbsr\t.Lgetpc_"#FUNC"\n\t"                 \
       ".Lgetpc_"#FUNC":\n\t"                       \
       "\tlrw\tr7,\t.Lgetpc_"#FUNC"@GOTPC\n\t"      \
       "\taddu\tr7, r15\n\t"                        \
       "\tlrw\tr6, "#FUNC"@GOTOFF\n\t"              \
       "\taddu\tr6, r7\n\t"                         \
       "\tjsr\tr6\n\t");                            \
       FORCE_CODE_SECTION_ALIGN                     \
       asm( TEXT_SECTION_ASM_OP);
#endif
#endif

#undef CPP_SPEC
#define CPP_SPEC "%{posix:-D_POSIX_SOURCE} %{pthread:-D_REENTRANT}"

/*
#define DONT_USE_BUILTIN_SETJMP 1
#define JMP_BUF_SIZE  76
*/
#undef FUNCTION_PROFILER
#define SAVE_LR     \
  "subi\tsp, 4\n\tstw\tlr, (sp)"
#define FUNCTION_PROFILER(file, labelno)                \
{                                                       \
    fprintf(file, "\t%s\n\tjbsr\t_mcount\n", SAVE_LR);  \
}
#define NO_PROFILE_COUNTERS 1
/* This flag used to enable or disable the sepical
   features only for linux toolchain.  */
#define TARGET_CSKY_LINUX 1

/* Clear the instruction cache from `BEG' to `END'.  This makes a
   call to the ARM_SYNC_ICACHE architecture specific syscall.  */
#define CLEAR_INSN_CACHE(BEG, END)                      \
  cacheflush (BEG, END-BEG, 3)
