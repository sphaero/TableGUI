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

void GUITabset_AddTab(TGUIWidget *AWidget, const char *ALabel)
{
  TIterator *BListTab = (TIterator *)Widget_GetPointer(AWidget, "listtab");
  if (BListTab)
  {
    Iterator_AddPointer(BListTab, Alloc_String(ALabel));
  };
};

int GUITabset_GetTabAt(TGUIWidget *AWidget, int AMouseX, int AMouseY)
{
  /*TIterator *BListTab = (TIterator *)Widget_GetPointer(AWidget, "listtab");
  TIterator *BIteratorTab = BListTab->FFirstChild;
  int BTabIndex = 0;
  int BTabPos = 0;
  int BTextWidth = 0;
  int BTextHeight = 0;
  int BPosition = Widget_GetInt(AWidget, "position");
  while (BIteratorTab)
  {
    TString *BString = (TString *)BIteratorTab->FPointer;
    
    if (BString)
    {
      TTF_SizeText(AWidget->FWindow->FFont, BString->FPointer, &BTextWidth, &BTextHeight);
      
      BTabPos = BTabPos + BPosition;
      
      if ((AMouseX >= BTabPos) &&
      (AMouseX < (BTabPos + BTextWidth + 8)))
      {
        break;
      };
      BTabPos = BTabPos + BTextWidth + 8;
    };
    BIteratorTab = BIteratorTab->FNext;
    BTabIndex = BTabIndex + 1;
  };
  
  return BTabIndex;*/
};

void GUITabset_MouseDown(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY)
{
  //if (AButton == )
  /*Widget_SetInt(AWidget, "activetab", GUITabset_GetTabAt(AWidget, AMouseX, AMouseY));
  
  int BSlidingAreaSize = 0;
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

void GUITabset_DeleteTab(TGUIWidget *AWidget, int AIndex)
{
  TIterator *BListTab = (TIterator *)Widget_GetPointer(AWidget, "listtab");
  if (BListTab)
  {
    Iterator_Remove(BListTab, Iterator_GetFromIndex(BListTab, AIndex));
  };
};

void GUITabset_Draw(TGUIWidget *AWidget)
{
  /*SDL_Renderer *BRenderer = AWidget->FWindow->FSDL_Renderer;
  TIterator *BListTab = (TIterator *)Widget_GetPointer(AWidget, "listtab");
  TIterator *BIteratorTab = NULL;
  SDL_Rect BRect;
  SDL_Surface *BText = NULL;
  SDL_Texture* BText_Texture = NULL;
  SDL_Color BTextColor;
  int BTabPos = 0;
  int BTabIndex = 0;
  int BPosition = Widget_GetInt(AWidget, "position");
  BTextColor.r = 0;
  BTextColor.g = 0;
  BTextColor.b = 0;
  BTextColor.a = 255;
  SDL_Color BBgColor;
  BBgColor.r = 0;
  BBgColor.g = 0;
  BBgColor.b = 0;
  BBgColor.a = 0;
  
  // BEGIN - Draw the background and the borders.
  SDL_SetRenderDrawColor(BRenderer, COLOR_CONTAINER_BACKGROUND_R, COLOR_CONTAINER_BACKGROUND_G, COLOR_CONTAINER_BACKGROUND_B, 255);
  SDL_RenderClear(BRenderer);
  
  BRect.x = 0;
  BRect.y = 0;
  BRect.w = Widget_GetInt(AWidget, "width");
  BRect.h = Widget_GetInt(AWidget, "height");
  
  
  if (AWidget->FWindow->FFont)
  {
    BIteratorTab = BListTab->FFirstChild;
    BTabIndex = 0;
    while (BIteratorTab)
    {
      TString *BString = (TString *)BIteratorTab->FPointer;
      
      if (BString)
      {
        BText = TTF_RenderText_Solid(AWidget->FWindow->FFont, BString->FPointer, BTextColor);
        BText_Texture = SDL_CreateTextureFromSurface(BRenderer, BText);
        SDL_FreeSurface(BText);
        
        SDL_QueryTexture(BText_Texture, NULL, NULL, &BRect.w, &BRect.h);
        BRect.x = BTabPos + 4 + BPosition;
        BRect.y = (int)((Widget_GetInt(AWidget, "height") / 2) - (BRect.h / 2));
        
        if (Widget_GetInt(AWidget, "activetab") == BTabIndex)
        {
          SDL_Rect BRectBG;
          BRectBG.x = BRect.x - 4;
          BRectBG.y = 0;
          BRectBG.w = BRect.w + 8;
          BRectBG.h = Widget_GetInt(AWidget, "height");
          
          SDL_SetRenderDrawColor(BRenderer, COLOR_BACKGROUND_SHADOW_R, COLOR_BACKGROUND_SHADOW_G, COLOR_BACKGROUND_SHADOW_B, 255);
          SDL_RenderFillRect(BRenderer, &BRectBG);
          

          SDL_SetRenderDrawColor(BRenderer, COLOR_BACKGROUND_SHADOW_R * 0.4, COLOR_BACKGROUND_SHADOW_G * 0.4, COLOR_BACKGROUND_SHADOW_B * 0.4, 255);
          // Left
          SDL_RenderDrawLine(BRenderer, BRectBG.x, 0, BRectBG.x, BRectBG.h);
          // Right
          SDL_RenderDrawLine(BRenderer, BRectBG.x + BRectBG.w - 1, 0, BRectBG.x + BRectBG.w - 1, BRectBG.h);


          SDL_SetRenderDrawColor(BRenderer, COLOR_BACKGROUND_SHADOW_R * 2, COLOR_BACKGROUND_SHADOW_G * 2, COLOR_BACKGROUND_SHADOW_B * 2, 255);
          // Left
          SDL_RenderDrawLine(BRenderer, BRectBG.x - 1, 0, BRectBG.x - 1, BRectBG.h);
          // Right
          SDL_RenderDrawLine(BRenderer, BRectBG.x + BRectBG.w, 0, BRectBG.x + BRectBG.w, BRectBG.h);
    
        };
        
        SDL_RenderCopy(BRenderer, BText_Texture, NULL, &BRect);
        
        BTabPos = BTabPos + BRect.w + 8;
        SDL_DestroyTexture(BText_Texture);
      };
      BIteratorTab = BIteratorTab->FNext;
      BTabIndex = BTabIndex + 1;
    };
  };
  SDL_RenderPresent(BRenderer);
  */
};

void Alloc_GUITabset(TGUIWidget *AWidget)
{
  Alloc_GUIWidget(AWidget);
  TIterator *BListTab = AllocIterator(NULL);
  
  Widget_AddPointer(AWidget, "listtab", BListTab);
  Widget_AddInt(AWidget, "activetab", 0);
  Widget_AddInt(AWidget, "position", 0);
  Widget_AddInt(AWidget, "length", 0);
  
  Widget_SetInt(AWidget, "height", 32);
  Widget_SetInt(AWidget, "width", 124);
  
  AWidget->FDraw = &GUITabset_Draw;  
  AWidget->FMouseDown = &GUITabset_MouseDown;  
};

