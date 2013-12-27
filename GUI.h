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
#include "GUI_draw.h"
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
typedef void (*TEventHandler_Referent)(TGUIWidget *AWidget, TGUIWidget *AWidgetReference);
typedef void (*TEventHandler_MouseButton)(TGUIWidget *AWidget, int AButton, int AMouseX, int AMouseY);
typedef void (*TEventHandler_Scroll)(TGUIWidget *AWidget, double AXOffset, double AYOffset);
typedef void (*TEventHandler_MouseMotion)(TGUIWidget *AWidget, int AMouseX, int AMouseY);
typedef void (*TEventHandler_Resize)(TGUIWidget *AWidget, int AMouseX, int AMouseY);
typedef void (*TEventHandler_Key)(TGUIWidget *AWidget, int AKey, int AScanCode, int AMods);
typedef void (*TEventHandler_Timer)(TGUIWidget *AWidget, const int AID, int AInterval);
typedef struct TGUITimerItemStruct TGUITimerItem;

#define LEFT 0
#define TOP 0
#define RIGHT 1
#define BOTTOM 1

struct TGUITimerItemStruct
{
  TEventHandler_Timer FCallbackFunction;
  int FID;
  int FInterval;
  bboolean FDestroy;
};

struct TGUIWidgetPropertiesStruct
{
  int FLeft;
  int FTop;
  int FWidth;
  int FHeight;
  TRect FGlobalRect;
  TRect FDestinationRect;
  
  TColorFloat FColor;
  
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
  //GLuint FFrameBufferObject;
  //GLuint FRenderBuffer_Color;
  //GLuint FRenderBuffer_Depth;
  //unsigned int FFrameBufferWidth;
  //unsigned int FFrameBufferHeight;
  // END - OpenGL instances for rendering;
  
  // BEGIN - Internal widget messages.
  TEventHandler_MouseButton FMouseDown;
  TEventHandler_MouseButton FMouseUp;
  TEventHandler_Default FMouseClick;
  TEventHandler_Scroll FScroll;
  TEventHandler_MouseMotion FMouseMove;
  TEventHandler_Default FMouseEnter;
  TEventHandler_Default FMouseLeave;
  TEventHandler_Resize FResize;
  TEventHandler_Referent FWidget_AddChild;
  TEventHandler_Key FKeyDown;
  TEventHandler_Key FKeyUp;
  TEventHandler_Default FDraw;
  TEventHandler_Default FFree;
  //TGUIWidgetProperties FAlignment;
  // END - Internal widget messages.
  
  TIterator *FListTimer;
  TIterator *FListChild;
  TIterator *FListProperty;
  TIterator *FListAbstractProperty; // This is for script language better access.
  TIterator *FListSignal;

  TGUIWidget *FParent;
};

struct TGUIWindowStruct
{
  char *FTitle;
  int FRunning;
  TGUIFont *FFont;
  GLFWwindow *FGLFW_Window;
  const GLFWvidmode *FVideoMode;
  //  GLuint FRenderBuffer_Color;
  //  GLuint FFrameBufferObjectReadWrite;
  //  GLuint FFrameBufferObject;
  //  unsigned int FFrameBufferWidth;
  //  unsigned int FFrameBufferHeight;
  
  unsigned int FWidth;
  unsigned int FHeight;
  int FPosX;
  int FPosY;
  
  TIterator *FClassesDirectories;
  
  TIterator *FListClientWidget;
  TIterator *FListWidget;
  TGUIWidget *FWidgetFocused;
  TGUIWidget *FDefaultFocusedWidget;
  
  TGUIWidget *FWidgetMouseOver;
  TGUIWidget *FWidgetMouseDown;
  int FMouseX;
  int FMouseY;
  int FRenderingFrameRate;
  bboolean FResolvingAlignment;
  bboolean FMouseDown;
};

int GetWidgetGlobalLeft(TGUIWidget *AWidget);
int GetWidgetGlobalTop(TGUIWidget *AWidget);
bboolean Widget_HasChild(TGUIWidget *AWidgetParent, TGUIWidget *AWidgetChild);
void Widget_AddChild(TGUIWidget *AWidgetParent, TGUIWidget *AWidgetChild);
TGUIWidget * FindWidget(TGUIWidget *AWidgetParent, const char *AWidgetName);
TGUIWidget * GetWidgetAt(TGUIWidget *AWidget, int AX, int AY);
void RenderWidget(TGUIWindow *AWindow, TGUIWidget *AWidget, TGUIWidgetProperties *AParentProperties, TGUIWidgetProperties *AWidgetProperties);
TGUIWidget *GUI_Alloc_Widget(TGUIWindow *AWindow, unsigned char *AWidgetClass, const char *AWidgetName);

void RenderWindow(TGUIWindow *AWindow);
void RunWindow(TGUIWindow *AWindow);
void Window_SetFullscreen(TGUIWindow *AWindow, bboolean AFullScreen);
TGUIWidget * Window_GetWidget(TGUIWindow *AWindow, unsigned char *AWidgetName);
GLFWwindow *GUI_Create_GLFWWindow(const char *ATitle, int APosX, int APosY, int AWidth, int AHeight, bboolean AFullScreen);
 TGUIWindow *GUI_Create_Window(const unsigned char *ATitle, int APosX, int APosY, int AWidth, int AHeight, bboolean AFullScreen);

void Widget_AddSignal(TGUIWidget *AWidget, unsigned char *ASignalName);
void * Widget_GetSignal(TGUIWidget *AWidget, unsigned char *ASignalName);
void Widget_SetSignal(TGUIWidget *AWidget, unsigned char *ASignalName, void *AFunctionReference);

void Widget_AddInt(TGUIWidget *AWidget, unsigned char *APropertyName, const int AValue);
void Widget_AddChar(TGUIWidget *AWidget, unsigned char *APropertyName, const char AValue);
void Widget_AddString(TGUIWidget *AWidget, unsigned char *APropertyName, unsigned char *AValue);
void Widget_AddDouble(TGUIWidget *AWidget, unsigned char *APropertyName, const double AValue);
void Widget_AddFloat(TGUIWidget *AWidget, unsigned char *APropertyName, const float AValue);

void Widget_SetInt(TGUIWidget *AWidget, unsigned char *APropertyName, const int AValue);
void Widget_SetString(TGUIWidget *AWidget, unsigned char *APropertyName, unsigned char *AValue);
void Widget_SetChar(TGUIWidget *AWidget, unsigned char *APropertyName, const char AValue);
void Widget_SetDouble(TGUIWidget *AWidget, unsigned char *APropertyName, const double AValue);
void Widget_SetFloat(TGUIWidget *AWidget, unsigned char *APropertyName, const float AValue);

int Widget_GetInt(TGUIWidget *AWidget, unsigned char *APropertyName);
char * Widget_GetString(TGUIWidget *AWidget, unsigned char *APropertyName);
char Widget_GetChar(TGUIWidget *AWidget, unsigned char *APropertyName);
double Widget_GetDouble(TGUIWidget *AWidget, unsigned char *APropertyName);
float Widget_GetFloat(TGUIWidget *AWidget, unsigned char *APropertyName);

#endif /* __MAIN_GUI_H__ */