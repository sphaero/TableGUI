/*
  This file is part of TableGUI.
  Copyright (c) 2014 Felipe Ferreira da Silva
  TableGUI is licensed under MIT license.
  See the file "LICENSE" for license details.
*/

#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <basicutils.h>
#include "GUI.h"
#include "GUI_font.h"
#include "GUI_theme.h"

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

void *Widget_GetRef(TGUIWidget *AWidget, char *APropertyName)
{
  return Get_Reference(AWidget->FListProperty, APropertyName);
};

int Initialize()
{
  if (glfwInit())
  {
    printf("[MESSAGE] GLFW initialized.\n");
  } else
  {
    printf("[ERROR] Fail to initialize GLFW.");
    exit(1);
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

int Window_AddClientWidget(TGUIWindow *AWindow, TGUIWidget *AClientWidget)
{
  Iterator_AddPointer(AWindow->FListClientWidget, AClientWidget);
  AClientWidget->FParent = NULL;
};

int Widget_AddChild(TGUIWidget *AWidgetParent, TGUIWidget *AWidgetChild)
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

    if (strcmp(AWidgetName, BWidget->FName->FPointer) == 0)
    {
      BResultWidget = BWidget;
      printf("[MESSAGE] Widget \"%s\" found.\n", BWidget->FName->FPointer);
      break;
    };

    BResultWidget = FindWidget(BWidget, AWidgetName);

    BIteratorWidget = BIteratorWidget->FNext;
  };
  
  return BResultWidget;
};

int GetWidgetGlobalLeft(TGUIWidget *AWidget)
{
  TGUIWidget *BWidget = NULL;
  int BResult = 0;
  
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  
  BResult = BWidgetProperties->FLeft;
  
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
  
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  
  BResult = BWidgetProperties->FTop;

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
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");

  int BWidgetLeft = GetWidgetGlobalLeft(AWidget);
  int BWidgetAttachTop = GetWidgetGlobalTop(AWidget);
  
  if ((AX > BWidgetLeft) &&
  (AX <= BWidgetLeft + BWidgetProperties->FWidth) &&
  (AY > BWidgetAttachTop) &&
  (AY <= BWidgetAttachTop + BWidgetProperties->FHeight))
  {
    BResultWidget = AWidget;

    BIteratorWidget = AWidget->FListChild->FFirstChild;
    while (BIteratorWidget)
    {
      BWidget = (TGUIWidget *)BIteratorWidget->FPointer;

      if (BWidgetProperties->FVisible)
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

TGUIWidget * Window_GetWidget(TGUIWindow *AWindow, char *AWidgetName)
{
  TIterator *BIteratorWidget = NULL;
  TGUIWidget *BWidget = NULL;
  BIteratorWidget = AWindow->FListWidget->FFirstChild;
  printf("[MESSAGE] Searching for widget \"%s\".\n", AWidgetName);
  
  while (BIteratorWidget)
  {
    BWidget = (TGUIWidget *)BIteratorWidget->FPointer;
    if (BWidget)
    {
      if (strcmp(BWidget->FName->FPointer, AWidgetName) == 0)
      {
        printf("[MESSAGE] Widget \"%s\" found.\n", BWidget->FName->FPointer);
        break;
      };
    };
    
    BIteratorWidget = BIteratorWidget->FNext;
  };

  return BWidget;
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

void Widget_ResolveAlignment(TGUIWindow *AWindow, TGUIWidget *AWidget, TGUIWidgetProperties *AWidgetProperties)
{
  TGUIWidgetProperties *BWidgetToAttachAlignment = NULL;
  int BReferenceLeft = 0;
  int BReferenceTop = 0;
  int BReferenceWidth = 0;
  int BReferenceHeight = 0;

  // BEGIN - Resolve the left alignment.
  if (AWidgetProperties->FLeftAlign)
  {
    if (AWidgetProperties->FLeftWidget)
    {
      BWidgetToAttachAlignment = (TGUIWidgetProperties *)Widget_GetPointer(AWidgetProperties->FLeftWidget, "prop");
      BReferenceLeft = BWidgetToAttachAlignment->FLeft;
      BReferenceWidth = BWidgetToAttachAlignment->FWidth;
    } else
    {
      if (AWidget->FParent)
      {
        BWidgetToAttachAlignment = (TGUIWidgetProperties *)Widget_GetPointer(AWidget->FParent, "prop");
        BReferenceLeft = BWidgetToAttachAlignment->FLeft;
        BReferenceWidth = BWidgetToAttachAlignment->FWidth;
      } else
      {
        BReferenceLeft = 0;
        BReferenceWidth = AWindow->FWidth;
      };
    };  
    if (AWidgetProperties->FLeftSide == LEFT)
    {
      AWidgetProperties->FLeft = BReferenceLeft + AWidgetProperties->FLeftSpacing;
    } else
    {
      AWidgetProperties->FLeft = (BReferenceLeft + BReferenceWidth) + AWidgetProperties->FLeftSpacing;
    };
  };
  // END - Resolve the left alignment.
  
  // BEGIN - Resolve the right alignment.
  if (AWidgetProperties->FRightAlign)
  {
    if (AWidgetProperties->FRightWidget)
    {
      BWidgetToAttachAlignment = (TGUIWidgetProperties *)Widget_GetPointer(AWidgetProperties->FRightWidget, "prop");
      BReferenceLeft = BWidgetToAttachAlignment->FLeft;
      BReferenceWidth = BWidgetToAttachAlignment->FWidth;
    } else
    {
      if (AWidget->FParent)
      {
        BWidgetToAttachAlignment = (TGUIWidgetProperties *)Widget_GetPointer(AWidget->FParent, "prop");
        BReferenceLeft = BWidgetToAttachAlignment->FLeft;
        BReferenceWidth = BWidgetToAttachAlignment->FWidth;
      } else
      {
        BReferenceLeft = 0;
        BReferenceWidth = AWindow->FWidth;
      };
    };
    if (AWidgetProperties->FRightSide == LEFT)
    {
      if (AWidgetProperties->FLeftAlign)
      {
        AWidgetProperties->FWidth = (BReferenceLeft) - AWidgetProperties->FLeft - AWidgetProperties->FRightSpacing;
      } else
      {
        AWidgetProperties->FLeft = ((BReferenceLeft) - AWidgetProperties->FRightSpacing) - (AWidgetProperties->FWidth);
      };
    } else
    {
      if (AWidgetProperties->FLeftAlign)
      {
        AWidgetProperties->FWidth = (BReferenceLeft + BReferenceWidth) - AWidgetProperties->FLeft - AWidgetProperties->FRightSpacing;
      } else
      {
        AWidgetProperties->FLeft = ((BReferenceLeft + BReferenceWidth) - AWidgetProperties->FRightSpacing) - (AWidgetProperties->FWidth);
      };
    };
  };
  // END - Resolve the right alignment.
  
  // BEGIN - Resolve the top alignment.
  if (AWidgetProperties->FTopAlign)
  {
    if (AWidgetProperties->FTopWidget)
    {
      BWidgetToAttachAlignment = (TGUIWidgetProperties *)Widget_GetPointer(AWidgetProperties->FTopWidget, "prop");
      BReferenceTop = BWidgetToAttachAlignment->FTop;
      BReferenceHeight = BWidgetToAttachAlignment->FHeight;
    } else
    {
      if (AWidget->FParent)
      {
        BWidgetToAttachAlignment = (TGUIWidgetProperties *)Widget_GetPointer(AWidget->FParent, "prop");
        BReferenceTop = BWidgetToAttachAlignment->FTop;
        BReferenceHeight = BWidgetToAttachAlignment->FHeight;
      } else
      {
        BReferenceTop = 0;
        BReferenceHeight = AWindow->FHeight;
      };
    };
    if (AWidgetProperties->FTopSide == LEFT)
    {
      AWidgetProperties->FTop = BReferenceTop + AWidgetProperties->FTopSpacing;
    } else
    {
      AWidgetProperties->FTop = (BReferenceTop + BReferenceHeight) + AWidgetProperties->FTopSpacing;
    };
  };
  // END - Resolve the top alignment.
  
  // BEGIN - Resolve the bottom alignment.
  if (AWidgetProperties->FBottomAlign)
  {
    if (AWidgetProperties->FBottomWidget)
    {
      BWidgetToAttachAlignment = (TGUIWidgetProperties *)Widget_GetPointer(AWidgetProperties->FBottomWidget, "prop");
      BReferenceTop = BWidgetToAttachAlignment->FTop;
      BReferenceHeight = BWidgetToAttachAlignment->FHeight;
    } else
    {
      if (AWidget->FParent)
      {
        BWidgetToAttachAlignment = (TGUIWidgetProperties *)Widget_GetPointer(AWidget->FParent, "prop");
        BReferenceTop = BWidgetToAttachAlignment->FTop;
        BReferenceHeight = BWidgetToAttachAlignment->FHeight;
      } else
      {
        BReferenceTop = 0;
        BReferenceHeight = AWindow->FHeight;
      };
    };
    if (AWidgetProperties->FBottomSide == LEFT)
    {
      if (AWidgetProperties->FTopAlign)
      {
        AWidgetProperties->FHeight = (BReferenceTop) - AWidgetProperties->FTop - AWidgetProperties->FBottomSpacing;
      } else
      {
        AWidgetProperties->FTop = ((BReferenceTop) - AWidgetProperties->FBottomSpacing) - (AWidgetProperties->FHeight);
      };
    } else
    {
      if (AWidgetProperties->FTopAlign)
      {
        AWidgetProperties->FHeight = (BReferenceTop + BReferenceHeight) - AWidgetProperties->FTop - AWidgetProperties->FBottomSpacing;
      } else
      {
        AWidgetProperties->FTop = ((BReferenceTop + BReferenceHeight) - AWidgetProperties->FBottomSpacing) - (AWidgetProperties->FHeight);
      };
    };
  };
  // END - Resolve the bottom alignment.
};

void Widget_PaintDefault(TGUIWindow *AWindow, TGUIWidget *AWidget)
{
  TGUIWidgetProperties *BWidgetProperties = Widget_GetPointer(AWidget, "prop");
  
  glColor4f(0.0, 0.0, 0.0, 1.0);
  glBegin(GL_LINE_STRIP);
    glVertex3f(BWidgetProperties->FWidth - 1.0, BWidgetProperties->FHeight - 1.0, 0.0);
    glVertex3f(0.0, BWidgetProperties->FHeight - 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(BWidgetProperties->FWidth - 1.0, 0.0, 0.0);
    glVertex3f(BWidgetProperties->FWidth - 1.0, BWidgetProperties->FHeight, 0.0);
  glEnd();
  glBegin(GL_LINES);
    // Diagonal line:
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(BWidgetProperties->FWidth - 1.0, BWidgetProperties->FHeight - 1.0, 0.0);
    // Diagonal line:
    glVertex3f(BWidgetProperties->FWidth - 1.0, 0.0, 0.0);
    glVertex3f(0.0, BWidgetProperties->FHeight - 1.0, 0.0);
  glEnd();
  glColor4f(0.9, 0.0, 0.0, 1.0);
  glBegin(GL_POINTS);
    glVertex3f(0.0, 0.0, 0.0);
  glEnd();
};

void glEnable2D(int AWidth, int AHeight, int AOrthoLeft, int AOrthoRight, int AOrthoBottom, int AOrthoTop)
{
	glViewport(0, 0, AWidth, AHeight);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(AOrthoLeft, AOrthoRight, AOrthoBottom, AOrthoTop, -1.0, 1.0);
  //glMatrixMode(GL_MODELVIEW);
  //glPushMatrix();
  //glLoadIdentity();
  //glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
  //glDisable(GL_DEPTH_TEST);
  //glDisable(GL_LIGHTING);
  glTranslatef(0.375, 0.375, 0.0);
  
  glEnable(GL_TEXTURE_2D);
  
  glDisable(GL_SMOOTH);		// Enable (gouraud) shading
	glDisable(GL_DEPTH_TEST); 	// Disable depth testing
  //glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

	//glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do

	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

  glDisable(GL_LIGHTING);
  glEnable(GL_BLEND);		// Enable blending (used for alpha) and blending function to use
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0);
  
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
};

void glDisable2D()
{
  /*//glPopAttrib();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  //glMatrixMode(GL_MODELVIEW);
  //glPopMatrix();*/
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
};

void RenderWidget(TGUIWindow *AWindow, TGUIWidget *AWidget, TGUIWidgetProperties *AWidgetProperties)
{
  TIterator *BIteratorWidget = NULL;
  TGUIWidget *BWidget = NULL;
  TGUIWidgetProperties *BWidgetProperties = NULL;
  
  if ((AWidgetProperties->FWidth != AWidget->FFrameBufferWidth) ||
  (AWidgetProperties->FHeight != AWidget->FFrameBufferHeight))
  {
    AWidget->FFrameBufferWidth = AWidgetProperties->FWidth;
    AWidget->FFrameBufferHeight = AWidgetProperties->FHeight;
    
    //printf("[MESSAGE] Changing framebuffer of widget \"%s\".\n", AWidget->FName->FPointer);
    GUI_ChangeFBO(&AWidget->FFrameBufferObject, &AWidget->FRenderBuffer_Color, &AWidget->FRenderBuffer_Depth,
                  AWidgetProperties->FWidth, AWidgetProperties->FHeight);
    //printf("[MESSAGE] Buffer of widget changed.\n");
  };
  
  // BEGIN - Prepare the widget for drawing.
  glBindFramebuffer(GL_FRAMEBUFFER, AWidget->FFrameBufferObject);
  glEnable2D(AWidgetProperties->FWidth, AWidgetProperties->FHeight, 0, AWidgetProperties->FWidth, AWidgetProperties->FHeight, 0);
  // END - Prepare the widget for drawing.
  
  glClearColor(0.4, 0.4, 0.4, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  
  // BEGIN - Call the drawing function.
  if (AWidget->FDraw)
  {
    Widget_PaintDefault(AWindow, AWidget);
    AWidget->FDraw(AWidget);
  } else
  {
    Widget_PaintDefault(AWindow, AWidget);
  };
  glFlush();
  // END - Call the drawing function.
  glDisable2D();
  
  BIteratorWidget = AWidget->FListChild->FFirstChild;
  while (BIteratorWidget)
  {
    BWidget = (TGUIWidget *)BIteratorWidget->FPointer;
    if (BWidget)
    {
      int BDestRectLeft = 0;
      int BDestRectTop = 0;
      int BDestRectWidth = 0;
      int BDestRectHeight = 0;
      
      BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidget, "prop");
      
      BDestRectLeft = BWidgetProperties->FLeft;
      BDestRectWidth = BDestRectLeft + BWidgetProperties->FWidth;
      BDestRectTop = AWidgetProperties->FHeight - BWidgetProperties->FTop - BWidgetProperties->FHeight;
      BDestRectHeight = BDestRectTop + BWidgetProperties->FHeight;
      
      if (BWidgetProperties->FVisible)
      {
        RenderWidget(AWindow, BWidget, BWidgetProperties);
      };
      
      // Target to copy from the render of the widget.
      glBindFramebuffer(GL_READ_FRAMEBUFFER, BWidget->FFrameBufferObject);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, AWidget->FFrameBufferObject);
      glReadBuffer(GL_COLOR_ATTACHMENT0);
      glDrawBuffer(GL_COLOR_ATTACHMENT0);
      
      glBlitFramebuffer(0, 0, BWidgetProperties->FWidth, BWidgetProperties->FHeight,
                        BDestRectLeft, BDestRectTop, BDestRectWidth, BDestRectHeight,
                        GL_COLOR_BUFFER_BIT,
                        GL_NEAREST);
    };
    BIteratorWidget = BIteratorWidget->FNext;
  };
  glFlush();
};

void ResolveAlignment(TGUIWindow *AWindow, TGUIWidget *AWidget)
{
  TIterator *BIteratorWidget = NULL;
  TGUIWidget *BWidget = NULL;
  
  // BEGIN - Resolve alignment.
  Widget_ResolveAlignment(AWindow, AWidget, Widget_GetPointer(AWidget, "prop"));
  // END - Resolve alignment.
  
  BIteratorWidget = AWidget->FListChild->FFirstChild;
  while (BIteratorWidget)
  {
    BWidget = (TGUIWidget *)BIteratorWidget->FPointer;
    if (BWidget)
    {
      ResolveAlignment(AWindow, BWidget);
    };
    BIteratorWidget = BIteratorWidget->FNext;
  };
};

void RenderWindow(TGUIWindow *AWindow)
{
  TIterator *BIteratorWidget = NULL;
  TGUIWidget *BClientWidget = NULL;
  TGUIWidgetProperties *BWidgetProperties = NULL;
  int BTextureWidth = 0;
  int BTextureHeight = 0;
  
  if ((AWindow->FWidth != AWindow->FFrameBufferWidth) ||
  (AWindow->FHeight != AWindow->FFrameBufferHeight))
  {
    AWindow->FFrameBufferWidth = AWindow->FWidth;
    AWindow->FFrameBufferHeight = AWindow->FHeight;

    //printf("[MESSAGE] Changing buffer of window.\n");
    GUI_ChangeFBO(&AWindow->FFrameBufferObject, &AWindow->FRenderBuffer_Color, NULL,
                  AWindow->FWidth, AWindow->FHeight);
    //printf("[MESSAGE] Buffer of window changed.\n");
  };
  
  // BEGIN - Render the client widgets on the window buffer.
  BIteratorWidget = AWindow->FListClientWidget->FFirstChild;
  while (BIteratorWidget)
  {
    BClientWidget = (TGUIWidget *)BIteratorWidget->FPointer;
    if (BClientWidget)
    {
      BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BClientWidget, "prop");
      int BDestRectLeft = 0;
      int BDestRectTop = 0;
      int BDestRectWidth = 0;
      int BDestRectHeight = 0;
      
      BDestRectLeft = BWidgetProperties->FLeft;
      BDestRectTop = AWindow->FHeight - BWidgetProperties->FTop - BWidgetProperties->FHeight;
      BDestRectWidth = BDestRectLeft + BWidgetProperties->FWidth;
      BDestRectHeight = BDestRectTop + BWidgetProperties->FHeight;
      
      if (BWidgetProperties->FVisible)
      {
        RenderWidget(AWindow, BClientWidget, BWidgetProperties);
      };

      // BEGIN - Copy from the client widget buffer to the window buffer.
      glBindFramebuffer(GL_READ_FRAMEBUFFER, BClientWidget->FFrameBufferObject);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);//AWindow->FFrameBufferObject);
      glReadBuffer(GL_COLOR_ATTACHMENT0);
      glDrawBuffer(GL_COLOR_ATTACHMENT0);
      glViewport(0, 0, AWindow->FWidth, AWindow->FHeight);
      
      glBlitFramebuffer(0, 0, BWidgetProperties->FWidth, BWidgetProperties->FHeight,
                        BDestRectLeft, BDestRectTop, BDestRectWidth, BDestRectHeight,
                        GL_COLOR_BUFFER_BIT,
                        GL_NEAREST);
      // END - Copy from the client widget buffer to the window buffer.
    };
    BIteratorWidget = BIteratorWidget->FNext;
  };
  glFlush();
  // END - Render the client widgets on the window buffer.

  // BEGIN - Copy from the window buffer to the screen buffer.
  /*glBindFramebuffer(GL_READ_FRAMEBUFFER, AWindow->FFrameBufferObject);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glReadBuffer(GL_COLOR_ATTACHMENT0 | GL_DEPTH_ATTACHMENT);
  glDrawBuffer(GL_COLOR_ATTACHMENT0 | GL_DEPTH_ATTACHMENT);
  glClearColor(0.4, 0.4, 0.4, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glEnable2D(BWindowWidth, BWindowHeight, 0, BWindowWidth, 0, BWindowHeight);
  
  glBlitFramebuffer(0, 0, BWindowWidth, BWindowHeight,
                    0, 0, BWindowWidth, BWindowHeight,
                    GL_COLOR_BUFFER_BIT,
                    GL_NEAREST);
  glFlush();
  glDisable2D();
  */
  // END - Copy from the window buffer to the screen buffer.
};

static void Window_Callback_MouseEnter(GLFWwindow* AWindow, int AEntered)
{
  TGUIWindow *BWindow = (TGUIWindow *)glfwGetWindowUserPointer(AWindow);
  if (AEntered)
  {
    //printf("[MESSAGE] Mouse entered window.\n");
    BWindow->FWidgetMouseOver = NULL;
  } else
  {
    if (BWindow->FWidgetMouseOver)
    {
      //printf("[MESSAGE] Mouse leave \"%s\".\n", BWindow->FWidgetMouseOver->FName->FPointer);
      if (BWindow->FWidgetMouseOver->FMouseLeave)
      {
        BWindow->FWidgetMouseOver->FMouseLeave(BWindow->FWidgetMouseOver);
      };
    };
    //printf("[MESSAGE] Mouse leaved window.\n");
    BWindow->FWidgetMouseOver = NULL;
  };
};

static void Window_Callback_MouseButton(GLFWwindow* AWindow, int AButton, int AAction, int AMods)
{
  TGUIWindow *BWindow = (TGUIWindow *)glfwGetWindowUserPointer(AWindow);
  
  if (AAction)
  {
    if (BWindow->FWidgetMouseOver)
    {
      TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWindow->FWidgetMouseOver, "prop");
      
      if (BWidgetProperties->FCanFocus)
      {
        BWindow->FWidgetFocused = BWindow->FWidgetMouseOver;
      };
      
      BWindow->FWidgetMouseDown = BWindow->FWidgetMouseOver;
      
      if (BWindow->FWidgetMouseOver->FMouseDown)
      {
        BWindow->FWidgetMouseOver->FMouseDown(BWindow->FWidgetMouseOver,  
                                              AButton,
                                              BWindow->FMouseX - GetWidgetGlobalLeft(BWindow->FWidgetMouseOver),
                                              BWindow->FMouseY - GetWidgetGlobalTop(BWindow->FWidgetMouseOver));
      };
      printf("[MESSAGE] Mouse button down at widget \"%s\".\n", BWindow->FWidgetMouseOver->FName->FPointer);
    };
  } else
  {
    if (BWindow->FWidgetMouseOver)
    {
      if (BWindow->FWidgetMouseOver->FMouseUp)
      {
        BWindow->FWidgetMouseOver->FMouseUp(BWindow->FWidgetMouseOver,
                                            AButton,
                                            BWindow->FMouseX - GetWidgetGlobalLeft(BWindow->FWidgetMouseOver),
                                            BWindow->FMouseY - GetWidgetGlobalTop(BWindow->FWidgetMouseOver));
        printf("[MESSAGE] Mouse button up at widget \"%s\".\n", BWindow->FWidgetMouseOver->FName->FPointer);
      };
    };
    BWindow->FWidgetMouseDown = NULL;
  };
};

static void Window_Callback_MousePosition(GLFWwindow* AWindow, double AMouseX, double AMouseY)
{
  TGUIWindow *BWindow = (TGUIWindow *)glfwGetWindowUserPointer(AWindow);
  TGUIWidget *BWidgetMouseOver = NULL;
  TGUIWidget *BClientWidget = NULL;
  TIterator *BIteratorWidget = NULL;
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
      
      // BEGIN - Widget enter and leave event.
      if (BWidgetMouseOver != BWindow->FWidgetMouseOver)
      {
        if (BWindow->FWidgetMouseOver)
        {
          //printf("[MESSAGE] Mouse leave \"%s\".\n", BWindow->FWidgetMouseOver->FName->FPointer);

          if (BWindow->FWidgetMouseOver->FMouseLeave)
          {
            BWindow->FWidgetMouseOver->FMouseLeave(BWindow->FWidgetMouseOver);
          };
        };

        if (BWidgetMouseOver)
        {
          //printf("[MESSAGE] Mouse enter \"%s\".\n", BWidgetMouseOver->FName->FPointer);

          if (BWidgetMouseOver->FMouseEnter)
          {
            BWidgetMouseOver->FMouseEnter(BWidgetMouseOver);
          };
        };
      };
      // END - Widget enter and leave event.
      
      // BEGIN - Widget move event.   
      if (BWindow->FWidgetMouseDown) 
      {
        if (BWindow->FWidgetMouseDown->FMouseMove)
        {
          BWindow->FWidgetMouseDown->FMouseMove(BWindow->FWidgetMouseDown,
                                                BWindow->FMouseX - GetWidgetGlobalLeft(BWindow->FWidgetMouseDown),
                                                BWindow->FMouseY - GetWidgetGlobalTop(BWindow->FWidgetMouseDown));
        };
      } else
      {
        if (BWidgetMouseOver)
        {
          if (BWidgetMouseOver->FMouseMove)
          {
            BWidgetMouseOver->FMouseMove(BWidgetMouseOver,
                                         BWindow->FMouseX - GetWidgetGlobalLeft(BWindow->FWidgetMouseOver),
                                         BWindow->FMouseY - GetWidgetGlobalTop(BWindow->FWidgetMouseOver));
          };
        };
      };
      // END - Widget move event.
      
      BWindow->FWidgetMouseOver = BWidgetMouseOver;
    };
  };
};

static void Window_Callback_Key(GLFWwindow* AWindow, int key, int scancode, int action, int mods)
{
  TGUIWindow *BWindow = (TGUIWindow *)glfwGetWindowUserPointer(AWindow);
  
  if (BWindow->FWidgetFocused)
  {
    if (BWindow->FWidgetFocused->FKey)
    {
      BWindow->FWidgetFocused->FKey(BWindow->FWidgetFocused, key, scancode, action, mods);
    };
  };
};

static void Window_Callback_Size(GLFWwindow* AWindow, int AWidth, int AHeight)
{
  TGUIWindow *BWindow = (TGUIWindow *)glfwGetWindowUserPointer(AWindow);
  //glfwGetWindowSize(AWindow, &BWindow->FWidth, &BWindow->FHeight);
  BWindow->FWidth = AWidth;
  BWindow->FHeight = AHeight;
};

void RunWindow(TGUIWindow *AWindow)
{
  TIterator *BIteratorWidget = NULL;
  TGUIWidget *BClientWidget = NULL;
  struct timeval BTime;
  double BMilisec = 0;
  double BPrintMilisec = 0;
  
  AWindow->FRunning = TRUE;
  glfwGetWindowSize(AWindow->FGLFW_Window, &AWindow->FWidth, &AWindow->FHeight);
  printf("[MESSAGE] Running window.\n");
  
  // BEGIN - Window main loop.
  while (!glfwWindowShouldClose(AWindow->FGLFW_Window))
  {
    glfwPollEvents();
    // BEGIN - Resolve alignment.
    BIteratorWidget = AWindow->FListClientWidget->FFirstChild;
    while (BIteratorWidget)
    {
      BClientWidget = (TGUIWidget *)BIteratorWidget->FPointer;
      if (BClientWidget)
      {
        ResolveAlignment(AWindow, BClientWidget);
      };
      BIteratorWidget = BIteratorWidget->FNext;
    };
    // END - Resolve alignment.
    
    RenderWindow(AWindow);
    glfwSwapBuffers(AWindow->FGLFW_Window);
    
    gettimeofday(&BTime, NULL);
    BPrintMilisec = (BTime.tv_sec) * 1000 + (BTime.tv_usec) / 1000;
    //printf("[TIME] %f\n", (BPrintMilisec - BMilisec));
    gettimeofday(&BTime, NULL);
    BMilisec = (BTime.tv_sec) * 1000 + (BTime.tv_usec) / 1000;
  };
  // ENDf - Window main loop.
  
  printf("[MESSAGE] Finishing window.\n");
};

void GUI_AllocFBO(GLuint *AFrameBufferObject, GLuint *ARenderBuffer_Color, GLuint *ARenderBuffer_Depth, int AWidth, int AHeight)
{
  glGenRenderbuffers(1, ARenderBuffer_Color);
  glBindRenderbuffer(GL_RENDERBUFFER, *ARenderBuffer_Color);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB8, AWidth, AHeight);

  //glGenRenderbuffers(1, ARenderBuffer_Depth);
  //glBindRenderbuffer(GL_RENDERBUFFER, *ARenderBuffer_Depth);
  //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, AWidth, AHeight);

  glGenFramebuffers(1, AFrameBufferObject);
  glBindFramebuffer(GL_FRAMEBUFFER, *AFrameBufferObject);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, *ARenderBuffer_Color);
  //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *ARenderBuffer_Depth);

  GLenum BCheck = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (BCheck != GL_FRAMEBUFFER_COMPLETE)
  {
    printf("[ERROR] There is a problem with the Framebuffer Object.\n");
  };

  if (!glIsRenderbuffer(*ARenderBuffer_Color))
  {
    printf("[ERROR] There is a problem with the color render.\n");
  };
};

void GUI_ChangeFBO(GLuint *AFrameBufferObject, GLuint *ARenderBuffer_Color, GLuint *ARenderBuffer_Depth, int AWidth, int AHeight)
{
  glDeleteFramebuffers(1, AFrameBufferObject);
  glDeleteRenderbuffers(1, ARenderBuffer_Color);
  //glDeleteRenderbuffers(1, ARenderBuffer_Depth);
  if (AWidth <= 0)
  {
    AWidth = 1;
  };
  if (AHeight <= 0)
  {
    AHeight = 1;
  };
  GUI_AllocFBO(AFrameBufferObject, ARenderBuffer_Color, ARenderBuffer_Depth, AWidth, AHeight);
};

TGUIWidget *GUI_Create_Widget(TGUIWindow *AWindow, char *AWidgetClass, const char *AWidgetName)
{
  TGUIWidget *BWidget = (TGUIWidget *)malloc(sizeof(TGUIWidget));
  TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)malloc(sizeof(TGUIWidgetProperties));
  BWidget->FWindow = AWindow;
  BWidget->FName = Alloc_String(AWidgetName);
  BWidget->FClass = Alloc_String(AWidgetClass);
  BWidget->FParent = NULL;
  
  Iterator_AddPointer(AWindow->FListWidget, BWidget);
  
  BWidget->FDraw = NULL;
  BWidget->FMouseDown = NULL;
  BWidget->FMouseUp = NULL;
  BWidget->FMouseMove = NULL;
  BWidget->FMouseEnter = NULL;
  BWidget->FMouseLeave = NULL;
  BWidget->FKey = NULL;
  
  BWidget->FListProperty = Alloc_Iterator(NULL);
  BWidget->FListChild = Alloc_Iterator(NULL);
  
  Widget_AddPointer(BWidget, "prop", BWidgetProperties);
  BWidgetProperties->FLeft = 0;
  BWidgetProperties->FTop = 0;
  BWidgetProperties->FWidth = 32;
  BWidgetProperties->FHeight = 32;
  
  BWidgetProperties->FLeft = FALSE;
  BWidgetProperties->FLeftWidget = NULL;
  BWidgetProperties->FLeftSide = LEFT;
  BWidgetProperties->FLeftSpacing = 0;
  
  BWidgetProperties->FRightAlign = FALSE;
  BWidgetProperties->FRightWidget = NULL;
  BWidgetProperties->FRightSide = LEFT;
  BWidgetProperties->FRightSpacing = 0;
  
  BWidgetProperties->FTopAlign = FALSE;
  BWidgetProperties->FTopWidget = NULL;
  BWidgetProperties->FTopSide = LEFT;
  BWidgetProperties->FTopSpacing = 0;
  
  BWidgetProperties->FBottomAlign = FALSE;
  BWidgetProperties->FBottomWidget = NULL;
  BWidgetProperties->FBottomSide = LEFT;
  BWidgetProperties->FBottomSpacing = 0;
  
  BWidgetProperties->FVisible = TRUE;
  BWidgetProperties->FEnabled = TRUE;
  BWidgetProperties->FCanFocus = TRUE;
  
  BWidget->FFrameBufferObject = 0;
  BWidget->FRenderBuffer_Color = 0;
  BWidget->FRenderBuffer_Depth = 0;
  GUI_AllocFBO(&BWidget->FFrameBufferObject,
               &BWidget->FRenderBuffer_Color,
               &BWidget->FRenderBuffer_Depth,
               BWidgetProperties->FWidth,
               BWidgetProperties->FHeight);

  // BEGIN - Call class allocation function.
  // To-do:
  // Create the class manager. Find the function based on the name of the class.
  // END - Call class allocation function.

  //printf("[MESSAGE] Widget of class \"%s\" created.\n", BWidget->FClass->FPointer);
  return BWidget;
};

TGUIWindow *GUI_Create_Window(const char *ATitle, int APosX, int APosY, int AWidth, int AHeight, bboolean AFullScreen)
{
  TGUIWindow *BWindow = NULL;
  BWindow = (TGUIWindow *)malloc(sizeof(TGUIWindow));
  GLFWmonitor *BMonitor;
  
  BWindow->FRunning = FALSE;
  BWindow->FListClientWidget = Alloc_Iterator(NULL);
  BWindow->FListWidget = Alloc_Iterator(NULL);
  BWindow->FWidgetMouseOver = NULL;
  BWindow->FMouseDown = FALSE;
  BWindow->FWidgetMouseDown = NULL;
  
  if (BWindow)
  {
    if (AFullScreen)
    {
      BWindow->FGLFW_Window = glfwCreateWindow(AWidth, AHeight, ATitle, glfwGetPrimaryMonitor(), NULL);
    } else
    {
      BWindow->FGLFW_Window = glfwCreateWindow(AWidth, AHeight, ATitle, NULL, NULL);
    };
    
    BMonitor = glfwGetWindowMonitor(BWindow->FGLFW_Window);
    if (!BMonitor)
    {
      BMonitor = glfwGetPrimaryMonitor();
    };
    
    const GLFWvidmode *BVideoMode = glfwGetVideoMode(BMonitor);
    glfwSetWindowPos(BWindow->FGLFW_Window, (BVideoMode->width / 2) - (AWidth / 2), 
                                            (BVideoMode->height / 2) - (AHeight / 2));
    glfwSetWindowUserPointer(BWindow->FGLFW_Window, BWindow);
    glfwMakeContextCurrent(BWindow->FGLFW_Window);
    
    char* l = setlocale(LC_ALL, ""); // or "pt_BR.UTF-8"
    if (l == NULL)
    {
      printf("[ERROR] Locale not set.\n");
    } else {
      printf("[MESSAGE] Locale set to %s.\n", l);
    };

    BWindow->FFont = Alloc_GUIFont("Serif", 12, 20);
    
    glfwSetCursorPosCallback(BWindow->FGLFW_Window, Window_Callback_MousePosition);
    glfwSetKeyCallback(BWindow->FGLFW_Window, Window_Callback_Key);
    glfwSetMouseButtonCallback(BWindow->FGLFW_Window, Window_Callback_MouseButton);
    glfwSetCursorEnterCallback(BWindow->FGLFW_Window, Window_Callback_MouseEnter);
    glfwSetFramebufferSizeCallback(BWindow->FGLFW_Window, Window_Callback_Size);
    
    GUI_AllocFBO(&BWindow->FFrameBufferObject, &BWindow->FRenderBuffer_Color, NULL, AWidth, AHeight);
  } else
  {
    printf("[ERROR] Failed to create window.\n");
    exit(1);
  };
  
  return BWindow;
};