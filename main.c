#include <GLFW/glfw3.h>
#include <stdio.h>
#include <basicutils.h>
#include "GUI.h"
#include "GUI_box.h"
#include "GUI_entry.h"
#include "GUI_button.h"
#include "GUI_tabset.h"
#include "GUI_notebook.h"
#include "GUI_treeview.h"
#include "GUI_checkbox.h"
#include "GUI_scrollbar.h"

void Tabset_OnTabChange(TGUIWidget *AWidget)
{
  TGUITabsetProperties *BTabsetProperties = (TGUITabsetProperties *)Widget_GetPointer(AWidget, "tabset");
  TGUIWidget *BNotebook = Window_GetWidget(AWidget->FWindow, "FNotebook");
  
  if (BNotebook)
  {
    GUINotebook_SetActivePage(BNotebook, BTabsetProperties->FActiveTab);
  };
};

void Button_OnClick(TGUIWidget *AWidget)
{
  //TGUIWidgetProperties *BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(AWidget, "prop");
  //BWidgetProperties->FVisible = FALSE;
  //Window_SetFullscreen(AWidget->FWindow, TRUE);
  TGUIWidget *BTabset = Window_GetWidget(AWidget->FWindow, "FTabset");
  
  if (BTabset)
  {
    GUITabset_SetActiveTab(BTabset, 1);
  };
};

int main( int argc, char* args[])
{
  TGUIWidgetProperties *BWidgetProperties = NULL;

  Initialize();
  TGUIWindow *BWindow = NULL;
  TGUIWidget *BWidgetClient = NULL;
  TGUIWidget *BWidgetBox = NULL;
  TGUIWidget *BWidgetButton = NULL;
  TGUIWidget *BWidgetEntry  = NULL;
  TGUIWidget *BWidgetNotebook = NULL;
  TGUIWidget *BWidgetPage = NULL;
  TGUIWidget *BWidgetCheckBox = NULL;
  TGUIWidget *BWidgetTabset = NULL;
  TGUIWidget *BWidgetTreeview = NULL;
  TGUIWidget *BWidgetScrollbar = NULL;
  BWindow = GUI_Create_Window("Title", 400, 0, 640, 480, FALSE);
  
  // BEGIN - Create the client widget.
  BWidgetClient = GUI_Create_Widget(BWindow, "box", "FClientBox");  
  Alloc_GUIBox(BWidgetClient);
  BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetClient, "prop");
  BWidgetProperties->FLeft = 0;
  BWidgetProperties->FTop = 0;
  BWidgetProperties->FWidth = 640;
  BWidgetProperties->FHeight = 480;
  BWidgetProperties->FLeftAlign = TRUE;
  BWidgetProperties->FLeftSide = LEFT;
  BWidgetProperties->FLeftWidget = NULL;
  BWidgetProperties->FLeftSpacing = 16;
  BWidgetProperties->FTopAlign = TRUE;
  BWidgetProperties->FTopSide = TOP;
  BWidgetProperties->FTopWidget = NULL;
  BWidgetProperties->FTopSpacing = 16;
  BWidgetProperties->FRightAlign = TRUE;
  BWidgetProperties->FRightSide = RIGHT;
  BWidgetProperties->FRightWidget = NULL;
  BWidgetProperties->FRightSpacing = -16;
  BWidgetProperties->FBottomAlign = TRUE;
  BWidgetProperties->FBottomSide = BOTTOM;
  BWidgetProperties->FBottomWidget = NULL;
  BWidgetProperties->FBottomSpacing = -16;
  Window_AddClientWidget(BWindow, BWidgetClient);
  // END - Create the client widget.
  
  // BEGIN - Create the button widget.
  BWidgetBox = GUI_Create_Widget(BWindow, "box", "FNotebookBox");  
  Alloc_GUIBox(BWidgetBox);
  BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetBox, "prop");
  BWidgetProperties->FLeft = 8;
  BWidgetProperties->FTop = 8;
  BWidgetProperties->FWidth = 200;
  BWidgetProperties->FHeight = 200;
  BWidgetProperties->FLeftAlign = TRUE;
  BWidgetProperties->FLeftSide = LEFT;
  BWidgetProperties->FLeftWidget = NULL;
  BWidgetProperties->FLeftSpacing = 256;
  BWidgetProperties->FTopAlign = TRUE;
  BWidgetProperties->FTopSide = TOP;
  BWidgetProperties->FTopWidget = NULL;
  BWidgetProperties->FTopSpacing = 8;
  BWidgetProperties->FRightAlign = TRUE;
  BWidgetProperties->FRightSide = RIGHT;
  BWidgetProperties->FRightWidget = NULL;
  BWidgetProperties->FRightSpacing = -8;
  BWidgetProperties->FBottomAlign = TRUE;
  BWidgetProperties->FBottomSide = RIGHT;
  BWidgetProperties->FBottomWidget = NULL;
  BWidgetProperties->FBottomSpacing = -8;
  Widget_AddChild(BWidgetClient, BWidgetBox);
  // END - Create the button widget.
  
  // BEGIN - Create the button widget.
  BWidgetButton = GUI_Create_Widget(BWindow, "button", "FButton");  
  Alloc_GUIButton(BWidgetButton);
  BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetButton, "prop");
  BWidgetProperties->FLeft = 8;
  BWidgetProperties->FTop = 8;
  BWidgetProperties->FWidth = 96;
  BWidgetProperties->FHeight = 24;
  Widget_AddChild(BWidgetBox, BWidgetButton);
  // END - Create the button widget.
  
  // BEGIN - Create the tabset widget.
  BWidgetTabset = GUI_Create_Widget(BWindow, "tabset", "FTabset");  
  Alloc_GUITabset(BWidgetTabset);
  BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetTabset, "prop");
  BWidgetProperties->FLeft = 0;
  BWidgetProperties->FTop = 0;
  BWidgetProperties->FWidth = 240;
  BWidgetProperties->FHeight = 60;
  BWidgetProperties->FLeftAlign = TRUE;
  BWidgetProperties->FLeftSide = LEFT;
  BWidgetProperties->FLeftWidget = NULL;
  BWidgetProperties->FLeftSpacing = 1;
  BWidgetProperties->FTopAlign = TRUE;
  BWidgetProperties->FTopSide = TOP;
  BWidgetProperties->FTopWidget = NULL;
  BWidgetProperties->FTopSpacing = 1;
  BWidgetProperties->FRightAlign = TRUE;
  BWidgetProperties->FRightSide = RIGHT;
  BWidgetProperties->FRightWidget = NULL;
  BWidgetProperties->FRightSpacing = -1;
  Widget_AddChild(BWidgetBox, BWidgetTabset);
  GUITabset_AddTab(BWidgetTabset, "Label for Tab 0");
  GUITabset_AddTab(BWidgetTabset, "Label for Tab 1");
  GUITabset_AddTab(BWidgetTabset, "Label for Tab 2");
  GUITabset_AddTab(BWidgetTabset, "Label for Tab 3");
  Widget_SetSignal(BWidgetTabset, "tab", &Tabset_OnTabChange);
  // END - Create the tabset widget.


  // BEGIN - Create the notebook widget.
  BWidgetNotebook = GUI_Create_Widget(BWindow, "notebook", "FNotebook");  
  Alloc_GUINotebook(BWidgetNotebook);
  BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetNotebook, "prop");
  BWidgetProperties->FLeft = 24;
  BWidgetProperties->FTop = 0;
  BWidgetProperties->FWidth = 240;
  BWidgetProperties->FHeight = 24;
  BWidgetProperties->FLeftAlign = TRUE;
  BWidgetProperties->FLeftSide = LEFT;
  BWidgetProperties->FLeftWidget = NULL;
  BWidgetProperties->FLeftSpacing = 1;
  BWidgetProperties->FTopAlign = TRUE;
  BWidgetProperties->FTopSide = BOTTOM;
  BWidgetProperties->FTopWidget = BWidgetTabset;
  BWidgetProperties->FTopSpacing = 0;
  BWidgetProperties->FRightAlign = TRUE;
  BWidgetProperties->FRightSide = RIGHT;
  BWidgetProperties->FRightWidget = NULL;
  BWidgetProperties->FRightSpacing = -1;
  BWidgetProperties->FBottomAlign = TRUE;
  BWidgetProperties->FBottomSide = RIGHT;
  BWidgetProperties->FBottomWidget = NULL;
  BWidgetProperties->FBottomSpacing = -1;
  Widget_AddChild(BWidgetBox, BWidgetNotebook);
  // END - Create the notebook widget.
  
  // BEGIN - Create the page widget.
  BWidgetPage = GUI_Create_Widget(BWindow, "box", "FPage 0");  
  Alloc_GUIBox(BWidgetPage);
  BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetPage, "prop");
  BWidgetProperties->FLeft = 0;
  BWidgetProperties->FTop = 0;
  BWidgetProperties->FWidth = 240;
  BWidgetProperties->FHeight = 180;
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
  BWidgetProperties->FBottomSide = RIGHT;
  BWidgetProperties->FBottomWidget = NULL;
  BWidgetProperties->FBottomSpacing = 0;
  Widget_AddChild(BWidgetNotebook, BWidgetPage);
  // END - Create the page widget.
  
  // BEGIN - Create the button widget.
  BWidgetButton = GUI_Create_Widget(BWindow, "button", "FButton");  
  Alloc_GUIButton(BWidgetButton);
  BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetButton, "prop");
  BWidgetProperties->FLeft = 8;
  BWidgetProperties->FTop = 8;
  BWidgetProperties->FWidth = 96;
  BWidgetProperties->FHeight = 24;
  Widget_AddChild(BWidgetPage, BWidgetButton);
  Widget_SetSignal(BWidgetButton, "click", &Button_OnClick);
  // END - Create the button widget.
  
  // BEGIN - Create the button widget.
  BWidgetButton = GUI_Create_Widget(BWindow, "button", "FButton");  
  Alloc_GUIButton(BWidgetButton);
  BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetButton, "prop");
  BWidgetProperties->FLeft = 30;
  BWidgetProperties->FTop = 48;
  BWidgetProperties->FWidth = 96;
  BWidgetProperties->FHeight = 24;
  Widget_AddChild(BWidgetPage, BWidgetButton);
  // END - Create the button widget.

  // BEGIN - Create the entry widget.
  BWidgetEntry = GUI_Create_Widget(BWindow, "entry", "FEntry");  
  Alloc_GUIEntry(BWidgetEntry);
  BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetEntry, "prop");
  BWidgetProperties->FLeft = 30;
  BWidgetProperties->FTop = 72;
  BWidgetProperties->FWidth = 96;
  BWidgetProperties->FHeight = 24;
  Widget_AddChild(BWidgetPage, BWidgetEntry);
  // END - Create the button widget.
  
  // BEGIN - Create the page widget.
  BWidgetPage = GUI_Create_Widget(BWindow, "box", "FPage 1");  
  Alloc_GUIBox(BWidgetPage);
  BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetPage, "prop");
  BWidgetProperties->FLeft = 0;
  BWidgetProperties->FTop = 0;
  BWidgetProperties->FWidth = 240;
  BWidgetProperties->FHeight = 180;
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
  BWidgetProperties->FBottomSide = RIGHT;
  BWidgetProperties->FBottomWidget = NULL;
  BWidgetProperties->FBottomSpacing = 0;
  Widget_AddChild(BWidgetNotebook, BWidgetPage);
  // END - Create the page widget.
  // BEGIN - Create the page widget.
  BWidgetPage = GUI_Create_Widget(BWindow, "box", "FPage 2");  
  Alloc_GUIBox(BWidgetPage);
  BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetPage, "prop");
  BWidgetProperties->FLeft = 0;
  BWidgetProperties->FTop = 0;
  BWidgetProperties->FWidth = 240;
  BWidgetProperties->FHeight = 180;
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
  BWidgetProperties->FBottomSide = RIGHT;
  BWidgetProperties->FBottomWidget = NULL;
  BWidgetProperties->FBottomSpacing = 0;
  Widget_AddChild(BWidgetNotebook, BWidgetPage);
  // END - Create the page widget.

  GUINotebook_SetActivePage(BWidgetNotebook, 0);
  
  /*
  int J = 0;
  int I = 0;
  int Count = 0;
  for (J = 0; J < 60; J++)
  {
    for (I = 0; I < 60; I++)
    {
      Count++;
      BWidgetButton = GUI_Create_Widget(BWindow, "button", "FButton");  
      Alloc_GUIButton(BWidgetButton);
      BWidgetProperties = (TGUIWidgetProperties *)Widget_GetPointer(BWidgetButton, "prop");
      BWidgetProperties->FLeft = I * 66;
      BWidgetProperties->FTop = J * 26;
      BWidgetProperties->FWidth = 64;
      BWidgetProperties->FHeight = 24;
      Widget_SetString(BWidgetButton, "text", "BUTTON");
      Widget_AddChild(BWidgetClient, BWidgetButton);
    // END - Create the button widget.
    };
  };
  */
  if (BWindow)
  {
    Window_Run(BWindow);
  };
  //printf("\n\n\nNum of widgets: %i\n\n\n", Count);
  return 0;
};
