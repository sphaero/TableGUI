#ifndef __GUI_DRAW_H__
#define __GUI_DRAW_H__
#include <GL/gl.h>

typedef struct TPointFloatStruct TPointFloat;
typedef struct TColorFloatStruct TColorFloat;
typedef struct TRectStruct TRect;
typedef struct TImageSheetStruct TImageSheet;

struct TPointFloatStruct
{
  float FX;
  float FY;
};

struct TColorFloatStruct
{
  float FRed;
  float FGreen;
  float FBlue;
};

struct TRectStruct
{
  int FLeft;
  int FRight;
  int FTop;
  int FBottom;
};

struct TImageSheetStruct
{
  int FTextureWidth;
  int FTextureHeight;
  int FGridWidth;
  int FGridHeight;
  int FImageCount;
  GLuint *FTexture;
};

void glDrawImage(TImageSheet *AImageSheet, float APosX, float APosY, int AImage);

TRect GetIntersection(TRect *ARectA, TRect *ARectB);
void glSetColor(TColorFloat AColor);
void glDrawCircle(const float ALeft, const float ATop, const float ARight, const float ABottom);
void glDrawCircleFill(const float ALeft, const float ATop, const float ARight, const float ABottom);
void glDrawRectangle(const float ALeft, const float ATop, const float ARight, const float ABottom);
void glDrawRectangleFill(const float ALeft, const float ATop, const float ARight, const float ABottom);

void glDrawBezierLine(const TPointFloat *APointArray);

#endif /* __GUI_DRAW_H__ */