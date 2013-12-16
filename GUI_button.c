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
#include "GUI_button.h"

void GUIButton_MouseDown(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY)
{
  GUIWidget_MouseDown(AWidget, AButton, AMouseX, AMouseY);
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  if (AButton == GLFW_MOUSE_BUTTON_LEFT)
  {
    BWidgetProperties->FDown = TRUE;
  } else
  if (AButton == GLFW_MOUSE_BUTTON_RIGHT)
  {
    BWidgetProperties->FDown = FALSE;
  };
};

void GUIButton_Draw(TGUIWidget *AWidget)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  if (BWidgetProperties->FEnabled)
  {
    // BEGIN - Draw the background and the borders.
    
    if (BWidgetProperties->FDown)
    {
      glColor4f(0.5, 0.5, 0.5, 1.0);
    } else
    {
      if (AWidget == AWidget->FWindow->FWidgetMouseOver)
      {
        glColor4f(0.8, 0.8, 0.8, 1.0);
      } else
      {
        glColor4f(0.7, 0.7, 0.7, 1.0);
      };
    };
    glBegin(GL_QUADS);
      glVertex3f(BWidgetProperties->FWidth, BWidgetProperties->FHeight, 0.0);
      glVertex3f(0.0, BWidgetProperties->FHeight, 0.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(BWidgetProperties->FWidth, 0.0, 0.0);
    glEnd();
    
    char *BText = Widget_GetString(AWidget, "text");

    glPrint(AWidget->FWindow->FFont, (BWidgetProperties->FWidth / 2) - (glTextWidth(AWidget->FWindow->FFont, BText) / 2),
                                     (BWidgetProperties->FHeight / 2) + (glTextHeight(AWidget->FWindow->FFont, BText) / 2),
                                     BText);
	  
    /*if (BDown)
    {
      glColor4f(0.7, 0.7, 0.7, 1.0);
    } else
    {
      if (AWidget == AWidget->FWindow->FWidgetMouseOver)
      {
        glColor4f(0.9, 0.9, 0.9, 1.0);
      } else
      {
        glColor4f(0.8, 0.8, 0.8, 1.0);
      };
    };
    glBegin(GL_LINE_STRIP);
      glVertex3f(BWidth - 1.0, BHeight - 1.0, 0.0);
      glVertex3f(0.0, BHeight - 1.0, 0.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(BWidth -1.0, 0.0, 0.0);
      glVertex3f(BWidth - 1.0, BHeight, 0.0);
    glEnd();
    
    glTranslatef(0.0, 0.0, 0.0);*/
  } else
  {
  
  };
};

void Alloc_GUIButton(TGUIWidget *AWidget)
{
  Alloc_GUIWidget(AWidget);
  Widget_AddString(AWidget, "text", "Button");
  
  AWidget->FDraw = &GUIButton_Draw;
  AWidget->FMouseDown = &GUIButton_MouseDown;
};

