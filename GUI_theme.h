/*
  This file is part of TableGUI.
  Copyright (c) 2014 Felipe Ferreira da Silva
  
  TableGUI is licensed under MIT license.
  See the file "LICENSE" for license details.
*/

#ifndef __GUI_THEME_H__
#define __GUI_THEME_H__

#include <stdio.h>
        
#define COLOR_DEFAULT_BACKGROUND_R 180
#define COLOR_DEFAULT_BACKGROUND_G 180
#define COLOR_DEFAULT_BACKGROUND_B 180

#define COLOR_CONTAINER_BACKGROUND_R 0.3
#define COLOR_CONTAINER_BACKGROUND_G 0.3
#define COLOR_CONTAINER_BACKGROUND_B 0.3

#define COLOR_CONTENT_BACKGROUND_R 38
#define COLOR_CONTENT_BACKGROUND_G 38
#define COLOR_CONTENT_BACKGROUND_B 38

#define COLOR_BACKGROUND_R 80
#define COLOR_BACKGROUND_G 80
#define COLOR_BACKGROUND_B 80

#define COLOR_BACKGROUND_SHADOW_R 30
#define COLOR_BACKGROUND_SHADOW_G 30
#define COLOR_BACKGROUND_SHADOW_B 30

#define COLOR_FOCUS_R 200
#define COLOR_FOCUS_G 120
#define COLOR_FOCUS_B 20

#define COLOR_BORDER_R 32
#define COLOR_BORDER_G 32
#define COLOR_BORDER_B 32 

typedef struct TColorFloatStruct TColorFloat;

struct TColorFloatStruct
{
  float FR;
  float FG;
  float FB;
};

#endif
