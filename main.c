#include <GLFW/glfw3.h>
#include <stdio.h>
#include <basicutils.h>
#include "GUI.h"
#include "GUI_button.h"
#include "GUI_checkbox.h"
#include "GUI_scrollbar.h"
#include "GUI_contentbox.h"

int main( int argc, char* args[])
{
  Initialize();
  
  TGUIWindow *BWindow = NULL;
  TGUIWidget *BWidgetClient = NULL;
  TGUIWidget *BWidgetButton = NULL;
  TGUIWidget *BWidgetCheckBox = NULL;
  TGUIWidget *BWidgetTabset = NULL;
  TGUIWidget *BWidgetScrollbar = NULL;
  BWindow = GUI_Create_Window("Title", 0, 0, 320, 240, 0);
  
  BWidgetClient = GUI_Create_Widget(BWindow, "contentbox", "FClientBox");  
  Alloc_GUIContentbox(BWidgetClient);
  Widget_SetInt(BWidgetClient, "left", 10);
  Widget_SetInt(BWidgetClient, "top", 50);
  Widget_SetInt(BWidgetClient, "width", 100);
  Widget_SetInt(BWidgetClient, "height", 30);
  Iterator_AddPointer(BWindow->FListClientWidget, BWidgetClient);
  
  BWidgetClient->FAlignment.FTop.FEnabled = TRUE;
  BWidgetClient->FAlignment.FTop.FAttatchToSide = TOP;
  BWidgetClient->FAlignment.FLeft.FEnabled = TRUE;
  BWidgetClient->FAlignment.FLeft.FAttatchToSide = LEFT;
  BWidgetClient->FAlignment.FBottom.FEnabled = TRUE;
  BWidgetClient->FAlignment.FBottom.FAttatchToSide = BOTTOM;
  BWidgetClient->FAlignment.FRight.FEnabled = TRUE;
  BWidgetClient->FAlignment.FRight.FAttatchToSide = RIGHT;
  
  
  BWidgetButton = GUI_Create_Widget(BWindow, "button", "FButton");
  Alloc_GUIButton(BWidgetButton);
  Widget_SetInt(BWidgetButton, "left", 60);
  Widget_SetInt(BWidgetButton, "top", 8);
  Widget_SetInt(BWidgetButton, "width", 96);
  Widget_SetInt(BWidgetButton, "height", 24);
  Widget_SetString(BWidgetButton, "text", "MyText");
  AddChild(BWidgetClient, BWidgetButton);
  
  BWidgetCheckBox = GUI_Create_Widget(BWindow, "checkbox", "FCheckbox");
  Alloc_GUICheckbox(BWidgetCheckBox);
  Widget_SetBool(BWidgetCheckBox, "checked", TRUE);
  Widget_SetInt(BWidgetCheckBox, "left", 60);
  Widget_SetInt(BWidgetCheckBox, "top", 48);
  AddChild(BWidgetClient, BWidgetCheckBox);
  
  BWidgetTabset = GUI_Create_Widget(BWindow, "tabset", "FTabset");
  Alloc_GUITabset(BWidgetTabset);
  Widget_SetInt(BWidgetTabset, "left", 100);
  Widget_SetInt(BWidgetTabset, "top", 200);
  Widget_SetInt(BWidgetTabset, "width", 100);
  Widget_SetInt(BWidgetTabset, "height", 24);
  //GUITabset_AddTab(BWidgetTabset, "tab1");
  //GUITabset_AddTab(BWidgetTabset, "tab2");
  AddChild(BWidgetClient, BWidgetTabset);
  
  BWidgetScrollbar = GUI_Create_Widget(BWindow, "scrollbar", "FScrollbar");
  Alloc_GUIScrollbar(BWidgetScrollbar);
  Widget_SetInt(BWidgetScrollbar, "left", 8);
  Widget_SetInt(BWidgetScrollbar, "top", 8);
  Widget_SetInt(BWidgetScrollbar, "height", 180);
  Widget_SetInt(BWidgetScrollbar, "max", 200);
  Widget_SetInt(BWidgetScrollbar, "page", 100);
  Widget_SetInt(BWidgetScrollbar, "position", 50);
  AddChild(BWidgetClient, BWidgetScrollbar);
  
  // Create another client widget.
  BWidgetClient = GUI_Create_Widget(BWindow, "box", "FModalBox");  
  Widget_SetInt(BWidgetClient, "left", 40);
  Widget_SetInt(BWidgetClient, "top", 24);
  Widget_SetInt(BWidgetClient, "width", 200);
  Widget_SetInt(BWidgetClient, "height", 150);
  //Iterator_AddPointer(BWindow->FListClientWidget, BWidgetClient);
  
  if (BWindow)
  {
    RunWindow(BWindow);
  };
  return 0;
};
