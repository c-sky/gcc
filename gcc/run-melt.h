/* Basile's static analysis (should have a better name) run-mmelt.h
   all include files for generated code
   
   Copyright 2008 Free Software Foundation, Inc.
   Contributed by Basile Starynkevitch <basile@starynkevitch.net>
   Indented with GNU indent 

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to
the Free Software Foundation, 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.  */

/* all file including this are somehow plugins, perhaps MELT specific ones */
#include "gcc-plugin.h"



/* usual GCC middle-end includes, copied from melt-runtime.c */

#include "config.h"

/* this is intended to pass -DDISABLE_CHECKING explicitly */
#ifdef DISABLE_CHECKING
#undef ENABLE_CHECKING
#endif

#include "system.h"
#include "coretypes.h"
#include "obstack.h"
#include "tm.h"
#include "tree.h"
#include "gimple.h"
#include "filenames.h"
#include "tree-pass.h"
#include "tree-dump.h"
#include "tree-flow.h"
#include "tree-iterator.h"
#include "tree-inline.h"
#include "basic-block.h"
#include "timevar.h"
#include "ggc.h"
#include "cgraph.h"
#include "diagnostic.h"
#include "flags.h"
#include "toplev.h"
#include "options.h"
#include "params.h"
#include "real.h"
#include "prefix.h"
#include "md5.h"
#include "cppdefault.h"


/* MELT specific includes */


#include "ppl_c.h"
#include "melt-runtime.h"


#define curfptr curfram__.varptr
#define curfnum curfram__.varnum
#define curfclos curfram__.clos
#define curfrout curfram__.clos->rout

/* these are added by the *melt-cc-script shell script */
extern const char melt_compiled_timestamp[];
extern const char melt_md5[];

/* this is generated by gengtype */
extern void gt_ggc_mx_melt_un (void*);

#warning temporary definitions for renaming


#define MELTGLOB_CLASS_DISCR MELTGLOB_CLASS_DISCRIMINANT
#define MELTGLOB_CTYPE_BASICBLOCK MELTGLOB_CTYPE_BASIC_BLOCK
#define MELTGLOB_CTYPE_GIMPLESEQ MELTGLOB_CTYPE_GIMPLE_SEQ
#define MELTGLOB_DISCR_ANYRECV MELTGLOB_DISCR_ANY_RECEIVER
#define MELTGLOB_DISCR_BASICBLOCK MELTGLOB_DISCR_BASIC_BLOCK
#define MELTGLOB_DISCR_CONSTINTEGER MELTGLOB_DISCR_CONSTANT_INTEGER
#define MELTGLOB_DISCR_GIMPLESEQ MELTGLOB_DISCR_GIMPLE_SEQ
#define MELTGLOB_DISCR_MAPBASICBLOCKS MELTGLOB_DISCR_MAP_BASIC_BLOCKS 
#define MELTGLOB_DISCR_MAPEDGES MELTGLOB_DISCR_MAP_EDGES	 
#define MELTGLOB_DISCR_MAPGIMPLES MELTGLOB_DISCR_MAP_GIMPLES
#define MELTGLOB_DISCR_MAPGIMPLESEQS MELTGLOB_DISCR_MAP_GIMPLE_SEQS	 
#define MELTGLOB_DISCR_MAPOBJECTS MELTGLOB_DISCR_MAP_OBJECTS	 
#define MELTGLOB_DISCR_MAPSTRINGS MELTGLOB_DISCR_MAP_STRINGS	 
#define MELTGLOB_DISCR_MAPTREES MELTGLOB_DISCR_MAP_TREES    
#define MELTGLOB_DISCR_MIXBIGINT MELTGLOB_DISCR_MIXED_BIGINT
#define MELTGLOB_DISCR_MIXEDINT MELTGLOB_DISCR_MIXED_INTEGER
#define MELTGLOB_DISCR_MIXEDLOC MELTGLOB_DISCR_MIXED_LOCATION
#define MELTGLOB_DISCR_NAMESTRING MELTGLOB_DISCR_NAME_STRING
#define MELTGLOB_DISCR_NULLRECV MELTGLOB_DISCR_NULL_RECEIVER
#define MELTGLOB_DISCR_SEQCLASS MELTGLOB_DISCR_CLASS_SEQUENCE
#define MELTGLOB_DISCR_SEQFIELD MELTGLOB_DISCR_FIELD_SEQUENCE
#define MELTGLOB_DISCR_VERBATIMSTRING MELTGLOB_DISCR_VERBATIM_STRING

/* eof run-melt.h */
