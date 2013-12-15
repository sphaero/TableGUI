/*
  This file is part of TableGUI.
  Copyright (c) 2014 Felipe Ferreira da Silva
  
  TableGUI is licensed under MIT license.
  See the file "LICENSE" for license details.
*/

#ifndef __GUI_BUTTON_H__
#define __GUI_BUTTON_H__
#include "GUI.h"
#include "GUI_theme.h"

void GUITabset_DeleteTab(TGUIWidget *AWidget, int AIndex);
void GUITabset_AddTab(TGUIWidget *AWidget, const char *ALabel);
void Alloc_GUITabset(TGUIWidget *AWidget);

#endif
