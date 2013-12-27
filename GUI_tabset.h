/*
  This file is part of TableGUI.
  Copyright (c) 2014 Felipe Ferreira da Silva
  
  TableGUI is licensed under MIT license.
  See the file "LICENSE" for license details.
*/

#ifndef __GUI_TABSET_H__
#define __GUI_TABSET_H__
#include "GUI.h"
#include "GUI_theme.h"

typedef struct TGUITabsetPropertiesStruct TGUITabsetProperties;
typedef void (*TEventHandler_DrawTab)(TGUIWidget *AWidget, int ALeft, int ARight, char *AText, bboolean AActive);

struct TGUITabsetPropertiesStruct
{
  signed int FPosition;
  int FActiveTab;
  bboolean FUseFixedLength;
  unsigned int FLength;
  TIterator *FListTab;
  bboolean FOrientation;

  bboolean FScrolling; 
  int FMouseDownAt; 
  int FTabsetLength; 
  // FALSE = Horizontal.
  // TRUE = Vertical;
};

void GUITabset_DeleteTab(TGUIWidget *AWidget, int AIndex);
void GUITabset_AddTab(TGUIWidget *AWidget, const char *ALabel);
void Alloc_GUITabset(TGUIWidget *AWidget);

#endif
