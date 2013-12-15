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
#include "GUI_theme.h"
#include "GUI_checkbox.h"

void GUIWidget_KeyDown(TGUIWidget *AWidget, int AKey)
{
  if (AWidget->FOnKeyDown)
  {
    //AWidget->FOnKeyDown(AWidget, AKey);
  };
};

void GUIWidget_KeyUp(TGUIWidget *AWidget, int AKey)
{
  if (AWidget->FOnKeyUp)
  {
    //AWidget->FOnKeyUp(AWidget, AKey);
  };
};

void GUIWidget_MouseDown(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY)
{
  if (Widget_GetBool(AWidget, "canfocus"))
  {
    AWidget->FWindow->FWidgetFocused = AWidget;
  };
  if (AWidget->FOnMouseDown)
  {
    //AWidget->FOnMouseDown(AWidget, AMouseX, AMouseY);
  };
  
  Widget_SetInt(AWidget, "down", TRUE);
};

void GUIWidget_MouseUp(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY)
{
  if (AWidget->FOnMouseUp)
  {
    //AWidget->FOnMouseUp(AWidget, AMouseX, AMouseY);
  };
  
  if (Widget_GetBool(AWidget, "down"))
  {
    if (AWidget->FMouseClick)
    {
      AWidget->FMouseClick(AWidget, AButton, AMouseX, AMouseY);
    };
  };
  
  Widget_SetInt(AWidget, "down", FALSE);
};

void GUIWidget_MouseClick(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY)
{
  if (AWidget->FOnMouseClick)
  {
    //AWidget->FOnMouseClick(AWidget);
  };
};

void GUIWidget_MouseEnter(TGUIWidget *AWidget)
{
  if ((AWidget == AWidget->FWindow->FWidgetFocused) &&
  (AWidget->FWindow->FMouseDown))
  {
    Widget_SetBool(AWidget, "down", TRUE);
  };
};

void GUIWidget_MouseLeave(TGUIWidget *AWidget)
{
  Widget_SetBool(AWidget, "down", FALSE);
};

void Alloc_GUIWidget(TGUIWidget *AWidget)
{
  Widget_SetInt(AWidget, "width", 96);
  Widget_SetInt(AWidget, "height", 16);
  
  AWidget->FDraw = NULL;
  AWidget->FMouseDown = &GUIWidget_MouseDown;
  AWidget->FMouseUp = &GUIWidget_MouseUp;
  AWidget->FMouseMove = NULL;
  AWidget->FMouseEnter = &GUIWidget_MouseEnter;
  AWidget->FMouseLeave = &GUIWidget_MouseLeave;
  AWidget->FMouseClick = &GUIWidget_MouseClick;
};

