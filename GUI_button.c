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
#include "GUI_widget.h"
#include "GUI_theme.h"
#include "GUI_button.h"

void GUIButton_Draw(TGUIWidget *AWidget)
{
  
  if (Widget_GetBool(AWidget, "enabled"))
  {
    // BEGIN - Draw the background and the borders.
    int BWidth = Widget_GetInt(AWidget, "width");
    int BHeight = Widget_GetInt(AWidget, "height");
    
    if (Widget_GetBool(AWidget, "down"))
    {
      glColor4f(0.5, 0.5, 0.5, 1.0);
    } else
    {
      if (AWidget == AWidget->FWindow->FWidgetMouseOver)
      {
        glColor4f(0.7, 0.7, 0.7, 1.0);
      } else
      {
        glColor4f(0.6, 0.6, 0.6, 1.0);
      };
    };
    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, BHeight, 0.0);
    glVertex3f(BWidth, BHeight, 0.0);
    glVertex3f(BWidth, 0.0, 0.0);
    glEnd();
    
    if (Widget_GetBool(AWidget, "down"))
    {
      glColor4f(0.3, 0.3, 0.3, 1.0);
    } else
    {
      if (AWidget == AWidget->FWindow->FWidgetMouseOver)
      {
        glColor4f(0.5, 0.5, 0.5, 1.0);
      } else
      {
        glColor4f(0.4, 0.4, 0.4, 1.0);
      };
    };
    glBegin(GL_LINES);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, BHeight, 0.0);
    glVertex3f(0.0, BHeight - 1, 0.0);
    glVertex3f(BWidth, BHeight - 1, 0.0);
    glVertex3f(BWidth, BHeight, 0.0);
    glVertex3f(BWidth, 1.0, 0.0);
    glVertex3f(BWidth, BHeight - 2, 0.0);
    glVertex3f(1.0, BHeight - 2, 0.0);
    glEnd();
    
      glColor4f(0.0, 0.0, 0.0, 1.0);
    glBegin(GL_POINT);
    glVertex3f(4.0, 4.0, 0.0);
    glEnd();
    
  } else
  {
  
  };
};

void Alloc_GUIButton(TGUIWidget *AWidget)
{
  Alloc_GUIWidget(AWidget);
  Widget_AddString(AWidget, "text", "Button");
  
  AWidget->FDraw = &GUIButton_Draw;  
};

