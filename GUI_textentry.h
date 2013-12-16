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

typedef struct TTextEntryPropertiesStruct TTextEntryProperties;

struct TTextEntryPropertiesStruct
{
  TIterator *FText;
  TIterator *FCursor;
  bboolean FTextWrap;
  
  int FPositionY;
  int FPositionX;
  bboolean FLeftLine;
  bboolean FShowGutter;
  bboolean FShowLineNumbers;
  TColorFloat FGutterBackground;
  TColorFloat FGutterForeground;
  TColorFloat FTextBackground;
  TColorFloat FTextForeground;
  TColorFloat FSelectionBackground;
  TColorFloat FSelectionForeground;
  bboolean FHighlightCurrentLine;
  bboolean FDrawSpaces;
};

char * GUITextEntry_GetPrintableCharacters(TIterator *AIterator);

void Alloc_GUITextEntry(TGUIWidget *AWidget);

#endif
