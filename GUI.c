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
#include "GUI_draw.h"
#include "GUI_font.h"
#include "GUI_theme.h"

#define GUI_DEBUG_MODE
#define GUI_DEEP_DEBUG_MODE

GLuint FCurrentTexture;

void Widget_AddSignal(TGUIWidget *AWidget, unsigned char *ASignalName)
{
  Add_Pointer(AWidget->FListSignal, ASignalName, NULL);
};

void * Widget_GetSignal(TGUIWidget *AWidget, unsigned char *ASignalName)
{
  return Get_Pointer(AWidget->FListSignal, ASignalName);
};

void Widget_SetSignal(TGUIWidget *AWidget, unsigned char *ASignalName, void *AFunctionReference)
{
   Set_Pointer(AWidget->FListSignal, ASignalName, AFunctionReference);
};

void Widget_AddBool(TGUIWidget *AWidget, unsigned char *APropertyName, const bboolean AValue)
{
  Add_Bool(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_AddInt(TGUIWidget *AWidget, unsigned char *APropertyName, const int AValue)
{
  Add_Integer(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_AddString(TGUIWidget *AWidget, unsigned char *APropertyName, unsigned char *AValue)
{
  Add_String(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_AddChar(TGUIWidget *AWidget, unsigned char *APropertyName, const char AValue)
{
  Add_Char(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_AddDouble(TGUIWidget *AWidget, unsigned char *APropertyName, const double AValue)
{
  Add_Double(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_AddFloat(TGUIWidget *AWidget, unsigned char *APropertyName, const float AValue)
{
  Add_Float(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_AddPointer(TGUIWidget *AWidget, unsigned char *APropertyName, void *AValue)
{
  Add_Pointer(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_SetBool(TGUIWidget *AWidget, unsigned char *APropertyName, const bboolean AValue)
{
  Set_Bool(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_SetInt(TGUIWidget *AWidget, unsigned char *APropertyName, const int AValue)
{
  Set_Integer(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_SetString(TGUIWidget *AWidget, unsigned char *APropertyName, unsigned char *AValue)
{
  Set_String(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_SetChar(TGUIWidget *AWidget, unsigned char *APropertyName, const char AValue)
{
  Set_Char(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_SetDouble(TGUIWidget *AWidget, unsigned char *APropertyName, const double AValue)
{
  Set_Double(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_SetFloat(TGUIWidget *AWidget, unsigned char *APropertyName, const float AValue)
{
  Set_Float(AWidget->FListProperty, APropertyName, AValue);
};

void Widget_SetPointer(TGUIWidget *AWidget, unsigned char *APropertyName, void *AValue)
{
  Set_Pointer(AWidget->FListProperty, APropertyName, AValue);
};

bboolean Widget_GetBool(TGUIWidget *AWidget, unsigned char *APropertyName)
{
  return Get_Bool(AWidget->FListProperty, APropertyName);
};

int Widget_GetInt(TGUIWidget *AWidget, unsigned char *APropertyName)
{
  return Get_Integer(AWidget->FListProperty, APropertyName);
};

char * Widget_GetString(TGUIWidget *AWidget, unsigned char *APropertyName)
{
  return Get_String(AWidget->FListProperty, APropertyName);
};

char Widget_GetChar(TGUIWidget *AWidget, unsigned char *APropertyName)
{
  return Get_Char(AWidget->FListProperty, APropertyName);
};

double Widget_GetDouble(TGUIWidget *AWidget, unsigned char *APropertyName)
{
  return Get_Double(AWidget->FListProperty, APropertyName);
};

float Widget_GetFloat(TGUIWidget *AWidget, unsigned char *APropertyName)
{
  return Get_Float(AWidget->FListProperty, APropertyName);
};

void *Widget_GetPointer(TGUIWidget *AWidget, unsigned char *APropertyName)
{
  return Get_Pointer(AWidget->FListProperty, APropertyName);
};

void *Widget_GetRef(TGUIWidget *AWidget, unsigned char *APropertyName)
{
  return Get_Reference(AWidget->FListProperty, APropertyName);
};

int Initialize()
{
  #ifdef GUI_DEBUG_MODE
  if (glfwInit())
  {
    printf("[MESSAGE] GLFW initialized.\n");
  } else
  {
    printf("[ERROR] Fail to initialize GLFW.");
    exit(1);
  };
  #else
  glfwInit();
  #endif
  return TRUE;
};

bboolean Widget_HasChild(TGUIWidget *AWidgetParent, TGUIWidget *AWidgetChild)
{
  TIterator *BIteratorWidget = AWidgetParent->FListChild->FFirstChild;
  bboolean BResult = FALSE;
  
  while (BIteratorWidget)
  {
    if (AWidgetChild == BIteratorWidget->FPointer)
    {
      BResult = TRUE;
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

void Widget_AddChild(TGUIWidget *AWidgetParent, TGUIWidget *AWidgetChild)
{
  if (!Widget_HasChild(AWidgetParent, AWidgetChild))
  {
    #ifdef GUI_DEBUG_MODE
    printf("[MESSAGE] Setting widget \"%s\" as child of widget \"%s\".\n", AWidgetChild->FName->FPointer, AWidgetParent->FName->FPointer);
    #endif
    Iterator_AddPointer(AWidgetParent->FListChild, AWidgetChild);
    AWidgetChild->FParent = AWidgetParent;
  };
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
      #ifdef GUI_DEBUG_MODE
      printf("[MESSAGE] Widget \"%s\" found.\n", BWidget->FName->FPointer);
      #endif
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
  
  if ((BWidgetProperties->FVisible) &&
  (AX > BWidgetProperties->FGlobalRect.FLeft) &&
  (AX <= BWidgetProperties->FGlobalRect.FRight) &&
  (AY > BWidgetProperties->FGlobalRect.FTop) &&
  (AY <= BWidgetProperties->FGlobalRect.FBottom))
  {
    BResultWidget = AWidget;
    BIteratorWidget = AWidget->FListChild->FLastChild;
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
      BIteratorWidget = BIteratorWidget->FPrevious;
    };
  };
  return BResultWidget;
};

void Window_SetFullscreen(TGUIWindow *AWindow, bboolean AFullScreen)
{
  glfwDestroyWindow(AWindow->FGLFW_Window);
  AWindow->FGLFW_Window = GUI_Create_GLFWWindow(AWindow->FTitle, AWindow->FPosX, AWindow->FPosY, AWindow->FWidth, AWindow->FHeight, AFullScreen);
  glfwSetWindowUserPointer(AWindow->FGLFW_Window, AWindow);
};

TGUIWidget * Window_GetWidget(TGUIWindow *AWindow, unsigned char *AWidgetName)
{
  TIterator *BIteratorWidget = NULL;
  TGUIWidget *BWidget = NULL;
  BIteratorWidget = AWindow->FListWidget->FFirstChild;
  #ifdef GUI_DEBUG_MODE
  printf("[MESSAGE] Searching for widget \"%s\".\n", AWidgetName);
  #endif
  while (BIteratorWidget)
  {
    BWidget = (TGUIWidget *)BIteratorWidget->FPointer;
    if (BWidget)
    {
      if (strcmp(BWidget->FName->FPointer, AWidgetName) == 0)
      {
        #ifdef GUI_DEBUG_MODE
        printf("[MESSAGE] Widget \"%s\" found.\n", BWidget->FName->FPointer);
        #endif
        break;
      };
    };
    BIteratorWidget = BIteratorWidget->FNext;
  };
  return BWidget;
};

void Widget_PaintDefault(TGUIWidget *AWidget)
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
  
  //glEnable(GL_TEXTURE_2D);
  
  glDisable(GL_SMOOTH);		// Enable (gouraud) shading
	glDisable(GL_DEPTH_TEST); 	// Disable depth testing
  //glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

	//glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do

	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

  glDisable(GL_LIGHTING);
  glEnable(GL_BLEND);		// Enable blending (used for alpha) and blending function to use
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
  //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

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

void Widget_Render(TGUIWidget *AWidget, TGUIWidgetProperties *AParentProperties, TGUIWidgetProperties *AWidgetProperties)
{
  TIterator *BIteratorChild = NULL;
  TGUIWidget *BChild = NULL;
  TGUIWidgetProperties *BChildProperties = NULL;
  TRect BParentRect = {0, 0, 0, 0};
  if (AParentProperties)
  {
    BParentRect.FLeft = AParentProperties->FDestinationRect.FLeft;
    BParentRect.FRight = AParentProperties->FDestinationRect.FRight;
    BParentRect.FTop = AParentProperties->FDestinationRect.FTop;
    BParentRect.FBottom = AParentProperties->FDestinationRect.FBottom;
  } else
  {
    BParentRect.FLeft = 0;
    BParentRect.FTop = 0;
    BParentRect.FRight = AWidget->FWindow->FWidth;
    BParentRect.FBottom = AWidget->FWindow->FHeight;
  };
  AWidgetProperties->FDestinationRect = GetIntersection(&AWidgetProperties->FGlobalRect, &BParentRect);
  
  if ((AWidgetProperties->FVisible) &&
  (AWidgetProperties->FDestinationRect.FLeft < AWidgetProperties->FDestinationRect.FRight) &&
  (AWidgetProperties->FDestinationRect.FTop < AWidgetProperties->FDestinationRect.FBottom))
  {
    glEnable(GL_SCISSOR_TEST);
    //glScissor(BRectDestination.FLeft, BRectDestination.FTop, BRectDestination.FRight - BRectDestination.FLeft, BRectDestination.FBottom -BRectDestination.FTop);
    glScissor(AWidgetProperties->FDestinationRect.FLeft, AWidget->FWindow->FHeight - AWidgetProperties->FDestinationRect.FTop - (AWidgetProperties->FDestinationRect.FBottom - AWidgetProperties->FDestinationRect.FTop), AWidgetProperties->FDestinationRect.FRight - AWidgetProperties->FDestinationRect.FLeft, AWidgetProperties->FDestinationRect.FBottom - AWidgetProperties->FDestinationRect.FTop);
    glPushMatrix();
    glTranslatef(AWidgetProperties->FGlobalRect.FLeft, AWidgetProperties->FGlobalRect.FTop, 0.0f);
    //glViewport(BRectDestination.FLeft, AWidget->FWindow->FHeight - BRectDestination.FTop, BRectDestination.FRight, AWidget->FWindow->FHeight - BRectDestination.FBottom);
    //glOrtho(0, AWidget->FWindow->FWidth, 0, AWidget->FWindow->FHeight, -1.0f, 1.0f);
    //glTranslatef(BRectDestination.FLeft, BRectDestination.FTop, 0.0f);
    if (AWidget->FDraw)
    {
      AWidget->FDraw(AWidget);
    } else
    {
      Widget_PaintDefault(AWidget);
    };
    glPopMatrix();
    glDisable(GL_SCISSOR_TEST);
    
    BIteratorChild = AWidget->FListChild->FFirstChild;
    while (BIteratorChild)
    {
      BChild = (TGUIWidget *)BIteratorChild->FPointer;
      if (BChild)
      {
        BChildProperties = (TGUIWidgetProperties *)Widget_GetPointer(BChild, "prop");
        Widget_Render(BChild, AWidgetProperties, BChildProperties);
      };
      BIteratorChild = BIteratorChild->FNext;
    };
  };
};

void Widget_ResolveAlignment(TGUIWidget *AWidget, TGUIWidgetProperties *AWidgetProperties)
{
  TGUIWidgetProperties *BWidgetToAttachAlignment = NULL;
  int BReferenceLeft = 0;
  int BReferenceTop = 0;
  int BReferenceWidth = 0;
  int BReferenceHeight = 0;
  int BPreviousLeft = AWidgetProperties->FLeft;
  int BPreviousTop = AWidgetProperties->FTop;
  int BPreviousWidth = AWidgetProperties->FWidth;
  int BPreviousHeight = AWidgetProperties->FHeight;
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
        BReferenceLeft = 0;
        BReferenceWidth = BWidgetToAttachAlignment->FWidth;
      } else
      {
        BReferenceLeft = 0;
        BReferenceWidth = AWidget->FWindow->FWidth;
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
        BReferenceLeft = 0;
        BReferenceWidth = BWidgetToAttachAlignment->FWidth;
      } else
      {
        BReferenceLeft = 0;
        BReferenceWidth = AWidget->FWindow->FWidth;
      };
    };
    if (AWidgetProperties->FRightSide == LEFT)
    {
      if (AWidgetProperties->FLeftAlign)
      {
        AWidgetProperties->FWidth = BReferenceLeft - AWidgetProperties->FLeft + AWidgetProperties->FRightSpacing;
      } else
      {
        AWidgetProperties->FLeft = ((BReferenceLeft) - AWidgetProperties->FRightSpacing) - (AWidgetProperties->FWidth);
      };
    } else
    {
      if (AWidgetProperties->FLeftAlign)
      {
        AWidgetProperties->FWidth = (BReferenceLeft + BReferenceWidth) - AWidgetProperties->FLeft + AWidgetProperties->FRightSpacing;
      } else
      {
        AWidgetProperties->FLeft = ((BReferenceLeft + BReferenceWidth) + AWidgetProperties->FRightSpacing) - (AWidgetProperties->FWidth);
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
        BReferenceTop = 0;
        BReferenceHeight = BWidgetToAttachAlignment->FHeight;
      } else
      {
        BReferenceTop = 0;
        BReferenceHeight = AWidget->FWindow->FHeight;
      };
    };
    if (AWidgetProperties->FTopSide == TOP)
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
        BReferenceTop = 0;
        BReferenceHeight = BWidgetToAttachAlignment->FHeight;
      } else
      {
        BReferenceTop = 0;
        BReferenceHeight = AWidget->FWindow->FHeight;
      };
    };
    if (AWidgetProperties->FBottomSide == TOP)
    {
      if (AWidgetProperties->FTopAlign)
      {
        AWidgetProperties->FHeight = BReferenceTop - AWidgetProperties->FTop + AWidgetProperties->FBottomSpacing;
      } else
      {
        AWidgetProperties->FTop = ((BReferenceTop) - AWidgetProperties->FBottomSpacing) - (AWidgetProperties->FHeight);
      };
    } else
    {
      if (AWidgetProperties->FTopAlign)
      {
        AWidgetProperties->FHeight = (BReferenceTop + BReferenceHeight) - AWidgetProperties->FTop + AWidgetProperties->FBottomSpacing;
      } else
      {
        AWidgetProperties->FTop = ((BReferenceTop + BReferenceHeight) + AWidgetProperties->FBottomSpacing) - (AWidgetProperties->FHeight);
      };
    };
  };
  // END - Resolve the bottom alignment.
  
  TRect BPreviousGlobalRect = {0, 0, 0, 0};
  BPreviousGlobalRect.FLeft = AWidgetProperties->FGlobalRect.FLeft;
  BPreviousGlobalRect.FTop = AWidgetProperties->FGlobalRect.FTop;
  BPreviousGlobalRect.FRight = AWidgetProperties->FGlobalRect.FRight;
  BPreviousGlobalRect.FBottom = AWidgetProperties->FGlobalRect.FBottom;
  
  AWidgetProperties->FGlobalRect.FLeft = GetWidgetGlobalLeft(AWidget);
  AWidgetProperties->FGlobalRect.FTop = GetWidgetGlobalTop(AWidget);
  AWidgetProperties->FGlobalRect.FRight = AWidgetProperties->FGlobalRect.FLeft + AWidgetProperties->FWidth;
  AWidgetProperties->FGlobalRect.FBottom = AWidgetProperties->FGlobalRect.FTop + AWidgetProperties->FHeight;
  
  if ((AWidget->FResize) &&
  ((BPreviousGlobalRect.FLeft != AWidgetProperties->FGlobalRect.FLeft) ||
   (BPreviousGlobalRect.FTop != AWidgetProperties->FGlobalRect.FTop) ||
   (BPreviousGlobalRect.FRight != AWidgetProperties->FGlobalRect.FRight) ||
   (BPreviousGlobalRect.FBottom != AWidgetProperties->FGlobalRect.FBottom)) ||
   (BPreviousLeft != AWidgetProperties->FLeft) ||
   (BPreviousTop != AWidgetProperties->FTop) ||
   (BPreviousWidth != AWidgetProperties->FWidth) ||
   (BPreviousHeight != AWidgetProperties->FHeight))
  {
    AWidget->FResize(AWidget, AWidgetProperties->FWidth, AWidgetProperties->FHeight);
  };
};

void Nested_ResolveAlignment(TGUIWidget *AWidget)
{
  TIterator *BIteratorWidget = NULL;
  TGUIWidget *BWidget = NULL;
  
  // BEGIN - Resolve alignment.
  Widget_ResolveAlignment(AWidget, (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop"));
  // END - Resolve alignment.
  
  BIteratorWidget = AWidget->FListChild->FFirstChild;
  while (BIteratorWidget)
  {
    BWidget = (TGUIWidget *)BIteratorWidget->FPointer;
    if (BWidget)
    {
      Nested_ResolveAlignment(BWidget);
    };
    BIteratorWidget = BIteratorWidget->FNext;
  };
};

void Widget_Invalidate(TGUIWidget *AWidget)
{
  TGUIWidgetProperties *BParentProperties = NULL;
  TGUIWidgetProperties *BWidgetProperties = NULL;
  
  #ifdef GUI_DEBUG_MODE
  printf("[MESSAGE] Widget \"%s\" invalidated.\n", AWidget->FName->FPointer);
  #endif
  if (AWidget->FParent)
  {
    BParentProperties = Widget_GetPointer(AWidget->FParent, "prop");
  };
  BWidgetProperties = Widget_GetPointer(AWidget, "prop");
  Widget_Render(AWidget, BParentProperties, BWidgetProperties);
};

void Window_ResolveAlignment(TGUIWindow *AWindow)
{
  if (AWindow->FResolvingAlignment)
  {
    return;
  };
  AWindow->FResolvingAlignment = TRUE;
  TIterator *BIteratorWidget = NULL;
  TGUIWidget *BClientWidget = NULL;

  TGUIWidgetProperties *BWidgetProperties = NULL;
  BIteratorWidget = AWindow->FListClientWidget->FFirstChild;
  while (BIteratorWidget)
  {
    BClientWidget = (TGUIWidget *)BIteratorWidget->FPointer;
    if (BClientWidget)
    {
      BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BClientWidget, "prop");
      if (BWidgetProperties->FVisible)
      {
        Nested_ResolveAlignment(BClientWidget);
      };
    };
    BIteratorWidget = BIteratorWidget->FNext;
  };
  AWindow->FResolvingAlignment = FALSE;
};

void Window_Render(TGUIWindow *AWindow)
{
  TIterator *BIteratorWidget = NULL;
  TGUIWidget *BClientWidget = NULL;
  TGUIWidgetProperties *BWidgetProperties = NULL;
  glEnable2D(AWindow->FWidth, AWindow->FHeight, 0, AWindow->FWidth, AWindow->FHeight, 0);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glDrawBuffer(GL_COLOR_ATTACHMENT0);
  
  //glViewport(0, AWindow->FHeight, AWindow->FWidth, 0);
  //glOrtho(0, AWindow->FWidth, AWindow->FHeight, 0, -1, 1);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
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
        Widget_Render(BClientWidget, NULL, BWidgetProperties);
      };
    };
    BIteratorWidget = BIteratorWidget->FNext;
  };
  glFlush();
  glDisable2D();
  AWindow->FRenderingFrameRate++;
};

static void Window_Callback_MouseEnter(GLFWwindow* AWindow, int AEntered)
{
  TGUIWindow *BWindow = (TGUIWindow *)glfwGetWindowUserPointer(AWindow);
  if (AEntered)
  {
    #ifdef GUI_DEBUG_MODE
    printf("[MESSAGE] Mouse entered window.\n");
    #endif
    BWindow->FWidgetMouseOver = NULL;
  } else
  {
    if (BWindow->FWidgetMouseOver)
    {
      #ifdef GUI_DEBUG_MODE
      printf("[MESSAGE] Mouse leave \"%s\".\n", BWindow->FWidgetMouseOver->FName->FPointer);
      #endif
      if (BWindow->FWidgetMouseOver->FMouseLeave)
      {
        BWindow->FWidgetMouseOver->FMouseLeave(BWindow->FWidgetMouseOver);
      };
    };
    #ifdef GUI_DEBUG_MODE
    printf("[MESSAGE] Mouse leaved window.\n");
    #endif
    BWindow->FWidgetMouseOver = NULL;
  };
};

static void Window_Callback_Scroll(GLFWwindow* AWindow, double AXOffset, double AYOffset)
{
  TGUIWindow *BWindow = (TGUIWindow *)glfwGetWindowUserPointer(AWindow);
  
  if (BWindow->FWidgetMouseOver)
  {
    if (BWindow->FWidgetMouseOver->FScroll)
    {
      BWindow->FWidgetMouseOver->FScroll(BWindow->FWidgetMouseOver,  
                                         AXOffset,
                                         AYOffset);
    };
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
        #ifdef GUI_DEBUG_MODE
        printf("[MESSAGE] Mouse button down at widget \"%s\".\n", BWindow->FWidgetMouseOver->FName->FPointer);
        #endif
        BWindow->FWidgetMouseOver->FMouseDown(BWindow->FWidgetMouseOver,  
                                              AButton,
                                              BWindow->FMouseX - GetWidgetGlobalLeft(BWindow->FWidgetMouseOver),
                                              BWindow->FMouseY - GetWidgetGlobalTop(BWindow->FWidgetMouseOver));
      };
    };
  } else
  {
    if (BWindow->FWidgetMouseDown)
    {
      if (BWindow->FWidgetMouseDown->FMouseUp)
      {
        #ifdef GUI_DEBUG_MODE
        printf("[MESSAGE] Mouse button up for widget \"%s\".\n", BWindow->FWidgetMouseDown->FName->FPointer);
        #endif
        BWindow->FWidgetMouseDown->FMouseUp(BWindow->FWidgetMouseDown,
                                            AButton,
                                            BWindow->FMouseX - GetWidgetGlobalLeft(BWindow->FWidgetMouseDown),
                                            BWindow->FMouseY - GetWidgetGlobalTop(BWindow->FWidgetMouseDown));
      };
    };
    if (BWindow->FWidgetMouseOver)
    {
      if (BWindow->FWidgetMouseOver->FMouseUp)
      {
        #ifdef GUI_DEBUG_MODE
        printf("[MESSAGE] Mouse button up at widget \"%s\".\n", BWindow->FWidgetMouseOver->FName->FPointer);
        #endif
        BWindow->FWidgetMouseOver->FMouseUp(BWindow->FWidgetMouseOver,
                                            AButton,
                                            BWindow->FMouseX - GetWidgetGlobalLeft(BWindow->FWidgetMouseOver),
                                            BWindow->FMouseY - GetWidgetGlobalTop(BWindow->FWidgetMouseOver));
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
          #ifdef GUI_DEBUG_MODE
          printf("[MESSAGE] Mouse leave widget \"%s\".\n", BWindow->FWidgetMouseOver->FName->FPointer);
          #endif
          if (BWindow->FWidgetMouseOver->FMouseLeave)
          {
            BWindow->FWidgetMouseOver->FMouseLeave(BWindow->FWidgetMouseOver);
          };
        };
        if (BWidgetMouseOver)
        {
          #ifdef GUI_DEBUG_MODE
          printf("[MESSAGE] Mouse enter widget \"%s\".\n", BWidgetMouseOver->FName->FPointer);
          #endif
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
          #ifdef GUI_DEBUG_MODE
          printf("[MESSAGE] Mouse move for widget \"%s\" (%i, %i).\n", BWindow->FWidgetMouseDown->FName->FPointer, BWindow->FMouseX - GetWidgetGlobalLeft(BWindow->FWidgetMouseDown), BWindow->FMouseY - GetWidgetGlobalTop(BWindow->FWidgetMouseDown));
          #endif
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
            #ifdef GUI_DEBUG_MODE
            printf("[MESSAGE] Mouse move at widget \"%s\" (%i, %i).\n", BWidgetMouseOver->FName->FPointer, BWindow->FMouseX - GetWidgetGlobalLeft(BWindow->FWidgetMouseOver), BWindow->FMouseY - GetWidgetGlobalTop(BWindow->FWidgetMouseOver));
            #endif
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
    if (action)
    {
      if (BWindow->FWidgetFocused->FKeyDown)
      {
        #ifdef GUI_DEBUG_MODE
        printf("[MESSAGE] Key down at widget \"%s\".\n", BWindow->FWidgetFocused->FName->FPointer);
        #endif
        BWindow->FWidgetFocused->FKeyDown(BWindow->FWidgetFocused, key, scancode, mods);
      };
    } else
    {
      if (BWindow->FWidgetFocused->FKeyUp)
      {
        #ifdef GUI_DEBUG_MODE
        printf("[MESSAGE] Key up at widget \"%s\".\n", BWindow->FWidgetFocused->FName->FPointer);
        #endif
        BWindow->FWidgetFocused->FKeyUp(BWindow->FWidgetFocused, key, scancode, mods);
      };
    };
  };
};

static void Window_Callback_Pos(GLFWwindow* AWindow, int APosX, int APosY)
{
  TGUIWindow *BWindow = (TGUIWindow *)glfwGetWindowUserPointer(AWindow);
  #ifdef GUI_DEBUG_MODE
  printf("[MESSAGE] Window positioned at (%i, %i).\n", APosX, APosY);
  #endif
  BWindow->FPosX = APosX;
  BWindow->FPosY = APosY;
};

static void Window_Callback_Size(GLFWwindow* AWindow, int AWidth, int AHeight)
{
  TGUIWindow *BWindow = (TGUIWindow *)glfwGetWindowUserPointer(AWindow);
  #ifdef GUI_DEBUG_MODE
  printf("[MESSAGE] Window sized to %ix%i.\n", AWidth, AHeight);
  #endif
  BWindow->FWidth = AWidth;
  BWindow->FHeight = AHeight;
  
  Window_ResolveAlignment(BWindow);
};

int timespec_milliseconds(struct timespec *a) 
{
    return a->tv_sec*1000 + a->tv_nsec/1000000;
};

int time_diff(struct timespec *t1, struct timespec *t2 )
{
  return timespec_milliseconds(t1) - timespec_milliseconds(t2);
};

int Window_AddTimer(TGUIWindow *AWindow, TEventHandler_Timer AFunction, int AInterval)
{
  TGUITimerItem *BTimerItem = (TGUITimerItem *)malloc(sizeof(TGUITimerItem));
  BTimerItem->FID = 0/* GET AN UNIQUE ID*/;
  BTimerItem->FInterval = AInterval;
  BTimerItem->FCallbackFunction = AFunction;
  //Add_Pointer(AWindow->FListTimer, BTimerItem);
  
  return BTimerItem->FID;
};

void Window_Run(TGUIWindow *AWindow)
{
  TIterator *BIteratorWidget = NULL;
  TGUIWidget *BClientWidget = NULL;
  double BTime = glfwGetTime();
  unsigned int BFrames = 0;
  double BDiff = 0;
  
  struct timespec BRenderingClockLast;
  struct timespec BRenderingClockCurrent;
  clock_gettime(CLOCK_REALTIME, &BRenderingClockLast);

  TGUIWidgetProperties *BWidgetProperties = NULL;
  AWindow->FRunning = TRUE;
  glfwGetWindowSize(AWindow->FGLFW_Window, &AWindow->FWidth, &AWindow->FHeight);
  #ifdef GUI_DEBUG_MODE
  printf("[MESSAGE] Running window.\n");
  #endif

  Window_ResolveAlignment(AWindow);
  glfwShowWindow(AWindow->FGLFW_Window);
  // BEGIN - Window main loop.
  while (!glfwWindowShouldClose(AWindow->FGLFW_Window))
  {
    glfwPollEvents();
    // BEGIN - Resolve alignment.
    // History:
    // Now that the algnment function was refactored, it is called only when
    // the widget size really change. And is disabled to be called again
    // until the the window FResolvingAlignment is setted to FALSE. Before
    // this, the process performance was about 360000 to 400000 frames per
    // second, now it is about 780000 to 910000. 2x faster.
    //Window_ResolveAlignment(AWindow);
    // END - Resolve alignment.
    
    clock_gettime(CLOCK_REALTIME, &BRenderingClockCurrent);
    BDiff = time_diff(&BRenderingClockCurrent, &BRenderingClockLast);
    if (BDiff > 16.666666667)
    {
      clock_gettime(CLOCK_REALTIME, &BRenderingClockLast);
      Window_Render(AWindow);
      glfwSwapBuffers(AWindow->FGLFW_Window);
    };
    BFrames++;
    
    if (glfwGetTime() - BTime >= 1)
    {
      #ifdef GUI_DEBUG_MODE
      // If you comment the following condition, the frame-rate will be printed each second.
      if ((BFrames < 59) || (AWindow->FRenderingFrameRate < 59))
      {
        // This message is printed only if the frame-rate is bellow the normal.
        printf("[MESSAGE] Process frame-rate: %i frames per second.\n", BFrames);
        printf("[MESSAGE] Rendering frame-rate: %i frames per second.\n", AWindow->FRenderingFrameRate);
      };
      #endif
      AWindow->FRenderingFrameRate = 0;
      BFrames = 0;
      BTime = glfwGetTime();
    };
  };
  // END - Window main loop.
  #ifdef GUI_DEBUG_MODE
  printf("[MESSAGE] Finishing window.\n");
  #endif
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
  //glEnable2D(AWidth, AHeight, 0, AWidth, AHeight, 0);
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

TGUIWidget *GUI_Create_Widget(TGUIWindow *AWindow, unsigned char *AWidgetClass, unsigned char *AWidgetName)
{
  #ifdef GUI_DEBUG_MODE
  printf("[MESSAGE] Creating widget named \"%s\".\n", AWidgetName);
  #endif
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
  BWidget->FKeyDown = NULL;
  BWidget->FKeyUp = NULL;
  BWidget->FScroll = NULL;
  
  BWidget->FListProperty = Alloc_Iterator(NULL);
  BWidget->FListAbstractProperty = Alloc_Iterator(NULL);
  BWidget->FListChild = Alloc_Iterator(NULL);
  BWidget->FListSignal = Alloc_Iterator(NULL);
  
  Widget_AddPointer(BWidget, "prop", BWidgetProperties);
  BWidgetProperties->FLeft = 0;
  BWidgetProperties->FTop = 0;
  BWidgetProperties->FWidth = 32;
  BWidgetProperties->FHeight = 32;
  
  BWidgetProperties->FLeftAlign = FALSE;
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

  BWidgetProperties->FColor.FRed = 0.4;
  BWidgetProperties->FColor.FGreen = 0.4;
  BWidgetProperties->FColor.FBlue = 0.4;
  
  BWidgetProperties->FDown = FALSE;

  //BWidget->FFrameBufferObject = 0;
  //BWidget->FRenderBuffer_Color = 0;
  //BWidget->FRenderBuffer_Depth = 0;
  /*GUI_AllocFBO(&BWidget->FFrameBufferObject,
               &BWidget->FRenderBuffer_Color,
               &BWidget->FRenderBuffer_Depth,
               BWidgetProperties->FWidth,
               BWidgetProperties->FHeight);*/

  // BEGIN - Call class allocation function.
  // To-do:
  // Create the class manager. Find the function based on the name of the class.
  // END - Call class allocation function.
  return BWidget;
};

GLFWwindow *GUI_Create_GLFWWindow(const char *ATitle, int APosX, int APosY, int AWidth, int AHeight, bboolean AFullScreen)
{
  GLFWwindow *BGLFWWindow;
  GLFWmonitor *BMonitor;
  
  glfwWindowHint(GLFW_VISIBLE, FALSE);    
  if (AFullScreen)
  {
    BGLFWWindow = glfwCreateWindow(AWidth, AHeight, ATitle, glfwGetPrimaryMonitor(), NULL);
  } else
  {
    BGLFWWindow = glfwCreateWindow(AWidth, AHeight, ATitle, NULL, NULL);
  };
  
  BMonitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *BVideoMode = glfwGetVideoMode(BMonitor);
  glfwSetWindowPos(BGLFWWindow, APosX, APosY);
  glfwMakeContextCurrent(BGLFWWindow);
  glfwSetCursorPosCallback(BGLFWWindow, Window_Callback_MousePosition);
  glfwSetKeyCallback(BGLFWWindow, Window_Callback_Key);
  glfwSetScrollCallback(BGLFWWindow, Window_Callback_Scroll);
  glfwSetMouseButtonCallback(BGLFWWindow, Window_Callback_MouseButton);
  glfwSetWindowPosCallback(BGLFWWindow, Window_Callback_Pos);
  glfwSetCursorEnterCallback(BGLFWWindow, Window_Callback_MouseEnter);
  glfwSetFramebufferSizeCallback(BGLFWWindow, Window_Callback_Size);
  glfwSwapInterval(0);
  return BGLFWWindow;
};

TGUIWindow *GUI_Create_Window(const unsigned char *ATitle, int APosX, int APosY, int AWidth, int AHeight, bboolean AFullScreen)
{
  TGUIWindow *BWindow = NULL;
  BWindow = (TGUIWindow *)malloc(sizeof(TGUIWindow));
  GLFWmonitor *BMonitor;
  BWindow->FTitle = (unsigned char *)malloc(sizeof(unsigned char) * (strlen(ATitle) + 1));
  memset(BWindow->FTitle, 0, (strlen(ATitle)));
  //memcpy(BWindow->FTitle, ATitle, strlen(ATitle));
  BWindow->FRunning = FALSE;
  BWindow->FListClientWidget = Alloc_Iterator(NULL);
  BWindow->FListWidget = Alloc_Iterator(NULL);
  BWindow->FWidgetMouseOver = NULL;
  BWindow->FMouseDown = FALSE;
  BWindow->FWidgetMouseDown = NULL;
  BWindow->FWidgetFocused = NULL;
  BWindow->FResolvingAlignment = FALSE;
  
  if (BWindow)
  {
    BWindow->FGLFW_Window = GUI_Create_GLFWWindow(ATitle, APosX, APosY, AWidth, AHeight, AFullScreen);
    glfwSetWindowUserPointer(BWindow->FGLFW_Window, BWindow);
    
    BWindow->FVideoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    char* l = setlocale(LC_ALL, ""); // or "pt_BR.UTF-8"
    if (l == NULL)
    {
      printf("[ERROR] Locale not set.\n");
    } else {
      printf("[MESSAGE] Locale set to %s.\n", l);
    };
    BWindow->FFont = Alloc_GUIFont("Serif", 12);
  };
  return BWindow;
};