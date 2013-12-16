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
#include "GUI_widget.h"
#include "GUI_theme.h"
#include "GUI_treeview.h"

void GUITreeview_DrawItem(TGUIWidget *AWidget, TIterator *AIterator, int ALevel, int *AIteratorYPosition, int AWidth, int AHeight, int AScreenXPosition, int AScreenYPosition)
{
  TIterator *BChild = AIterator->FFirstChild;
  
  while (BChild)
  {
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glBegin(GL_QUADS);
      glVertex3f((ALevel * 16) + AWidth - 1.0 - AScreenXPosition, *AIteratorYPosition + 16.0 - 1.0 - AScreenYPosition, 0.0);
      glVertex3f((ALevel * 16) + 1.0 - AScreenXPosition, *AIteratorYPosition + 16.0 - 1.0 - AScreenYPosition, 0.0);
      glVertex3f((ALevel * 16) + 1.0 - AScreenXPosition, *AIteratorYPosition + 1.0 - AScreenYPosition, 0.0);
      glVertex3f((ALevel * 16) + AWidth - 1.0 - AScreenXPosition, *AIteratorYPosition + 1.0 - AScreenYPosition, 0.0);
    glEnd();
    // To-do:
    // Call here te node drawing function.
    *AIteratorYPosition = *AIteratorYPosition + 16;
    
    if (BChild->FFirstChild)
    {
      // Draw the childs of BChild.
      GUITreeview_DrawItem(AWidget, BChild, ALevel + 1, AIteratorYPosition, AWidth, AHeight, AScreenXPosition, AScreenYPosition);
    };
    
    BChild = BChild->FNext;
  };
};

void GUITreeview_Draw(TGUIWidget *AWidget)
{
  int BWidth = Widget_GetInt(AWidget, "w");
  int BHeight = Widget_GetInt(AWidget, "h");
  int BIteratorYPosition = 0;
  TIterator *BTree = Widget_GetPointer(AWidget, "tree");
  // BEGIN - Draw background.
  // END - Draw background.
  
  glColor4f(0.3, 0.3, 0.3, 1.0);
  glTranslatef(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
    glVertex3f(BWidth, BHeight, 0.0);
    glVertex3f(0.0, BHeight, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(BWidth, 0.0, 0.0);
  glEnd();
  
  // BEGIN - Draw items.
  // Draw the children of BTree.
  GUITreeview_DrawItem(AWidget, BTree, 0, &BIteratorYPosition, BWidth, BHeight, 0, 0);
  
  // END - Draw items.
  // BEGIN - Draw the background and the borders.
};

void Alloc_GUITreeview(TGUIWidget *AWidget)
{
  Alloc_GUIWidget(AWidget);
  
  TIterator *BTree = Alloc_Iterator(NULL);
  Widget_AddPointer(AWidget, "tree", BTree);
  Widget_AddInt(AWidget, "posx", 0);
  Widget_AddInt(AWidget, "posy", 0);
  
  TIterator *BItemA = Alloc_Iterator(NULL);
  Iterator_Add(BTree, BItemA);
  TIterator *BItemB = Alloc_Iterator(NULL);
  Iterator_Add(BTree, BItemB);
  TIterator *BItemC = Alloc_Iterator(NULL);
  Iterator_Add(BTree, BItemC);
  TIterator *BItemD = Alloc_Iterator(NULL);
  Iterator_Add(BTree, BItemD);
  TIterator *BItemE = Alloc_Iterator(NULL);
  Iterator_Add(BTree, BItemE);
  
  TIterator *BItemBA = Alloc_Iterator(NULL);
  Iterator_Add(BItemB, BItemBA);
  TIterator *BItemBB = Alloc_Iterator(NULL);
  Iterator_Add(BItemB, BItemBB);
  TIterator *BItemBC = Alloc_Iterator(NULL);
  Iterator_Add(BItemB, BItemBC);
  
  TIterator *BItemCA = Alloc_Iterator(NULL);
  Iterator_Add(BItemC, BItemCA);
  
  
  AWidget->FDraw = &GUITreeview_Draw;  
};

