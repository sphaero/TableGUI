#ifndef __GUIFONT_H__
#define __GUIFONT_H__
#include <GL/gl.h>

typedef struct TGUIFontStruct TGUIFont;
typedef struct TGUIFontExtentStruct TGUIFontExtent;

struct TGUIFontExtentStruct
{
  int FAdvanceX;
  int FAdvanceY;
  int FBearingX;
  int FBearingY;
  int FWidth;
  int FHeight;
};

struct TGUIFontStruct
{
  GLuint FTexture;
  unsigned int FTextureWidth;
  unsigned int FTextureHeight;
  unsigned int FGridWidth;
  unsigned int FGridHeight;
  TGUIFontExtent *FExtents;

  float FHeight;
  char *FFontName;
};

//GUIFont_MakeCharTexture(TGUIFont *AFont, TGUIFontChar *AFontChar, unsigned char AChar);
void GUIFont_GetGreaterSize(const char *AFontName, float AHeight, unsigned int *ACharWidth, unsigned int *ACharHeight);
TGUIFont *Alloc_GUIFont(const char *AFontName, float AHeight);
void glPrint(const TGUIFont *AFont, int AX, int AY, const unsigned char *AText, float AColorRed, float AColorGreen, float AColorBlue);
int glTextHeight(const TGUIFont *AFont, const unsigned char *AText);
int glTextWidth(const TGUIFont *AFont, const unsigned char *AText);
int glTextWidthUntil(const TGUIFont *AFont, const unsigned char *AText, int AIndex);


#endif /* __GUIFONT_H__ */