
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_javax_crypto_mac_HMacFactory__
#define __gnu_javax_crypto_mac_HMacFactory__

#pragma interface

#include <java/lang/Object.h>
extern "Java"
{
  namespace gnu
  {
    namespace javax
    {
      namespace crypto
      {
        namespace mac
        {
            class HMacFactory;
            class IMac;
        }
      }
    }
  }
}

class gnu::javax::crypto::mac::HMacFactory : public ::java::lang::Object
{

  HMacFactory();
public:
  static ::gnu::javax::crypto::mac::IMac * getInstance(::java::lang::String *);
  static ::java::util::Set * getNames();
  static ::java::lang::Class class$;
};

#endif // __gnu_javax_crypto_mac_HMacFactory__
