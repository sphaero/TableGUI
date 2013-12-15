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


//Screen dimension constants

void Widget_AddBool(TGUIWidget *AWidget, char *APropertyName, const bboolean AValue)
{
  Add_Bool(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_AddInt(TGUIWidget *AWidget, char *APropertyName, const int AValue)
{
  Add_Integer(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_AddString(TGUIWidget *AWidget, char *APropertyName, char *AValue)
{
  Add_String(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_AddChar(TGUIWidget *AWidget, char *APropertyName, const char AValue)
{
  Add_Char(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_AddDouble(TGUIWidget *AWidget, char *APropertyName, const double AValue)
{
  Add_Double(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_AddFloat(TGUIWidget *AWidget, char *APropertyName, const float AValue)
{
  Add_Float(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_AddPointer(TGUIWidget *AWidget, char *APropertyName, void *AValue)
{
  Add_Pointer(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_SetBool(TGUIWidget *AWidget, char *APropertyName, const bboolean AValue)
{
  Set_Bool(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_SetInt(TGUIWidget *AWidget, char *APropertyName, const int AValue)
{
  Set_Integer(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_SetString(TGUIWidget *AWidget, char *APropertyName, char *AValue)
{
  Set_String(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_SetChar(TGUIWidget *AWidget, char *APropertyName, const char AValue)
{
  Set_Char(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_SetDouble(TGUIWidget *AWidget, char *APropertyName, const double AValue)
{
  Set_Double(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_SetFloat(TGUIWidget *AWidget, char *APropertyName, const float AValue)
{
  Set_Float(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_SetPointer(TGUIWidget *AWidget, char *APropertyName, void *AValue)
{
  Set_Pointer(AWidget->FListProperty, APropertyName, AValue);
};

bboolean Widget_GetBool(TGUIWidget *AWidget, char *APropertyName)
{
  return Get_Bool(AWidget->FListProperty, APropertyName);
};

int Widget_GetInt(TGUIWidget *AWidget, char *APropertyName)
{
  return Get_Integer(AWidget->FListProperty, APropertyName);
};

char * Widget_GetString(TGUIWidget *AWidget, char *APropertyName)
{
  return Get_String(AWidget->FListProperty, APropertyName);
};

char Widget_GetChar(TGUIWidget *AWidget, char *APropertyName)
{
  return Get_Char(AWidget->FListProperty, APropertyName);
};

double Widget_GetDouble(TGUIWidget *AWidget, char *APropertyName)
{
  return Get_Double(AWidget->FListProperty, APropertyName);
};

float Widget_GetFloat(TGUIWidget *AWidget, char *APropertyName)
{
  return Get_Float(AWidget->FListProperty, APropertyName);
};

void *Widget_GetPointer(TGUIWidget *AWidget, char *APropertyName)
{
  return Get_Pointer(AWidget->FListProperty, APropertyName);
};

int Initialize()
{
  if (glfwInit())
  {
    printf("[MESSAGE] GLFW initialized.\n");
  } else
  {
    printf("[ERROR] Fail to initialize GLFW.");
    exit(EXIT_FAILURE);
  };
  
  return TRUE;
};

int HasChild(TGUIWidget *AWidgetParent, TGUIWidget *AWidgetChild)
{
  TIterator *BIteratorWidget = AWidgetParent->FListChild->FFirstChild;
  int BResult = 0;
  
  while (BIteratorWidget)
  {
    if (AWidgetChild == BIteratorWidget->FPointer)
    {
      BResult = 1;
      break;
    };
    BIteratorWidget = BIteratorWidget->FNext;
  };
  
  return BResult;
};

int AddChild(TGUIWidget *AWidgetParent, TGUIWidget *AWidgetChild)
{
  Iterator_AddPointer(AWidgetParent->FListChild, AWidgetChild);
  AWidgetChild->FParent = AWidgetParent;
};

TGUIWidget * FindWidget(TGUIWidget *AWidgetParent, const char *AWidgetName)
{
  TIterator *BIteratorWidget = AWidgetParent->FListChild->FFirstChild;
  TGUIWidget *BWidget = NULL;
  TGUIWidget *BResultWidget = NULL;
  
  while ((BIteratorWidget) &&
  (BResultWidget == NULL))
  {
    BWidget = (TGUIWidget *)BIteratorWidget->FPointer;
    
    if (strcmp(AWidgetName, BWidget->FName->FPointer))
    {
      BResultWidget = BWidget;
      break;
    };
    
    BResultWidget = FindWidget(BWidget, AWidgetName);
    
    BIteratorWidget = BIteratorWidget->FNext;
  };
  
  return BResultWidget;
};

void Alloc_Frame(TGUIWidget *AWidget)
{

};

void Alloc_ComboBox(TGUIWidget *AWidget)
{

};

void Alloc_Entry(TGUIWidget *AWidget)
{

};

void Alloc_ToolBar(TGUIWidget *AWidget)
{

};

void Alloc_ScrollBar(TGUIWidget *AWidget)
{

};

void Alloc_Button(TGUIWidget *AWidget)
{

};

void Alloc_Paned(TGUIWidget *AWidget)
{

};

void Alloc_Box(TGUIWidget *AWidget)
{

};

void Alloc_Container(TGUIWidget *AWidget)
{
  
};

void Alloc_Widget(TGUIWidget *AWidget)
{
  
};

int HasClassDirectory(TGUIWindow *AWindow, const char *ADirectory)
{

};

void AddClassDirectory(TGUIWindow *AWindow, const char *ADirectory)
{
  char *BDirectory = NULL;
  
  if (!HasClassDirectory(AWindow, ADirectory))
  {
    BDirectory = (char *)malloc(strlen(ADirectory) + sizeof(char));
    memset(BDirectory, "\0", strlen(ADirectory) + sizeof(char));
    memcpy(BDirectory, ADirectory, strlen(ADirectory));
    
    Iterator_AddPointer(AWindow->FClassesDirectories, ADirectory);
  };
};

int GetWidgetGlobalLeft(TGUIWidget *AWidget)
{
  TGUIWidget *BWidget = NULL;
  int BResult = 0;
  
  BResult = Widget_GetInt(AWidget, "left");
  
  if (AWidget->FParent)
  {
    BResult = BResult + GetWidgetGlobalLeft(AWidget->FParent);
  };
  return BResult;
};

int GetWidgetGlobalTop(TGUIWidget *AWidget)
{
  TGUIWidget *BWidget = NULL;
  int BResult = 0;
  
  BResult = Widget_GetInt(AWidget, "top");
  
  if (AWidget->FParent)
  {
    BResult = BResult + GetWidgetGlobalTop(AWidget->FParent);
  };
  return BResult;
};

TGUIWidget * GetWidgetAt(TGUIWidget *AWidget, int AX, int AY)
{
  TGUIWidget *BResultWidget = NULL;
  TGUIWidget *BResultWidgetChild = NULL;
  TGUIWidget *BWidget = NULL;
  TIterator *BIteratorWidget = NULL;
  
  int BWidgetLeft = GetWidgetGlobalLeft(AWidget);
  int BWidgetTop = GetWidgetGlobalTop(AWidget);
  int BWidgetWidth = Widget_GetInt(AWidget, "width");
  int BWidgetHeight = Widget_GetInt(AWidget, "height");
  
  if ((AX > BWidgetLeft) &&
  (AX <= BWidgetLeft + BWidgetWidth) &&
  (AY > BWidgetTop) &&
  (AY <= BWidgetTop + BWidgetHeight))
  {
    BResultWidget = AWidget;
    
    BIteratorWidget = AWidget->FListChild->FFirstChild;
    while (BIteratorWidget)
    {
      BWidget = (TGUIWidget *)BIteratorWidget->FPointer;
      
      if (Widget_GetBool(BWidget, "visible"))
      {
        BResultWidgetChild = GetWidgetAt(BWidget, AX, AY);
      };
      
      if (BResultWidgetChild)
      {
        BResultWidget = BResultWidgetChild;
        break;
      };
      BIteratorWidget = BIteratorWidget->FNext;
    };
  };
  
  return BResultWidget;
};

void Widget_ResolveAlignment(TGUIWindow *AWindow, TGUIWidget *AWidget)
{
  int BWidgetLeft = 0;
  int BWidgetTop = 0;
  int BWidgetRight = 0;
  int BWidgetBottom = 0;
  int BWindowWidth = 0;
  int BWindowHeight = 0;
  
  glfwGetWindowSize(AWindow->FGLFW_Window, &BWindowWidth, &BWindowHeight);
  
  if (AWidget->FAlignment.FLeft.FAttatchToWidget)
  {
    BWidgetLeft = Widget_GetInt(AWidget->FAlignment.FLeft.FAttatchToWidget, "left");
    BWidgetTop = Widget_GetInt(AWidget->FAlignment.FLeft.FAttatchToWidget, "top");
    BWidgetRight = BWidgetLeft + Widget_GetInt(AWidget->FAlignment.FLeft.FAttatchToWidget, "width");
    BWidgetBottom = BWidgetTop + Widget_GetInt(AWidget->FAlignment.FLeft.FAttatchToWidget, "height");
  } else
  {
    BWidgetLeft = 0;
    BWidgetTop = 0;
    BWidgetRight = BWindowWidth;
    BWidgetBottom = BWindowHeight;
  };
  
  if ((AWidget->FAlignment.FLeft.FAttatchToSide == FALSE) &&
  (AWidget->FAlignment.FLeft.FEnabled))
  {
    // If attatch the "left" to the side "left"/"FALSE" of FAttatchToWidget:
    Widget_SetInt(AWidget, "left", BWidgetLeft + AWidget->FAlignment.FLeft.FSpacing);
  } else
  if ((AWidget->FAlignment.FLeft.FAttatchToSide == TRUE) &&
  (AWidget->FAlignment.FLeft.FEnabled))
  {
    // If attatch the "left" to the side "right"/"TRUE" of FAttatchToWidget:
    Widget_SetInt(AWidget, "left", BWidgetRight + AWidget->FAlignment.FLeft.FSpacing);
  };
  
  if ((AWidget->FAlignment.FRight.FAttatchToSide == FALSE) &&
  (AWidget->FAlignment.FRight.FEnabled))
  {
    // If attatch the "right" to the side "left"/"FALSE" of FAttatchToWidget:
    Widget_SetInt(AWidget, "width", Widget_GetInt(AWidget, "left") - BWidgetLeft - AWidget->FAlignment.FLeft.FSpacing);
  } else
  if ((AWidget->FAlignment.FRight.FAttatchToSide == TRUE) &&
  (AWidget->FAlignment.FRight.FEnabled))
  {
    // If attatch the "right" to the side "right"/"TRUE" of FAttatchToWidget:
    Widget_SetInt(AWidget, "width", BWidgetRight - Widget_GetInt(AWidget, "left") + AWidget->FAlignment.FLeft.FSpacing);
  };
  
  
  
  if ((AWidget->FAlignment.FTop.FAttatchToSide == FALSE) &&
  (AWidget->FAlignment.FTop.FEnabled))
  {
    // If attatch the "top" to the side "top"/"FALSE" of FAttatchToWidget:
    Widget_SetInt(AWidget, "top", BWidgetTop + AWidget->FAlignment.FTop.FSpacing);
  } else
  if ((AWidget->FAlignment.FTop.FAttatchToSide == TRUE) &&
  (AWidget->FAlignment.FTop.FEnabled))
  {
    // If attatch the "top" to the side "bottom"/"TRUE" of FAttatchToWidget:
    Widget_SetInt(AWidget, "top", BWidgetBottom + AWidget->FAlignment.FTop.FSpacing);
  };
  
  if ((AWidget->FAlignment.FBottom.FAttatchToSide == FALSE) &&
  (AWidget->FAlignment.FBottom.FEnabled))
  {
    // If attatch the "bottom" to the side "top"/"FALSE" of FAttatchToWidget:
    Widget_SetInt(AWidget, "height", Widget_GetInt(AWidget, "top") - BWidgetTop - AWidget->FAlignment.FTop.FSpacing);
  } else
  if ((AWidget->FAlignment.FBottom.FAttatchToSide == TRUE) &&
  (AWidget->FAlignment.FBottom.FEnabled))
  {
    // If attatch the "bottom" to the side "bottom"/"TRUE" of FAttatchToWidget:
    Widget_SetInt(AWidget, "height", BWidgetBottom - Widget_GetInt(AWidget, "top") + AWidget->FAlignment.FTop.FSpacing);
  };
  
  if (AWidget->FParent == NULL)
  {
    //printf("Wants the right as \"%i\".\n", Widget_GetInt(AWidget, "width"));
  };
};

void Widget_PaintDefault(TGUIWindow *AWindow, TGUIWidget *AWidget)
{
  int BWidth = Widget_GetInt(AWidget, "width");
  int BHeight = Widget_GetInt(AWidget, "height");
  
  glColor4f(0.0, 0.0, 0.0, 1.0);
  glBegin(GL_LINES);
    // Top line:
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(BWidth, 1.0, 0.0);
    // Left line:
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, BHeight, 0.0);
    // Right line:
    glVertex3f(BWidth, 1.0, 0.0);
    glVertex3f(BWidth, BHeight, 0.0);
    // Bottom line:
    glVertex3f(1.0, BHeight - 1, 0.0);
    glVertex3f(BWidth, BHeight - 1, 0.0);
    // Diagonal line:
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(BWidth, BHeight, 0.0);
    // Diagonal line:
    glVertex3f(BWidth, 0.0, 0.0);
    glVertex3f(0.0, BHeight, 0.0);
  glEnd();
};

void RenderWidget(TGUIWindow *AWindow, TGUIWidget *AWidget)
{
  TIterator *BIteratorWidget = NULL;
  TGUIWidget *BWidget = NULL;
  int BWidth = 0;
  int BHeight = 0;
  
  Widget_ResolveAlignment(AWindow, AWidget);
  
  BWidth = Widget_GetInt(AWidget, "width");
  BHeight = Widget_GetInt(AWidget, "height");
  
  if ((BWidth != AWidget->FFrameBufferWidth) ||
  (BHeight != AWidget->FFrameBufferHeight))
  {
    AWidget->FFrameBufferWidth = BWidth;
    AWidget->FFrameBufferHeight = BHeight;
    
    //printf("[MESSAGE] Changing framebuffer of widget \"%s\".\n", AWidget->FName->FPointer);
    GUI_ChangeFBO(&AWidget->FFrameBufferObject, &AWidget->FRenderBuffer_Color, &AWidget->FRenderBuffer_Depth,
                  BWidth, BHeight);
    //printf("[MESSAGE] Buffer of widget changed.\n");
  };
  
  // BEGIN - Prepare the widget for drawing.
  glBindFramebuffer(GL_FRAMEBUFFER, AWidget->FFrameBufferObject);
  glClearColor(0.4, 0.4, 0.4, 1.0);
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );
  
  glViewport(0, 0, BWidth, BHeight);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, BWidth, BHeight, 0.0, 1.0, -1.0);
   
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  
  glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushAttrib(GL_ENABLE_BIT);
  
  // END - Prepare the widget for drawing.
  
  // BEGIN - Call the drawing function.
  if (AWidget->FDraw)
  {
    //AWidget->FDraw(AWidget);
    Widget_PaintDefault(AWindow, AWidget);
  } else
  {
    Widget_PaintDefault(AWindow, AWidget);
  };
  // END - Call the drawing function.
  glPopAttrib();
  glMatrixMode( GL_PROJECTION );
  glPopMatrix();
  glMatrixMode( GL_MODELVIEW );
  glPopMatrix();
  
  glFlush();
  
  
  
  
  
  
  
  
  
  
  
  
  
  BIteratorWidget = AWidget->FListChild->FFirstChild;
  while (BIteratorWidget)
  {
    BWidget = (TGUIWidget *)BIteratorWidget->FPointer;
    if (BWidget)
    { 
      int BDestRectLeft = Widget_GetInt(BWidget, "left");
      int BDestRectTop = Widget_GetInt(BWidget, "top");
      int BDestRectWidth = BDestRectLeft + Widget_GetInt(BWidget, "width");
      int BDestRectHeight = BDestRectTop + Widget_GetInt(BWidget, "height");
      
      if (Widget_GetBool(BWidget, "visible"))
      {
        RenderWidget(AWindow, BWidget);
      };
      
      
      // Target to copy from the render of the widget.
      glBindFramebuffer(GL_READ_FRAMEBUFFER, BWidget->FFrameBufferObject);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, AWidget->FFrameBufferObject);
      glReadBuffer(GL_COLOR_ATTACHMENT0 | GL_DEPTH_ATTACHMENT);
      glDrawBuffer(GL_COLOR_ATTACHMENT0 | GL_DEPTH_ATTACHMENT);
      
      
      glBlitFramebuffer(0, 0, Widget_GetInt(BWidget, "width"), Widget_GetInt(BWidget, "height"),
                        BDestRectLeft, BDestRectTop, BDestRectWidth, BDestRectHeight,
                        GL_COLOR_BUFFER_BIT,
                        GL_NEAREST);
      
    };
    BIteratorWidget = BIteratorWidget->FNext;
  };
  
  glFlush();
};

void Draw_Hatch(TGUIWindow *AWindow, int AWidth, int AHeight)
{
  // Description:
  // This function is used to draw a hatch effect when the window has more than
  // one client widgets.
  
  // To-do:
  // Rewrite this function based on OpenGL.
  
  
  /*int BLine = -(int)(AWidth / 8);
  SDL_SetRenderDrawColor(AWindow->FSDL_Renderer, 0, 0, 0, 80);
  while ((BLine * 8) < AWidth)
  {
    SDL_RenderDrawLine(AWindow->FSDL_Renderer, (BLine * 8), 0, (BLine * 8) + AHeight - 1, AHeight - 1);
    BLine = BLine + 1;
  };
  
  BLine = -(int)(AWidth / 8);
  SDL_SetRenderDrawColor(AWindow->FSDL_Renderer, 0, 0, 0, 60);
  while ((BLine * 8) < AWidth)
  {
    SDL_RenderDrawLine(AWindow->FSDL_Renderer, (BLine * 8) - 1, 0, (BLine * 8) + AHeight - 1 - 1, AHeight - 1);
    BLine = BLine + 1;
  };
  BLine = -(int)(AWidth / 8);
  while ((BLine * 8) < AWidth)
  {
    SDL_RenderDrawLine(AWindow->FSDL_Renderer, (BLine * 8) + 1, 0, (BLine * 8) + AHeight - 1 + 1, AHeight - 1);
    BLine = BLine + 1;
  };

  BLine = -(int)(AWidth / 8);
  SDL_SetRenderDrawColor(AWindow->FSDL_Renderer, 0, 0, 0, 10);
  while ((BLine * 8) < AWidth)
  {
    SDL_RenderDrawLine(AWindow->FSDL_Renderer, (BLine * 8) - 2, 0, (BLine * 8) + AHeight - 1 - 2, AHeight - 1);
    BLine = BLine + 1;
  };
  BLine = -(int)(AWidth / 8);
  while ((BLine * 8) < AWidth)
  {
    SDL_RenderDrawLine(AWindow->FSDL_Renderer, (BLine * 8) + 2, 0, (BLine * 8) + AHeight - 1 + 2, AHeight - 1);
    BLine = BLine + 1;
  };*/
};

void RenderWindow(TGUIWindow *AWindow)
{
  TIterator *BIteratorWidget = NULL;
  TGUIWidget *BClientWidget = NULL;
  int BWindowWidth = 0;
  int BWindowHeight = 0;
  int BTextureWidth = 0;
  int BTextureHeight = 0;
  
  glfwGetWindowSize(AWindow->FGLFW_Window, &BWindowWidth, &BWindowHeight);
  
  if ((BWindowWidth != AWindow->FFrameBufferWidth) ||
  (BWindowHeight != AWindow->FFrameBufferHeight))
  {
    AWindow->FFrameBufferWidth = BWindowWidth;
    AWindow->FFrameBufferHeight = BWindowHeight;
    
    //printf("[MESSAGE] Changing buffer of window.\n");
    GUI_ChangeFBO(&AWindow->FFrameBufferObject, &AWindow->FRenderBuffer_Color, &AWindow->FRenderBuffer_Depth,
                  BWindowWidth, BWindowHeight);
    //printf("[MESSAGE] Buffer of window changed.\n");
  };
  
  // BEGIN - Clear the window buffer.
  glBindFramebuffer(GL_FRAMEBUFFER, AWindow->FFrameBufferObject);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );
  glViewport(0, 0, BWindowWidth, BWindowHeight);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, BWindowWidth, BWindowHeight, 0.0, 1.0, -1.0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushAttrib(GL_ENABLE_BIT);
  
  glPopAttrib();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glFlush();
  // END - Clear the window buffer.
  
  // BEGIN - Render the client widgets on the window buffer.
  BIteratorWidget = AWindow->FListClientWidget->FFirstChild;
  while (BIteratorWidget)
  {
    BClientWidget = (TGUIWidget *)BIteratorWidget->FPointer;
    if (BClientWidget)
    {
      int BDestRectLeft = Widget_GetInt(BClientWidget, "left");
      int BDestRectTop = Widget_GetInt(BClientWidget, "top");
      int BDestRectWidth = BDestRectLeft + Widget_GetInt(BClientWidget, "width");
      int BDestRectHeight = BDestRectTop + Widget_GetInt(BClientWidget, "height");
      
      if (Widget_GetBool(BClientWidget, "visible"))
      {
        RenderWidget(AWindow, BClientWidget);
      };
      
      // BEGIN - Copy from the client widget buffer to the window buffer.
      glBindFramebuffer(GL_READ_FRAMEBUFFER, BClientWidget->FFrameBufferObject);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, AWindow->FFrameBufferObject);
      glReadBuffer(GL_COLOR_ATTACHMENT0 | GL_DEPTH_ATTACHMENT);
      glDrawBuffer(GL_COLOR_ATTACHMENT0 | GL_DEPTH_ATTACHMENT);
      glViewport(0, 0, BWindowWidth, BWindowHeight);
      
      glBlitFramebuffer(0, 0, Widget_GetInt(BClientWidget, "width"), Widget_GetInt(BClientWidget, "height"),
                        BDestRectLeft, BDestRectTop, BDestRectWidth, BDestRectHeight,
                        GL_COLOR_BUFFER_BIT,
                        GL_NEAREST);
      glFlush();
      // END - Copy from the client widget buffer to the window buffer.
    };
    BIteratorWidget = BIteratorWidget->FNext;
  };
  // END - Render the client widgets on the window buffer.
  
  // BEGIN - Copy from the window buffer to the screen buffer.
  glBindFramebuffer(GL_READ_FRAMEBUFFER, AWindow->FFrameBufferObject);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glReadBuffer(GL_COLOR_ATTACHMENT0 | GL_DEPTH_ATTACHMENT);
  glDrawBuffer(GL_COLOR_ATTACHMENT0 | GL_DEPTH_ATTACHMENT);
  glViewport(0, 0, BWindowWidth, BWindowHeight);
  
  glBlitFramebuffer(0, 0, BWindowWidth, BWindowHeight,
                    0, BWindowHeight, BWindowWidth, 0,
                    GL_COLOR_BUFFER_BIT,
                    GL_NEAREST);
  glFlush();
  // END - Copy from the window buffer to the screen buffer.
      
  glfwSwapBuffers(AWindow->FGLFW_Window);
};

static void Window_Callback_MouseEnter(GLFWwindow* AWindow, int AEntered)
{
  
};

static void Window_Callback_MouseButton(GLFWwindow* AWindow, int AButton, int AAction, int AMods)
{
  
};

static void Window_Callback_MousePosition(GLFWwindow* AWindow, double AMouseX, double AMouseY)
{
  TGUIWidget *BWidgetMouseOver = NULL;
  TGUIWidget *BClientWidget = NULL;
  TIterator *BIteratorWidget = NULL;
  TGUIWindow *BWindow = (TGUIWindow *)glfwGetWindowUserPointer(AWindow);
  BWindow->FMouseX = AMouseX;
  BWindow->FMouseY = AMouseY;
  
  // Mouse input works only on the last client widget. This is the modal
  // behaviour.
  BIteratorWidget = BWindow->FListClientWidget->FLastChild;
  if (BIteratorWidget)
  {
    BClientWidget = (TGUIWidget *)BIteratorWidget->FPointer;
    if (BClientWidget)
    {
      BWidgetMouseOver = GetWidgetAt(BClientWidget, BWindow->FMouseX, BWindow->FMouseY);
      if (BWidgetMouseOver != BWindow->FWidgetMouseOver)
      {
        if (BWindow->FWidgetMouseOver)
        {
          printf("[MESSAGE] Mouse leave \"%s\".\n", BWindow->FWidgetMouseOver->FName->FPointer);
          
          if (BWindow->FWidgetMouseOver->FMouseLeave)
          {
            BWindow->FWidgetMouseOver->FMouseLeave(BWindow->FWidgetMouseOver);
          };
        };
        
        if (BWidgetMouseOver)
        {
          printf("[MESSAGE] Mouse enter \"%s\".\n", BWidgetMouseOver->FName->FPointer);
          
          if (BWidgetMouseOver->FMouseEnter)
          {
            BWidgetMouseOver->FMouseEnter(BWidgetMouseOver);
          };
        };
      };
      
      if (BWidgetMouseOver)
      {
        if (BWidgetMouseOver->FMouseMove)
        {
          BWidgetMouseOver->FMouseMove(BWidgetMouseOver, BWindow->FMouseX - GetWidgetGlobalLeft(BWindow->FWidgetMouseOver), BWindow->FMouseY - GetWidgetGlobalTop(BWindow->FWidgetMouseOver));
        };
      };
      BWindow->FWidgetMouseOver = BWidgetMouseOver;
    };
  };  
};

static void Window_Callback_Key(GLFWwindow* AWindow, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE)
  {
    glfwSetWindowShouldClose(AWindow, GL_TRUE);
  };
  
  if (action)
  {
    printf("[MESSAGE] Key down.\n");
  } else
  {
    printf("[MESSAGE] Key up.\n");
  };
};

void RunWindow(TGUIWindow *AWindow)
{
  TIterator *BIteratorWidget = NULL;
  TGUIWidget *BClientWidget = NULL;
  
  AWindow->FRunning = TRUE;
  printf("[MESSAGE] Running window.\n");
  
  // BEGIN - Window main loop.
  while (!glfwWindowShouldClose(AWindow->FGLFW_Window))
  {
    glfwPollEvents();
    
    // To-do:
    // Copy the events from the SDL loop to the GLFW callbacks. The SDL loop
    // works, but need to be converted to work based on GLFW.
    
    // This is the SDL main loop.
    /*while (SDL_PollEvent(&BSDLEvent))
    {
      if (BSDLEvent.type == SDL_QUIT)
      {
        AWindow->FRunning = FALSE;
      } else
      if (BSDLEvent.type == SDL_WINDOWEVENT)
      {
        printf("[MESSAGE] Window event recieved.\n");
        if (BSDLEvent.window.event == SDL_WINDOWEVENT_EXPOSED)
        {
          RenderWindow(AWindow);
        } else
        if (BSDLEvent.window.event == SDL_WINDOWEVENT_RESIZED)
        {
          BIteratorWidget = AWindow->FListClientWidget->FLastChild;
          if (BIteratorWidget)
          {
            BClientWidget = (TGUIWidget *)BIteratorWidget->FPointer;
            if (BClientWidget)
            {
              int BWindowWidth = 0;
              int BWindowHeight = 0;
              SDL_GetWindowSize(AWindow->FSDL_Window, &BWindowWidth, &BWindowHeight);
              printf("[MESSAGE] Resizing widget \"%s\" to (%i, %i).\n", BClientWidget->FName, BWindowWidth, BWindowHeight);
              //Widget_SetInt(BClientWidget, "width", BWindowWidth);
              //Widget_SetInt(BClientWidget, "height", BWindowHeight);
            };
          };
          RenderWindow(AWindow);
        } else
        if (BSDLEvent.window.event == SDL_WINDOWEVENT_LEAVE)
        {
          printf("[MESSAGE] Mouse leave window.\n");
          AWindow->FWidgetMouseOver = NULL;
        };
        printf("[MESSAGE] Window end.\n");
      } else
      if (BSDLEvent.type == SDL_MOUSEBUTTONDOWN)
      {
        AWindow->FMouseDown = TRUE;
        if (AWindow->FWidgetMouseOver)
        {
          if (Widget_GetBool(AWindow->FWidgetMouseOver, "canfocus"))
          {
            AWindow->FWidgetFocused = AWindow->FWidgetMouseOver;
          };
          if (AWindow->FWidgetMouseOver->FMouseDown)
          {
            AWindow->FWidgetMouseOver->FMouseDown(AWindow->FWidgetMouseOver, 0, AWindow->FMouseX - GetWidgetGlobalLeft(AWindow->FWidgetMouseOver), AWindow->FMouseY - GetWidgetGlobalTop(AWindow->FWidgetMouseOver));
            //BWidgetMouseOver->FMouseButtonDown(BWidgetMouseOver, BMouseX - GetWidgetGlobalLeft(BWidgetMouseOver), BMouseY - GetWidgetGlobalTop(BWidgetMouseOver));
          };
        };
      } else
      if (BSDLEvent.type == SDL_MOUSEBUTTONUP)
      {
        AWindow->FMouseDown = FALSE;
        if (AWindow->FWidgetMouseOver)
        {
          if (AWindow->FWidgetMouseOver->FMouseUp)
          {
            AWindow->FWidgetMouseOver->FMouseUp(AWindow->FWidgetMouseOver, 0, AWindow->FMouseX - GetWidgetGlobalLeft(AWindow->FWidgetMouseOver), AWindow->FMouseY - GetWidgetGlobalTop(AWindow->FWidgetMouseOver));
            //BWidgetMouseOver->FMouseButtonDown(BWidgetMouseOver, BMouseX - GetWidgetGlobalLeft(BWidgetMouseOver), BMouseY - GetWidgetGlobalTop(BWidgetMouseOver));
          };
        };
      } else
      if (BSDLEvent.type == SDL_MOUSEWHEEL)
      {
      
      } else
      if (BSDLEvent.type == SDL_MOUSEMOTION)
      {
        TGUIWidget *BWidgetMouseOver = NULL;
        SDL_GetMouseState(&AWindow->FMouseX, &AWindow->FMouseY);
        
        BIteratorWidget = AWindow->FListClientWidget->FLastChild;
        if (BIteratorWidget)
        {
          BClientWidget = (TGUIWidget *)BIteratorWidget->FPointer;
          
          if (BClientWidget)
          {
            BWidgetMouseOver = GetWidgetAt(BClientWidget, AWindow->FMouseX, AWindow->FMouseY);
            //printf("[MESSAGE] Mouse over \"%s\".\n", BWidgetMouseOver->FName);
            
            if (BWidgetMouseOver != AWindow->FWidgetMouseOver)
            {
              if (AWindow->FWidgetMouseOver)
              {
                printf("[MESSAGE] Mouse leave \"%s\".\n", AWindow->FWidgetMouseOver->FName);
                
                if (AWindow->FWidgetMouseOver->FMouseLeave)
                {
                  AWindow->FWidgetMouseOver->FMouseLeave(AWindow->FWidgetMouseOver);
                };
              };
              
              if (BWidgetMouseOver)
              {
                printf("[MESSAGE] Mouse enter \"%s\".\n", BWidgetMouseOver->FName);
                
                if (BWidgetMouseOver->FMouseEnter)
                {
                  BWidgetMouseOver->FMouseEnter(BWidgetMouseOver);
                };
              };
            };
            
            if (BWidgetMouseOver)
            {
              if (BWidgetMouseOver->FMouseMove)
              {
                BWidgetMouseOver->FMouseMove(BWidgetMouseOver, AWindow->FMouseX - GetWidgetGlobalLeft(AWindow->FWidgetMouseOver), AWindow->FMouseY - GetWidgetGlobalTop(AWindow->FWidgetMouseOver));
              };
            };
            AWindow->FWidgetMouseOver = BWidgetMouseOver;
          };
        };
      } else
      if (BSDLEvent.type == SDL_KEYDOWN)
      {
      
      } else
      if (BSDLEvent.type == SDL_KEYUP)
      {
      
      } else
      {
          printf("[MESSAGE] Unhandled event recieved.\n");
      };
    };*/
    
    RenderWindow(AWindow);
  };
  // ENDf - Window main loop.
  printf("[MESSAGE] Finishing window.\n");
};

void GUI_AllocFBO(GLuint *AFrameBufferObject, GLuint *ARenderBuffer_Color, GLuint *ARenderBuffer_Depth, int AWidth, int AHeight)
{
  glGenRenderbuffers(1, ARenderBuffer_Color);
  glBindRenderbuffer(GL_RENDERBUFFER, *ARenderBuffer_Color);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB8, AWidth, AHeight);
  
  glGenRenderbuffers(1, ARenderBuffer_Depth);
  glBindRenderbuffer(GL_RENDERBUFFER, *ARenderBuffer_Depth);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, AWidth, AHeight);
  
  glGenFramebuffers(1, AFrameBufferObject);
  glBindFramebuffer(GL_FRAMEBUFFER, *AFrameBufferObject);
  
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, *ARenderBuffer_Color);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *ARenderBuffer_Depth);
  
  GLenum BCheck = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (BCheck == GL_FRAMEBUFFER_COMPLETE)
  {
    //printf("[MESSAGE] Framebuffer Object created.\n");
  } else
  {
    printf("[ERROR] There is a problem with the Framebuffer Object.\n");
  };
  
  if (glIsRenderbuffer(*ARenderBuffer_Color))
  {
    //printf("[MESSAGE] Color color render created.\n");
  } else
  {
    printf("[ERROR] There is a problem with the color render.\n");
  };
  
  if (glIsRenderbuffer(*ARenderBuffer_Depth))
  {
    //printf("[MESSAGE] Depth render created.\n");
  } else
  {
    printf("[ERROR] There is a problem with the depth render.\n");
  };
};

void GUI_ChangeFBO(GLuint *AFrameBufferObject, GLuint *ARenderBuffer_Color, GLuint *ARenderBuffer_Depth, int AWidth, int AHeight)
{
  glDeleteFramebuffers(1, AFrameBufferObject);
  glDeleteRenderbuffers(1, ARenderBuffer_Color);
  glDeleteRenderbuffers(1, ARenderBuffer_Depth);
  
  GUI_AllocFBO(AFrameBufferObject, ARenderBuffer_Color, ARenderBuffer_Depth, AWidth, AHeight);
};

TGUIWidget *GUI_Create_Widget(TGUIWindow *AWindow, char *AWidgetClass, const char *AWidgetName)
{
  TGUIWidget *BWidget = (TGUIWidget *)malloc(sizeof(TGUIWidget));
  BWidget->FWindow = AWindow;
  BWidget->FName = Alloc_String(AWidgetName);
  BWidget->FClass = Alloc_String(AWidgetClass);
  BWidget->FParent = NULL;
  
  BWidget->FAlignment.FTop.FAttatchToWidget = NULL;
  BWidget->FAlignment.FTop.FAttatchToSide = TOP;
  BWidget->FAlignment.FTop.FSpacing = 0;
  BWidget->FAlignment.FTop.FEnabled = FALSE;
  BWidget->FAlignment.FLeft.FAttatchToWidget = NULL;
  BWidget->FAlignment.FLeft.FAttatchToSide = LEFT;
  BWidget->FAlignment.FLeft.FSpacing = 0;
  BWidget->FAlignment.FLeft.FEnabled = FALSE;
  BWidget->FAlignment.FBottom.FAttatchToWidget = NULL;
  BWidget->FAlignment.FBottom.FAttatchToSide = BOTTOM;
  BWidget->FAlignment.FBottom.FSpacing = 0;
  BWidget->FAlignment.FBottom.FEnabled = FALSE;
  BWidget->FAlignment.FRight.FAttatchToWidget = NULL;
  BWidget->FAlignment.FRight.FAttatchToSide = RIGHT;
  BWidget->FAlignment.FRight.FSpacing = 0;
  BWidget->FAlignment.FRight.FEnabled = FALSE;
  
  BWidget->FDraw = NULL;
  BWidget->FMouseDown = NULL;
  BWidget->FMouseUp = NULL;
  BWidget->FMouseMove = NULL;
  BWidget->FMouseEnter = NULL;
  BWidget->FMouseLeave = NULL;
  
  BWidget->FListProperty = AllocIterator(NULL);
  BWidget->FListChild = AllocIterator(NULL);
  
  Widget_AddBool(BWidget, "canfocus", TRUE);
  Widget_AddBool(BWidget, "enabled", TRUE);
  Widget_AddBool(BWidget, "visible", TRUE);
  Widget_AddBool(BWidget, "down", FALSE);
  Widget_AddInt(BWidget, "left", 0);
  Widget_AddInt(BWidget, "top", 0);
  Widget_AddInt(BWidget, "width", 24);
  Widget_AddInt(BWidget, "height", 24);
  Widget_AddFloat(BWidget, "zoom", 1.0);
  
  BWidget->FFrameBufferObject = 0;
  BWidget->FRenderBuffer_Color = 0;
  BWidget->FRenderBuffer_Depth = 0;
  GUI_AllocFBO(&BWidget->FFrameBufferObject, &BWidget->FRenderBuffer_Color, &BWidget->FRenderBuffer_Depth, Widget_GetInt(BWidget, "width"), Widget_GetInt(BWidget, "height"));
  
  // BEGIN - Call class allocation function.
  // To-do:
  // Create the class manager. Find the function based on the name of the class.
  // END - Call class allocation function.
  
  printf("[MESSAGE] Widget of class \"%s\" created.\n", BWidget->FClass->FPointer);
  return BWidget;
};

TGUIWindow *GUI_Create_Window(const char *ATitle, int APosX, int APosY, int AWidth, int AHeight, int AFlags)
{
  TGUIWindow *BWindow = NULL;
  BWindow = (TGUIWindow *)malloc(sizeof(TGUIWindow));
  
  BWindow->FRunning = FALSE;
  BWindow->FListClientWidget = AllocIterator(NULL);
  BWindow->FWidgetMouseOver = NULL;
  BWindow->FMouseDown = FALSE;
  
  if (BWindow)
  {
    BWindow->FGLFW_Window = glfwCreateWindow(AWidth, AHeight, ATitle, NULL, NULL);
    glfwSetWindowUserPointer(BWindow->FGLFW_Window, BWindow);
    glfwMakeContextCurrent(BWindow->FGLFW_Window);
    
    glfwSetCursorPosCallback(BWindow->FGLFW_Window, Window_Callback_MousePosition);
    glfwSetKeyCallback(BWindow->FGLFW_Window, Window_Callback_Key);
    glfwSetMouseButtonCallback(BWindow->FGLFW_Window, Window_Callback_MouseButton);
    glfwSetCursorEnterCallback(BWindow->FGLFW_Window, Window_Callback_MouseEnter);
    
    GUI_AllocFBO(&BWindow->FFrameBufferObject, &BWindow->FRenderBuffer_Color, &BWindow->FRenderBuffer_Depth, AWidth, AHeight);
  
    printf("[MESSAGE] Window created.\n" );
  } else
  {
    printf("[ERROR] Failed to create window.\n");
  };
  
  return BWindow;
};

