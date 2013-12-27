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
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include "GUI.h"
#include "GUI_font.h"
#include "GUI_widget.h"
#include "GUI_theme.h"
#include "GUI_Label.h"

void GUILabel_Draw(TGUIWidget *AWidget)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  
  glClearColor(BWidgetProperties->FColor.FRed, BWidgetProperties->FColor.FGreen, BWidgetProperties->FColor.FRed, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  
  glPushAttrib(GL_SCISSOR_BIT);
  glScissor(BWidgetProperties->FGlobalRect.FLeft + 2, BWidgetProperties->FGlobalRect.FTop + 2, BWidgetProperties->FGlobalRect.FRight - BWidgetProperties->FGlobalRect.FLeft - 4, BWidgetProperties->FGlobalRect.FBottom - BWidgetProperties->FGlobalRect.FTop - 4);
  glPrint(AWidget->FWindow->FFont, 2,
                                   (BWidgetProperties->FHeight / 2) + (glTextHeight(AWidget->FWindow->FFont, "Wg") / 2),
                                   BLabelProperties->FText->FPointer);
  glPopAttrib();
};

void Alloc_GUILabel(TGUIWidget *AWidget)
{
  Alloc_GUIWidget(AWidget);
  TGUILabelProperties *BLabelProperties = (TGUILabelProperties *)malloc(sizeof(TGUILabelProperties));
  Widget_AddPointer(AWidget, "label", BLabelProperties);
  
  BLabelProperties->FText = Alloc_String("Label");
  BLabelProperties->FMultipleLines = FALSE;
  BLabelProperties->FWordWrap = FALSE;
  BLabelProperties->FHorizontalAlignment = 0.5;
  BLabelProperties->FVerticalAlignment = 0.5;
  BLabelProperties->FUseMarkup = FALSE;
  BLabelProperties->FCanSelect = FALSE;
  BLabelProperties->FJu = FALSE;
  BLabelProperties->FVerticalAlignment = 0;
  
  AWidget->FDraw = &GUILabel_Draw;
};