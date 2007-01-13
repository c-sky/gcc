
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_swing_text_JTextComponent$DefaultKeymap__
#define __javax_swing_text_JTextComponent$DefaultKeymap__

#pragma interface

#include <java/lang/Object.h>
#include <gcj/array.h>

extern "Java"
{
  namespace javax
  {
    namespace swing
    {
        class Action;
        class KeyStroke;
      namespace text
      {
          class JTextComponent$DefaultKeymap;
          class Keymap;
      }
    }
  }
}

class javax::swing::text::JTextComponent$DefaultKeymap : public ::java::lang::Object
{

public:
  JTextComponent$DefaultKeymap(::java::lang::String *);
  virtual void addActionForKeyStroke(::javax::swing::KeyStroke *, ::javax::swing::Action *);
  virtual ::javax::swing::Action * getAction(::javax::swing::KeyStroke *);
  virtual JArray< ::javax::swing::Action * > * getBoundActions();
  virtual JArray< ::javax::swing::KeyStroke * > * getBoundKeyStrokes();
  virtual ::javax::swing::Action * getDefaultAction();
  virtual JArray< ::javax::swing::KeyStroke * > * getKeyStrokesForAction(::javax::swing::Action *);
  virtual ::java::lang::String * getName();
  virtual ::javax::swing::text::Keymap * getResolveParent();
  virtual jboolean isLocallyDefined(::javax::swing::KeyStroke *);
  virtual void removeBindings();
  virtual void removeKeyStrokeBinding(::javax::swing::KeyStroke *);
  virtual void setDefaultAction(::javax::swing::Action *);
  virtual void setResolveParent(::javax::swing::text::Keymap *);
public: // actually package-private
  ::java::lang::String * __attribute__((aligned(__alignof__( ::java::lang::Object)))) name;
  ::javax::swing::text::Keymap * parent;
  ::java::util::Hashtable * map;
  ::javax::swing::Action * defaultAction;
public:
  static ::java::lang::Class class$;
};

#endif // __javax_swing_text_JTextComponent$DefaultKeymap__
