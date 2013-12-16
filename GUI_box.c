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
#include "GUI_box.h"

void GUIBox_Draw(TGUIWidget *AWidget)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  glColor4f(0.4, 0.4, 0.4, 1.0);
  glBegin(GL_QUADS);
    glVertex3f(BWidgetProperties->FWidth, BWidgetProperties->FHeight, 0.0);
    glVertex3f(0.0, BWidgetProperties->FHeight, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(BWidgetProperties->FWidth, 0.0, 0.0);
  glEnd();

  glLineStipple(1, 0xAAAA);
  glEnable(GL_LINE_STIPPLE);
  glColor4f(0.3, 0.3, 0.3, 1.0);
  glBegin(GL_LINE_STRIP);
    glVertex3f(BWidgetProperties->FWidth - 1.0, BWidgetProperties->FHeight - 1.0, 0.0);
    glVertex3f(0.0, BWidgetProperties->FHeight - 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(BWidgetProperties->FWidth - 1.0, 0.0, 0.0);
    glVertex3f(BWidgetProperties->FWidth - 1.0, BWidgetProperties->FHeight, 0.0);
  glEnd();
  glDisable(GL_LINE_STIPPLE);
};

void Alloc_GUIBox(TGUIWidget *AWidget)
{
  Alloc_GUIWidget(AWidget);
  
  AWidget->FDraw = &GUIBox_Draw;
};

