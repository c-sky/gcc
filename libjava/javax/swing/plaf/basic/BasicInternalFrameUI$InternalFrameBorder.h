
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_swing_plaf_basic_BasicInternalFrameUI$InternalFrameBorder__
#define __javax_swing_plaf_basic_BasicInternalFrameUI$InternalFrameBorder__

#pragma interface

#include <javax/swing/border/AbstractBorder.h>
extern "Java"
{
  namespace java
  {
    namespace awt
    {
        class Component;
        class Graphics;
        class Insets;
    }
  }
  namespace javax
  {
    namespace swing
    {
      namespace plaf
      {
        namespace basic
        {
            class BasicInternalFrameUI;
            class BasicInternalFrameUI$InternalFrameBorder;
        }
      }
    }
  }
}

class javax::swing::plaf::basic::BasicInternalFrameUI$InternalFrameBorder : public ::javax::swing::border::AbstractBorder
{

public: // actually package-private
  BasicInternalFrameUI$InternalFrameBorder(::javax::swing::plaf::basic::BasicInternalFrameUI *);
public:
  virtual jboolean isBorderOpaque();
  virtual ::java::awt::Insets * getBorderInsets(::java::awt::Component *);
  virtual void paintBorder(::java::awt::Component *, ::java::awt::Graphics *, jint, jint, jint, jint);
public: // actually package-private
  static const jint bSize = 5;
  static const jint cornerSize = 10;
  ::javax::swing::plaf::basic::BasicInternalFrameUI * __attribute__((aligned(__alignof__( ::javax::swing::border::AbstractBorder)))) this$0;
public:
  static ::java::lang::Class class$;
};

#endif // __javax_swing_plaf_basic_BasicInternalFrameUI$InternalFrameBorder__
