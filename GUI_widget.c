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
#include "GUI_theme.h"
#include "GUI_checkbox.h"

void GUIWidget_KeyDown(TGUIWidget *AWidget, int AKey, int AScancode, int AMods)
{
  //if (AWidget->FOnKeyDown)
  {
    //AWidget->FOnKeyDown(AWidget, AKey);
  };
};

void GUIWidget_KeyUp(TGUIWidget *AWidget, int AKey, int AScancode, int AMods)
{
  //if (AWidget->FOnKeyUp)
  {
    //AWidget->FOnKeyUp(AWidget, AKey);
  };
};

void GUIWidget_MouseDown(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  TEventHandler_MouseButton BMouseDown = (TEventHandler_MouseButton)Widget_GetSignal(AWidget, "mousedown");
  
  if (BMouseDown)
  {
    BMouseDown(AWidget, AButton, AMouseX, AMouseY);
  };

  if (BWidgetProperties->FCanFocus)
  {
    AWidget->FWindow->FWidgetFocused = AWidget;
  };
  //if (AWidget->FOnMouseDown)
  {
    //AWidget->FOnMouseDown(AWidget, AMouseX, AMouseY);
  };
  
  BWidgetProperties->FDown = TRUE;
};

void GUIWidget_MouseUp(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  TEventHandler_MouseButton BMouseUp = (TEventHandler_MouseButton *)Widget_GetSignal(AWidget, "mouseup");
  
  if (BMouseUp)
  {
    BMouseUp(AWidget, AButton, AMouseX, AMouseY);
  };
  
  if (BWidgetProperties->FDown)
  {
    if (AWidget->FMouseClick)
    {
      AWidget->FMouseClick(AWidget);
    };
  };
  
  BWidgetProperties->FDown = FALSE;
};

void GUIWidget_MouseClick(TGUIWidget *AWidget)
{
  TEventHandler_Default BMouseClick = (TEventHandler_Default)Widget_GetSignal(AWidget, "click");
  if (BMouseClick)
  {
    BMouseClick(AWidget);
  };
};

void GUIWidget_MouseEnter(TGUIWidget *AWidget)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  
  if ((AWidget == AWidget->FWindow->FWidgetFocused) &&
  (AWidget == AWidget->FWindow->FWidgetMouseDown))
  {
    if (BWidgetProperties)
    {
      BWidgetProperties->FDown = TRUE;
    };
  };
};

void GUIWidget_MouseLeave(TGUIWidget *AWidget)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  BWidgetProperties->FDown = FALSE;
};

void GUIWidget_Resize(TGUIWidget *AWidget, int AWidth, int AHeight)
{
  Widget_Invalidate(AWidget);
};

void GUIWidget_Free(TGUIWidget *AWidget)
{
  TIterator *BIteratorChild = AWidget->FListChild->FFirstChild;
  TGUIWidget *BChild;
  while (BIteratorChild)
  {
    BChild = (TGUIWidget *)BIteratorChild->FPointer;
    if (BChild)
    {
      if (BChild->FFree)
      {
        BChild->FFree(BChild);
      }
    };
  };
};

void Alloc_GUIWidget(TGUIWidget *AWidget)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  BWidgetProperties->FWidth = 96;
  BWidgetProperties->FHeight = 24;
  BWidgetProperties->FColor.FRed = 0.25;
  BWidgetProperties->FColor.FGreen = 0.25f;
  BWidgetProperties->FColor.FBlue = 0.25f;
  AWidget->FDraw = NULL;
  AWidget->FMouseDown = &GUIWidget_MouseDown;
  AWidget->FMouseUp = &GUIWidget_MouseUp;
  AWidget->FMouseMove = NULL;
  AWidget->FMouseEnter = &GUIWidget_MouseEnter;
  AWidget->FMouseLeave = &GUIWidget_MouseLeave;
  AWidget->FMouseClick = &GUIWidget_MouseClick;
  AWidget->FKeyDown = &GUIWidget_KeyDown;
  AWidget->FKeyUp = &GUIWidget_KeyUp;
  AWidget->FResize = &GUIWidget_Resize;
  
  Widget_AddSignal(AWidget, "draw");
  Widget_AddSignal(AWidget, "click");
  Widget_AddSignal(AWidget, "dblclick");
  Widget_AddSignal(AWidget, "mousedown");
  Widget_AddSignal(AWidget, "mouseup");
  Widget_AddSignal(AWidget, "mousemove");
  Widget_AddSignal(AWidget, "mouseenter");
  Widget_AddSignal(AWidget, "mouseleave");
  Widget_AddSignal(AWidget, "keydown");
  Widget_AddSignal(AWidget, "keyup");
  Widget_AddSignal(AWidget, "resize");
  Widget_AddSignal(AWidget, "startdrag");
  Widget_AddSignal(AWidget, "enddrag");
  Widget_AddSignal(AWidget, "dragover");
  Widget_AddSignal(AWidget, "dragdrop");
  Widget_AddSignal(AWidget, "enter");
  Widget_AddSignal(AWidget, "exit");
  String_Assign(AWidget->FClass, "widget");
};