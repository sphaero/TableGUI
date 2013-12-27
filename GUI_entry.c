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
#include "GUI_entry.h"

void GUIEntry_AdjustPosition(TGUIWidget *AWidget, TGUIWidgetProperties *AWidgetProperties, TGUIEntryProperties *AEntryProperties)
{
  int BCaretX = glTextWidthUntil(AWidget->FWindow->FFont, AEntryProperties->FText->FPointer, AEntryProperties->FCaret) - AEntryProperties->FPosition;
  
  if (BCaretX > (AWidgetProperties->FWidth - 10))
  {
    AEntryProperties->FPosition += BCaretX - (AWidgetProperties->FWidth - 10);
  } else
  if (BCaretX < 0)
  {
    AEntryProperties->FPosition += BCaretX;
  };
};

void GUIEntry_KeyDown(TGUIWidget *AWidget, int AKey, int AScancode, int AMods)
{
  GUIWidget_KeyDown(AWidget, AKey, AScancode, AMods);
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  TGUIEntryProperties *BEntryProperties = (TGUIEntryProperties *)Widget_GetPointer(AWidget, "ent");
  bboolean BCapsLock = FALSE;

  if (AKey == GLFW_KEY_LEFT)
  {
    BEntryProperties->FCaret--;
  } else
  if (AKey == GLFW_KEY_RIGHT)
  {
    BEntryProperties->FCaret++;
  } else  
  if ((AKey == GLFW_KEY_BACKSPACE) && (BEntryProperties->FCaret > 0))
  {
    if (String_Remove(BEntryProperties->FText, BEntryProperties->FCaret - 1))
    {
      BEntryProperties->FCaret--;
    };
  } else  
  if ((AKey == GLFW_KEY_DELETE) && (BEntryProperties->FCaret < BEntryProperties->FText->FCount))
  {
    String_Remove(BEntryProperties->FText, BEntryProperties->FCaret);
  } else
  if ((AKey >= GLFW_KEY_SPACE) && (AKey <= GLFW_KEY_GRAVE_ACCENT))
  {
    #ifndef _WIN32
    Display* BDisplay = glfwGetX11Display();
    if (BDisplay)
    {
      unsigned int BState;
      XkbGetIndicatorState(BDisplay, XkbUseCoreKbd, &BState);
      BCapsLock = (BState & 0x01) == 1;
      BCapsLock = !BCapsLock;
    }
    if ( (AKey >= 41) && (AKey <= 90) &&
    (BCapsLock))
    {
      AKey += 32;
    };
    #endif
    String_InsertChar(BEntryProperties->FText, AKey, BEntryProperties->FCaret);
    BEntryProperties->FCaret++;
  };

  if (BEntryProperties->FCaret < 0)
  {
    BEntryProperties->FCaret = 0;
  };
  if (BEntryProperties->FCaret > BEntryProperties->FText->FCount)
  {
    BEntryProperties->FCaret = BEntryProperties->FText->FCount;
  };
  
  GUIEntry_AdjustPosition(AWidget, BWidgetProperties, BEntryProperties);
  
  //if (AWidget->FOnKeyDown)
  {
    //AWidget->FOnKeyDown(AWidget, AKey);
  };
};

void GUIEntry_MouseDown(TGUIWidget *AWidget, int AEntry, int AMouseX, int AMouseY)
{
  if (AEntry == GLFW_MOUSE_BUTTON_LEFT)
  {
    GUIWidget_MouseDown(AWidget, AEntry, AMouseX, AMouseY);
  };
};

void GUIEntry_Draw(TGUIWidget *AWidget)
{
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  TGUIEntryProperties *BEntryProperties = (TGUIEntryProperties *)Widget_GetPointer(AWidget, "ent");
  
  glClearColor(BWidgetProperties->FColor.FRed, BWidgetProperties->FColor.FGreen, BWidgetProperties->FColor.FBlue, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  
  glColor4f(0.1, 0.1, 0.1, 1.0);
  glBegin(GL_LINE_STRIP);
    glVertex3f(BWidgetProperties->FWidth - 1.0, BWidgetProperties->FHeight - 1.0, 0.0);
    glVertex3f(0.0, BWidgetProperties->FHeight - 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(BWidgetProperties->FWidth - 1.0, 0.0, 0.0);
    glVertex3f(BWidgetProperties->FWidth - 1.0, BWidgetProperties->FHeight, 0.0);
  glEnd();
  
  glColor4f(0.15, 0.15, 0.15, 1.0);
  glBegin(GL_LINES);
    glVertex3f(4.0, 4.0, 0.0);
    glVertex3f(4.0, BWidgetProperties->FHeight - 4.0, 0.0);
    glVertex3f(5.0, 4.0, 0.0);
    glVertex3f(5.0, BWidgetProperties->FHeight - 4.0, 0.0);
  glEnd();
  
  glPushAttrib(GL_SCISSOR_TEST);
  glScissor(BWidgetProperties->FDestinationRect.FLeft + 6, AWidget->FWindow->FHeight - BWidgetProperties->FDestinationRect.FTop - (BWidgetProperties->FDestinationRect.FBottom - BWidgetProperties->FDestinationRect.FTop) - 6, BWidgetProperties->FDestinationRect.FRight - BWidgetProperties->FDestinationRect.FLeft - 6 - 4, BWidgetProperties->FDestinationRect.FBottom - BWidgetProperties->FDestinationRect.FTop + 6);
  glPrint(AWidget->FWindow->FFont, 8 - BEntryProperties->FPosition,
                                   (BWidgetProperties->FHeight / 2) + (glTextHeight(AWidget->FWindow->FFont, "Wg") / 2),
                                   BEntryProperties->FText->FPointer,
                                   1.0f, 1.0f, 1.0f);
  glPopAttrib();
  glScissor(BWidgetProperties->FDestinationRect.FLeft, AWidget->FWindow->FHeight - BWidgetProperties->FDestinationRect.FTop - (BWidgetProperties->FDestinationRect.FBottom - BWidgetProperties->FDestinationRect.FTop), BWidgetProperties->FDestinationRect.FRight - BWidgetProperties->FDestinationRect.FLeft, BWidgetProperties->FDestinationRect.FBottom - BWidgetProperties->FDestinationRect.FTop);
  
  if ((AWidget->FWindow->FWidgetFocused == AWidget) && ((int)(glfwGetTime() * 4) % 2))
  {
    int BCaretX = glTextWidthUntil(AWidget->FWindow->FFont, BEntryProperties->FText->FPointer, BEntryProperties->FCaret) - BEntryProperties->FPosition;
    glColor4f(0.5, 0.5, 0.5, 1.0);
    glBegin(GL_LINES);
      glVertex3f(BCaretX + 7.0, 5.0, 0.0);
      glVertex3f(BCaretX + 7.0, BWidgetProperties->FHeight - 5.0, 0.0);
    glEnd();
  };
};

void Alloc_GUIEntry(TGUIWidget *AWidget)
{
  Alloc_GUIWidget(AWidget);
  TGUIEntryProperties *BEntryProperties = (TGUIEntryProperties *)malloc(sizeof(TGUIEntryProperties));
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  
  BWidgetProperties->FColor.FRed = 0.2f;
  BWidgetProperties->FColor.FGreen = 0.2f;
  BWidgetProperties->FColor.FBlue = 0.2f; 
  BEntryProperties->FText = Alloc_String("Entry");
  BEntryProperties->FCaret = 0;
  BEntryProperties->FPosition = 0;
  
  Widget_AddPointer(AWidget, "ent", BEntryProperties);
  
  AWidget->FDraw = &GUIEntry_Draw;
  AWidget->FMouseDown = &GUIEntry_MouseDown;
  AWidget->FKeyDown = &GUIEntry_KeyDown;
};