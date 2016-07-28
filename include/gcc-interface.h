/* Generic interface between GCC and GDB

   Copyright (C) 2014-2015 Free Software Foundation, Inc.

   This file is part of GCC.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef GCC_INTERFACE_H
#define GCC_INTERFACE_H

/* This header defines the interface to the GCC API.  It must be both
   valid C and valid C++, because it is included by both programs.  */

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque typedefs for objects passed through the interface.  */

typedef unsigned long long gcc_type;
typedef unsigned long long gcc_decl;

/* An address in the inferior.  */

typedef unsigned long long gcc_address;

/* Forward declaration.  */

struct gcc_base_context;

/* Defined versions of the generic API.  */

enum gcc_base_api_version
{
  GCC_FE_VERSION_0 = 0,
  GCC_FE_VERSION_1 = 1,
};

/* The operations defined by the GCC base API.  This is the vtable for
   the real context structure which is passed around.

   The "base" API is concerned with basics shared by all compiler
   front ends: setting command-line arguments, the file names, etc.

   Front-end-specific interfaces inherit from this one.  */

struct gcc_base_vtable
{
  /* The actual version implemented in this interface.  This field can
     be relied on not to move, so users can always check it if they
     desire.  The value is one of the gcc_base_api_version constants.
  */

  unsigned int version;

  /* Set the compiler's command-line options for the next compilation.
     TRIPLET_REGEXP is a regular expression that is used to match the
     configury triplet prefix to the compiler.
     The arguments are copied by GCC.  ARGV need not be
     NULL-terminated.  The arguments must be set separately for each
     compilation; that is, after a compile is requested, the
     previously-set arguments cannot be reused.

     This returns NULL on success.  On failure, returns a malloc()d
     error message.  The caller is responsible for freeing it.  */

  char *(*set_arguments) (struct gcc_base_context *self,
			  const char *triplet_regexp,
			  int argc, char **argv);

  /* Set the file name of the program to compile.  The string is
     copied by the method implementation, but the caller must
     guarantee that the file exists through the compilation.  */

  void (*set_source_file) (struct gcc_base_context *self, const char *file);

  /* Set a callback to use for printing error messages.  DATUM is
     passed through to the callback unchanged.  */

  void (*set_print_callback) (struct gcc_base_context *self,
			      void (*print_function) (void *datum,
						      const char *message),
			      void *datum);

  /* Perform the compilation.  FILENAME is the name of the resulting
     object file.  VERBOSE can be set to cause GCC to print some
     information as it works.  Returns true on success, false on
     error.  */

  int /* bool */ (*compile) (struct gcc_base_context *self,
			     const char *filename,
			     int /* bool */ verbose);

  /* Destroy this object.  */

  void (*destroy) (struct gcc_base_context *self);
};

/* The GCC object.  */

struct gcc_base_context
{
  /* The virtual table.  */

  const struct gcc_base_vtable *ops;
};

/* The name of the dummy wrapper function generated by gdb.  */

#define GCC_FE_WRAPPER_FUNCTION "_gdb_expr"

#ifdef __cplusplus
}
#endif

#endif /* GCC_INTERFACE_H */
