/*
  This file is part of TableGUI.
  Copyright (c) 2014 Felipe Ferreira da Silva
  
  TableGUI is licensed under MIT license.
  See the file "LICENSE" for license details.
*/

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <basicutils.h>
#include "GUI.h"
#include "GUI_font.h"
#include "GUI_widget.h"
#include "GUI_theme.h"
#include "GUI_textentry.h"

char * GUITextEntry_GetPrintableCharacters(TIterator *AIterator)
{
  unsigned char *BText = (unsigned char *)malloc(sizeof(unsigned char));
  BText[0] = '\0';
  int BSize = 1;
  
  while ((isdigit(*(unsigned char *)AIterator->FPointer)) &&
  ((unsigned char *)AIterator->FPointer != ' '))
  {
    BSize++;
    BText = (unsigned char *)realloc(BText, sizeof(unsigned char *) * BSize);
    AIterator = AIterator->FNext;
  };
  
  return BText;
};

void GUITextEntry_KeyDown(TGUIWidget *AWidget, int AKey, int AScanCode, int AMods)
{
  TTextEntryProperties *BTextEntryProperties = Widget_GetPointer(AWidget, "text");
  
  if (((AKey >= 32) && (AKey <= 96)) ||
  (AKey == GLFW_KEY_ENTER) ||
  (AKey == GLFW_KEY_TAB))
  {
    unsigned char *BChar = (unsigned char *)malloc(sizeof(unsigned char));
    *BChar = AKey;
    TIterator *BIterator = Alloc_Iterator(BChar);
    Iterator_Insert(BTextEntryProperties->FText, BTextEntryProperties->FCursor, BIterator, ipBefore);
    
    BTextEntryProperties->FCursor = BIterator;
  } else
  {
    switch (AKey)
    {
      case GLFW_KEY_BACKSPACE:
      {
        if (BTextEntryProperties->FCursor->FPrevious)
        {
          Iterator_Remove(BTextEntryProperties->FText, BTextEntryProperties->FCursor->FPrevious);
        };
        break;
      };
      
    };
  };
};

void GUITextEntry_MouseDown(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY)
{
  GUIWidget_MouseDown(AWidget, AButton, AMouseX, AMouseY);
};

void GUITextEntry_Draw(TGUIWidget *AWidget)
{
  TTextEntryProperties *BTextEntryProperties = Widget_GetPointer(AWidget, "text");
  TIterator *BIterator = BTextEntryProperties->FText->FFirstChild;
  int BLine = 0;
  int BLineHeight = glTextHeight(AWidget->FWindow->FFont, "Wg");
  int BX = 0;
  unsigned char *BWord = NULL;
  
  while (BIterator)
  {
    // Draw only the text in the visible area.
    if isdigit(*(unsigned char *)BIterator->FPointer)
    {
      BWord = GUITextEntry_GetPrintableCharacters(BIterator);
      glPrint(AWidget->FWindow->FFont, BX, BLine * BLineHeight, BWord);
      BX = BX + glTextWidth(AWidget->FWindow->FFont, BWord);
      free(BWord);
    } else
    {
      if (*(unsigned char *)BIterator->FPointer == '\n')
      {
        BX = 0;
      } else
      if (*(unsigned char *)BIterator->FPointer == ' ')
      {
        BX = BX + glTextWidth(AWidget->FWindow->FFont, " \0");
      } else
      if (*(unsigned char *)BIterator->FPointer == '\0')
      {
        break;
      };
    };
    BIterator = BIterator->FNext;
  };
};

void Alloc_GUITextEntry(TGUIWidget *AWidget)
{
  Alloc_GUIWidget(AWidget);
  TTextEntryProperties *BTextEntryProperties = (TTextEntryProperties *)malloc(sizeof(BTextEntryProperties));
  
  Widget_AddPointer(AWidget, "text", BTextEntryProperties);
  Widget_AddPointer(AWidget, "cur", NULL);
  
  AWidget->FDraw = &GUITextEntry_Draw;
  AWidget->FMouseDown = &GUITextEntry_MouseDown;
};

