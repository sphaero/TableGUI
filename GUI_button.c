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
#include "GUI_font.h"
#include "GUI_widget.h"
#include "GUI_theme.h"
#include "GUI_button.h"

void GUIButton_MouseDown(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY)
{
  if (AButton == GLFW_MOUSE_BUTTON_LEFT)
  {
    GUIWidget_MouseDown(AWidget, AButton, AMouseX, AMouseY);
  };
};

void GUIButton_Draw(TGUIWidget *AWidget)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  TGUIButtonProperties *BButtonProperties = (TGUIButtonProperties *)Widget_GetPointer(AWidget, "btn");
  
  if (BWidgetProperties->FEnabled)
  {
    if (BWidgetProperties->FDown)
    {
      glSetColor(BButtonProperties->FColorDown);
    } else
    {
      if (AWidget == AWidget->FWindow->FWidgetMouseOver)
      {
        glSetColor(BButtonProperties->FColorHighlight);
      } else
      {
        glSetColor(BButtonProperties->FColorNormal);
      };
    };
  } else
  {
    glSetColor(BButtonProperties->FColorDisabled);
  };
  glClear(GL_COLOR_BUFFER_BIT);
  glPrint(AWidget->FWindow->FFont, (BWidgetProperties->FWidth / 2) - (glTextWidth(AWidget->FWindow->FFont, BButtonProperties->FText->FPointer) / 2),
                                   (BWidgetProperties->FHeight / 2) + (glTextHeight(AWidget->FWindow->FFont, BButtonProperties->FText->FPointer) / 2),
                                   BButtonProperties->FText->FPointer,
                                   0.0f, 0.0f, 0.0f);
};

void Alloc_GUIButton(TGUIWidget *AWidget)
{
  Alloc_GUIWidget(AWidget);
  TGUIButtonProperties *BButtonProperties = (TGUIButtonProperties *)malloc(sizeof(TGUIButtonProperties));
  
  BButtonProperties->FText = Alloc_String("Button");
  BButtonProperties->FImageTexture = 0;
  
  BButtonProperties->FColorNormal.FRed = 0.5f;
  BButtonProperties->FColorNormal.FGreen = 0.5f;
  BButtonProperties->FColorNormal.FBlue = 0.5f;
  
  BButtonProperties->FColorDown.FRed = 0.1f;
  BButtonProperties->FColorDown.FGreen = 0.35f;
  BButtonProperties->FColorDown.FBlue = 0.1f;
  
  BButtonProperties->FColorFocused.FRed = 0.2f;
  BButtonProperties->FColorFocused.FGreen = 0.6f;
  BButtonProperties->FColorFocused.FBlue = 0.2f;
  
  BButtonProperties->FColorDisabled.FRed = 0.35f;
  BButtonProperties->FColorDisabled.FGreen = 0.35f;
  BButtonProperties->FColorDisabled.FBlue = 0.35f;

  BButtonProperties->FColorHighlight.FRed = 0.35f;
  BButtonProperties->FColorHighlight.FGreen = 0.8f;
  BButtonProperties->FColorHighlight.FBlue = 0.35f;
  
  Widget_AddPointer(AWidget, "btn", BButtonProperties);
  
  AWidget->FDraw = &GUIButton_Draw;
  AWidget->FMouseDown = &GUIButton_MouseDown;
};

