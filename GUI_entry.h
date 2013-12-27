/*
  This file is part of TableGUI.
  Copyright (c) 2014 Felipe Ferreira da Silva
  
  TableGUI is licensed under MIT license.
  See the file "LICENSE" for license details.
*/

#ifndef __GUI_ENTRY_H__
#define __GUI_ENTRY_H__
#include "GUI.h"
#include "GUI_theme.h"

typedef struct TGUIEntryPropertiesStruct TGUIEntryProperties;

struct TGUIEntryPropertiesStruct
{
  int FTimerID;
  int FCaret;
  int FSelectionStart;
  int FPosition;
  TString *FText;
};

void Alloc_GUIEntry(TGUIWidget *AWidget);

#endif
