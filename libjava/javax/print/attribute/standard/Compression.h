
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_print_attribute_standard_Compression__
#define __javax_print_attribute_standard_Compression__

#pragma interface

#include <javax/print/attribute/EnumSyntax.h>
#include <gcj/array.h>

extern "Java"
{
  namespace javax
  {
    namespace print
    {
      namespace attribute
      {
          class EnumSyntax;
        namespace standard
        {
            class Compression;
        }
      }
    }
  }
}

class javax::print::attribute::standard::Compression : public ::javax::print::attribute::EnumSyntax
{

public: // actually protected
  Compression(jint);
public:
  virtual ::java::lang::Class * getCategory();
  virtual ::java::lang::String * getName();
public: // actually protected
  virtual JArray< ::java::lang::String * > * getStringTable();
  virtual JArray< ::javax::print::attribute::EnumSyntax * > * getEnumValueTable();
private:
  static const jlong serialVersionUID = -5716748913324997674LL;
public:
  static ::javax::print::attribute::standard::Compression * NONE;
  static ::javax::print::attribute::standard::Compression * DEFLATE;
  static ::javax::print::attribute::standard::Compression * GZIP;
  static ::javax::print::attribute::standard::Compression * COMPRESS;
private:
  static JArray< ::java::lang::String * > * stringTable;
  static JArray< ::javax::print::attribute::standard::Compression * > * enumValueTable;
public:
  static ::java::lang::Class class$;
};

#endif // __javax_print_attribute_standard_Compression__
