#include <GLFW/glfw3.h>
#include <stdio.h>
#include <basicutils.h>
#include "GUI.h"
#include "GUI_box.h"
#include "GUI_button.h"
#include "GUI_tabset.h"
#include "GUI_treeview.h"
#include "GUI_checkbox.h"
#include "GUI_scrollbar.h"

int main( int argc, char* args[])
{
  TGUIWidgetProperties *BWidgetProperties = NULL;

  Initialize();
  TGUIWindow *BWindow = NULL;
  TGUIWidget *BWidgetClient = NULL;
  TGUIWidget *BWidgetButton = NULL;
  TGUIWidget *BWidgetCheckBox = NULL;
  TGUIWidget *BWidgetTabset = NULL;
  TGUIWidget *BWidgetTreeview = NULL;
  TGUIWidget *BWidgetScrollbar = NULL;
  BWindow = GUI_Create_Window("Title", 0, 0, 320, 240, FALSE);
  
  // BEGIN - Create the client widget.
  BWidgetClient = GUI_Create_Widget(BWindow, "box", "FClientBox");  
  Alloc_GUIBox(BWidgetClient);
  BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetClient, "prop");
  BWidgetProperties->FLeft = 0;
  BWidgetProperties->FTop = 0;
  BWidgetProperties->FWidth = 320;
  BWidgetProperties->FHeight = 240;
  BWidgetProperties->FLeftAlign = TRUE;
  BWidgetProperties->FLeftSide = LEFT;
  BWidgetProperties->FLeftWidget = NULL;
  BWidgetProperties->FLeftSpacing = 0;
  BWidgetProperties->FTopAlign = TRUE;
  BWidgetProperties->FTopSide = TOP;
  BWidgetProperties->FTopWidget = NULL;
  BWidgetProperties->FTopSpacing = 0;
  BWidgetProperties->FRightAlign = TRUE;
  BWidgetProperties->FRightSide = RIGHT;
  BWidgetProperties->FRightWidget = NULL;
  BWidgetProperties->FRightSpacing = 0;
  BWidgetProperties->FBottomAlign = TRUE;
  BWidgetProperties->FBottomSide = BOTTOM;
  BWidgetProperties->FBottomWidget = NULL;
  BWidgetProperties->FBottomSpacing = 0;
  Window_AddClientWidget(BWindow, BWidgetClient);
  // END - Create the client widget.
  
  // BEGIN - Create the button widget.
  BWidgetButton = GUI_Create_Widget(BWindow, "button", "FButton");  
  Alloc_GUIButton(BWidgetButton);
  BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetButton, "prop");
  BWidgetProperties->FLeft = 8;
  BWidgetProperties->FTop = 32;
  BWidgetProperties->FWidth = 96;
  BWidgetProperties->FHeight = 24;
  Widget_AddChild(BWidgetClient, BWidgetButton);
  // END - Create the button widget.
  
  // BEGIN - Create the tabset widget.
  BWidgetTabset = GUI_Create_Widget(BWindow, "tabset", "FTabset");  
  Alloc_GUITabset(BWidgetTabset);
  BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetTabset, "prop");
  BWidgetProperties->FLeft = 0;
  BWidgetProperties->FTop = 0;
  BWidgetProperties->FWidth = 320;
  BWidgetProperties->FHeight = 24;
  Widget_AddChild(BWidgetClient, BWidgetTabset);
  
  GUITabset_AddTab(BWidgetTabset, "Tab0");
  GUITabset_AddTab(BWidgetTabset, "Label for Tab1");
  // END - Create the tabset widget.
  
  if (BWindow)
  {
    RunWindow(BWindow);
  };
  return 0;
};
