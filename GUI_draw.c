/*
  This file is part of TableGUI.
  Copyright (c) 2014 Felipe Ferreira da Silva
  
  TableGUI is licensed under MIT license.
  See the file "LICENSE" for license details.
*/

#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <basicutils.h>
#include "GUI.h"
#include "GUI_draw.h"

TRect GetIntersection(TRect *ARectA, TRect *ARectB)
{
  TRect BReturn = {0, 0, 0, 0};

  if (ARectA->FLeft > ARectB->FLeft)
  {
    BReturn.FLeft = ARectA->FLeft;
  } else
  {
    BReturn.FLeft = ARectB->FLeft;
  };

  if (ARectA->FTop > ARectB->FTop)
  {
    BReturn.FTop = ARectA->FTop;
  } else
  {
    BReturn.FTop = ARectB->FTop;
  };
  
  if (ARectA->FRight < ARectB->FRight)
  {
    BReturn.FRight = ARectA->FRight;
  } else
  {
    BReturn.FRight = ARectB->FRight;
  };

  if (ARectA->FBottom < ARectB->FBottom)
  {
    BReturn.FBottom = ARectA->FBottom;
  } else
  {
    BReturn.FBottom = ARectB->FBottom;
  };

  return BReturn;
};

void glSetColor(TColorFloat AColor)
{
  glClearColor(AColor.FRed, AColor.FGreen, AColor.FBlue, 1.0);
  glColor4f(AColor.FRed, AColor.FGreen, AColor.FBlue, 1.0);
};