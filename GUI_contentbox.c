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
#include "GUI_contentbox.h"

void Draw_ContentHatch(TGUIWidget *AWidget)
{
  /*int BWidth = Widget_GetInt(AWidget, "width");
  int BHeight = Widget_GetInt(AWidget, "height");
  
  int BLine = -(int)(BWidth / 8);
  SDL_SetRenderDrawColor(AWidget->FWindow->FSDL_Renderer, 0, 0, 0, 52);
  
  while ((BLine * 8) < BWidth)
  {
    SDL_RenderDrawLine(AWidget->FWindow->FSDL_Renderer, (BLine * 8), 0, (BLine * 8) + BHeight - 1, BHeight - 1);
    BLine = BLine + 1;
  };
  
  BLine = 0;
  while ((BLine * 8) < (BWidth * 2))
  {
    SDL_RenderDrawLine(AWidget->FWindow->FSDL_Renderer, (BLine * 8), 0, (BLine * 8) - BHeight + 1, BHeight - 1);
    BLine = BLine + 1;
  };*/
  
};

void GUIContentbox_Draw(TGUIWidget *AWidget)
{
  /*SDL_Renderer *BRenderer = AWidget->FWindow->FSDL_Renderer;
  
  SDL_SetRenderDrawColor(BRenderer, COLOR_CONTENT_BACKGROUND_R, COLOR_CONTENT_BACKGROUND_G, COLOR_CONTENT_BACKGROUND_B, 255);
  SDL_RenderClear(BRenderer);
  
  Draw_ContentHatch(AWidget);
  
  SDL_RenderPresent(BRenderer);*/
};

void Alloc_GUIContentbox(TGUIWidget *AWidget)
{
  Alloc_GUIWidget(AWidget);
  AWidget->FDraw = &GUIContentbox_Draw;
  
};

