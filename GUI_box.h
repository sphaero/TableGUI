/*
  This file is part of TableGUI.
  Copyright (c) 2014 Felipe Ferreira da Silva
  
  TableGUI is licensed under MIT license.
  See the file "LICENSE" for license details.
*/

#ifndef __GUI_BOX_H__
#define __GUI_BOX_H__
#include "GUI.h"
#include "GUI_theme.h"

struct TGUIBoxAlignmentStruct
{
  bboolean FExpand;
  bboolean FFill;
};

void Alloc_GUIBox(TGUIWidget *AWidget);

#endif
