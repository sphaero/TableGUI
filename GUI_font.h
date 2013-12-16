#ifndef __GUIFONT_H__
#define __GUIFONT_H__
#include <GL/gl.h>

typedef struct TGUIFontStruct TGUIFont;
typedef struct TGUIFontCharStruct TGUIFontChar;

struct TGUIFontCharStruct
{
  int FAdvanceX;
  int FAdvanceY;
  int FBearingX;
  int FBearingY;
  int FWidth;
  int FHeight;
  GLuint FTexture;
};
struct TGUIFontStruct
{
  int FTextureSize;
  float FHeight;
  TGUIFontChar *FFontChar;
  char *FFontName;
};

GUIFont_MakeCharTexture(TGUIFont *AFont, TGUIFontChar *AFontChar, unsigned char AChar);
TGUIFont *Alloc_GUIFont(const char *AFontName, float AHeight, int ATextureSize);
void glPrint(const TGUIFont *AFont, int AX, int AY, const unsigned char *AText);
int glTextHeight(const TGUIFont *AFont, const unsigned char *AText);
int glTextWidth(const TGUIFont *AFont, const unsigned char *AText);


#endif /* __GUIFONT_H__ */