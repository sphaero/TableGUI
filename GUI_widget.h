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

void GUIWidget_KeyDown(TGUIWidget *AWidget, int AKey, int AScancode, int AMods);

void GUIWidget_KeyUp(TGUIWidget *AWidget, int AKey, int AScancode, int AMods);

void GUIWidget_MouseDown(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY);

void GUIWidget_MouseUp(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY);

void GUIWidget_MouseClick(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY);

void GUIWidget_MouseEnter(TGUIWidget *AWidget);

void GUIWidget_MouseLeave(TGUIWidget *AWidget);

void Alloc_GUIWidget(TGUIWidget *AWidget);
