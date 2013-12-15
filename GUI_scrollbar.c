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
#include "GUI_scrollbar.h"

void GUIScrollbar_MouseMove(TGUIWidget *AWidget, int AMouseX, int AMouseY)
{
  /*int BSlidingAreaSize = 0;
  
  if (Widget_GetBool(AWidget, "down"))
  {
    printf("000.\n");
    BSlidingAreaSize = Widget_GetInt(AWidget, "height");
    
    if (Widget_GetBool(AWidget, "buttonvisible"))
    {
      BSlidingAreaSize = BSlidingAreaSize - (Widget_GetInt(AWidget, "buttonsize") * 2);
    };
    printf("AAA.\n");
    int Top = AMouseY - Widget_GetInt(AWidget, "mousedownat");
    if (Widget_GetBool(AWidget, "buttonvisible"))
    {
      Top = Top - Widget_GetInt(AWidget, "buttonsize");
    };
    printf("BBB.\n");
    Widget_SetInt(AWidget, "position", Top * Widget_GetInt(AWidget, "max") / BSlidingAreaSize);
    
    printf("CCC.\n");
    if (Widget_GetInt(AWidget, "position") < 0)
    {
      Widget_SetInt(AWidget, "position", 0);
    };
    if (Widget_GetInt(AWidget, "position") + Widget_GetInt(AWidget, "page") > Widget_GetInt(AWidget, "max"))
    {
      Widget_SetInt(AWidget, "position", Widget_GetInt(AWidget, "max") - Widget_GetInt(AWidget, "page"));
    };
    
    printf("[MESSAGE] Scrollbar position at (%i).\n", Widget_GetInt(AWidget, "position"));
  };*/
};

void GUIScrollbar_MouseDown(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY)
{
  /*int BSlidingAreaSize = 0;
  int BSliderSize = 0;
  SDL_Rect BRect;
  
  BSlidingAreaSize = Widget_GetInt(AWidget, "height");
  if (Widget_GetBool(AWidget, "buttonvisible"))
  {
    BSlidingAreaSize = BSlidingAreaSize - (Widget_GetInt(AWidget, "buttonsize") * 2);
  };
    
  BSliderSize = BSlidingAreaSize * Widget_GetInt(AWidget, "page") / Widget_GetInt(AWidget, "max");
  if (BSliderSize < 16)
  {
    BSliderSize = 16;
  };
    
  BRect.x = 1;
  BRect.y = Widget_GetInt(AWidget, "position") * BSlidingAreaSize / Widget_GetInt(AWidget, "max");
  if (Widget_GetBool(AWidget, "buttonvisible"))
  {
    BRect.y = BRect.y + Widget_GetInt(AWidget, "buttonsize");
  };
  BRect.w = Widget_GetInt(AWidget, "width") - 2;
  BRect.h = BSliderSize;
  
  if ((AMouseY >= BRect.y) &&
  (AMouseY < BRect.y + BRect.h))
  {
    if (Widget_GetBool(AWidget, "enabled"))
    {
      Widget_SetBool(AWidget, "down", TRUE);
      Widget_SetInt(AWidget, "mousedownat", AMouseY - BRect.y);
      printf("[MESSAGE] Mouse captured at (%i).\n", AMouseY - BRect.y);
    };
  };
  
  // Call ancestor MouseDown:
  GUIWidget_MouseDown(AWidget, AButton, AMouseX, AMouseY);*/
};

void GUIScrollbar_Draw(TGUIWidget *AWidget)
{
  /*SDL_Renderer *BRenderer = AWidget->FWindow->FSDL_Renderer;
  SDL_Rect BRect;
  SDL_Surface *BText = NULL;
  SDL_Texture* BText_Texture = NULL;
  SDL_Color BTextColor;
  BTextColor.r = 0;
  BTextColor.g = 0;
  BTextColor.b = 0;
  BTextColor.a = 255;
  SDL_Color BBgColor;
  BBgColor.r = 0;
  BBgColor.g = 0;
  BBgColor.b = 0;
  BBgColor.a = 0;
  
  int BSlidingAreaSize = 0;
  int BSliderSize = 0;
  
  if (Widget_GetBool(AWidget, "enabled"))
  {
    // BEGIN - Draw the background and the borders.
    SDL_SetRenderDrawColor(BRenderer, COLOR_CONTENT_BACKGROUND_R, COLOR_CONTENT_BACKGROUND_G, COLOR_CONTENT_BACKGROUND_B, 255);
    SDL_RenderClear(BRenderer);
    
    
    BSlidingAreaSize = Widget_GetInt(AWidget, "height");
    if (Widget_GetBool(AWidget, "buttonvisible"))
    {
      BSlidingAreaSize = BSlidingAreaSize - (Widget_GetInt(AWidget, "buttonsize") * 2);
    };
    
    BSliderSize = BSlidingAreaSize * Widget_GetInt(AWidget, "page") / Widget_GetInt(AWidget, "max");
    if (BSliderSize < 16)
    {
      BSliderSize = 16;
    };
    
    BRect.x = 1;
    BRect.y = Widget_GetInt(AWidget, "position") * BSlidingAreaSize / Widget_GetInt(AWidget, "max");
    if (Widget_GetBool(AWidget, "buttonvisible"))
    {
      BRect.y = BRect.y + Widget_GetInt(AWidget, "buttonsize");
    };
    BRect.w = Widget_GetInt(AWidget, "width") - 2;
    BRect.h = BSliderSize;
    
    if (Widget_GetBool(AWidget, "down"))
    {
      SDL_SetRenderDrawColor(BRenderer, COLOR_BACKGROUND_SHADOW_R, COLOR_BACKGROUND_SHADOW_G, COLOR_BACKGROUND_SHADOW_B, 255);
    } else
    {
      if (AWidget->FWindow->FWidgetMouseOver == AWidget)
      {
        SDL_SetRenderDrawColor(BRenderer, COLOR_BACKGROUND_R * 1.1, COLOR_BACKGROUND_G * 1.1, COLOR_BACKGROUND_B * 1.1, 255);
      } else
      {
        SDL_SetRenderDrawColor(BRenderer, COLOR_BACKGROUND_R, COLOR_BACKGROUND_G, COLOR_BACKGROUND_B, 255);
      };
    };
    
    SDL_RenderFillRect(BRenderer, &BRect);
        
    SDL_RenderPresent(BRenderer);
  } else
  {
  
  };*/
};

void Alloc_GUIScrollbar(TGUIWidget *AWidget)
{
  // Call ancestor allocation function:
  Alloc_GUIWidget(AWidget);
  Widget_AddBool(AWidget, "orientation", FALSE); // FALSE = VERTICAL; TRUE = HORIZONTAL;
  
  Widget_AddBool(AWidget, "buttonvisible", TRUE);
  Widget_AddInt(AWidget, "buttonsize", 16);
  Widget_AddInt(AWidget, "position", 0);
  Widget_AddInt(AWidget, "max", 1);
  Widget_AddInt(AWidget, "page", 1);
  Widget_AddInt(AWidget, "mousedownat", 0);
  
  Widget_SetInt(AWidget, "width", 16);
  Widget_SetBool(AWidget, "canfocus", FALSE);
  
  AWidget->FDraw = &GUIScrollbar_Draw;
  AWidget->FMouseDown = &GUIScrollbar_MouseDown;
  AWidget->FMouseMove = &GUIScrollbar_MouseMove;
};

