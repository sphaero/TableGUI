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

typedef struct TGUIButtonPropertiesStruct TGUIButtonProperties;

struct TGUIButtonPropertiesStruct
{
  TColorFloat FColorNormal;
  TColorFloat FColorDown;
  TColorFloat FColorFocused;
  TColorFloat FColorDisabled;
  TColorFloat FColorHighlight;
  TString *FText;
  GLuint FImageTexture;
};

void Alloc_GUIButton(TGUIWidget *AWidget);

#endif
