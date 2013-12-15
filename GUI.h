/*
  This file is part of TableGUI.
  Copyright (c) 2014 Felipe Ferreira da Silva
  
  TableGUI is licensed under MIT license.
  See the file "LICENSE" for license details.
*/

#ifndef __GUI_H__
#define __GUI_H__
#include <GL/gl.h>
#include <GLFW/glfw3.h>

//#include <libxml2/tree.h>
//#include <libxml2/xmlreader.h>
//#include <libxml2/xmlwriter.h>
#include <basicutils.h>


typedef struct TGUIAttachmentStruct TGUIAttachment;
typedef struct TGUIAlignmentStruct TGUIAlignment;
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


typedef void (*EventOnDraw)(TGUIWidget *AWidget);

#define LEFT 0
#define TOP 0
#define RIGHT 1
#define BOTTOM 1

struct TGUIAttachmentStruct
{
  TGUIWidget *FAttatchToWidget;
  bboolean FAttatchToSide;
  // FALSE = Left/Top;
  // TRUE = Right/Bottom;
  int FSpacing;
  bboolean FEnabled;
};

struct TGUIAlignmentStruct
{
  TGUIAttachment FTop;
  TGUIAttachment FLeft;
  TGUIAttachment FRight;
  TGUIAttachment FBottom;
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
  int FFrameBufferWidth;
  int FFrameBufferHeight;
  // END - OpenGL instances for rendering;
  
  // BEGIN - Internal widget messages.
  TEventHandler_MouseButton FMouseDown;
  TEventHandler_MouseButton FMouseUp;
  TEventHandler_MouseButton FMouseClick;
  TEventHandler_MouseMotion FMouseMove;
  TEventHandler_Default FMouseEnter;
  TEventHandler_Default FMouseLeave;
  void *FKeyDown;
  void *FKeyUp;
  TEventHandler_Default FDraw;
  void *FFree;
  TGUIAlignment FAlignment;
  // END - Internal widget messages.
  
  void *FOnMouseDown;
  void *FOnMouseUp;
  void *FOnMouseClick;
  void *FOnMouseMove;
  void *FOnMouseEnter;
  void *FOnMouseLeave;
  void *FOnKeyDown;
  void *FOnKeyUp;
  
  
  TIterator *FListChild;
  TIterator *FListProperty;
  TIterator *FListEvent;
  TGUIWidget *FParent;
};

struct TGUIWindowStruct
{
  int FRunning;
  //TTF_Font *FFont;
  GLFWwindow *FGLFW_Window;
    GLuint FFrameBufferObject;
    GLuint FRenderBuffer_Color;
    GLuint FRenderBuffer_Depth;
    int FFrameBufferWidth;
    int FFrameBufferHeight;
  
  TIterator *FClassesDirectories;
  
  TIterator *FListClientWidget;
  TGUIWidget *FWidgetFocused;
  TGUIWidget *FDefaultFocusedWidget;
  
  TGUIWidget *FWidgetMouseOver;
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
void RenderWidget(TGUIWindow *AWindow, TGUIWidget *AWidget);
TGUIWidget *GUI_Alloc_Widget(TGUIWindow *AWindow, char *AWidgetClass, const char *AWidgetName);

void RenderWindow(TGUIWindow *AWindow);
void RunWindow(TGUIWindow *AWindow);

TGUIWindow *GUI_Create_Window(const char *ATitle, int APosX, int APosY, int AWidth, int AHeight, int AFlags);

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

#endif /* __MAIN_FRAMEEDITORSPRITE_H__ */
