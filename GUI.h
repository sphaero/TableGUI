/*
  This file is part of TableGUI.
  Copyright (c) 2014 Felipe Ferreira da Silva
  
  TableGUI is licensed under MIT license.
  See the file "LICENSE" for license details.
*/

#ifndef __GUI_H__
#define __GUI_H__
#include <stdio.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <basicutils.h>
#include "GUI_font.h"

typedef struct TGUIWidgetPropertiesStruct TGUIWidgetProperties;
typedef struct TGUIWidgetStruct TGUIWidget;
typedef struct TGUIWindowStruct TGUIWindow;
typedef struct TGUIEventHandlerStruct TGUIEventHandler;
typedef struct TGUIEventButtonStruct TGUIEventButton;
typedef struct TGUIEventMotionStruct TGUIEventMotion;
typedef struct TGUIEventKeyPressStruct TGUIEventKeyPress;
typedef struct TGUIEventKeyReleaseStruct TGUIEventKeyRelease;
typedef void (*TEventHandler_Default)(TGUIWidget *AWidget);
typedef void (*TEventHandler_Draw)(TGUIWidget *AWidget);
typedef void (*TEventHandler_MouseButton)(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY);
typedef void (*TEventHandler_MouseMotion)(TGUIWidget *AWidget, int AMouseX, int AMouseY);
typedef void (*TEventHandler_Key)(TGUIWidget *AWidget, int AKey, int AScanCode, int AAction, int AMods);

#define LEFT 0
#define TOP 0
#define RIGHT 1
#define BOTTOM 1

struct TGUIWidgetPropertiesStruct
{
  int FLeft;
  int FTop;
  unsigned int FWidth;
  unsigned int FHeight;
  
  bboolean FCanFocus;
  bboolean FVisible;
  bboolean FEnabled;
  bboolean FDown;

  bboolean FLeftAlign;
  TGUIWidget *FLeftWidget;
  bboolean FLeftSide;
  int FLeftSpacing;
  
  bboolean FTopAlign;
  TGUIWidget *FTopWidget;
  bboolean FTopSide;
  int FTopSpacing;
  
  bboolean FRightAlign;
  TGUIWidget *FRightWidget;
  bboolean FRightSide;
  int FRightSpacing;
  
  bboolean FBottomAlign;
  TGUIWidget *FBottomWidget;
  bboolean FBottomSide;
  int FBottomSpacing;
};

struct TGUIWidgetStruct
{
  TString *FName;
  TString *FClass;
  TGUIWindow *FWindow;
  
  // BEGIN - OpenGL instances for rendering;
  GLuint FFrameBufferObject;
  GLuint FRenderBuffer_Color;
  GLuint FRenderBuffer_Depth;
  unsigned int FFrameBufferWidth;
  unsigned int FFrameBufferHeight;
  // END - OpenGL instances for rendering;
  
  // BEGIN - Internal widget messages.
  TEventHandler_MouseButton FMouseDown;
  TEventHandler_MouseButton FMouseUp;
  TEventHandler_MouseButton FMouseClick;
  TEventHandler_MouseMotion FMouseMove;
  TEventHandler_Default FMouseEnter;
  TEventHandler_Default FMouseLeave;
  TEventHandler_Key FKey;
  TEventHandler_Default FDraw;
  void *FFree;
  //TGUIWidgetProperties FAlignment;
  // END - Internal widget messages.
  
  TIterator *FListChild;
  TIterator *FListProperty;
  TIterator *FListSignal;
  // Basic signais:
  // * on-mouse-move
  // * on-mouse-down
  // * on-mouse-up
  // * on-mouse-enter
  // * on-mouse-leave
  // * on-key-down
  // * on-key-up
  // * on-draw
  // * on-start-drag
  // * on-drag-drop
  // * on-drag-over
  TGUIWidget *FParent;
};

struct TGUIWindowStruct
{
  int FRunning;
  TGUIFont *FFont;
  GLFWwindow *FGLFW_Window;
    GLuint FRenderBuffer_Color;
    GLuint FFrameBufferObjectReadWrite;
    GLuint FFrameBufferObject;
    unsigned int FFrameBufferWidth;
    unsigned int FFrameBufferHeight;
  
  unsigned int FWidth;
  unsigned int FHeight;
  
  TIterator *FClassesDirectories;
  
  TIterator *FListClientWidget;
  TIterator *FListWidget;
  TGUIWidget *FWidgetFocused;
  TGUIWidget *FDefaultFocusedWidget;
  
  TGUIWidget *FWidgetMouseOver;
  TGUIWidget *FWidgetMouseDown;
  int FMouseX;
  int FMouseY;
  bboolean FMouseDown;
};

int GetWidgetGlobalLeft(TGUIWidget *AWidget);
int GetWidgetGlobalTop(TGUIWidget *AWidget);
int HasChild(TGUIWidget *AWidgetParent, TGUIWidget *AWidgetChild);
int AddChild(TGUIWidget *AWidgetParent, TGUIWidget *AWidgetChild);
TGUIWidget * FindWidget(TGUIWidget *AWidgetParent, const char *AWidgetName);
TGUIWidget * GetWidgetAt(TGUIWidget *AWidget, int AX, int AY);
void RenderWidget(TGUIWindow *AWindow, TGUIWidget *AWidget, TGUIWidgetProperties *AAlignment);
TGUIWidget *GUI_Alloc_Widget(TGUIWindow *AWindow, char *AWidgetClass, const char *AWidgetName);

void RenderWindow(TGUIWindow *AWindow);
void RunWindow(TGUIWindow *AWindow);
TGUIWidget * Window_GetWidget(TGUIWindow *AWindow, char *AWidgetName);
TGUIWindow *GUI_Create_Window(const char *ATitle, int APosX, int APosY, int AWidth, int AHeight, bboolean AFullScreen);

void Widget_AddInt(TGUIWidget *AWidget, char *APropertyName, const int AValue);
void Widget_AddChar(TGUIWidget *AWidget, char *APropertyName, const char AValue);
void Widget_AddString(TGUIWidget *AWidget, char *APropertyName, char *AValue);
void Widget_AddDouble(TGUIWidget *AWidget, char *APropertyName, const double AValue);
void Widget_AddFloat(TGUIWidget *AWidget, char *APropertyName, const float AValue);

void Widget_SetInt(TGUIWidget *AWidget, char *APropertyName, const int AValue);
void Widget_SetString(TGUIWidget *AWidget, char *APropertyName, char *AValue);
void Widget_SetChar(TGUIWidget *AWidget, char *APropertyName, const char AValue);
void Widget_SetDouble(TGUIWidget *AWidget, char *APropertyName, const double AValue);
void Widget_SetFloat(TGUIWidget *AWidget, char *APropertyName, const float AValue);

int Widget_GetInt(TGUIWidget *AWidget, char *APropertyName);
char * Widget_GetString(TGUIWidget *AWidget, char *APropertyName);
char Widget_GetChar(TGUIWidget *AWidget, char *APropertyName);
double Widget_GetDouble(TGUIWidget *AWidget, char *APropertyName);
float Widget_GetFloat(TGUIWidget *AWidget, char *APropertyName);

#endif /* __MAIN_GUI_H__ */