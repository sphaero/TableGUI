#ifndef __GUI_DRAW_H__
#define __GUI_DRAW_H__
#include <GL/gl.h>

typedef struct TPointFloatStruct TPointFloat;

struct TPointFloatStruct
{
  float FX;
  float FY;
};

void glDrawCircle(const float ALeft, const float ATop, const float ARight, const float ABottom);
void glDrawCircleFill(const float ALeft, const float ATop, const float ARight, const float ABottom);
void glDrawRectangle(const float ALeft, const float ATop, const float ARight, const float ABottom);
void glDrawRectangleFill(const float ALeft, const float ATop, const float ARight, const float ABottom);

void glDrawBezierLine(const TPointFloat *APointArray);

#endif /* __GUI_DRAW_H__ */