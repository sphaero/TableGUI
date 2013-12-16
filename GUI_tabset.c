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
#include "GUI_widget.h"
#include "GUI_theme.h"
#include "GUI_button.h"
#include "GUI_tabset.h"

void GUITabset_AddTab(TGUIWidget *AWidget, const char *ALabel)
{
  TGUITabsetProperties *BTabsetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "tabset");
  Iterator_AddPointer(BTabsetProperties->FListTab, Alloc_String(ALabel));
};

void GUITabset_SetActiveTab(TGUIWidget *AWidget, const int AIndex)
{
  TGUITabsetProperties *BTabsetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "tabset");
  BTabsetProperties->FActiveTab = AIndex;
};

int GUITabset_GetTabAt(TGUIWidget *AWidget, int AMouseX, int AMouseY)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  TGUITabsetProperties *BTabsetProperties = (TGUITabsetProperties *)Widget_GetPointer(AWidget, "tabset");
  TIterator *BIteratorTab = NULL;
  
  int BReturn = -1;
  int BTextWidth = 0;
  int BTextHeight = 0;
  int BTabPos = 0;
  int BTabIndex = 0;
  
  BIteratorTab = BTabsetProperties->FListTab->FFirstChild;
  BTabIndex = 0;
  if (BTabsetProperties->FOrientation == FALSE)
  {
    while (BIteratorTab)
    {
      TString *BString = (TString *)BIteratorTab->FPointer;
      if (BString)
      {
        BTextWidth = glTextWidth(AWidget->FWindow->FFont, String_Value(BString));
        BTextHeight = glTextHeight(AWidget->FWindow->FFont, String_Value(BString));
        
        if ((AMouseX >= BTabPos + BTabsetProperties->FPosition) &&
          (AMouseX < BTabPos + 8 + BTabsetProperties->FPosition + BTextWidth))
        {
          BReturn = BTabIndex;
        };
        BTabPos = BTabPos + BTextWidth + 8;
      };
      BIteratorTab = BIteratorTab->FNext;
      BTabIndex = BTabIndex + 1;
    };
  } else
  {
    // Vertical orientation.
  }
  return BReturn;
};

void GUITabset_MouseDown(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY)
{
  TGUITabsetProperties *BTabsetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "tabset");
  GUIWidget_MouseDown(AWidget, AButton, AMouseX, AMouseY);
  BTabsetProperties->FActiveTab = GUITabset_GetTabAt(AWidget, AMouseX, AMouseY);
};

void GUITabset_DeleteTab(TGUIWidget *AWidget, int AIndex)
{
  TGUITabsetProperties *BTabsetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "tabset");
  Iterator_Remove(BTabsetProperties->FListTab, Iterator_GetFromIndex(BTabsetProperties->FListTab, AIndex));
};

void GUITabset_Draw(TGUIWidget *AWidget)
{
  TIterator *BListTab = (TIterator *)Widget_GetPointer(AWidget, "listtab");
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  TGUITabsetProperties *BTabsetProperties = (TGUITabsetProperties *)Widget_GetPointer(AWidget, "tabset");
  TIterator *BIteratorTab = NULL;
  
  int BTextWidth = 0;
  int BTextHeight = 0;
  int BTabPos = 0;
  int BTabIndex = 0;

  glColor4f(0.35, 0.35, 0.35, 1.0);
  glBegin(GL_QUADS);
    glVertex3f(BWidgetProperties->FWidth, BWidgetProperties->FHeight, 0.0);
    glVertex3f(0.0, BWidgetProperties->FHeight, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(BWidgetProperties->FWidth, 0.0, 0.0);
  glEnd();
  
  BIteratorTab = BTabsetProperties->FListTab->FFirstChild;
  BTabIndex = 0;
  while (BIteratorTab)
  {
    TString *BString = (TString *)BIteratorTab->FPointer;
    if (BString)
    {
      BTextWidth = glTextWidth(AWidget->FWindow->FFont, String_Value(BString));
      BTextHeight = glTextHeight(AWidget->FWindow->FFont, String_Value(BString));
      if (BTabIndex == BTabsetProperties->FActiveTab)
      {
        glColor4f(0.4, 0.4, 0.4, 1.0);
        glBegin(GL_QUADS);
          glVertex3f(BTabPos + 8 + BTabsetProperties->FPosition + BTextWidth, BWidgetProperties->FHeight, 0.0);
          glVertex3f(BTabPos + BTabsetProperties->FPosition, BWidgetProperties->FHeight, 0.0);
          glVertex3f(BTabPos + BTabsetProperties->FPosition, 0.0, 0.0);
          glVertex3f(BTabPos + 8 + BTabsetProperties->FPosition + BTextWidth, 0.0, 0.0);
        glEnd();
      };
      glPrint(AWidget->FWindow->FFont, BTabPos + 4 + BTabsetProperties->FPosition, (BWidgetProperties->FHeight / 2) + (BTextHeight / 2), String_Value(BString));
      BTabPos = BTabPos + BTextWidth + 8;
    };
    BIteratorTab = BIteratorTab->FNext;
    BTabIndex = BTabIndex + 1;
  };
};

void Alloc_GUITabset(TGUIWidget *AWidget)
{
  Alloc_GUIWidget(AWidget);
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  TGUITabsetProperties *BTabsetProperties = (TGUITabsetProperties *)malloc(sizeof(TGUITabsetProperties));
  
  BWidgetProperties->FWidth = 96;
  BWidgetProperties->FHeight = 24;
  BTabsetProperties->FPosition = 0;
  BTabsetProperties->FListTab = Alloc_Iterator(NULL);
  BTabsetProperties->FUseFixedLength = FALSE;
  BTabsetProperties->FLength = 96;
  BTabsetProperties->FActiveTab = -1;
  BTabsetProperties->FOrientation = FALSE;
  
  Widget_AddPointer(AWidget, "tabset", BTabsetProperties);
  
  AWidget->FDraw = &GUITabset_Draw;  
  AWidget->FMouseDown = &GUITabset_MouseDown;  
};