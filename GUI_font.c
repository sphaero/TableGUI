#include <string.h>
//#include <glib/gprintf.h>
#include <cairo/cairo.h>
#include "GUI.h"
#include "GUI_font.h"

extern GLuint FCurrentTexture;

int max(int AA, int AB)
{
  if (AA > AB)
  {
    return AA;
  } else
  {
    return AB;
  };
};

int glTextWidth(const TGUIFont *AFont, const unsigned char *AText)
{        
  unsigned char *BChar = AText;
  int BTextWidth = 0;
  TGUIFontExtent *BCharExtent = NULL;
  
  while (*BChar != '\0')
  {
    if ((*BChar >= 32) && (*BChar <= 125))
    {
      BCharExtent = &AFont->FExtents[*BChar];
      BTextWidth = BTextWidth + BCharExtent->FAdvanceX + max(1, BCharExtent->FBearingX);
    };
    BChar++;
  };
  return BTextWidth;
};

int glTextWidthUntil(const TGUIFont *AFont, const unsigned char *AText, int ALength)
{
  unsigned char *BChar = AText;
  int BTextWidth = 0;
  TGUIFontExtent *BCharExtent = NULL;
  int BIndex = 0;  
  while ((*BChar != '\0') &&
  (BIndex < ALength))
  {
    if ((*BChar >= 32) && (*BChar <= 125))
    {
      BCharExtent = &AFont->FExtents[*BChar];
      BTextWidth = BTextWidth + BCharExtent->FAdvanceX + max(1, BCharExtent->FBearingX);
    };
    BIndex++;
    BChar++;
  };
  return BTextWidth;
};

int glTextHeight(const TGUIFont *AFont, const unsigned char *AText)
{        
  unsigned char *BChar = AText;
  int BTextHeight = 0;
  TGUIFontExtent *BCharExtent = NULL;
  
  while (*BChar != '\0')
  {
    if ((*BChar >= 32) && (*BChar <= 125))
    {
      BCharExtent = &AFont->FExtents[*BChar];
      if (BCharExtent->FHeight >BTextHeight)
      {
        BTextHeight = BCharExtent->FHeight;
      };
    };
    BChar++;
  };
  return BTextHeight;
};

void glPrint(const TGUIFont *AFont, int AX, int AY, const unsigned char *AText, float AColorRed, float AColorGreen, float AColorBlue)
{        
  unsigned char *BChar = AText;
  TGUIFontExtent *BCharExtent = NULL;
  
  float BPixelWidth = 1.0f / AFont->FTextureWidth;
  float BPixelHeight = 1.0f / AFont->FTextureHeight;
  float BOffsetX = 0.0f;
  int BOffsetY = 0;
  
  float BRow = 0;
  float BColumn = 0;
  float BTextureRectWidth = AFont->FGridWidth * BPixelWidth;
  float BTextureRectHeight = AFont->FGridHeight * BPixelHeight;
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  GLuint BCurrentTexture;
  if (BCurrentTexture != AFont->FTexture)
  {
    glBindTexture(GL_TEXTURE_2D, AFont->FTexture);
    BCurrentTexture = AFont->FTexture;
  };
  glTranslatef(AX, AY, 0.0);
  glBegin(GL_QUADS);
  glColor3f(AColorRed, AColorGreen, AColorBlue);
  while (*BChar != '\0')
  {
    if ((*BChar >= 32) && (*BChar <= 125))
    {
      BCharExtent = &AFont->FExtents[*BChar];
      //glPushMatrix();

      //glTranslatef(0.0, -BCharExtent->FHeight + (BCharExtent->FHeight + BCharExtent->FBearingY), 0.0);
      BOffsetY = -BCharExtent->FHeight + (BCharExtent->FHeight + BCharExtent->FBearingY);
      //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
      //glColor4f(0.9, 0.0, 0.0, 0.0);
      
      BRow = ((int)(*BChar / 16)) * BPixelHeight * AFont->FGridHeight; // To-do: Refactore this.
      BColumn = ((int)(*BChar % 16)) * BPixelWidth * AFont->FGridWidth; // To-do: Refactore this.
      
        glTexCoord2f(BColumn,                     BRow);                      glVertex3f( BOffsetX + 0.0f,              BOffsetY + 0.0f,               0.1f);
        glTexCoord2f(BColumn,                     BRow + BTextureRectHeight); glVertex3f( BOffsetX + 0.0f,              BOffsetY + AFont->FGridHeight, 0.1f);
        glTexCoord2f(BColumn + BTextureRectWidth, BRow + BTextureRectHeight); glVertex3f( BOffsetX + AFont->FGridWidth, BOffsetY + AFont->FGridHeight, 0.1f);
        glTexCoord2f(BColumn + BTextureRectWidth, BRow);                      glVertex3f( BOffsetX + AFont->FGridWidth, BOffsetY + 0.0f,               0.1f);
      
      //glPopMatrix();
      BOffsetX = BOffsetX + BCharExtent->FAdvanceX + max(1, BCharExtent->FBearingX);
      //glTranslatef(BCharExtent->FAdvanceX + BCharExtent->FBearingX, 0.0, 0.0);
    };
    BChar++;
  };
  glEnd();
  glDisable(GL_TEXTURE_2D);
  //glBindTexture(GL_TEXTURE_2D, NULL);
  glPopMatrix();
};

int Get_NextP2(int AInteger)
{
  int BReturnValue = 1;
  while (BReturnValue <= AInteger)
  {
    BReturnValue <<= 1;
  };
  return BReturnValue;
};

void GUIFont_GetGreaterSize(const char *AFontName, float AHeight, unsigned int *ACharWidth, unsigned int *ACharHeight)
{
  cairo_text_extents_t *BExtents = (cairo_text_extents_t *)malloc(sizeof(cairo_text_extents_t));
  unsigned char *BText = (unsigned char *)malloc(sizeof(unsigned char) * 2);
  BText[0] = 0;
  BText[1] = '\0';
  
  cairo_surface_t *BSurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                                         1,
                                                         1);
  cairo_t *BContext = cairo_create(BSurface);
  
  cairo_font_options_t *cfo = cairo_font_options_create();
  cairo_font_options_set_antialias(cfo, CAIRO_ANTIALIAS_SUBPIXEL);
  cairo_set_font_options(BContext, cfo);
  cairo_select_font_face(BContext, AFontName, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(BContext, AHeight);
  
  for (BText[0] = 0; BText[0] < 255; BText[0]++)
  {
    cairo_text_extents(BContext, BText, BExtents);
    if (BExtents)
    {
      if (*ACharHeight < BExtents->height)
      {
        *ACharHeight = BExtents->height;
      };
      if (*ACharWidth < BExtents->width)
      {
        *ACharWidth = BExtents->width;
      };
    };
  };
  cairo_destroy(BContext);
  cairo_surface_destroy(BSurface);
};

TGUIFont *Alloc_GUIFont(const char *AFontName, float AHeight)
{
  TGUIFont *BFont = (TGUIFont *)malloc(sizeof(TGUIFont));
  BFont->FGridWidth = 0;
  BFont->FGridHeight = 0;
  BFont->FHeight = AHeight;
  BFont->FExtents = (TGUIFontExtent *)malloc(sizeof(TGUIFontExtent) * 256);
  TGUIFontExtent *BCharExtent = BFont->FExtents;
  cairo_text_extents_t *BExtents = (cairo_text_extents_t *)malloc(sizeof(cairo_text_extents_t));
  int BRow = 0;
  int BColumn = 0;
  GUIFont_GetGreaterSize(AFontName, AHeight, &BFont->FGridWidth, &BFont->FGridHeight);
  printf("[MESSAGE] Font grid of size (%i, %i).\n", BFont->FGridWidth, BFont->FGridHeight);
  BFont->FTextureWidth = Get_NextP2(BFont->FGridWidth * 16);
  BFont->FTextureHeight = Get_NextP2(BFont->FGridHeight * 16);
  printf("[MESSAGE] Font texture of size (%i, %i).\n", BFont->FTextureWidth, BFont->FTextureHeight);
  
  unsigned char *BData = NULL;
  unsigned char *BText = (unsigned char *)malloc(sizeof(unsigned char) * 2);
  BText[0] = 0;
  BText[1] = '\0';

  // Create texture data .
  cairo_surface_t *BSurface = cairo_image_surface_create(CAIRO_FORMAT_A8,
                                                         BFont->FTextureWidth,
                                                         BFont->FTextureHeight);
  cairo_t *BContext = cairo_create(BSurface);
  
  cairo_set_antialias(BContext, CAIRO_ANTIALIAS_NONE);
  cairo_set_operator(BContext, CAIRO_OPERATOR_OVER);
  cairo_set_source_rgba(BContext, 0.0, 0.0, 0.0, 0.0);
  
  cairo_font_options_t *cfo = cairo_font_options_create();
  cairo_font_options_set_antialias(cfo, CAIRO_ANTIALIAS_SUBPIXEL);
  cairo_set_font_options(BContext, cfo);
  cairo_set_source_rgba(BContext, 0.0, 0.0, 0.0, 1.0);
  cairo_select_font_face(BContext, AFontName, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(BContext, AHeight);
  
  for (BText[0] = 0; BText[0] < 255; BText[0]++)
  {
    cairo_text_extents(BContext, BText, BExtents);
    if (BExtents)
    {
      BCharExtent->FAdvanceX = BExtents->x_advance;
      if (BText[0] == 32)
      {
        //BCharExtent->FAdvanceX = BFont->FGridWidth;
      };
      BCharExtent->FAdvanceY = BExtents->y_advance;
      BCharExtent->FBearingX = BExtents->x_bearing;
      BCharExtent->FBearingY = BExtents->y_bearing;
      BCharExtent->FWidth = BExtents->width;
      BCharExtent->FHeight = BExtents->height;
      BRow = BText[0] / 16;
      BColumn = BText[0] % 16;
      cairo_move_to(BContext, -BExtents->x_bearing + (BColumn * BFont->FGridWidth), -BExtents->y_bearing + (BRow * BFont->FGridHeight));
      cairo_show_text(BContext, BText);
    } else
    {
      printf("[MESSAGE] Fail to create font. Extents of char %i returned as null.\n", BText[0]);
      return NULL;
    };
    BCharExtent++;
  };
  cairo_surface_flush(BSurface);
  //cairo_surface_write_to_png(BSurface, "/home/felipefs/Desktop/texture.png");
  BData = cairo_image_surface_get_data(BSurface);
  glGenTextures(1, &BFont->FTexture);
  glBindTexture(GL_TEXTURE_2D, BFont->FTexture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
  //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, BFont->FTextureWidth, BFont->FTextureHeight,
               0, GL_ALPHA, GL_UNSIGNED_BYTE, BData);
  
  cairo_destroy(BContext);
  cairo_surface_destroy(BSurface);
  //free(BData);
  if (glIsTexture(BFont->FTexture) == GL_FALSE)
  {
    printf("[ERROR] Fail to create character texture of size %ix%i.\n", BFont->FTextureWidth, BFont->FTextureHeight);
  };
  printf("[MESSAGE] Font created.\n");
  return BFont;
};

void GUIFont_Clear(TGUIFont *AFont)
{
  
};