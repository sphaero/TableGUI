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
#include "GUI_notebook.h"

void GUINotebook_SetActivePage(TGUIWidget *AWidget, const int AIndex)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  if (Widget_GetInt(AWidget, "page") != AIndex)
  {
    TIterator *BChildIterator = AWidget->FListChild->FFirstChild;
    TGUIWidget *BChild = NULL;
    int BIndex = 0;
    Widget_SetInt(AWidget, "page", AIndex);
    
    while (BChildIterator)
    {
      BChild = (TGUIWidget *)BChildIterator->FPointer;
      TGUIWidgetProperties *BChildProperties = (TGUIWidgetProperties *)Widget_GetPointer(BChild, "prop");
      if (BIndex == AIndex)
      {
        BChildProperties->FVisible = TRUE;
        printf("Set widget %s visible.\n", BChild->FName->FPointer);
      } else
      {
        BChildProperties->FVisible = FALSE;
        printf("Set widget %s invisible.\n", BChild->FName->FPointer);
      };

      BIndex++;
      BChildIterator = BChildIterator->FNext;
    };
  }
};

void GUINotebook_Draw(TGUIWidget *AWidget)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  glClearColor(0.35, 0.35, 0.35, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
};

void Alloc_GUINotebook(TGUIWidget *AWidget)
{
  Alloc_GUIWidget(AWidget);
  Widget_AddInt(AWidget, "page", -1);
  AWidget->FDraw = &GUINotebook_Draw;  
};