/** Copyright (C) 2013 Free Software Foundation, Inc.
  This generated file meltrunsup.h is part of GCC.

                  [DON'T EDIT THIS GENERATED FILE]

    GCC is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3, or (at your option)
    any later version.

    GCC is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GCC; see the file COPYING3.  If not see
    <http://www.gnu.org/licenses/>.
**/



/** from generate_runtypesupport_enum_objmagic **/
enum meltobmag_en /*generated*/ { MELTOBMAG__NONE = 0,

                                  MELTOBMAG__FIRST /* first valid object magic */ =20000,

                                  /* value descriptor object magic */
                                  /*valdesc #1 VALDESC_BUCKETLONGS*/
                                  MELTOBMAG_BUCKETLONGS /*valmagic*/ =20000,

                                  /*valdesc #2 VALDESC_CLOSURE*/
                                  MELTOBMAG_CLOSURE /*valmagic*/ =20001,

                                  /*valdesc #3 VALDESC_DECAY*/
                                  MELTOBMAG_DECAY /*valmagic*/ =20002,

                                  /*valdesc #4 VALDESC_HOOK*/
                                  MELTOBMAG_HOOK /*valmagic*/ =20003,

                                  /*valdesc #5 VALDESC_INT*/
                                  MELTOBMAG_INT /*valmagic*/ =20004,

                                  /*valdesc #6 VALDESC_LIST*/
                                  MELTOBMAG_LIST /*valmagic*/ =20005,

                                  /*valdesc #7 VALDESC_MAPOBJECTS*/
                                  MELTOBMAG_MAPOBJECTS /*valmagic*/ =20006,

                                  /*valdesc #8 VALDESC_MAPSTRINGS*/
                                  MELTOBMAG_MAPSTRINGS /*valmagic*/ =20007,

                                  /*valdesc #9 VALDESC_MIXBIGINT*/
                                  MELTOBMAG_MIXBIGINT /*valmagic*/ =20008,

                                  /*valdesc #10 VALDESC_MIXINT*/
                                  MELTOBMAG_MIXINT /*valmagic*/ =20009,

                                  /*valdesc #11 VALDESC_MIXLOC*/
                                  MELTOBMAG_MIXLOC /*valmagic*/ =20010,

                                  /*valdesc #12 VALDESC_MULTIPLE*/
                                  MELTOBMAG_MULTIPLE /*valmagic*/ =20011,

                                  /*valdesc #13 VALDESC_OBJECT*/
                                  MELTOBMAG_OBJECT /*valmagic*/ =20012,

                                  /*valdesc #14 VALDESC_PAIR*/
                                  MELTOBMAG_PAIR /*valmagic*/ =20013,

                                  /*valdesc #15 VALDESC_REAL*/
                                  MELTOBMAG_REAL /*valmagic*/ =20014,

                                  /*valdesc #16 VALDESC_ROUTINE*/
                                  MELTOBMAG_ROUTINE /*valmagic*/ =20015,

                                  /*valdesc #17 VALDESC_SPECIAL_DATA*/
                                  MELTOBMAG_SPECIAL_DATA /*valmagic*/ =20016,

                                  /*valdesc #18 VALDESC_STRBUF*/
                                  MELTOBMAG_STRBUF /*valmagic*/ =20017,

                                  /*valdesc #19 VALDESC_STRING*/
                                  MELTOBMAG_STRING /*valmagic*/ =20018,

                                  /* ctype gty object magic */
                                  /*gtyctype #1 CTYPE_BASIC_BLOCK*/
                                  MELTOBMAG_BASICBLOCK /*boxedmagic*/ =20019,
                                  MELTOBMAG_MAPBASICBLOCKS /*mapmagic*/ =20020,
                                  /*gtyctype #2 CTYPE_BITMAP*/
                                  MELTOBMAG_BITMAP /*boxedmagic*/ =20021,
                                  MELTOBMAG_MAPBITMAPS /*mapmagic*/ =20022,
                                  /*gtyctype #3 CTYPE_EDGE*/
                                  MELTOBMAG_EDGE /*boxedmagic*/ =20023,
                                  MELTOBMAG_MAPEDGES /*mapmagic*/ =20024,
                                  /*gtyctype #4 CTYPE_GIMPLE*/
                                  MELTOBMAG_GIMPLE /*boxedmagic*/ =20025,
                                  MELTOBMAG_MAPGIMPLES /*mapmagic*/ =20026,
                                  /*gtyctype #5 CTYPE_GIMPLE_SEQ*/
                                  MELTOBMAG_GIMPLESEQ /*boxedmagic*/ =20027,
                                  MELTOBMAG_MAPGIMPLESEQS /*mapmagic*/ =20028,
                                  /*gtyctype #6 CTYPE_LOOP*/
                                  MELTOBMAG_LOOP /*boxedmagic*/ =20029,
                                  MELTOBMAG_MAPLOOPS /*mapmagic*/ =20030,
                                  /*gtyctype #7 CTYPE_RTVEC*/
                                  MELTOBMAG_RTVEC /*boxedmagic*/ =20031,
                                  MELTOBMAG_MAPRTVECS /*mapmagic*/ =20032,
                                  /*gtyctype #8 CTYPE_RTX*/
                                  MELTOBMAG_RTX /*boxedmagic*/ =20033,
                                  MELTOBMAG_MAPRTXS /*mapmagic*/ =20034,
                                  /*gtyctype #9 CTYPE_TREE*/
                                  MELTOBMAG_TREE /*boxedmagic*/ =20035,
                                  MELTOBMAG_MAPTREES /*mapmagic*/ =20036,
                                  MELTOBMAG__LAST
                                }; /* end generated enum meltobmag_en */
#define MELT_COUNT_GENERATED_OBJMAGIC 28
/*** end from generate_runtypesupport_enum_objmagic **/


/** generated by generate_runtypesupport_gty **/

#ifndef meltobject_ptr_t_TYPEDEFINED
typedef struct meltobject_st* meltobject_ptr_t ;
#define meltobject_ptr_t_TYPEDEFINED
#endif /*meltobject_ptr_t_TYPEDEFINED*/


#ifndef melt_ptr_t_TYPEDEFINED
typedef union melt_un* melt_ptr_t ;
#define melt_ptr_t_TYPEDEFINED
#endif /*melt_ptr_t_TYPEDEFINED*/


#ifndef meltroutine_ptr_t_TYPEDEFINED
typedef struct meltroutine_st *meltroutine_ptr_t ;
#define meltroutine_ptr_t_TYPEDEFINED
#endif /*meltroutine_ptr_t_TYPEDEFINED*/


#ifndef meltclosure_ptr_t_TYPEDEFINED
typedef struct meltclosure_st *meltclosure_ptr_t ;
#define meltclosure_ptr_t_TYPEDEFINED
#endif /*meltclosure_ptr_t_TYPEDEFINED*/


#ifndef meltroutfun_t_TYPEDEFINED
typedef melt_ptr_t meltroutfun_t (struct meltclosure_st* meltclosp_,
                                  melt_ptr_t meltfirstargp_,
                                  const melt_argdescr_cell_t meltxargdescr_[],
                                  union meltparam_un *meltxargtab_,
                                  const melt_argdescr_cell_t meltxresdescr_[],
                                  union meltparam_un *meltxrestab_) ;
#define meltroutfun_t_TYPEDEFINED
#endif /*meltroutfun_t_TYPEDEFINED*/


/* generated ctype gty structures */


/*gtyctype #1 CTYPE_BASIC_BLOCK*/
struct GTY (()) meltbasicblock_st   /* when MELTOBMAG_BASICBLOCK*/
{
    meltobject_ptr_t discr;
    basic_block val;
};
struct GTY (()) entrybasicblockmelt_st   /* for MELTOBMAG_MAPBASICBLOCKS*/
{
    basic_block e_at;
    melt_ptr_t e_va;
};
struct GTY (()) meltmapbasicblocks_st   /* when MELTOBMAG_MAPBASICBLOCKS*/
{
    /* keep in sync with meltmappointers_st */
    meltobject_ptr_t discr;
    unsigned count;
    unsigned char lenix;
    melt_ptr_t meltmap_aux;
    struct entrybasicblockmelt_st* GTY ((length ("melt_primtab[%h.lenix]"))) entab;
};


/*gtyctype #2 CTYPE_BITMAP*/
struct GTY (()) meltbitmap_st   /* when MELTOBMAG_BITMAP*/
{
    meltobject_ptr_t discr;
    bitmap val;
};
struct GTY (()) entrybitmapmelt_st   /* for MELTOBMAG_MAPBITMAPS*/
{
    bitmap e_at;
    melt_ptr_t e_va;
};
struct GTY (()) meltmapbitmaps_st   /* when MELTOBMAG_MAPBITMAPS*/
{
    /* keep in sync with meltmappointers_st */
    meltobject_ptr_t discr;
    unsigned count;
    unsigned char lenix;
    melt_ptr_t meltmap_aux;
    struct entrybitmapmelt_st* GTY ((length ("melt_primtab[%h.lenix]"))) entab;
};


/*gtyctype #3 CTYPE_EDGE*/
struct GTY (()) meltedge_st   /* when MELTOBMAG_EDGE*/
{
    meltobject_ptr_t discr;
    edge val;
};
struct GTY (()) entryedgemelt_st   /* for MELTOBMAG_MAPEDGES*/
{
    edge e_at;
    melt_ptr_t e_va;
};
struct GTY (()) meltmapedges_st   /* when MELTOBMAG_MAPEDGES*/
{
    /* keep in sync with meltmappointers_st */
    meltobject_ptr_t discr;
    unsigned count;
    unsigned char lenix;
    melt_ptr_t meltmap_aux;
    struct entryedgemelt_st* GTY ((length ("melt_primtab[%h.lenix]"))) entab;
};


/*gtyctype #4 CTYPE_GIMPLE*/
struct GTY (()) meltgimple_st   /* when MELTOBMAG_GIMPLE*/
{
    meltobject_ptr_t discr;
    gimple val;
};
struct GTY (()) entrygimplemelt_st   /* for MELTOBMAG_MAPGIMPLES*/
{
    gimple e_at;
    melt_ptr_t e_va;
};
struct GTY (()) meltmapgimples_st   /* when MELTOBMAG_MAPGIMPLES*/
{
    /* keep in sync with meltmappointers_st */
    meltobject_ptr_t discr;
    unsigned count;
    unsigned char lenix;
    melt_ptr_t meltmap_aux;
    struct entrygimplemelt_st* GTY ((length ("melt_primtab[%h.lenix]"))) entab;
};


/*gtyctype #5 CTYPE_GIMPLE_SEQ*/
struct GTY (()) meltgimpleseq_st   /* when MELTOBMAG_GIMPLESEQ*/
{
    meltobject_ptr_t discr;
    gimple_seq val;
};
struct GTY (()) entrygimpleseqmelt_st   /* for MELTOBMAG_MAPGIMPLESEQS*/
{
    gimple_seq e_at;
    melt_ptr_t e_va;
};
struct GTY (()) meltmapgimpleseqs_st   /* when MELTOBMAG_MAPGIMPLESEQS*/
{
    /* keep in sync with meltmappointers_st */
    meltobject_ptr_t discr;
    unsigned count;
    unsigned char lenix;
    melt_ptr_t meltmap_aux;
    struct entrygimpleseqmelt_st* GTY ((length ("melt_primtab[%h.lenix]"))) entab;
};


/*gtyctype #6 CTYPE_LOOP*/
struct GTY (()) meltloop_st   /* when MELTOBMAG_LOOP*/
{
    meltobject_ptr_t discr;
    loop_p val;
};
struct GTY (()) entryloopmelt_st   /* for MELTOBMAG_MAPLOOPS*/
{
    loop_p e_at;
    melt_ptr_t e_va;
};
struct GTY (()) meltmaploops_st   /* when MELTOBMAG_MAPLOOPS*/
{
    /* keep in sync with meltmappointers_st */
    meltobject_ptr_t discr;
    unsigned count;
    unsigned char lenix;
    melt_ptr_t meltmap_aux;
    struct entryloopmelt_st* GTY ((length ("melt_primtab[%h.lenix]"))) entab;
};


/*gtyctype #7 CTYPE_RTVEC*/
struct GTY (()) meltrtvec_st   /* when MELTOBMAG_RTVEC*/
{
    meltobject_ptr_t discr;
    rtvec val;
};
struct GTY (()) entryrtvecmelt_st   /* for MELTOBMAG_MAPRTVECS*/
{
    rtvec e_at;
    melt_ptr_t e_va;
};
struct GTY (()) meltmaprtvecs_st   /* when MELTOBMAG_MAPRTVECS*/
{
    /* keep in sync with meltmappointers_st */
    meltobject_ptr_t discr;
    unsigned count;
    unsigned char lenix;
    melt_ptr_t meltmap_aux;
    struct entryrtvecmelt_st* GTY ((length ("melt_primtab[%h.lenix]"))) entab;
};


/*gtyctype #8 CTYPE_RTX*/
struct GTY (()) meltrtx_st   /* when MELTOBMAG_RTX*/
{
    meltobject_ptr_t discr;
    rtx val;
};
struct GTY (()) entryrtxmelt_st   /* for MELTOBMAG_MAPRTXS*/
{
    rtx e_at;
    melt_ptr_t e_va;
};
struct GTY (()) meltmaprtxs_st   /* when MELTOBMAG_MAPRTXS*/
{
    /* keep in sync with meltmappointers_st */
    meltobject_ptr_t discr;
    unsigned count;
    unsigned char lenix;
    melt_ptr_t meltmap_aux;
    struct entryrtxmelt_st* GTY ((length ("melt_primtab[%h.lenix]"))) entab;
};


/*gtyctype #9 CTYPE_TREE*/
struct GTY (()) melttree_st   /* when MELTOBMAG_TREE*/
{
    meltobject_ptr_t discr;
    tree val;
};
struct GTY (()) entrytreemelt_st   /* for MELTOBMAG_MAPTREES*/
{
    tree e_at;
    melt_ptr_t e_va;
};
struct GTY (()) meltmaptrees_st   /* when MELTOBMAG_MAPTREES*/
{
    /* keep in sync with meltmappointers_st */
    meltobject_ptr_t discr;
    unsigned count;
    unsigned char lenix;
    melt_ptr_t meltmap_aux;
    struct entrytreemelt_st* GTY ((length ("melt_primtab[%h.lenix]"))) entab;
};


/* value GTY types */

/*gtyvaldesc #1 VALDESC_BUCKETLONGS*/
struct GTY((variable_size)) meltbucketlongs_st /* when MELTOBMAG_BUCKETLONGS */
{
    meltobject_ptr_t discr;
    /* from VALDESC_BUCKETLONGS in warmelt-base.melt */
    melt_ptr_t buckl_aux; /* auxiliary data */
    unsigned char buckl_lenix; /* index in melt_primtab for allocated length */
    int buckl_xnum; /* extra number */
    unsigned buckl_ucount;     /* used count of bucket entries */
    struct melt_bucketlongentry_st GTY ((length("melt_primtab[%h.buckl_lenix]")))
    buckl_entab[MELT_FLEXIBLE_DIM]; /* sorted by increasing ebl_at */

}; /* end meltbucketlongs_st */
/* decl. chunk */
/* decl VALDESC_BUCKETLONGS  in warmelt-base.melt */
typedef struct meltbucketlongs_st* meltbucketlongs_ptr_t;
#ifndef ggc_alloc_meltbucketlongs_st
#define ggc_alloc_meltbucketlongs_st(SIZE) ((struct meltbucketlongs_st *)(ggc_internal_alloc_stat (SIZE MEM_STAT_INFO)))
#endif




/*gtyvaldesc #2 VALDESC_CLOSURE*/
struct GTY((variable_size)) meltclosure_st /* when MELTOBMAG_CLOSURE */
{
    meltobject_ptr_t discr;
    /* from VALDESC_CLOSURE in warmelt-base.melt */
    meltroutine_ptr_t rout;
    unsigned nbval;
    melt_ptr_t GTY ((length ("%h.nbval"))) tabval[MELT_FLEXIBLE_DIM];

}; /* end meltclosure_st */
/* decl. chunk */
/* decl VALDESC_CLOSURE  in warmelt-base.melt */
#define MELT_CLOSURE_STRUCT(N) {                \
    meltobject_ptr_t discr;                     \
    meltroutine_ptr_t rout;			\
    unsigned nbval;                             \
    melt_ptr_t tabval[N+1]; }




/*gtyvaldesc #3 VALDESC_DECAY*/
struct GTY(( mark_hook ("melt_mark_decay"))) meltdecay_st /* when MELTOBMAG_DECAY */
{
    meltobject_ptr_t discr;
    /* from VALDESC_DECAY in warmelt-base.melt */
    melt_ptr_t val;
    unsigned remain;		/* remaining number of marking */

}; /* end meltdecay_st */
/* no decl. chunk */


/*gtyvaldesc #4 VALDESC_HOOK*/
struct GTY((variable_size)) melthook_st /* when MELTOBMAG_HOOK */
{
    meltobject_ptr_t discr;
    /* from VALDESC_HOOK in warmelt-base.melt */
    char hookname[MELT_HOOKNAME_LEN];
    void* GTY ((skip)) hookad;
    melt_ptr_t hookdata;
    unsigned nbval;
    melt_ptr_t GTY ((length ("%h.nbval"))) tabval[MELT_FLEXIBLE_DIM];

}; /* end melthook_st */
/* decl. chunk */
/* decl VALDESC_HOOK  in warmelt-base.melt */
#ifndef melthook_ptr_t_TYPEDEFINED
typedef struct melthook_st *melthook_ptr_t;
#define  melthook_ptr_t_TYPEDEFINED
#endif /*melthook_ptr_t_TYPEDEFINED from VALDESC_ROUTINE */

/* unsafely set inside the melthook_st pointed by Hptr the
   routine function pointer to Hookroot */
#define MELT_HOOK_SET_ROUTCODE(Hptr,Hookrout) do {	\
  ((struct melthook_st*)(Hptr))->hookad		        \
     = (void*) (Hookrout);				\
} while(0)

#define MELT_HOOK_STRUCT(N) {		        \
  meltobject_ptr_t discr;			\
  char hookname[MELT_HOOKNAME_LEN];		\
  void* hookad;			                \
  melt_ptr_t hookdata;				\
  unsigned nbval;				\
  melt_ptr_t tabval[N+1]; }




/*gtyvaldesc #5 VALDESC_INT*/
struct GTY(()) meltint_st /* when MELTOBMAG_INT */
{
    meltobject_ptr_t discr;
    /* from VALDESC_INT in warmelt-base.melt */
    long val;

}; /* end meltint_st */
/* decl. chunk */
/* decl VALDESC_INT in warmelt-base.melt */
typedef struct meltint_st *meltint_ptr_t;
#define melt_unsafe_boxed_int_value(V) (((meltint_ptr_t)(V))->val)
static inline long melt_boxed_int_value(melt_ptr_t v)
{
    return (melt_magic_discr(v)==MELTOBMAG_INT)? melt_unsafe_boxed_int_value(v) : 0L;
}




/*gtyvaldesc #6 VALDESC_LIST*/
struct GTY(()) meltlist_st /* when MELTOBMAG_LIST */
{
    meltobject_ptr_t discr;
    /* from VALDESC_LIST in warmelt-base.melt */
    struct meltpair_st *first;
    struct meltpair_st *last;

}; /* end meltlist_st */
/* decl. chunk */
/* decl VALDESC_LIST in warmelt-base.melt */
typedef struct meltlist_st *meltlist_ptr_t;




/*gtyvaldesc #7 VALDESC_MAPOBJECTS*/
struct GTY(()) meltmapobjects_st /* when MELTOBMAG_MAPOBJECTS */
{
    meltobject_ptr_t discr;
    /* from VALDESC_MAPOBJECTS in warmelt-base.melt */
    unsigned count;
    unsigned char lenix;
    melt_ptr_t meltmap_aux;
    struct entryobjectsmelt_st *GTY ((length ("melt_primtab[%h.lenix]")))
    entab;
    /* the following field is usually the value of entab (for
       objects in the young zone), to allocate the object and its fields
       at once; hence its GTY-ed length is zero */
    struct entryobjectsmelt_st GTY ((length ("0"))) map_space[MELT_FLEXIBLE_DIM];

}; /* end meltmapobjects_st */
/* decl. chunk */
/* decl VALDESC_MAPOBJECTS in warmelt-base.melt */
typedef struct meltmapobjects_st* meltmapobjects_ptr_t;




/*gtyvaldesc #8 VALDESC_MAPSTRINGS*/
struct GTY(()) meltmapstrings_st /* when MELTOBMAG_MAPSTRINGS */
{
    meltobject_ptr_t discr;
    /* from VALDESC_MAPSTRINGS in warmelt-base.melt */
    unsigned count;
    unsigned char lenix;
    melt_ptr_t meltmap_aux;
    struct entrystringsmelt_st *GTY ((length ("melt_primtab[%h.lenix]")))
    entab;

}; /* end meltmapstrings_st */
/* no decl. chunk */


/*gtyvaldesc #9 VALDESC_MIXBIGINT*/
struct GTY((variable_size)) meltmixbigint_st /* when MELTOBMAG_MIXBIGINT */
{
    meltobject_ptr_t discr;
    /* from VALDESC_MIXBIGINT in warmelt-base.melt */
    /* an exported array mpz compatible; since we use an exported mpz format,
       the value can be copied and trashed by MELT garbage collector without
       harm. */
    melt_ptr_t ptrval;
    bool negative;
    unsigned biglen;
    /* no GTY on tabig, it is a array of non-pointer data */
    long tabig[MELT_FLEXIBLE_DIM];

}; /* end meltmixbigint_st */
/* no decl. chunk */


/*gtyvaldesc #10 VALDESC_MIXINT*/
struct GTY(()) meltmixint_st /* when MELTOBMAG_MIXINT */
{
    meltobject_ptr_t discr;
    /* from VALDESC_MIXINT in warmelt-base.melt */
    melt_ptr_t ptrval;
    long intval;

}; /* end meltmixint_st */
/* no decl. chunk */


/*gtyvaldesc #11 VALDESC_MIXLOC*/
struct GTY(()) meltmixloc_st /* when MELTOBMAG_MIXLOC */
{
    meltobject_ptr_t discr;
    /* from VALDESC_MIXLOC in warmelt-base.melt.melt */
    melt_ptr_t ptrval;
    long intval;
    location_t locval;

}; /* end meltmixloc_st */
/* no decl. chunk */


/*gtyvaldesc #12 VALDESC_MULTIPLE*/
struct GTY((variable_size)) meltmultiple_st /* when MELTOBMAG_MULTIPLE */
{
    meltobject_ptr_t discr;
    /* from VALDESC_MULTIPLE in warmelt-base.melt */
    unsigned nbval;
    melt_ptr_t GTY ((length ("%h.nbval"))) tabval[MELT_FLEXIBLE_DIM];

}; /* end meltmultiple_st */
/* decl. chunk */
/* decl VALDESC_MULTIPLE in warmelt-base.melt */
#define MELT_MULTIPLE_STRUCT(N) {               \
    meltobject_ptr_t discr;                     \
    unsigned nbval;                             \
    melt_ptr_t tabval[N+1];  }
typedef struct meltmultiple_st* meltmultiple_ptr_t;




/*gtyvaldesc #13 VALDESC_OBJECT*/
struct GTY((variable_size)) meltobject_st /* when MELTOBMAG_OBJECT */
{
    meltobject_ptr_t discr;
    /* from VALDESC_OBJECT in warmelt-base.melt */
    unsigned obj_hash;		/* hash code of the object */
    unsigned short obj_num;
    unsigned short obj_len;
    melt_ptr_t GTY ((length ("%h.obj_len"))) obj_vartab[MELT_FLEXIBLE_DIM];

}; /* end meltobject_st */
/* decl. chunk */
/* decl VALDESC_OBJECT */
#define meltobj_class discr
#define meltobj_magic obj_num
#define MELT_OBJECT_STRUCT(N) {			\
  meltobject_ptr_t meltobj_class;		\
  unsigned obj_hash;				\
  unsigned short obj_num;			\
  unsigned short obj_len;			\
  melt_ptr_t* obj_vartab[N];			\
  long _gap; }




/*gtyvaldesc #14 VALDESC_PAIR*/
struct GTY(( chain_next ("%h.tl"))) meltpair_st /* when MELTOBMAG_PAIR */
{
    meltobject_ptr_t discr;
    /* from VALDESC_PAIR in warmelt-base.melt */
    melt_ptr_t hd;
    struct meltpair_st *tl;

}; /* end meltpair_st */
/* decl. chunk */
/* decl VALDESC_PAIR in warmelt-base.melt */
typedef struct meltpair_st *meltpair_ptr_t;




/*gtyvaldesc #15 VALDESC_REAL*/
struct GTY(()) meltreal_st /* when MELTOBMAG_REAL */
{
    meltobject_ptr_t discr;
    /* from VALDESC_REAL in warmelt-base.melt */
    REAL_VALUE_TYPE val;

}; /* end meltreal_st */
/* no decl. chunk */


/*gtyvaldesc #16 VALDESC_ROUTINE*/
struct GTY((variable_size)) meltroutine_st /* when MELTOBMAG_ROUTINE */
{
    meltobject_ptr_t discr;
    /* from VALDESC_ROUTINE in warmelt-base.melt */
    char routdescr[MELT_ROUTDESCR_LEN];
    meltroutfun_t* GTY ((skip)) routfunad;
    melt_ptr_t routdata;
    unsigned nbval;
    melt_ptr_t GTY ((length ("%h.nbval"))) tabval[MELT_FLEXIBLE_DIM];

}; /* end meltroutine_st */
/* decl. chunk */
/* decl VALDESC_ROUTINE */
#ifndef meltroutine_ptr_t_TYPEDEFINED
typedef struct meltroutine_st *meltroutine_ptr_t;
#define  meltroutine_ptr_t_TYPEDEFINED
#endif /*meltroutine_ptr_t_TYPEDEFINED from VALDESC_ROUTINE */

/* unsafely set inside the meltroutine_st pointed by Rptr the
   routine function pointer to Rout */
#define MELT_ROUTINE_SET_ROUTCODE(Rptr,Rout) do {	\
  ((struct meltroutine_st*)(Rptr))->routfunad		\
     = (Rout);						\
} while(0)

#define MELT_ROUTINE_STRUCT(N) {		\
  meltobject_ptr_t discr;			\
  char routdescr[MELT_ROUTDESCR_LEN];		\
  meltroutfun_t* routfunad;			\
  melt_ptr_t routdata;				\
  unsigned nbval;				\
  melt_ptr_t tabval[N+1]; }




/*gtyvaldesc #17 VALDESC_SPECIAL_DATA*/
struct GTY(( mark_hook ("melt_mark_specialdata"))) meltspecialdata_st /* when MELTOBMAG_SPECIAL_DATA */
{
    meltobject_ptr_t discr;
    /* from VALDESC_SPECIAL_DATA in warmelt-base.melt */
    int meltspec_mark;
    unsigned meltspec_kind;
    struct meltspecialdata_st *GTY ((skip)) meltspec_next;
    melt_ptr_t meltspec_value;
    struct meltspecialpayload_st GTY ((skip)) meltspec_payload;

}; /* end meltspecialdata_st */
/* no decl. chunk */


/*gtyvaldesc #18 VALDESC_STRBUF*/
struct GTY(()) meltstrbuf_st /* when MELTOBMAG_STRBUF */
{
    meltobject_ptr_t discr;
    /* from VALDESC_STRBUF in warmelt-base.melt */
    /* no GTY on bufzn, it a scalar data */
    char * bufzn;
    unsigned char buflenix;	/* allocated length index of
				   buffer */
    unsigned bufstart;
    unsigned bufend;		/* start & end useful positions */
    /* the following field is usually the value of buf (for
       objects in the young zone), to allocate the object and its fields
       at once; no GTY length on buf_space, since it is a non pointer data. */
    char  buf_space[MELT_FLEXIBLE_DIM];

}; /* end meltstrbuf_st */
/* no decl. chunk */


/*gtyvaldesc #19 VALDESC_STRING*/
struct GTY((variable_size)) meltstring_st /* when MELTOBMAG_STRING */
{
    meltobject_ptr_t discr;
    /* from VALDESC_STRING in warmelt-base.melt */
    unsigned slen;
    char val[MELT_FLEXIBLE_DIM];	/* null terminated */

}; /* end meltstring_st */
/* decl. chunk */
/* decl VALDESC_STRING from warmelt-base.melt */
#define MELT_STRING_STRUCT(N) {			\
  meltobject_ptr_t discr;			\
  unsigned slen;                                \
  char val[(N)+1];	/* null terminated */	\
  long _gap; }



/* our generated MELT union for everything */
typedef union
    GTY ((desc ("%0.u_discr->meltobj_magic"))) melt_un
{
    /*generated melt_un*/
    meltobject_ptr_t GTY ((skip)) u_discr;
    struct meltforward_st GTY ((skip)) u_forward;

    /*union gtyctype #1 CTYPE_BASIC_BLOCK*/
    struct meltbasicblock_st GTY ((tag("MELTOBMAG_BASICBLOCK"))) u_basicblock; /* generated boxed union member */
    struct meltmapbasicblocks_st GTY ((tag("MELTOBMAG_MAPBASICBLOCKS"))) u_mapbasicblocks; /* generated map union member */

    /*union gtyctype #2 CTYPE_BITMAP*/
    struct meltbitmap_st GTY ((tag("MELTOBMAG_BITMAP"))) u_bitmap; /* generated boxed union member */
    struct meltmapbitmaps_st GTY ((tag("MELTOBMAG_MAPBITMAPS"))) u_mapbitmaps; /* generated map union member */

    /*union gtyctype #3 CTYPE_EDGE*/
    struct meltedge_st GTY ((tag("MELTOBMAG_EDGE"))) u_edge; /* generated boxed union member */
    struct meltmapedges_st GTY ((tag("MELTOBMAG_MAPEDGES"))) u_mapedges; /* generated map union member */

    /*union gtyctype #4 CTYPE_GIMPLE*/
    struct meltgimple_st GTY ((tag("MELTOBMAG_GIMPLE"))) u_gimple; /* generated boxed union member */
    struct meltmapgimples_st GTY ((tag("MELTOBMAG_MAPGIMPLES"))) u_mapgimples; /* generated map union member */

    /*union gtyctype #5 CTYPE_GIMPLE_SEQ*/
    struct meltgimpleseq_st GTY ((tag("MELTOBMAG_GIMPLESEQ"))) u_gimpleseq; /* generated boxed union member */
    struct meltmapgimpleseqs_st GTY ((tag("MELTOBMAG_MAPGIMPLESEQS"))) u_mapgimpleseqs; /* generated map union member */

    /*union gtyctype #6 CTYPE_LOOP*/
    struct meltloop_st GTY ((tag("MELTOBMAG_LOOP"))) u_loop; /* generated boxed union member */
    struct meltmaploops_st GTY ((tag("MELTOBMAG_MAPLOOPS"))) u_maploops; /* generated map union member */

    /*union gtyctype #7 CTYPE_RTVEC*/
    struct meltrtvec_st GTY ((tag("MELTOBMAG_RTVEC"))) u_rtvec; /* generated boxed union member */
    struct meltmaprtvecs_st GTY ((tag("MELTOBMAG_MAPRTVECS"))) u_maprtvecs; /* generated map union member */

    /*union gtyctype #8 CTYPE_RTX*/
    struct meltrtx_st GTY ((tag("MELTOBMAG_RTX"))) u_rtx; /* generated boxed union member */
    struct meltmaprtxs_st GTY ((tag("MELTOBMAG_MAPRTXS"))) u_maprtxs; /* generated map union member */

    /*union gtyctype #9 CTYPE_TREE*/
    struct melttree_st GTY ((tag("MELTOBMAG_TREE"))) u_tree; /* generated boxed union member */
    struct meltmaptrees_st GTY ((tag("MELTOBMAG_MAPTREES"))) u_maptrees; /* generated map union member */


    /*union.valdesc #1 VALDESC_BUCKETLONGS*/
    struct meltbucketlongs_st GTY ((tag("MELTOBMAG_BUCKETLONGS"))) u_bucketlongs; /* generated value union member */

    /*union.valdesc #2 VALDESC_CLOSURE*/
    struct meltclosure_st GTY ((tag("MELTOBMAG_CLOSURE"))) u_closure; /* generated value union member */

    /*union.valdesc #3 VALDESC_DECAY*/
    struct meltdecay_st GTY ((tag("MELTOBMAG_DECAY"))) u_decay; /* generated value union member */

    /*union.valdesc #4 VALDESC_HOOK*/
    struct melthook_st GTY ((tag("MELTOBMAG_HOOK"))) u_hook; /* generated value union member */

    /*union.valdesc #5 VALDESC_INT*/
    struct meltint_st GTY ((tag("MELTOBMAG_INT"))) u_int; /* generated value union member */

    /*union.valdesc #6 VALDESC_LIST*/
    struct meltlist_st GTY ((tag("MELTOBMAG_LIST"))) u_list; /* generated value union member */

    /*union.valdesc #7 VALDESC_MAPOBJECTS*/
    struct meltmapobjects_st GTY ((tag("MELTOBMAG_MAPOBJECTS"))) u_mapobjects; /* generated value union member */

    /*union.valdesc #8 VALDESC_MAPSTRINGS*/
    struct meltmapstrings_st GTY ((tag("MELTOBMAG_MAPSTRINGS"))) u_mapstrings; /* generated value union member */

    /*union.valdesc #9 VALDESC_MIXBIGINT*/
    struct meltmixbigint_st GTY ((tag("MELTOBMAG_MIXBIGINT"))) u_mixbigint; /* generated value union member */

    /*union.valdesc #10 VALDESC_MIXINT*/
    struct meltmixint_st GTY ((tag("MELTOBMAG_MIXINT"))) u_mixint; /* generated value union member */

    /*union.valdesc #11 VALDESC_MIXLOC*/
    struct meltmixloc_st GTY ((tag("MELTOBMAG_MIXLOC"))) u_mixloc; /* generated value union member */

    /*union.valdesc #12 VALDESC_MULTIPLE*/
    struct meltmultiple_st GTY ((tag("MELTOBMAG_MULTIPLE"))) u_multiple; /* generated value union member */

    /*union.valdesc #13 VALDESC_OBJECT*/
    struct meltobject_st GTY ((tag("MELTOBMAG_OBJECT"))) u_object; /* generated value union member */

    /*union.valdesc #14 VALDESC_PAIR*/
    struct meltpair_st GTY ((tag("MELTOBMAG_PAIR"))) u_pair; /* generated value union member */

    /*union.valdesc #15 VALDESC_REAL*/
    struct meltreal_st GTY ((tag("MELTOBMAG_REAL"))) u_real; /* generated value union member */

    /*union.valdesc #16 VALDESC_ROUTINE*/
    struct meltroutine_st GTY ((tag("MELTOBMAG_ROUTINE"))) u_routine; /* generated value union member */

    /*union.valdesc #17 VALDESC_SPECIAL_DATA*/
    struct meltspecialdata_st GTY ((tag("MELTOBMAG_SPECIAL_DATA"))) u_special_data; /* generated value union member */

    /*union.valdesc #18 VALDESC_STRBUF*/
    struct meltstrbuf_st GTY ((tag("MELTOBMAG_STRBUF"))) u_strbuf; /* generated value union member */

    /*union.valdesc #19 VALDESC_STRING*/
    struct meltstring_st GTY ((tag("MELTOBMAG_STRING"))) u_string; /* generated value union member */

} melt_un_t /*end generated melt_un*/;


/* cast.valdesc #1 meltbucketlongs_st*/
static inline struct meltbucketlongs_st* meltcast_meltbucketlongs_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_BUCKETLONGS)
        return (struct meltbucketlongs_st*) p;
    return NULL;
} /* end meltcast_meltbucketlongs_st*/


/* cast.valdesc #2 meltclosure_st*/
static inline struct meltclosure_st* meltcast_meltclosure_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_CLOSURE)
        return (struct meltclosure_st*) p;
    return NULL;
} /* end meltcast_meltclosure_st*/


/* cast.valdesc #3 meltdecay_st*/
static inline struct meltdecay_st* meltcast_meltdecay_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_DECAY)
        return (struct meltdecay_st*) p;
    return NULL;
} /* end meltcast_meltdecay_st*/


/* cast.valdesc #4 melthook_st*/
static inline struct melthook_st* meltcast_melthook_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_HOOK)
        return (struct melthook_st*) p;
    return NULL;
} /* end meltcast_melthook_st*/


/* cast.valdesc #5 meltint_st*/
static inline struct meltint_st* meltcast_meltint_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_INT)
        return (struct meltint_st*) p;
    return NULL;
} /* end meltcast_meltint_st*/


/* cast.valdesc #6 meltlist_st*/
static inline struct meltlist_st* meltcast_meltlist_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_LIST)
        return (struct meltlist_st*) p;
    return NULL;
} /* end meltcast_meltlist_st*/


/* cast.valdesc #7 meltmapobjects_st*/
static inline struct meltmapobjects_st* meltcast_meltmapobjects_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_MAPOBJECTS)
        return (struct meltmapobjects_st*) p;
    return NULL;
} /* end meltcast_meltmapobjects_st*/


/* cast.valdesc #8 meltmapstrings_st*/
static inline struct meltmapstrings_st* meltcast_meltmapstrings_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_MAPSTRINGS)
        return (struct meltmapstrings_st*) p;
    return NULL;
} /* end meltcast_meltmapstrings_st*/


/* cast.valdesc #9 meltmixbigint_st*/
static inline struct meltmixbigint_st* meltcast_meltmixbigint_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_MIXBIGINT)
        return (struct meltmixbigint_st*) p;
    return NULL;
} /* end meltcast_meltmixbigint_st*/


/* cast.valdesc #10 meltmixint_st*/
static inline struct meltmixint_st* meltcast_meltmixint_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_MIXINT)
        return (struct meltmixint_st*) p;
    return NULL;
} /* end meltcast_meltmixint_st*/


/* cast.valdesc #11 meltmixloc_st*/
static inline struct meltmixloc_st* meltcast_meltmixloc_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_MIXLOC)
        return (struct meltmixloc_st*) p;
    return NULL;
} /* end meltcast_meltmixloc_st*/


/* cast.valdesc #12 meltmultiple_st*/
static inline struct meltmultiple_st* meltcast_meltmultiple_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_MULTIPLE)
        return (struct meltmultiple_st*) p;
    return NULL;
} /* end meltcast_meltmultiple_st*/


/* cast.valdesc #13 meltobject_st*/
static inline struct meltobject_st* meltcast_meltobject_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_OBJECT)
        return (struct meltobject_st*) p;
    return NULL;
} /* end meltcast_meltobject_st*/


/* cast.valdesc #14 meltpair_st*/
static inline struct meltpair_st* meltcast_meltpair_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_PAIR)
        return (struct meltpair_st*) p;
    return NULL;
} /* end meltcast_meltpair_st*/


/* cast.valdesc #15 meltreal_st*/
static inline struct meltreal_st* meltcast_meltreal_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_REAL)
        return (struct meltreal_st*) p;
    return NULL;
} /* end meltcast_meltreal_st*/


/* cast.valdesc #16 meltroutine_st*/
static inline struct meltroutine_st* meltcast_meltroutine_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_ROUTINE)
        return (struct meltroutine_st*) p;
    return NULL;
} /* end meltcast_meltroutine_st*/


/* cast.valdesc #17 meltspecialdata_st*/
static inline struct meltspecialdata_st* meltcast_meltspecialdata_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_SPECIAL_DATA)
        return (struct meltspecialdata_st*) p;
    return NULL;
} /* end meltcast_meltspecialdata_st*/


/* cast.valdesc #18 meltstrbuf_st*/
static inline struct meltstrbuf_st* meltcast_meltstrbuf_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_STRBUF)
        return (struct meltstrbuf_st*) p;
    return NULL;
} /* end meltcast_meltstrbuf_st*/


/* cast.valdesc #19 meltstring_st*/
static inline struct meltstring_st* meltcast_meltstring_st(melt_ptr_t p)
{
    if (p && melt_magic_discr(p) == MELTOBMAG_STRING)
        return (struct meltstring_st*) p;
    return NULL;
} /* end meltcast_meltstring_st*/

/** end generated by generate_runtypesupport_gty **/



/** start of code generated by generate_runtypesupport_param **/
/* support for MELT parameter passing*/
enum /* generated enumeration for MELT parameters */
{
    MELTBPAR__NONE=0,
    /*gtyctype #1 CTYPE_BASIC_BLOCK*/
    MELTBPAR_BB   /*=1*/,
#define MELTBPARSTR_BB  "\x1"

    /*gtyctype #2 CTYPE_BITMAP*/
    MELTBPAR_BITMAP   /*=2*/,
#define MELTBPARSTR_BITMAP  "\x2"

    /*gtyctype #3 CTYPE_CSTRING*/
    MELTBPAR_CSTRING   /*=3*/,
#define MELTBPARSTR_CSTRING  "\x3"

    /*gtyctype #4 CTYPE_EDGE*/
    MELTBPAR_EDGE   /*=4*/,
#define MELTBPARSTR_EDGE  "\x4"

    /*gtyctype #5 CTYPE_GIMPLE*/
    MELTBPAR_GIMPLE   /*=5*/,
#define MELTBPARSTR_GIMPLE  "\x5"

    /*gtyctype #6 CTYPE_GIMPLE_SEQ*/
    MELTBPAR_GIMPLESEQ   /*=6*/,
#define MELTBPARSTR_GIMPLESEQ  "\x6"

    /*gtyctype #7 CTYPE_LONG*/
    MELTBPAR_LONG   /*=7*/,
#define MELTBPARSTR_LONG  "\x7"

    /*gtyctype #8 CTYPE_LOOP*/
    MELTBPAR_LOOP   /*=8*/,
#define MELTBPARSTR_LOOP  "\x8"

    /*gtyctype #9 CTYPE_RTVEC*/
    MELTBPAR_RTVEC   /*=9*/,
#define MELTBPARSTR_RTVEC  "\x9"

    /*gtyctype #10 CTYPE_RTX*/
    MELTBPAR_RTX   /*=10*/,
#define MELTBPARSTR_RTX  "\xa"

    /*gtyctype #11 CTYPE_TREE*/
    MELTBPAR_TREE   /*=11*/,
#define MELTBPARSTR_TREE  "\xb"

    /*gtyctype #12 CTYPE_VALUE*/
    MELTBPAR_PTR   /*=12*/,
#define MELTBPARSTR_PTR  "\xc"

    /*gtyctype #13 CTYPE_VOID*/
    /*-- non parameter --*/
    /*-- non paramstr --*/

    MELTBPAR__LAST
}; /*end enum for MELT parameters*/

union meltparam_un /* generated union for MELT parameters */
{
    void* meltbp_any;

    /*ctype #1 CTYPE_BASIC_BLOCK*/
    basic_block meltbp_bb; /*argument param.*/

    basic_block *meltbp_bbptr; /*result param.*/
    /*ctype #2 CTYPE_BITMAP*/
    bitmap meltbp_bitmap; /*argument param.*/

    bitmap *meltbp_bitmapptr; /*result param.*/
    /*ctype #3 CTYPE_CSTRING*/
    const char* meltbp_cstring; /*argument param.*/

    /*no result*/
    /*ctype #4 CTYPE_EDGE*/
    edge meltbp_edge; /*argument param.*/

    edge *meltbp_edgeptr; /*result param.*/
    /*ctype #5 CTYPE_GIMPLE*/
    gimple meltbp_gimple; /*argument param.*/

    gimple *meltbp_gimpleptr; /*result param.*/
    /*ctype #6 CTYPE_GIMPLE_SEQ*/
    gimple_seq meltbp_gimpleseq; /*argument param.*/

    gimple_seq *meltbp_gimpleseqptr; /*result param.*/
    /*ctype #7 CTYPE_LONG*/
    long meltbp_long; /*argument param.*/

    long *meltbp_longptr; /*result param.*/
    /*ctype #8 CTYPE_LOOP*/
    loop_p meltbp_loop; /*argument param.*/

    loop_p *meltbp_loopptr; /*result param.*/
    /*ctype #9 CTYPE_RTVEC*/
    rtvec meltbp_rtvec; /*argument param.*/

    rtvec *meltbp_rtvecptr; /*result param.*/
    /*ctype #10 CTYPE_RTX*/
    rtx meltbp_rtx; /*argument param.*/

    rtx *meltbp_rtxptr; /*result param.*/
    /*ctype #11 CTYPE_TREE*/
    tree meltbp_tree; /*argument param.*/

    tree *meltbp_treeptr; /*result param.*/
    /*ctype #12 CTYPE_VALUE*/
    melt_ptr_t meltbp_vptr; /*argument param.*/

    melt_ptr_t *meltbp_aptr; /*result param.*/
    /*ctype #13 CTYPE_VOID*/
    /* no argument */

    /*no result*/
}; /* end generated union for MELT parameters */
/** end of code generated by generate_runtypesupport_param **/


melt_ptr_t melt_code_to_ctype (int);

/** declaration generated by generate_runtypesupport_mag2str **/
const char* melt_obmag_string (int i);
#define MELT_OBMAG_STRING_generated



/** start of declarations generated by generate_runtypesupport_boxingfun **/
/*gtyctype #1 CTYPE_BASIC_BLOCK*/
melt_ptr_t meltgc_new_basicblock(meltobject_ptr_t discr, basic_block val);
void meltgc_basicblock_updatebox(melt_ptr_t boxp, basic_block val);

static inline basic_block melt_basicblock_content(melt_ptr_t box_p)
{
    if (melt_magic_discr(box_p) == MELTOBMAG_BASICBLOCK)
        return ((struct meltbasicblock_st*)box_p)->val;
    return (basic_block)0;
} /* end generated melt_basicblock_content */

/*gtyctype #2 CTYPE_BITMAP*/
melt_ptr_t meltgc_new_bitmap(meltobject_ptr_t discr, bitmap val);
void meltgc_bitmap_updatebox(melt_ptr_t boxp, bitmap val);

static inline bitmap melt_bitmap_content(melt_ptr_t box_p)
{
    if (melt_magic_discr(box_p) == MELTOBMAG_BITMAP)
        return ((struct meltbitmap_st*)box_p)->val;
    return (bitmap)0;
} /* end generated melt_bitmap_content */

/*gtyctype #3 CTYPE_EDGE*/
melt_ptr_t meltgc_new_edge(meltobject_ptr_t discr, edge val);
void meltgc_edge_updatebox(melt_ptr_t boxp, edge val);

static inline edge melt_edge_content(melt_ptr_t box_p)
{
    if (melt_magic_discr(box_p) == MELTOBMAG_EDGE)
        return ((struct meltedge_st*)box_p)->val;
    return (edge)0;
} /* end generated melt_edge_content */

/*gtyctype #4 CTYPE_GIMPLE*/
melt_ptr_t meltgc_new_gimple(meltobject_ptr_t discr, gimple val);
void meltgc_gimple_updatebox(melt_ptr_t boxp, gimple val);

static inline gimple melt_gimple_content(melt_ptr_t box_p)
{
    if (melt_magic_discr(box_p) == MELTOBMAG_GIMPLE)
        return ((struct meltgimple_st*)box_p)->val;
    return (gimple)0;
} /* end generated melt_gimple_content */

/*gtyctype #5 CTYPE_GIMPLE_SEQ*/
melt_ptr_t meltgc_new_gimpleseq(meltobject_ptr_t discr, gimple_seq val);
void meltgc_gimpleseq_updatebox(melt_ptr_t boxp, gimple_seq val);

static inline gimple_seq melt_gimpleseq_content(melt_ptr_t box_p)
{
    if (melt_magic_discr(box_p) == MELTOBMAG_GIMPLESEQ)
        return ((struct meltgimpleseq_st*)box_p)->val;
    return (gimple_seq)0;
} /* end generated melt_gimpleseq_content */

/*gtyctype #6 CTYPE_LOOP*/
melt_ptr_t meltgc_new_loop(meltobject_ptr_t discr, loop_p val);
void melt_loop_updatebox(melt_ptr_t boxp, loop_p val);

static inline loop_p melt_loop_content(melt_ptr_t box_p)
{
    if (melt_magic_discr(box_p) == MELTOBMAG_LOOP)
        return ((struct meltloop_st*)box_p)->val;
    return (loop_p)0;
} /* end generated melt_loop_content */

/*gtyctype #7 CTYPE_RTVEC*/
melt_ptr_t meltgc_new_rtvec(meltobject_ptr_t discr, rtvec val);
void meltgc_rtvec_updatebox(melt_ptr_t boxp, rtvec val);

static inline rtvec melt_rtvec_content(melt_ptr_t box_p)
{
    if (melt_magic_discr(box_p) == MELTOBMAG_RTVEC)
        return ((struct meltrtvec_st*)box_p)->val;
    return (rtvec)0;
} /* end generated melt_rtvec_content */

/*gtyctype #8 CTYPE_RTX*/
melt_ptr_t meltgc_new_rtx(meltobject_ptr_t discr, rtx val);
void meltgc_rtx_updatebox(melt_ptr_t boxp, rtx val);

static inline rtx melt_rtx_content(melt_ptr_t box_p)
{
    if (melt_magic_discr(box_p) == MELTOBMAG_RTX)
        return ((struct meltrtx_st*)box_p)->val;
    return (rtx)0;
} /* end generated melt_rtx_content */

/*gtyctype #9 CTYPE_TREE*/
melt_ptr_t meltgc_new_tree(meltobject_ptr_t discr, tree val);
void meltgc_tree_updatebox(melt_ptr_t boxp, tree val);

static inline tree melt_tree_content(melt_ptr_t box_p)
{
    if (melt_magic_discr(box_p) == MELTOBMAG_TREE)
        return ((struct melttree_st*)box_p)->val;
    return (tree)0;
} /* end generated melt_tree_content */


/** end of declarations generated by generate_runtypesupport_boxingfun **/



/** start of code generated by generate_runtypesupport_mapfun **/

/*gtyctype #1 CTYPE_BASIC_BLOCK*/

/***map support for GTY ctype CTYPE_BASIC_BLOCK **/
static inline melt_ptr_t /*New map for CTYPE_BASIC_BLOCK*/ meltgc_new_mapbasicblocks (meltobject_ptr_t discr, unsigned len)
{
    /*generated map creation */
    if (melt_magic_discr ((melt_ptr_t) discr) != MELTOBMAG_OBJECT)
        return NULL ;
    if (discr->meltobj_magic != MELTOBMAG_MAPBASICBLOCKS) /* not map magic */
        return NULL ;
    return (melt_ptr_t) meltgc_raw_new_mappointers (discr, len) ;
} /*end generated new map for CTYPE_BASIC_BLOCK */

static inline melt_ptr_t /* Map getter for CTYPE_BASIC_BLOCK*/ melt_get_mapbasicblocks (melt_ptr_t map_p, basic_block attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPBASICBLOCKS)
        return NULL;
    return melt_raw_get_mappointers ((void*)map_p, (void*)attr);
} /*end generated map getter for CTYPE_BASIC_BLOCK*/

static inline void /* Map putter for CTYPE_BASIC_BLOCK*/ melt_put_mapbasicblocks (melt_ptr_t map_p, basic_block attr, melt_ptr_t valu_p)
{
    if (!map_p || !attr || !valu_p
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPBASICBLOCKS)
        return;
    meltgc_raw_put_mappointers ((void*)map_p, (void*)attr, valu_p);
} /*end generated map putter for CTYPE_BASIC_BLOCK*/
static inline void /* Map remover for CTYPE_BASIC_BLOCK*/ melt_remove_mapbasicblocks (melt_ptr_t map_p, basic_block attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPBASICBLOCKS)
        return;
    meltgc_raw_remove_mappointers ((void*)map_p, (void*)attr);
} /*end generated map remover for CTYPE_BASIC_BLOCK*/
static inline unsigned /* Map counter for CTYPE_BASIC_BLOCK*/ melt_count_mapbasicblocks (struct meltmapbasicblocks_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPBASICBLOCKS)
        return 0;
    return map_s->count;
} /*end generated map counter for CTYPE_BASIC_BLOCK*/
static inline unsigned /* Map size for CTYPE_BASIC_BLOCK*/ melt_size_mapbasicblocks (struct meltmapbasicblocks_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPBASICBLOCKS)
        return 0;
    return melt_primtab[map_s->lenix];
} /*end generated map size for CTYPE_BASIC_BLOCK*/
static inline basic_block/* Map nth attr for CTYPE_BASIC_BLOCK*/ melt_nthattr_mapbasicblocks (struct meltmapbasicblocks_st* map_s, int ix)
{
    basic_block at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPBASICBLOCKS)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return at;
} /*end generated map nth attr for CTYPE_BASIC_BLOCK*/
static inline melt_ptr_t /* Map nth value for CTYPE_BASIC_BLOCK*/ melt_nthval_mapbasicblocks (struct meltmapbasicblocks_st* map_s, int ix)
{
    basic_block at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPBASICBLOCKS)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return map_s->entab[ix].e_va;
} /*end generated map nth value for CTYPE_BASIC_BLOCK*/
/* map auxiliary data access for CTYPE_BASIC_BLOCK */
static inline melt_ptr_t melt_auxdata_mapbasicblocks (melt_ptr_t map_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPBASICBLOCKS)
        return ((struct meltmapbasicblocks_st*)map_p)->meltmap_aux;
    return NULL;
}

/* map auxiliary data put for CTYPE_BASIC_BLOCK */
static inline melt_ptr_t melt_auxput_mapbasicblocks (melt_ptr_t map_p, melt_ptr_t val_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPBASICBLOCKS)
        {
            ((struct meltmapbasicblocks_st*)map_p)->meltmap_aux = val_p;
            meltgc_touch_dest (map_p, val_p);
        }
    return NULL;
}

/***end of map support for GTY ctype CTYPE_BASIC_BLOCK **/

/*gtyctype #2 CTYPE_BITMAP*/

/***map support for GTY ctype CTYPE_BITMAP **/
static inline melt_ptr_t /*New map for CTYPE_BITMAP*/ meltgc_new_mapbitmaps (meltobject_ptr_t discr, unsigned len)
{
    /*generated map creation */
    if (melt_magic_discr ((melt_ptr_t) discr) != MELTOBMAG_OBJECT)
        return NULL ;
    if (discr->meltobj_magic != MELTOBMAG_MAPBITMAPS) /* not map magic */
        return NULL ;
    return (melt_ptr_t) meltgc_raw_new_mappointers (discr, len) ;
} /*end generated new map for CTYPE_BITMAP */

static inline melt_ptr_t /* Map getter for CTYPE_BITMAP*/ melt_get_mapbitmaps (melt_ptr_t map_p, bitmap attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPBITMAPS)
        return NULL;
    return melt_raw_get_mappointers ((void*)map_p, (void*)attr);
} /*end generated map getter for CTYPE_BITMAP*/

static inline void /* Map putter for CTYPE_BITMAP*/ melt_put_mapbitmaps (melt_ptr_t map_p, bitmap attr, melt_ptr_t valu_p)
{
    if (!map_p || !attr || !valu_p
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPBITMAPS)
        return;
    meltgc_raw_put_mappointers ((void*)map_p, (void*)attr, valu_p);
} /*end generated map putter for CTYPE_BITMAP*/
static inline void /* Map remover for CTYPE_BITMAP*/ melt_remove_mapbitmaps (melt_ptr_t map_p, bitmap attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPBITMAPS)
        return;
    meltgc_raw_remove_mappointers ((void*)map_p, (void*)attr);
} /*end generated map remover for CTYPE_BITMAP*/
static inline unsigned /* Map counter for CTYPE_BITMAP*/ melt_count_mapbitmaps (struct meltmapbitmaps_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPBITMAPS)
        return 0;
    return map_s->count;
} /*end generated map counter for CTYPE_BITMAP*/
static inline unsigned /* Map size for CTYPE_BITMAP*/ melt_size_mapbitmaps (struct meltmapbitmaps_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPBITMAPS)
        return 0;
    return melt_primtab[map_s->lenix];
} /*end generated map size for CTYPE_BITMAP*/
static inline bitmap/* Map nth attr for CTYPE_BITMAP*/ melt_nthattr_mapbitmaps (struct meltmapbitmaps_st* map_s, int ix)
{
    bitmap at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPBITMAPS)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return at;
} /*end generated map nth attr for CTYPE_BITMAP*/
static inline melt_ptr_t /* Map nth value for CTYPE_BITMAP*/ melt_nthval_mapbitmaps (struct meltmapbitmaps_st* map_s, int ix)
{
    bitmap at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPBITMAPS)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return map_s->entab[ix].e_va;
} /*end generated map nth value for CTYPE_BITMAP*/
/* map auxiliary data access for CTYPE_BITMAP */
static inline melt_ptr_t melt_auxdata_mapbitmaps (melt_ptr_t map_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPBITMAPS)
        return ((struct meltmapbitmaps_st*)map_p)->meltmap_aux;
    return NULL;
}

/* map auxiliary data put for CTYPE_BITMAP */
static inline melt_ptr_t melt_auxput_mapbitmaps (melt_ptr_t map_p, melt_ptr_t val_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPBITMAPS)
        {
            ((struct meltmapbitmaps_st*)map_p)->meltmap_aux = val_p;
            meltgc_touch_dest (map_p, val_p);
        }
    return NULL;
}

/***end of map support for GTY ctype CTYPE_BITMAP **/

/*gtyctype #3 CTYPE_EDGE*/

/***map support for GTY ctype CTYPE_EDGE **/
static inline melt_ptr_t /*New map for CTYPE_EDGE*/ meltgc_new_mapedges (meltobject_ptr_t discr, unsigned len)
{
    /*generated map creation */
    if (melt_magic_discr ((melt_ptr_t) discr) != MELTOBMAG_OBJECT)
        return NULL ;
    if (discr->meltobj_magic != MELTOBMAG_MAPEDGES) /* not map magic */
        return NULL ;
    return (melt_ptr_t) meltgc_raw_new_mappointers (discr, len) ;
} /*end generated new map for CTYPE_EDGE */

static inline melt_ptr_t /* Map getter for CTYPE_EDGE*/ melt_get_mapedges (melt_ptr_t map_p, edge attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPEDGES)
        return NULL;
    return melt_raw_get_mappointers ((void*)map_p, (void*)attr);
} /*end generated map getter for CTYPE_EDGE*/

static inline void /* Map putter for CTYPE_EDGE*/ melt_put_mapedges (melt_ptr_t map_p, edge attr, melt_ptr_t valu_p)
{
    if (!map_p || !attr || !valu_p
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPEDGES)
        return;
    meltgc_raw_put_mappointers ((void*)map_p, (void*)attr, valu_p);
} /*end generated map putter for CTYPE_EDGE*/
static inline void /* Map remover for CTYPE_EDGE*/ melt_remove_mapedges (melt_ptr_t map_p, edge attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPEDGES)
        return;
    meltgc_raw_remove_mappointers ((void*)map_p, (void*)attr);
} /*end generated map remover for CTYPE_EDGE*/
static inline unsigned /* Map counter for CTYPE_EDGE*/ melt_count_mapedges (struct meltmapedges_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPEDGES)
        return 0;
    return map_s->count;
} /*end generated map counter for CTYPE_EDGE*/
static inline unsigned /* Map size for CTYPE_EDGE*/ melt_size_mapedges (struct meltmapedges_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPEDGES)
        return 0;
    return melt_primtab[map_s->lenix];
} /*end generated map size for CTYPE_EDGE*/
static inline edge/* Map nth attr for CTYPE_EDGE*/ melt_nthattr_mapedges (struct meltmapedges_st* map_s, int ix)
{
    edge at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPEDGES)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return at;
} /*end generated map nth attr for CTYPE_EDGE*/
static inline melt_ptr_t /* Map nth value for CTYPE_EDGE*/ melt_nthval_mapedges (struct meltmapedges_st* map_s, int ix)
{
    edge at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPEDGES)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return map_s->entab[ix].e_va;
} /*end generated map nth value for CTYPE_EDGE*/
/* map auxiliary data access for CTYPE_EDGE */
static inline melt_ptr_t melt_auxdata_mapedges (melt_ptr_t map_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPEDGES)
        return ((struct meltmapedges_st*)map_p)->meltmap_aux;
    return NULL;
}

/* map auxiliary data put for CTYPE_EDGE */
static inline melt_ptr_t melt_auxput_mapedges (melt_ptr_t map_p, melt_ptr_t val_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPEDGES)
        {
            ((struct meltmapedges_st*)map_p)->meltmap_aux = val_p;
            meltgc_touch_dest (map_p, val_p);
        }
    return NULL;
}

/***end of map support for GTY ctype CTYPE_EDGE **/

/*gtyctype #4 CTYPE_GIMPLE*/

/***map support for GTY ctype CTYPE_GIMPLE **/
static inline melt_ptr_t /*New map for CTYPE_GIMPLE*/ meltgc_new_mapgimples (meltobject_ptr_t discr, unsigned len)
{
    /*generated map creation */
    if (melt_magic_discr ((melt_ptr_t) discr) != MELTOBMAG_OBJECT)
        return NULL ;
    if (discr->meltobj_magic != MELTOBMAG_MAPGIMPLES) /* not map magic */
        return NULL ;
    return (melt_ptr_t) meltgc_raw_new_mappointers (discr, len) ;
} /*end generated new map for CTYPE_GIMPLE */

static inline melt_ptr_t /* Map getter for CTYPE_GIMPLE*/ melt_get_mapgimples (melt_ptr_t map_p, gimple attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPGIMPLES)
        return NULL;
    return melt_raw_get_mappointers ((void*)map_p, (void*)attr);
} /*end generated map getter for CTYPE_GIMPLE*/

static inline void /* Map putter for CTYPE_GIMPLE*/ melt_put_mapgimples (melt_ptr_t map_p, gimple attr, melt_ptr_t valu_p)
{
    if (!map_p || !attr || !valu_p
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPGIMPLES)
        return;
    meltgc_raw_put_mappointers ((void*)map_p, (void*)attr, valu_p);
} /*end generated map putter for CTYPE_GIMPLE*/
static inline void /* Map remover for CTYPE_GIMPLE*/ melt_remove_mapgimples (melt_ptr_t map_p, gimple attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPGIMPLES)
        return;
    meltgc_raw_remove_mappointers ((void*)map_p, (void*)attr);
} /*end generated map remover for CTYPE_GIMPLE*/
static inline unsigned /* Map counter for CTYPE_GIMPLE*/ melt_count_mapgimples (struct meltmapgimples_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPGIMPLES)
        return 0;
    return map_s->count;
} /*end generated map counter for CTYPE_GIMPLE*/
static inline unsigned /* Map size for CTYPE_GIMPLE*/ melt_size_mapgimples (struct meltmapgimples_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPGIMPLES)
        return 0;
    return melt_primtab[map_s->lenix];
} /*end generated map size for CTYPE_GIMPLE*/
static inline gimple/* Map nth attr for CTYPE_GIMPLE*/ melt_nthattr_mapgimples (struct meltmapgimples_st* map_s, int ix)
{
    gimple at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPGIMPLES)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return at;
} /*end generated map nth attr for CTYPE_GIMPLE*/
static inline melt_ptr_t /* Map nth value for CTYPE_GIMPLE*/ melt_nthval_mapgimples (struct meltmapgimples_st* map_s, int ix)
{
    gimple at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPGIMPLES)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return map_s->entab[ix].e_va;
} /*end generated map nth value for CTYPE_GIMPLE*/
/* map auxiliary data access for CTYPE_GIMPLE */
static inline melt_ptr_t melt_auxdata_mapgimples (melt_ptr_t map_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPGIMPLES)
        return ((struct meltmapgimples_st*)map_p)->meltmap_aux;
    return NULL;
}

/* map auxiliary data put for CTYPE_GIMPLE */
static inline melt_ptr_t melt_auxput_mapgimples (melt_ptr_t map_p, melt_ptr_t val_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPGIMPLES)
        {
            ((struct meltmapgimples_st*)map_p)->meltmap_aux = val_p;
            meltgc_touch_dest (map_p, val_p);
        }
    return NULL;
}

/***end of map support for GTY ctype CTYPE_GIMPLE **/

/*gtyctype #5 CTYPE_GIMPLE_SEQ*/

/***map support for GTY ctype CTYPE_GIMPLE_SEQ **/
static inline melt_ptr_t /*New map for CTYPE_GIMPLE_SEQ*/ meltgc_new_mapgimpleseqs (meltobject_ptr_t discr, unsigned len)
{
    /*generated map creation */
    if (melt_magic_discr ((melt_ptr_t) discr) != MELTOBMAG_OBJECT)
        return NULL ;
    if (discr->meltobj_magic != MELTOBMAG_MAPGIMPLESEQS) /* not map magic */
        return NULL ;
    return (melt_ptr_t) meltgc_raw_new_mappointers (discr, len) ;
} /*end generated new map for CTYPE_GIMPLE_SEQ */

static inline melt_ptr_t /* Map getter for CTYPE_GIMPLE_SEQ*/ melt_get_mapgimpleseqs (melt_ptr_t map_p, gimple_seq attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPGIMPLESEQS)
        return NULL;
    return melt_raw_get_mappointers ((void*)map_p, (void*)attr);
} /*end generated map getter for CTYPE_GIMPLE_SEQ*/

static inline void /* Map putter for CTYPE_GIMPLE_SEQ*/ melt_put_mapgimpleseqs (melt_ptr_t map_p, gimple_seq attr, melt_ptr_t valu_p)
{
    if (!map_p || !attr || !valu_p
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPGIMPLESEQS)
        return;
    meltgc_raw_put_mappointers ((void*)map_p, (void*)attr, valu_p);
} /*end generated map putter for CTYPE_GIMPLE_SEQ*/
static inline void /* Map remover for CTYPE_GIMPLE_SEQ*/ melt_remove_mapgimpleseqs (melt_ptr_t map_p, gimple_seq attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPGIMPLESEQS)
        return;
    meltgc_raw_remove_mappointers ((void*)map_p, (void*)attr);
} /*end generated map remover for CTYPE_GIMPLE_SEQ*/
static inline unsigned /* Map counter for CTYPE_GIMPLE_SEQ*/ melt_count_mapgimpleseqs (struct meltmapgimpleseqs_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPGIMPLESEQS)
        return 0;
    return map_s->count;
} /*end generated map counter for CTYPE_GIMPLE_SEQ*/
static inline unsigned /* Map size for CTYPE_GIMPLE_SEQ*/ melt_size_mapgimpleseqs (struct meltmapgimpleseqs_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPGIMPLESEQS)
        return 0;
    return melt_primtab[map_s->lenix];
} /*end generated map size for CTYPE_GIMPLE_SEQ*/
static inline gimple_seq/* Map nth attr for CTYPE_GIMPLE_SEQ*/ melt_nthattr_mapgimpleseqs (struct meltmapgimpleseqs_st* map_s, int ix)
{
    gimple_seq at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPGIMPLESEQS)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return at;
} /*end generated map nth attr for CTYPE_GIMPLE_SEQ*/
static inline melt_ptr_t /* Map nth value for CTYPE_GIMPLE_SEQ*/ melt_nthval_mapgimpleseqs (struct meltmapgimpleseqs_st* map_s, int ix)
{
    gimple_seq at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPGIMPLESEQS)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return map_s->entab[ix].e_va;
} /*end generated map nth value for CTYPE_GIMPLE_SEQ*/
/* map auxiliary data access for CTYPE_GIMPLE_SEQ */
static inline melt_ptr_t melt_auxdata_mapgimpleseqs (melt_ptr_t map_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPGIMPLESEQS)
        return ((struct meltmapgimpleseqs_st*)map_p)->meltmap_aux;
    return NULL;
}

/* map auxiliary data put for CTYPE_GIMPLE_SEQ */
static inline melt_ptr_t melt_auxput_mapgimpleseqs (melt_ptr_t map_p, melt_ptr_t val_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPGIMPLESEQS)
        {
            ((struct meltmapgimpleseqs_st*)map_p)->meltmap_aux = val_p;
            meltgc_touch_dest (map_p, val_p);
        }
    return NULL;
}

/***end of map support for GTY ctype CTYPE_GIMPLE_SEQ **/

/*gtyctype #6 CTYPE_LOOP*/

/***map support for GTY ctype CTYPE_LOOP **/
static inline melt_ptr_t /*New map for CTYPE_LOOP*/ meltgc_new_maploops (meltobject_ptr_t discr, unsigned len)
{
    /*generated map creation */
    if (melt_magic_discr ((melt_ptr_t) discr) != MELTOBMAG_OBJECT)
        return NULL ;
    if (discr->meltobj_magic != MELTOBMAG_MAPLOOPS) /* not map magic */
        return NULL ;
    return (melt_ptr_t) meltgc_raw_new_mappointers (discr, len) ;
} /*end generated new map for CTYPE_LOOP */

static inline melt_ptr_t /* Map getter for CTYPE_LOOP*/ melt_get_maploops (melt_ptr_t map_p, loop_p attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPLOOPS)
        return NULL;
    return melt_raw_get_mappointers ((void*)map_p, (void*)attr);
} /*end generated map getter for CTYPE_LOOP*/

static inline void /* Map putter for CTYPE_LOOP*/ melt_put_maploops (melt_ptr_t map_p, loop_p attr, melt_ptr_t valu_p)
{
    if (!map_p || !attr || !valu_p
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPLOOPS)
        return;
    meltgc_raw_put_mappointers ((void*)map_p, (void*)attr, valu_p);
} /*end generated map putter for CTYPE_LOOP*/
static inline void /* Map remover for CTYPE_LOOP*/ melt_remove_maploops (melt_ptr_t map_p, loop_p attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPLOOPS)
        return;
    meltgc_raw_remove_mappointers ((void*)map_p, (void*)attr);
} /*end generated map remover for CTYPE_LOOP*/
static inline unsigned /* Map counter for CTYPE_LOOP*/ melt_count_maploops (struct meltmaploops_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPLOOPS)
        return 0;
    return map_s->count;
} /*end generated map counter for CTYPE_LOOP*/
static inline unsigned /* Map size for CTYPE_LOOP*/ melt_size_maploops (struct meltmaploops_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPLOOPS)
        return 0;
    return melt_primtab[map_s->lenix];
} /*end generated map size for CTYPE_LOOP*/
static inline loop_p/* Map nth attr for CTYPE_LOOP*/ melt_nthattr_maploops (struct meltmaploops_st* map_s, int ix)
{
    loop_p at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPLOOPS)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return at;
} /*end generated map nth attr for CTYPE_LOOP*/
static inline melt_ptr_t /* Map nth value for CTYPE_LOOP*/ melt_nthval_maploops (struct meltmaploops_st* map_s, int ix)
{
    loop_p at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPLOOPS)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return map_s->entab[ix].e_va;
} /*end generated map nth value for CTYPE_LOOP*/
/* map auxiliary data access for CTYPE_LOOP */
static inline melt_ptr_t melt_auxdata_maploops (melt_ptr_t map_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPLOOPS)
        return ((struct meltmaploops_st*)map_p)->meltmap_aux;
    return NULL;
}

/* map auxiliary data put for CTYPE_LOOP */
static inline melt_ptr_t melt_auxput_maploops (melt_ptr_t map_p, melt_ptr_t val_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPLOOPS)
        {
            ((struct meltmaploops_st*)map_p)->meltmap_aux = val_p;
            meltgc_touch_dest (map_p, val_p);
        }
    return NULL;
}

/***end of map support for GTY ctype CTYPE_LOOP **/

/*gtyctype #7 CTYPE_RTVEC*/

/***map support for GTY ctype CTYPE_RTVEC **/
static inline melt_ptr_t /*New map for CTYPE_RTVEC*/ meltgc_new_maprtvecs (meltobject_ptr_t discr, unsigned len)
{
    /*generated map creation */
    if (melt_magic_discr ((melt_ptr_t) discr) != MELTOBMAG_OBJECT)
        return NULL ;
    if (discr->meltobj_magic != MELTOBMAG_MAPRTVECS) /* not map magic */
        return NULL ;
    return (melt_ptr_t) meltgc_raw_new_mappointers (discr, len) ;
} /*end generated new map for CTYPE_RTVEC */

static inline melt_ptr_t /* Map getter for CTYPE_RTVEC*/ melt_get_maprtvecs (melt_ptr_t map_p, rtvec attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPRTVECS)
        return NULL;
    return melt_raw_get_mappointers ((void*)map_p, (void*)attr);
} /*end generated map getter for CTYPE_RTVEC*/

static inline void /* Map putter for CTYPE_RTVEC*/ melt_put_maprtvecs (melt_ptr_t map_p, rtvec attr, melt_ptr_t valu_p)
{
    if (!map_p || !attr || !valu_p
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPRTVECS)
        return;
    meltgc_raw_put_mappointers ((void*)map_p, (void*)attr, valu_p);
} /*end generated map putter for CTYPE_RTVEC*/
static inline void /* Map remover for CTYPE_RTVEC*/ melt_remove_maprtvecs (melt_ptr_t map_p, rtvec attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPRTVECS)
        return;
    meltgc_raw_remove_mappointers ((void*)map_p, (void*)attr);
} /*end generated map remover for CTYPE_RTVEC*/
static inline unsigned /* Map counter for CTYPE_RTVEC*/ melt_count_maprtvecs (struct meltmaprtvecs_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPRTVECS)
        return 0;
    return map_s->count;
} /*end generated map counter for CTYPE_RTVEC*/
static inline unsigned /* Map size for CTYPE_RTVEC*/ melt_size_maprtvecs (struct meltmaprtvecs_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPRTVECS)
        return 0;
    return melt_primtab[map_s->lenix];
} /*end generated map size for CTYPE_RTVEC*/
static inline rtvec/* Map nth attr for CTYPE_RTVEC*/ melt_nthattr_maprtvecs (struct meltmaprtvecs_st* map_s, int ix)
{
    rtvec at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPRTVECS)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return at;
} /*end generated map nth attr for CTYPE_RTVEC*/
static inline melt_ptr_t /* Map nth value for CTYPE_RTVEC*/ melt_nthval_maprtvecs (struct meltmaprtvecs_st* map_s, int ix)
{
    rtvec at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPRTVECS)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return map_s->entab[ix].e_va;
} /*end generated map nth value for CTYPE_RTVEC*/
/* map auxiliary data access for CTYPE_RTVEC */
static inline melt_ptr_t melt_auxdata_maprtvecs (melt_ptr_t map_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPRTVECS)
        return ((struct meltmaprtvecs_st*)map_p)->meltmap_aux;
    return NULL;
}

/* map auxiliary data put for CTYPE_RTVEC */
static inline melt_ptr_t melt_auxput_maprtvecs (melt_ptr_t map_p, melt_ptr_t val_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPRTVECS)
        {
            ((struct meltmaprtvecs_st*)map_p)->meltmap_aux = val_p;
            meltgc_touch_dest (map_p, val_p);
        }
    return NULL;
}

/***end of map support for GTY ctype CTYPE_RTVEC **/

/*gtyctype #8 CTYPE_RTX*/

/***map support for GTY ctype CTYPE_RTX **/
static inline melt_ptr_t /*New map for CTYPE_RTX*/ meltgc_new_maprtxs (meltobject_ptr_t discr, unsigned len)
{
    /*generated map creation */
    if (melt_magic_discr ((melt_ptr_t) discr) != MELTOBMAG_OBJECT)
        return NULL ;
    if (discr->meltobj_magic != MELTOBMAG_MAPRTXS) /* not map magic */
        return NULL ;
    return (melt_ptr_t) meltgc_raw_new_mappointers (discr, len) ;
} /*end generated new map for CTYPE_RTX */

static inline melt_ptr_t /* Map getter for CTYPE_RTX*/ melt_get_maprtxs (melt_ptr_t map_p, rtx attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPRTXS)
        return NULL;
    return melt_raw_get_mappointers ((void*)map_p, (void*)attr);
} /*end generated map getter for CTYPE_RTX*/

static inline void /* Map putter for CTYPE_RTX*/ melt_put_maprtxs (melt_ptr_t map_p, rtx attr, melt_ptr_t valu_p)
{
    if (!map_p || !attr || !valu_p
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPRTXS)
        return;
    meltgc_raw_put_mappointers ((void*)map_p, (void*)attr, valu_p);
} /*end generated map putter for CTYPE_RTX*/
static inline void /* Map remover for CTYPE_RTX*/ melt_remove_maprtxs (melt_ptr_t map_p, rtx attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPRTXS)
        return;
    meltgc_raw_remove_mappointers ((void*)map_p, (void*)attr);
} /*end generated map remover for CTYPE_RTX*/
static inline unsigned /* Map counter for CTYPE_RTX*/ melt_count_maprtxs (struct meltmaprtxs_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPRTXS)
        return 0;
    return map_s->count;
} /*end generated map counter for CTYPE_RTX*/
static inline unsigned /* Map size for CTYPE_RTX*/ melt_size_maprtxs (struct meltmaprtxs_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPRTXS)
        return 0;
    return melt_primtab[map_s->lenix];
} /*end generated map size for CTYPE_RTX*/
static inline rtx/* Map nth attr for CTYPE_RTX*/ melt_nthattr_maprtxs (struct meltmaprtxs_st* map_s, int ix)
{
    rtx at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPRTXS)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return at;
} /*end generated map nth attr for CTYPE_RTX*/
static inline melt_ptr_t /* Map nth value for CTYPE_RTX*/ melt_nthval_maprtxs (struct meltmaprtxs_st* map_s, int ix)
{
    rtx at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPRTXS)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return map_s->entab[ix].e_va;
} /*end generated map nth value for CTYPE_RTX*/
/* map auxiliary data access for CTYPE_RTX */
static inline melt_ptr_t melt_auxdata_maprtxs (melt_ptr_t map_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPRTXS)
        return ((struct meltmaprtxs_st*)map_p)->meltmap_aux;
    return NULL;
}

/* map auxiliary data put for CTYPE_RTX */
static inline melt_ptr_t melt_auxput_maprtxs (melt_ptr_t map_p, melt_ptr_t val_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPRTXS)
        {
            ((struct meltmaprtxs_st*)map_p)->meltmap_aux = val_p;
            meltgc_touch_dest (map_p, val_p);
        }
    return NULL;
}

/***end of map support for GTY ctype CTYPE_RTX **/

/*gtyctype #9 CTYPE_TREE*/

/***map support for GTY ctype CTYPE_TREE **/
static inline melt_ptr_t /*New map for CTYPE_TREE*/ meltgc_new_maptrees (meltobject_ptr_t discr, unsigned len)
{
    /*generated map creation */
    if (melt_magic_discr ((melt_ptr_t) discr) != MELTOBMAG_OBJECT)
        return NULL ;
    if (discr->meltobj_magic != MELTOBMAG_MAPTREES) /* not map magic */
        return NULL ;
    return (melt_ptr_t) meltgc_raw_new_mappointers (discr, len) ;
} /*end generated new map for CTYPE_TREE */

static inline melt_ptr_t /* Map getter for CTYPE_TREE*/ melt_get_maptrees (melt_ptr_t map_p, tree attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPTREES)
        return NULL;
    return melt_raw_get_mappointers ((void*)map_p, (void*)attr);
} /*end generated map getter for CTYPE_TREE*/

static inline void /* Map putter for CTYPE_TREE*/ melt_put_maptrees (melt_ptr_t map_p, tree attr, melt_ptr_t valu_p)
{
    if (!map_p || !attr || !valu_p
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPTREES)
        return;
    meltgc_raw_put_mappointers ((void*)map_p, (void*)attr, valu_p);
} /*end generated map putter for CTYPE_TREE*/
static inline void /* Map remover for CTYPE_TREE*/ melt_remove_maptrees (melt_ptr_t map_p, tree attr)
{
    if (!map_p || !attr
            || melt_magic_discr ((melt_ptr_t) map_p) != MELTOBMAG_MAPTREES)
        return;
    meltgc_raw_remove_mappointers ((void*)map_p, (void*)attr);
} /*end generated map remover for CTYPE_TREE*/
static inline unsigned /* Map counter for CTYPE_TREE*/ melt_count_maptrees (struct meltmaptrees_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPTREES)
        return 0;
    return map_s->count;
} /*end generated map counter for CTYPE_TREE*/
static inline unsigned /* Map size for CTYPE_TREE*/ melt_size_maptrees (struct meltmaptrees_st* map_s)
{
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPTREES)
        return 0;
    return melt_primtab[map_s->lenix];
} /*end generated map size for CTYPE_TREE*/
static inline tree/* Map nth attr for CTYPE_TREE*/ melt_nthattr_maptrees (struct meltmaptrees_st* map_s, int ix)
{
    tree at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPTREES)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return at;
} /*end generated map nth attr for CTYPE_TREE*/
static inline melt_ptr_t /* Map nth value for CTYPE_TREE*/ melt_nthval_maptrees (struct meltmaptrees_st* map_s, int ix)
{
    tree at = 0;
    if (!map_s
            || melt_magic_discr ((melt_ptr_t) map_s) != MELTOBMAG_MAPTREES)
        return 0;
    at = map_s->entab[ix].e_at;
    if ((void*) at == (void*) HTAB_DELETED_ENTRY) return 0;
    return map_s->entab[ix].e_va;
} /*end generated map nth value for CTYPE_TREE*/
/* map auxiliary data access for CTYPE_TREE */
static inline melt_ptr_t melt_auxdata_maptrees (melt_ptr_t map_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPTREES)
        return ((struct meltmaptrees_st*)map_p)->meltmap_aux;
    return NULL;
}

/* map auxiliary data put for CTYPE_TREE */
static inline melt_ptr_t melt_auxput_maptrees (melt_ptr_t map_p, melt_ptr_t val_p)
{
    if (melt_magic_discr (map_p) == MELTOBMAG_MAPTREES)
        {
            ((struct meltmaptrees_st*)map_p)->meltmap_aux = val_p;
            meltgc_touch_dest (map_p, val_p);
        }
    return NULL;
}

/***end of map support for GTY ctype CTYPE_TREE **/

/** end of code generated by generate_runtypesupport_mapfun **/



/** start of code generated by generate_runtypesupport_predef_fields **/

#define MELT_HAS_PREDEF_CLASS_ALARM_HANDLER
/* predefined class CLASS_ALARM_HANDLER index 1 */ enum
{
    MELTFIELD_ALARMH_PERIOD = 1 /*in CLASS_ALARM_HANDLER*/,
    MELTFIELD_ALARMH_CLOS = 2 /*in CLASS_ALARM_HANDLER*/,
    MELTFIELD_ALARMH_DATA = 3 /*in CLASS_ALARM_HANDLER*/,
    MELTLENGTH_CLASS_ALARM_HANDLER = 4
} ;
#define MELT_HAS_PREDEF_CLASS_CHILD_PROCESS_HANDLER
/* predefined class CLASS_CHILD_PROCESS_HANDLER index 2 */ enum
{
    MELTFIELD_CHILPROH_PID = 1 /*in CLASS_CHILD_PROCESS_HANDLER*/,
    MELTFIELD_CHILPROH_CLOS = 2 /*in CLASS_CHILD_PROCESS_HANDLER*/,
    MELTFIELD_CHILPROH_DATA = 3 /*in CLASS_CHILD_PROCESS_HANDLER*/,
    MELTLENGTH_CLASS_CHILD_PROCESS_HANDLER = 4
} ;
#define MELT_HAS_PREDEF_CLASS_CITERATOR
/* predefined class CLASS_CITERATOR index 3 */ enum
{
    MELTFIELD_CITER_START_FORMALS = 2 /*in CLASS_CITERATOR*/,
    MELTFIELD_CITER_STATE = 3 /*in CLASS_CITERATOR*/,
    MELTFIELD_CITER_BODY_FORMALS = 4 /*in CLASS_CITERATOR*/,
    MELTFIELD_CITER_EXPBEFORE = 5 /*in CLASS_CITERATOR*/,
    MELTFIELD_CITER_EXPAFTER = 6 /*in CLASS_CITERATOR*/,
    MELTLENGTH_CLASS_CITERATOR = 7
} ;
#define MELT_HAS_PREDEF_CLASS_CLASS
/* predefined class CLASS_CLASS index 4 */ enum
{
    MELTFIELD_CLASS_ANCESTORS = 5 /*in CLASS_CLASS*/,
    MELTFIELD_CLASS_FIELDS = 6 /*in CLASS_CLASS*/,
    MELTFIELD_CLASS_DATA = 7 /*in CLASS_CLASS*/,
    MELTLENGTH_CLASS_CLASS = 8
} ;
#define MELT_HAS_PREDEF_CLASS_CMATCHER
/* predefined class CLASS_CMATCHER index 5 */ enum
{
    MELTFIELD_CMATCH_STATE = 5 /*in CLASS_CMATCHER*/,
    MELTFIELD_CMATCH_EXPTEST = 6 /*in CLASS_CMATCHER*/,
    MELTFIELD_CMATCH_EXPFILL = 7 /*in CLASS_CMATCHER*/,
    MELTFIELD_CMATCH_EXPOPER = 8 /*in CLASS_CMATCHER*/,
    MELTLENGTH_CLASS_CMATCHER = 9
} ;
#define MELT_HAS_PREDEF_CLASS_CTYPE
/* predefined class CLASS_CTYPE index 6 */ enum
{
    MELTFIELD_CTYPE_CNAME = 4 /*in CLASS_CTYPE*/,
    MELTFIELD_CTYPE_PARCHAR = 5 /*in CLASS_CTYPE*/,
    MELTFIELD_CTYPE_PARSTRING = 6 /*in CLASS_CTYPE*/,
    MELTFIELD_CTYPE_ARGFIELD = 7 /*in CLASS_CTYPE*/,
    MELTFIELD_CTYPE_RESFIELD = 8 /*in CLASS_CTYPE*/,
    MELTFIELD_CTYPE_MARKER = 9 /*in CLASS_CTYPE*/,
    MELTFIELD_CTYPE_ALTKEYWORD = 10 /*in CLASS_CTYPE*/,
    MELTFIELD_CTYPE_AUTOBOXDISCR = 11 /*in CLASS_CTYPE*/,
    MELTFIELD_CTYPE_AUTOCONSTBOXDISCR = 12 /*in CLASS_CTYPE*/,
    MELTLENGTH_CLASS_CTYPE = 13
} ;
#define MELT_HAS_PREDEF_CLASS_CTYPE_GTY
/* predefined class CLASS_CTYPE_GTY index 7 */ enum
{
    MELTFIELD_CTYPG_BOXEDMAGIC = 13 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_MAPMAGIC = 14 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_BOXEDSTRUCT = 15 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_BOXEDUNIMEMB = 16 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_ENTRYSTRUCT = 17 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_MAPSTRUCT = 18 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_MAPDISCR = 19 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_MAPUNIMEMB = 20 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_BOXFUN = 21 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_UNBOXFUN = 22 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_UPDATEBOXFUN = 23 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_NEWMAPFUN = 24 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_MAPGETFUN = 25 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_MAPPUTFUN = 26 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_MAPREMOVEFUN = 27 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_MAPCOUNTFUN = 28 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_MAPSIZEFUN = 29 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_MAPNATTFUN = 30 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_MAPNVALFUN = 31 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_MAPAUXDATAFUN = 32 /*in CLASS_CTYPE_GTY*/,
    MELTFIELD_CTYPG_MAPAUXPUTFUN = 33 /*in CLASS_CTYPE_GTY*/,
    MELTLENGTH_CLASS_CTYPE_GTY = 34
} ;
#define MELT_HAS_PREDEF_CLASS_CTYPE_PLAIN
/* predefined class CLASS_CTYPE_PLAIN index 8 */ enum
{
    MELTFIELD_CTYPP_BOXING = 13 /*in CLASS_CTYPE_PLAIN*/,
    MELTFIELD_CTYPP_UNBOXING = 14 /*in CLASS_CTYPE_PLAIN*/,
    MELTLENGTH_CLASS_CTYPE_PLAIN = 15
} ;
#define MELT_HAS_PREDEF_CLASS_DISCRIMINANT
/* predefined class CLASS_DISCRIMINANT index 9 */ enum
{
    MELTFIELD_DISC_METHODICT = 2 /*in CLASS_DISCRIMINANT*/,
    MELTFIELD_DISC_SENDER = 3 /*in CLASS_DISCRIMINANT*/,
    MELTFIELD_DISC_SUPER = 4 /*in CLASS_DISCRIMINANT*/,
    MELTLENGTH_CLASS_DISCRIMINANT = 5
} ;
#define MELT_HAS_PREDEF_CLASS_ENVIRONMENT
/* predefined class CLASS_ENVIRONMENT index 10 */ enum
{
    MELTFIELD_ENV_BIND = 0 /*in CLASS_ENVIRONMENT*/,
    MELTFIELD_ENV_PREV = 1 /*in CLASS_ENVIRONMENT*/,
    MELTFIELD_ENV_PROC = 2 /*in CLASS_ENVIRONMENT*/,
    MELTLENGTH_CLASS_ENVIRONMENT = 3
} ;
#define MELT_HAS_PREDEF_CLASS_FIELD
/* predefined class CLASS_FIELD index 11 */ enum
{
    MELTFIELD_FLD_OWNCLASS = 2 /*in CLASS_FIELD*/,
    MELTFIELD_FLD_DATA = 3 /*in CLASS_FIELD*/,
    MELTLENGTH_CLASS_FIELD = 4
} ;
#define MELT_HAS_PREDEF_CLASS_FORMAL_BINDING
/* predefined class CLASS_FORMAL_BINDING index 12 */ enum
{
    MELTFIELD_FBIND_TYPE = 1 /*in CLASS_FORMAL_BINDING*/,
    MELTLENGTH_CLASS_FORMAL_BINDING = 2
} ;
#define MELT_HAS_PREDEF_CLASS_FUNMATCHER
/* predefined class CLASS_FUNMATCHER index 13 */ enum
{
    MELTFIELD_FMATCH_MATCHF = 5 /*in CLASS_FUNMATCHER*/,
    MELTFIELD_FMATCH_APPLYF = 6 /*in CLASS_FUNMATCHER*/,
    MELTFIELD_FMATCH_DATA = 7 /*in CLASS_FUNMATCHER*/,
    MELTLENGTH_CLASS_FUNMATCHER = 8
} ;
#define MELT_HAS_PREDEF_CLASS_GCC_GIMPLE_PASS
/* predefined class CLASS_GCC_GIMPLE_PASS index 14 */ enum
{
    MELTLENGTH_CLASS_GCC_GIMPLE_PASS = 10
} ;
#define MELT_HAS_PREDEF_CLASS_GCC_PASS
/* predefined class CLASS_GCC_PASS index 15 */ enum
{
    MELTFIELD_GCCPASS_GATE = 2 /*in CLASS_GCC_PASS*/,
    MELTFIELD_GCCPASS_EXEC = 3 /*in CLASS_GCC_PASS*/,
    MELTFIELD_GCCPASS_DATA = 4 /*in CLASS_GCC_PASS*/,
    MELTFIELD_GCCPASS_PROPERTIES_REQUIRED = 5 /*in CLASS_GCC_PASS*/,
    MELTFIELD_GCCPASS_PROPERTIES_PROVIDED = 6 /*in CLASS_GCC_PASS*/,
    MELTFIELD_GCCPASS_PROPERTIES_DESTROYED = 7 /*in CLASS_GCC_PASS*/,
    MELTFIELD_GCCPASS_TODO_FLAGS_START = 8 /*in CLASS_GCC_PASS*/,
    MELTFIELD_GCCPASS_TODO_FLAGS_FINISH = 9 /*in CLASS_GCC_PASS*/,
    MELTLENGTH_CLASS_GCC_PASS = 10
} ;
#define MELT_HAS_PREDEF_CLASS_GCC_PRAGMA
/* predefined class CLASS_GCC_PRAGMA index 16 */ enum
{
    MELTFIELD_GCCPRAGMA_HANDLER = 2 /*in CLASS_GCC_PRAGMA*/,
    MELTFIELD_GCCPRAGMA_DATA = 3 /*in CLASS_GCC_PRAGMA*/,
    MELTLENGTH_CLASS_GCC_PRAGMA = 4
} ;
#define MELT_HAS_PREDEF_CLASS_GCC_RTL_PASS
/* predefined class CLASS_GCC_RTL_PASS index 17 */ enum
{
    MELTLENGTH_CLASS_GCC_RTL_PASS = 10
} ;
#define MELT_HAS_PREDEF_CLASS_GCC_SIMPLE_IPA_PASS
/* predefined class CLASS_GCC_SIMPLE_IPA_PASS index 18 */ enum
{
    MELTLENGTH_CLASS_GCC_SIMPLE_IPA_PASS = 10
} ;
#define MELT_HAS_PREDEF_CLASS_GCC_TRANSFORM_IPA_PASS
/* predefined class CLASS_GCC_TRANSFORM_IPA_PASS index 19 */ enum
{
    MELTFIELD_GCCTRIPAPASS_STMT_FIXUP = 10 /*in CLASS_GCC_TRANSFORM_IPA_PASS*/,
    MELTFIELD_GCCTRIPAPASS_FUNCTION_TRANSFORM = 11 /*in CLASS_GCC_TRANSFORM_IPA_PASS*/,
    MELTFIELD_GCCTRIPAPASS_VARIABLE_TRANSFORM = 12 /*in CLASS_GCC_TRANSFORM_IPA_PASS*/,
    MELTLENGTH_CLASS_GCC_TRANSFORM_IPA_PASS = 13
} ;
#define MELT_HAS_PREDEF_CLASS_HOOK_DESCRIPTOR
/* predefined class CLASS_HOOK_DESCRIPTOR index 20 */ enum
{
    MELTFIELD_HOOKDESC_IN_FORMALS = 2 /*in CLASS_HOOK_DESCRIPTOR*/,
    MELTFIELD_HOOKDESC_OUT_FORMALS = 3 /*in CLASS_HOOK_DESCRIPTOR*/,
    MELTFIELD_HOOKDESC_CTYPE = 4 /*in CLASS_HOOK_DESCRIPTOR*/,
    MELTFIELD_HOOKDESC_HOOK = 5 /*in CLASS_HOOK_DESCRIPTOR*/,
    MELTLENGTH_CLASS_HOOK_DESCRIPTOR = 6
} ;
#define MELT_HAS_PREDEF_CLASS_INPUT_CHANNEL_HANDLER
/* predefined class CLASS_INPUT_CHANNEL_HANDLER index 21 */ enum
{
    MELTFIELD_INCH_SBUF = 1 /*in CLASS_INPUT_CHANNEL_HANDLER*/,
    MELTFIELD_INCH_CLOS = 2 /*in CLASS_INPUT_CHANNEL_HANDLER*/,
    MELTFIELD_INCH_DATA = 3 /*in CLASS_INPUT_CHANNEL_HANDLER*/,
    MELTLENGTH_CLASS_INPUT_CHANNEL_HANDLER = 4
} ;
#define MELT_HAS_PREDEF_CLASS_KEYWORD
/* predefined class CLASS_KEYWORD index 22 */ enum
{
    MELTLENGTH_CLASS_KEYWORD = 3
} ;
#define MELT_HAS_PREDEF_CLASS_LOCATED
/* predefined class CLASS_LOCATED index 23 */ enum
{
    MELTFIELD_LOCA_LOCATION = 1 /*in CLASS_LOCATED*/,
    MELTLENGTH_CLASS_LOCATED = 2
} ;
#define MELT_HAS_PREDEF_CLASS_MELT_MODE
/* predefined class CLASS_MELT_MODE index 24 */ enum
{
    MELTFIELD_MELTMODE_HELP = 2 /*in CLASS_MELT_MODE*/,
    MELTFIELD_MELTMODE_FUN = 3 /*in CLASS_MELT_MODE*/,
    MELTFIELD_MELTMODE_DATA = 4 /*in CLASS_MELT_MODE*/,
    MELTLENGTH_CLASS_MELT_MODE = 5
} ;
#define MELT_HAS_PREDEF_CLASS_NAMED
/* predefined class CLASS_NAMED index 25 */ enum
{
    MELTFIELD_NAMED_NAME = 1 /*in CLASS_NAMED*/,
    MELTLENGTH_CLASS_NAMED = 2
} ;
#define MELT_HAS_PREDEF_CLASS_PRIMITIVE
/* predefined class CLASS_PRIMITIVE index 26 */ enum
{
    MELTFIELD_PRIM_FORMALS = 2 /*in CLASS_PRIMITIVE*/,
    MELTFIELD_PRIM_TYPE = 3 /*in CLASS_PRIMITIVE*/,
    MELTFIELD_PRIM_EXPANSION = 4 /*in CLASS_PRIMITIVE*/,
    MELTLENGTH_CLASS_PRIMITIVE = 5
} ;
#define MELT_HAS_PREDEF_CLASS_PROPED
/* predefined class CLASS_PROPED index 27 */ enum
{
    MELTFIELD_PROP_TABLE = 0 /*in CLASS_PROPED*/,
    MELTLENGTH_CLASS_PROPED = 1
} ;
#define MELT_HAS_PREDEF_CLASS_REFERENCE
/* predefined class CLASS_REFERENCE index 28 */ enum
{
    MELTFIELD_REFERENCED_VALUE = 0 /*in CLASS_REFERENCE*/,
    MELTLENGTH_CLASS_REFERENCE = 1
} ;
#define MELT_HAS_PREDEF_CLASS_ROOT
/* predefined class CLASS_ROOT index 29 */ enum
{
    MELTLENGTH_CLASS_ROOT = 0
} ;
#define MELT_HAS_PREDEF_CLASS_SELECTOR
/* predefined class CLASS_SELECTOR index 30 */ enum
{
    MELTFIELD_SEL_SIGNATURE = 2 /*in CLASS_SELECTOR*/,
    MELTFIELD_SEL_DATA = 3 /*in CLASS_SELECTOR*/,
    MELTLENGTH_CLASS_SELECTOR = 4
} ;
#define MELT_HAS_PREDEF_CLASS_SEXPR
/* predefined class CLASS_SEXPR index 31 */ enum
{
    MELTFIELD_SEXP_CONTENTS = 2 /*in CLASS_SEXPR*/,
    MELTLENGTH_CLASS_SEXPR = 3
} ;
#define MELT_HAS_PREDEF_CLASS_SEXPR_MACROSTRING
/* predefined class CLASS_SEXPR_MACROSTRING index 32 */ enum
{
    MELTLENGTH_CLASS_SEXPR_MACROSTRING = 3
} ;
#define MELT_HAS_PREDEF_CLASS_SYMBOL
/* predefined class CLASS_SYMBOL index 33 */ enum
{
    MELTFIELD_SYMB_DATA = 2 /*in CLASS_SYMBOL*/,
    MELTLENGTH_CLASS_SYMBOL = 3
} ;
#define MELT_HAS_PREDEF_CLASS_SYSTEM_DATA
/* predefined class CLASS_SYSTEM_DATA index 34 */ enum
{
    MELTFIELD_SYSDATA_MODE_DICT = 2 /*in CLASS_SYSTEM_DATA*/,
    MELTFIELD_SYSDATA_SYMBOLDICT = 3 /*in CLASS_SYSTEM_DATA*/,
    MELTFIELD_SYSDATA_KEYWDICT = 4 /*in CLASS_SYSTEM_DATA*/,
    MELTFIELD_SYSDATA_PASS_DICT = 5 /*in CLASS_SYSTEM_DATA*/,
    MELTFIELD_SYSDATA_DEBUGMSG = 6 /*in CLASS_SYSTEM_DATA*/,
    MELTFIELD_SYSDATA_STDOUT = 7 /*in CLASS_SYSTEM_DATA*/,
    MELTFIELD_SYSDATA_STDERR = 8 /*in CLASS_SYSTEM_DATA*/,
    MELTFIELD_SYSDATA_DUMPFILE = 9 /*in CLASS_SYSTEM_DATA*/,
    MELTFIELD_SYSDATA_OPTION_SET = 10 /*in CLASS_SYSTEM_DATA*/,
    MELTFIELD_SYSDATA_MELTPRAGMAS = 11 /*in CLASS_SYSTEM_DATA*/,
    MELTFIELD_SYSDATA_SRC_LOC_FILE_DICT = 12 /*in CLASS_SYSTEM_DATA*/,
    MELTFIELD_SYSDATA___SPARE1 = 13 /*in CLASS_SYSTEM_DATA*/,
    MELTFIELD_SYSDATA___SPARE2 = 14 /*in CLASS_SYSTEM_DATA*/,
    MELTFIELD_SYSDATA___SPARE3 = 15 /*in CLASS_SYSTEM_DATA*/,
    MELTFIELD_SYSDATA___SPARE4 = 16 /*in CLASS_SYSTEM_DATA*/,
    MELTLENGTH_CLASS_SYSTEM_DATA = 17
} ;
/** end of code generated by generate_runtypesupport_predef_fields **/


/* declarations generated by generate_runtypesupport_predefined_hooks for 146 predefined */

/*predefined hook declaration HOOK_ALL_IPA_PASSES_END #106*/
MELT_EXTERN void melthookproc_HOOK_ALL_IPA_PASSES_END();

/*predefined hook declaration HOOK_ALL_IPA_PASSES_START #107*/
MELT_EXTERN void melthookproc_HOOK_ALL_IPA_PASSES_START();

/*predefined hook declaration HOOK_ALL_PASSES_END #108*/
MELT_EXTERN void melthookproc_HOOK_ALL_PASSES_END();

/*predefined hook declaration HOOK_ALL_PASSES_START #109*/
MELT_EXTERN void melthookproc_HOOK_ALL_PASSES_START();

/*predefined hook declaration HOOK_EARLY_GIMPLE_PASSES_END #110*/
MELT_EXTERN void melthookproc_HOOK_EARLY_GIMPLE_PASSES_END();

/*predefined hook declaration HOOK_EARLY_GIMPLE_PASSES_START #111*/
MELT_EXTERN void melthookproc_HOOK_EARLY_GIMPLE_PASSES_START();

/*predefined hook declaration HOOK_EXIT_FINALIZER #112*/
MELT_EXTERN void melthookproc_HOOK_EXIT_FINALIZER();

/*predefined hook declaration HOOK_FINISH_DECL #113*/
MELT_EXTERN void melthookproc_HOOK_FINISH_DECL(tree meltin_TFNDECL_p0);

/*predefined hook declaration HOOK_FINISH_TYPE #114*/
MELT_EXTERN void melthookproc_HOOK_FINISH_TYPE(tree meltin_TFNDECL_p0);

/*predefined hook declaration HOOK_FINISH_UNIT #115*/
MELT_EXTERN void melthookproc_HOOK_FINISH_UNIT();

/*predefined hook declaration HOOK_GIMPLE_EXECUTE #116*/
MELT_EXTERN long melthookproc_HOOK_GIMPLE_EXECUTE();

/*predefined hook declaration HOOK_GIMPLE_GATE #117*/
MELT_EXTERN long melthookproc_HOOK_GIMPLE_GATE();

/*predefined hook declaration HOOK_HANDLE_SIGALRM #118*/
MELT_EXTERN void melthookproc_HOOK_HANDLE_SIGALRM();

/*predefined hook declaration HOOK_HANDLE_SIGCHLD #119*/
MELT_EXTERN void melthookproc_HOOK_HANDLE_SIGCHLD();

/*predefined hook declaration HOOK_HANDLE_SIGIO #120*/
MELT_EXTERN void melthookproc_HOOK_HANDLE_SIGIO();

/*predefined hook declaration HOOK_INTERN_KEYWORD #121*/
MELT_EXTERN melt_ptr_t melthookproc_HOOK_INTERN_KEYWORD(melt_ptr_t meltin_KEYWV_p0);

/*predefined hook declaration HOOK_INTERN_SYMBOL #122*/
MELT_EXTERN melt_ptr_t melthookproc_HOOK_INTERN_SYMBOL(melt_ptr_t meltin_SYMBV_p0);

/*predefined hook declaration HOOK_LOW_DEBUG_VALUE_AT #123*/
MELT_EXTERN void melthookproc_HOOK_LOW_DEBUG_VALUE_AT(melt_ptr_t meltin_VAL_p0, const char* meltin_FILENAME_p1, long meltin_LINENO_p2, const char* meltin_MSG_p3, long meltin_COUNT_p4);

/*predefined hook declaration HOOK_MELT_ATTRIBUTE_DEFINER #124*/
MELT_EXTERN void melthookproc_HOOK_MELT_ATTRIBUTE_DEFINER(tree meltin_DECL_p0, tree meltin_NAME_p1, melt_ptr_t meltin_ATTRSEQ_p2, const char* meltin_FILELOC_p3, long meltin_LINENO_p4);

/*predefined hook declaration HOOK_NAMED_KEYWORD #125*/
MELT_EXTERN melt_ptr_t melthookproc_HOOK_NAMED_KEYWORD(const char* meltin_NAM_p0, long meltin_CREATE_p1);

/*predefined hook declaration HOOK_NAMED_SYMBOL #126*/
MELT_EXTERN melt_ptr_t melthookproc_HOOK_NAMED_SYMBOL(const char* meltin_NAM_p0, long meltin_CREATE_p1);

/*predefined hook declaration HOOK_OVERRIDE_GATE #127*/
MELT_EXTERN void melthookproc_HOOK_OVERRIDE_GATE(long meltin_BEFOREGATE_p0, long* meltout_AFTERGATE_o0);

/*predefined hook declaration HOOK_PASS_EXECUTION #128*/
MELT_EXTERN void melthookproc_HOOK_PASS_EXECUTION(const char* meltin_PASSNAME_p0, long meltin_PASSNUM_p1);

/*predefined hook declaration HOOK_POLL_INPUTS #129*/
MELT_EXTERN void melthookproc_HOOK_POLL_INPUTS(long meltin_DELAYMS_p0);

/*predefined hook declaration HOOK_PRE_GENERICIZE #130*/
MELT_EXTERN void melthookproc_HOOK_PRE_GENERICIZE(tree meltin_TFNDECL_p0);

/*predefined hook declaration HOOK_RTL_EXECUTE #131*/
MELT_EXTERN long melthookproc_HOOK_RTL_EXECUTE();

/*predefined hook declaration HOOK_RTL_GATE #132*/
MELT_EXTERN long melthookproc_HOOK_RTL_GATE();

/*predefined hook declaration HOOK_SIMPLE_IPA_EXECUTE #133*/
MELT_EXTERN long melthookproc_HOOK_SIMPLE_IPA_EXECUTE();

/*predefined hook declaration HOOK_SIMPLE_IPA_GATE #134*/
MELT_EXTERN long melthookproc_HOOK_SIMPLE_IPA_GATE();

/*predefined hook declaration HOOK_START_UNIT #135*/
MELT_EXTERN void melthookproc_HOOK_START_UNIT();

/*predefined hook declaration HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER #136*/
MELT_EXTERN melt_ptr_t melthookproc_HOOK_FRESH_ENVIRONMENT_REFERENCE_MAKER(melt_ptr_t meltin_PREVENV_p0, const char* meltin_MODULNAME_p1);

/*predefined hook declaration HOOK_SYMBOL_IMPORTER #137*/
MELT_EXTERN melt_ptr_t melthookproc_HOOK_SYMBOL_IMPORTER(const char* meltin_SYMNAMESTR_p0, const char* meltin_MODULENAMESTR_p1, melt_ptr_t meltin_PARENV_p2);

/*predefined hook declaration HOOK_VALUE_EXPORTER #138*/
MELT_EXTERN void melthookproc_HOOK_VALUE_EXPORTER(melt_ptr_t meltin_SYM_p0, melt_ptr_t meltin_VAL_p1, melt_ptr_t meltin_CONTENV_p2);

/*predefined hook declaration HOOK_MACRO_EXPORTER #139*/
MELT_EXTERN void melthookproc_HOOK_MACRO_EXPORTER(melt_ptr_t meltin_SYM_p0, melt_ptr_t meltin_VAL_p1, melt_ptr_t meltin_CONTENV_p2);

/*predefined hook declaration HOOK_PATMACRO_EXPORTER #140*/
MELT_EXTERN void melthookproc_HOOK_PATMACRO_EXPORTER(melt_ptr_t meltin_SYM_p0, melt_ptr_t meltin_MACVAL_p1, melt_ptr_t meltin_PATVAL_p2, melt_ptr_t meltin_CONTENV_p3);
/* end of declarations generated by generate_runtypesupport_predefined_hooks for 146 predefined */

/*** End of declaration file meltbuild-sources/generated/meltrunsup.h generated on 2013 Jun 26
 * by GCC MELT 4.8.0 20130314 (experimental) [melt-branch revision 200402] MELT_0.9.9-post . ***/
