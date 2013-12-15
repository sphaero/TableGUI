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
#include "GUI_button.h"

void GUIButton_KeyDown(TGUIWidget *AWidget, int AKey)
{
  if (AWidget->FOnKeyDown)
  {
    //AWidget->FOnKeyDown(AWidget, AKey);
  };
};

void GUIButton_KeyUp(TGUIWidget *AWidget, int AKey)
{
  if (AWidget->FOnKeyUp)
  {
    //AWidget->FOnKeyUp(AWidget, AKey);
  };
};

void GUIButton_MouseDown(TGUIWidget *AWidget, int AKey, int AMouseX, int AMouseY)
{
  AWidget->FWindow->FWidgetFocused = AWidget;
  if (AWidget->FOnMouseDown)
  {
    //AWidget->FOnMouseDown(AWidget, AMouseX, AMouseY);
  };
  
  if (Widget_GetBool(AWidget, "enabled"))
  {
    Widget_SetInt(AWidget, "down", TRUE);
  };
};

void GUIButton_MouseUp(TGUIWidget *AWidget, int AKey, int AMouseX, int AMouseY)
{
  if (AWidget->FOnMouseUp)
  {
    //AWidget->FOnMouseUp(AWidget, AMouseX, AMouseY);
  };
  
  if (Widget_GetBool(AWidget, "down"))
  {
    Widget_SetBool(AWidget, "down", FALSE);
    
    if (AWidget->FOnMouseClick)
    {
      //AWidget->FOnMouseClick(AWidget);
    };
  };
};

void GUIButton_MouseEnter(TGUIWidget *AWidget)
{
};

void GUIButton_MouseLeave(TGUIWidget *AWidget)
{
  Widget_SetBool(AWidget, "down", FALSE);
};

void GUIButton_Resize(TGUIWidget *AWidget)
{
  TGUIWidget *BWidget = NULL;
  TElement *BIteratorWidget = NULL;
  
  while (BIteratorWidget)
  {
    BWidget = (TGUIWidget *)BIteratorWidget->FPointer;
    
    if (Widget_GetBool(AWidget, "orientation"))
    {
      Widget_SetInt(BWidget, "left", 0);
      
    };
    BIteratorWidget = BIteratorWidget->FNext;
  };
};

void GUIButton_Draw(TGUIWidget *AWidget)
{
  SDL_Renderer *BRenderer = AWidget->FWindow->FSDL_Renderer;
  
  SDL_SetRenderDrawColor(BRenderer, COLOR_CONTAINER_BACKGROUND_R, COLOR_CONTAINER_BACKGROUND_G, COLOR_CONTAINER_BACKGROUND_B, 255);
  SDL_RenderClear(BRenderer);
  
  SDL_RenderPresent(BRenderer);
};

void Alloc_GUIButton(TGUIWidget *AWidget)
{
  printf("[MESSAGE] Widget as \"box\".\n");
  Widget_AddInt(AWidget, "slots", 1);
  Widget_AddBool(AWidget, "orientation", FALSE);
  
  AWidget->FDraw = &GUIButton_Draw;
  AWidget->FMouseDown = &GUIButton_MouseDown;
  AWidget->FMouseUp = &GUIButton_MouseUp;
  AWidget->FMouseEnter = &GUIButton_MouseEnter;
  AWidget->FMouseLeave = &GUIButton_MouseLeave;
  printf("[MESSAGE] Widget as \"box\". Done.\n");
  
};

