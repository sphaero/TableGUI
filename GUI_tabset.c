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

void GUITabset_UpdateTabsetLength(TGUIWidget *AWidget)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  TGUITabsetProperties *BTabsetProperties = (TGUITabsetProperties *)Widget_GetPointer(AWidget, "tabset");
  TIterator *BIteratorTab = NULL;
  
  int BReturn = -1;
  int BTextWidth = 0;
  int BTextHeight = 0;
  int BTabPos = 0;
  
  BIteratorTab = BTabsetProperties->FListTab->FFirstChild;
  if (BTabsetProperties->FOrientation == FALSE)
  {
    while (BIteratorTab)
    {
      TString *BString = (TString *)BIteratorTab->FPointer;
      if (BString)
      {
        BTextWidth = glTextWidth(AWidget->FWindow->FFont, String_Value(BString));
        BTextHeight = glTextHeight(AWidget->FWindow->FFont, String_Value(BString));

        BTabPos = BTabPos + BTextWidth + 8;
      };
      BIteratorTab = BIteratorTab->FNext;
    };
  } else
  {
    // Vertical orientation.
  }
  BTabsetProperties->FTabsetLength = BTabPos;
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
        BTabPos = BTabPos + BTextWidth + 8 - 1;
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

void GUITabset_AddTab(TGUIWidget *AWidget, const char *ALabel)
{
  TGUITabsetProperties *BTabsetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "tabset");
  Iterator_AddPointer(BTabsetProperties->FListTab, Alloc_String(ALabel));
  GUITabset_UpdateTabsetLength(AWidget);
};

void GUITabset_SetActiveTab(TGUIWidget *AWidget, const int AIndex)
{
  TEventHandler_Default BTagChange = (TEventHandler_Default)Widget_GetSignal(AWidget, "tab");
  TGUITabsetProperties *BTabsetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "tabset");
  if (BTabsetProperties->FActiveTab != AIndex)
  {
    BTabsetProperties->FActiveTab = AIndex;
    //printf("[MESSAGE] %s active tab is %i.\n", AWidget->FName->FPointer, AIndex);
    if (BTagChange)
    {
      BTagChange(AWidget);
    };
  };
};

void GUITabset_DeleteTab(TGUIWidget *AWidget, int AIndex)
{
  TGUITabsetProperties *BTabsetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "tabset");
  Iterator_Remove(BTabsetProperties->FListTab, Iterator_GetFromIndex(BTabsetProperties->FListTab, AIndex));
  GUITabset_UpdateTabsetLength(AWidget);
};

void GUITabset_AdjustTabPosition(TGUIWidget *AWidget, TGUIWidgetProperties *AWidgetProperties, TGUITabsetProperties *ATabsetProperties)
{
  if (ATabsetProperties->FTabsetLength <= AWidgetProperties->FWidth)
  {
    if (ATabsetProperties->FPosition + ATabsetProperties->FTabsetLength > AWidgetProperties->FWidth)
    {
      ATabsetProperties->FPosition = AWidgetProperties->FWidth - ATabsetProperties->FTabsetLength;
    };
    if (ATabsetProperties->FPosition < 0)
    {
      ATabsetProperties->FPosition = 0;
    };
  } else
  {
    if (ATabsetProperties->FPosition < (int)(AWidgetProperties->FWidth - ATabsetProperties->FTabsetLength))
    {
      ATabsetProperties->FPosition = AWidgetProperties->FWidth - ATabsetProperties->FTabsetLength;
    };
    if (ATabsetProperties->FPosition > 0)
    {
      ATabsetProperties->FPosition = 0;
    };
  };
};

void GUITabset_Scroll(TGUIWidget *AWidget, double AXOffset, double AYOffset)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  TGUITabsetProperties *BTabsetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "tabset");
  
  BTabsetProperties->FPosition = BTabsetProperties->FPosition - (-AXOffset * (BWidgetProperties->FWidth / 100));
  GUITabset_AdjustTabPosition(AWidget, BWidgetProperties, BTabsetProperties);
};

void GUITabset_MouseMove(TGUIWidget *AWidget, int AMouseX, int AMouseY)
{ 
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  TGUITabsetProperties *BTabsetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "tabset");
  
  if (BTabsetProperties->FScrolling)
  {
    int BDiff = BTabsetProperties->FMouseDownAt - AMouseX;
    BTabsetProperties->FMouseDownAt = AMouseX;
    BTabsetProperties->FPosition = BTabsetProperties->FPosition - BDiff;
    GUITabset_AdjustTabPosition(AWidget, BWidgetProperties, BTabsetProperties);

    if (AMouseX + BWidgetProperties->FGlobalRect.FLeft > AWidget->FWindow->FWidth - 2)
    {
      printf("Change cursor position to 0.\n");
      glfwSetCursorPos(AWidget->FWindow->FGLFW_Window, 1, BWidgetProperties->FGlobalRect.FTop + AMouseY);
      printf("Now mouse at 0.\n");
      BTabsetProperties->FMouseDownAt = -BWidgetProperties->FGlobalRect.FLeft;
    };
    if (AMouseX + BWidgetProperties->FGlobalRect.FLeft < 1)
    {
      printf("Change cursor position to window width.\n");
      glfwSetCursorPos(AWidget->FWindow->FGLFW_Window, AWidget->FWindow->FWidth - 2, BWidgetProperties->FGlobalRect.FTop + AMouseY);
      BTabsetProperties->FMouseDownAt = AWidget->FWindow->FWidth - 2 - BWidgetProperties->FGlobalRect.FLeft;
      printf("Now mouse down at %i.\n", BTabsetProperties->FMouseDownAt);
    };
    
  };
};

void GUITabset_MouseDown(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY)
{
  TGUITabsetProperties *BTabsetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "tabset");
  GUIWidget_MouseDown(AWidget, AButton, AMouseX, AMouseY);
  if (AButton == GLFW_MOUSE_BUTTON_LEFT)
  {
    GUITabset_SetActiveTab(AWidget, GUITabset_GetTabAt(AWidget, AMouseX, AMouseY));
  } else
  {
    BTabsetProperties->FScrolling = TRUE;
    BTabsetProperties->FMouseDownAt = AMouseX;
  };
};

void GUITabset_MouseUp(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY)
{
  TGUITabsetProperties *BTabsetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "tabset");
  GUIWidget_MouseUp(AWidget, AButton, AMouseX, AMouseY);
  if (AButton == GLFW_MOUSE_BUTTON_LEFT)
  {
    GUITabset_SetActiveTab(AWidget, GUITabset_GetTabAt(AWidget, AMouseX, AMouseY));
  };
  BTabsetProperties->FScrolling = FALSE;
  BTabsetProperties->FMouseDownAt = 0;
};

void GUITabset_Resize(TGUIWidget *AWidget, double AWidth, double AHeight)
{
  GUIWidget_Resize(AWidget, AWidth, AHeight);
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  TGUITabsetProperties *BTabsetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "tabset");
  GUITabset_AdjustTabPosition(AWidget, BWidgetProperties, BTabsetProperties);
};

void GUITabset_Draw(TGUIWidget *AWidget)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  TGUITabsetProperties *BTabsetProperties = (TGUITabsetProperties *)Widget_GetPointer(AWidget, "tabset");
  TIterator *BIteratorTab = NULL;
  
  TEventHandler_DrawTab BDrawTab = (TEventHandler_DrawTab)Widget_GetSignal(AWidget, "drawtab");
  TEventHandler_Default BDraw = (TEventHandler_Default)Widget_GetSignal(AWidget, "drawtab");
  
  int BTextWidth = 0;
  int BTextHeight = 0;
  int BTabPos = 0;
  int BTabIndex = 0;
  glClearColor(0.35, 0.35, 0.35, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (BDraw)
  {
    BDraw(AWidget);
  };
  
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
          glVertex3f( BTabPos + BTabsetProperties->FPosition + BTextWidth + 8, 0.0f,                             0.0f);
          glVertex3f( BTabPos + BTabsetProperties->FPosition,                  0.0f,                             0.0f);
          glVertex3f( BTabPos + BTabsetProperties->FPosition,                  BWidgetProperties->FHeight,       0.0f);
          glVertex3f( BTabPos + BTabsetProperties->FPosition + BTextWidth + 8, BWidgetProperties->FHeight,       0.0f);
        glEnd();
      };
      glPrint(AWidget->FWindow->FFont, BTabPos + 4 + BTabsetProperties->FPosition, (BWidgetProperties->FHeight / 2) + (BTextHeight / 2), String_Value(BString), 0.0f, 0.0f, 0.0f);
      if (BDrawTab)
      {
        BDrawTab(AWidget, BTabPos, BTabPos + BTextWidth + 8, String_Value(BString), BTabIndex);
      };
      BTabPos = BTabPos + BTextWidth + 8;
    };
    BIteratorTab = BIteratorTab->FNext;
    BTabIndex++;
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
  BTabsetProperties->FScrolling = FALSE;
  BTabsetProperties->FMouseDownAt = 0;
  BTabsetProperties->FTabsetLength = 0;
  
  Widget_AddPointer(AWidget, "tabset", BTabsetProperties);
  Widget_AddSignal(AWidget, "drawtab");
  Widget_AddSignal(AWidget, "tab");
  
  AWidget->FDraw = &GUITabset_Draw;
  AWidget->FMouseDown = &GUITabset_MouseDown;
  AWidget->FMouseMove = &GUITabset_MouseMove;
  AWidget->FMouseUp = &GUITabset_MouseUp;
  AWidget->FScroll = &GUITabset_Scroll;
  AWidget->FResize = &GUITabset_Resize;
};