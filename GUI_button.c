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

void GUIButton_Draw(TGUIWidget *AWidget)
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
  
  if (Widget_GetBool(AWidget, "enabled"))
  {
    // BEGIN - Draw the background and the borders.
    SDL_SetRenderDrawColor(BRenderer, COLOR_CONTAINER_BACKGROUND_R, COLOR_CONTAINER_BACKGROUND_G, COLOR_CONTAINER_BACKGROUND_B, 255);
    SDL_RenderClear(BRenderer);
    
    BRect.x = 1;
    BRect.y = 1;
    BRect.w = Widget_GetInt(AWidget, "width") - 2;
    BRect.h = Widget_GetInt(AWidget, "height") - 2;
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
    
    SDL_SetRenderDrawColor(BRenderer, COLOR_BORDER_R, COLOR_BORDER_R, COLOR_BORDER_B, 255);
    
    BRect.x = 0;
    BRect.y = 0;
    BRect.w = Widget_GetInt(AWidget, "width");
    BRect.h = Widget_GetInt(AWidget, "height");
    
    // Top
    SDL_RenderDrawLine(BRenderer, 1, 0, BRect.w - 1 - 1, 0);
    // Down
    SDL_RenderDrawLine(BRenderer, 1, BRect.h - 1, BRect.w - 1 - 1, BRect.h - 1);
    // Left
    SDL_RenderDrawLine(BRenderer, 0, 1, 0, BRect.h - 1 - 1);
    // Right
    SDL_RenderDrawLine(BRenderer, BRect.w - 1, 1, BRect.w - 1, BRect.h - 1 - 1);
    
    if (AWidget->FWindow->FWidgetFocused == AWidget)
    {
      SDL_SetRenderDrawColor(BRenderer, COLOR_FOCUS_R, COLOR_FOCUS_G, COLOR_FOCUS_B, 255);
      // Top
      SDL_RenderDrawLine(BRenderer, 1, 1, BRect.w - 1 - 1, 1);
      // Down
      SDL_RenderDrawLine(BRenderer, 1, BRect.h - 1 - 1, BRect.w - 1 - 1, BRect.h - 1 - 1);
      // Left
      SDL_RenderDrawLine(BRenderer, 1, 1, 1, BRect.h - 1 - 1);
      // Right
      SDL_RenderDrawLine(BRenderer, BRect.w - 1 - 1, 1, BRect.w - 1 - 1, BRect.h - 1 - 1);
    };
    // END - Draw the background and the borders.
    
    if (AWidget->FWindow->FFont)
    {
      BText = TTF_RenderText_Solid(AWidget->FWindow->FFont, Widget_GetString(AWidget, "text"), BTextColor);
      BText_Texture = SDL_CreateTextureFromSurface(BRenderer, BText);
      SDL_FreeSurface(BText);
      
      SDL_QueryTexture(BText_Texture, NULL, NULL, &BRect.w, &BRect.h);
      BRect.x = (int)((Widget_GetInt(AWidget, "width") / 2) - (BRect.w / 2));
      BRect.y = (int)((Widget_GetInt(AWidget, "height") / 2) - (BRect.h / 2));
      
      SDL_RenderCopy(BRenderer, BText_Texture, NULL, &BRect);
      SDL_DestroyTexture(BText_Texture);
    };
    SDL_RenderPresent(BRenderer);
  } else
  {
  
  };*/
};

void Alloc_GUIButton(TGUIWidget *AWidget)
{
  Alloc_GUIWidget(AWidget);
  Widget_AddString(AWidget, "text", "Button");
  
  AWidget->FDraw = &GUIButton_Draw;  
};

