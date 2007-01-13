
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_java_awt_peer_qt_QtFontPeer__
#define __gnu_java_awt_peer_qt_QtFontPeer__

#pragma interface

#include <gnu/java/awt/peer/ClasspathFontPeer.h>
#include <gcj/array.h>

extern "Java"
{
  namespace gnu
  {
    namespace java
    {
      namespace awt
      {
        namespace peer
        {
          namespace qt
          {
              class QtFontMetrics;
              class QtFontPeer;
          }
        }
      }
    }
  }
  namespace java
  {
    namespace awt
    {
        class Font;
        class FontMetrics;
      namespace font
      {
          class FontRenderContext;
          class GlyphVector;
          class LineMetrics;
      }
      namespace geom
      {
          class Rectangle2D;
      }
    }
    namespace text
    {
        class CharacterIterator;
    }
  }
}

class gnu::java::awt::peer::qt::QtFontPeer : public ::gnu::java::awt::peer::ClasspathFontPeer
{

public:
  QtFontPeer(::java::lang::String *, jint);
  QtFontPeer(::java::lang::String *, jint, jint);
  QtFontPeer(::java::lang::String *, ::java::util::Map *);
  virtual void init();
private:
  void create(::java::lang::String *, jint, jint);
public:
  virtual void dispose();
  virtual jboolean canDisplay(::java::awt::Font *, jchar);
  virtual jint canDisplayUpTo(::java::awt::Font *, ::java::text::CharacterIterator *, jint, jint);
  virtual ::java::lang::String * getSubFamilyName(::java::awt::Font *, ::java::util::Locale *);
  virtual ::java::lang::String * getPostScriptName(::java::awt::Font *);
  virtual jint getNumGlyphs(::java::awt::Font *);
  virtual jint getMissingGlyphCode(::java::awt::Font *);
  virtual jbyte getBaselineFor(::java::awt::Font *, jchar);
  virtual ::java::lang::String * getGlyphName(::java::awt::Font *, jint);
  virtual ::java::awt::font::GlyphVector * createGlyphVector(::java::awt::Font *, ::java::awt::font::FontRenderContext *, ::java::text::CharacterIterator *);
  virtual ::java::awt::font::GlyphVector * createGlyphVector(::java::awt::Font *, ::java::awt::font::FontRenderContext *, JArray< jint > *);
  virtual ::java::awt::font::GlyphVector * layoutGlyphVector(::java::awt::Font *, ::java::awt::font::FontRenderContext *, JArray< jchar > *, jint, jint, jint);
  virtual ::java::awt::FontMetrics * getFontMetrics(::java::awt::Font *);
  virtual jboolean hasUniformLineMetrics(::java::awt::Font *);
  virtual ::java::awt::font::LineMetrics * getLineMetrics(::java::awt::Font *, ::java::text::CharacterIterator *, jint, jint, ::java::awt::font::FontRenderContext *);
  virtual ::java::awt::geom::Rectangle2D * getMaxCharBounds(::java::awt::Font *, ::java::awt::font::FontRenderContext *);
private:
  jlong __attribute__((aligned(__alignof__( ::gnu::java::awt::peer::ClasspathFontPeer)))) nativeObject;
  ::gnu::java::awt::peer::qt::QtFontMetrics * metrics;
public:
  static ::java::lang::Class class$;
};

#endif // __gnu_java_awt_peer_qt_QtFontPeer__
