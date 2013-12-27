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
  
  glClearColor(BWidgetProperties->FColor.FRed, BWidgetProperties->FColor.FGreen, BWidgetProperties->FColor.FBlue, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1, 0xAAAA);
  glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
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
  String_Assign(AWidget->FClass, "box");
};

