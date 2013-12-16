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
#include "GUI_font.h"
#include "GUI_widget.h"
#include "GUI_theme.h"
#include "GUI_splitter.h"

void GUISplitter_MoveSplitter(TGUIWidget *AWidget, int AMousePos, int AOffset)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  TGUIWidgetProperties *BParentWidgetProperties = NULL;
  int BParentMax = 0;
  if (AWidget->FWindow->FWidgetMouseDown == AWidget)
  {
    if (Widget_GetBool(AWidget, "ori"))
    {
      int BGlobalWidgetY = GetWidgetGlobalTop(AWidget);
      // Horizontal:
      BWidgetProperties->FTop = BWidgetProperties->FTop + AMousePos - AOffset;

      if (AWidget->FParent)
      {
        BParentWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget->FParent, "prop");
        BParentMax = BParentWidgetProperties->FHeight;
      } else
      {
        BParentMax = AWidget->FWindow->FHeight;
      };
      if (BWidgetProperties->FTop + BWidgetProperties->FHeight > BParentMax)
      {
        BWidgetProperties->FTop = BParentMax - BWidgetProperties->FHeight;
      };
      if (BWidgetProperties->FTop < 0)
      {
        BWidgetProperties->FTop = 0;
      };
      BWidgetProperties->FTop = (int)(BWidgetProperties->FTop / 8) * 8;
    } else
    {
      int BGlobalWidgetX = GetWidgetGlobalLeft(AWidget);
      // Vertical:
      BWidgetProperties->FLeft = BWidgetProperties->FLeft + AMousePos - AOffset;
      
      if (AWidget->FParent)
      {
        BParentWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget->FParent, "prop");
        BParentMax = BParentWidgetProperties->FWidth;
      } else
      {
        BParentMax = AWidget->FWindow->FWidth;
      };
      if (BWidgetProperties->FLeft + BWidgetProperties->FWidth > BParentMax)
      {
        BWidgetProperties->FLeft = BParentMax - BWidgetProperties->FWidth;
      };
      if (BWidgetProperties->FLeft < 0)
      {
        BWidgetProperties->FLeft = 0;
      };
      BWidgetProperties->FLeft = (int)(BWidgetProperties->FLeft / 8) * 8;
    };
  };
};

void GUISplitter_MouseMove(TGUIWidget *AWidget, int AMouseX, int AMouseY)
{
  if (Widget_GetBool(AWidget, "ori"))
  {
    GUISplitter_MoveSplitter(AWidget, AMouseY, Widget_GetInt(AWidget, "offset"));
  } else
  {
    GUISplitter_MoveSplitter(AWidget, AMouseX, Widget_GetInt(AWidget, "offset"));
  };
};

void GUISplitter_MouseDown(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY)
{
  if (Widget_GetBool(AWidget, "ori"))
  {
    Widget_SetInt(AWidget, "offset", AMouseY);
  } else
  {
    Widget_SetInt(AWidget, "offset", AMouseX);
  };
};

void GUISplitter_Draw(TGUIWidget *AWidget)
{
  // BEGIN - Draw the background and the borders.
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  
  glClearColor(0.45, 0.45, 0.45, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  
  /*glColor4f(0.5, 0.5, 0.5, 1.0);
  glTranslatef(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
    glVertex3f(BWidth, BHeight, 0.0);
    glVertex3f(0.0, BHeight, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(BWidth, 0.0, 0.0);
  glEnd();*/
};

void Alloc_GUISplitter(TGUIWidget *AWidget)
{
  Alloc_GUIWidget(AWidget);
  Widget_AddBool(AWidget, "ori", FALSE);
  Widget_AddInt(AWidget, "offset", 0);
  // FALSE = Vertical
  // TRUE = Horizontal
  
  AWidget->FDraw = &GUISplitter_Draw;
  AWidget->FMouseDown = &GUISplitter_MouseDown;
  AWidget->FMouseMove = &GUISplitter_MouseMove;
};

