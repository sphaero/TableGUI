#include <string.h>
//#include <glib/gprintf.h>
#include <cairo/cairo.h>
#include "GUI_font.h"

int Get_NextP2(int AInteger)
{
  int BReturnValue = 1;
  while (BReturnValue <= AInteger)
  {
    BReturnValue <<= 1;
  };
  return BReturnValue;
};

GUIFont_MakeCharTexture(TGUIFont *AFont, TGUIFontChar *AFontChar, unsigned char AChar)
{
  printf("[MESSAGE] Making texture for character %c (%i)'.\n", AChar, AChar);
  unsigned char *BData = NULL;
  unsigned char *BDataTexture = NULL;
  cairo_text_extents_t *BExtents = (cairo_text_extents_t *)malloc(sizeof(cairo_text_extents_t));
  unsigned char *BText = (unsigned char *)malloc(sizeof(unsigned char) * 2);
  BText[0] = AChar;
  BText[1] = '\0';
  
  cairo_surface_t *BSurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                                         AFont->FTextureSize,
                                                         AFont->FTextureSize);
  cairo_t *BContext = cairo_create(BSurface);
  //printf("[MESSAGE] Character advance x = %i.\n", AFontChar->FAdvanceX);
  cairo_set_antialias(BContext, CAIRO_ANTIALIAS_NONE);
  cairo_set_operator(BContext, CAIRO_OPERATOR_OVER);
  cairo_set_source_rgba(BContext, 0.0, 0.0, 0.0, 0.0);
  // 0.0 0.0 0.0 0.0
  //  A   R   G   B
  //  R   G   B   A
  
  cairo_paint(BContext);
  
  cairo_font_options_t *cfo = cairo_font_options_create();
  cairo_font_options_set_antialias(cfo, CAIRO_ANTIALIAS_SUBPIXEL);
  cairo_set_font_options(BContext, cfo);
  
  cairo_set_source_rgba(BContext, 0.0, 0.0, 0.0, 1.0);
  cairo_select_font_face(BContext, AFont->FFontName, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(BContext, AFont->FHeight);
  cairo_text_extents(BContext, BText, BExtents);
  if (BExtents)
  {
    AFontChar->FAdvanceX = BExtents->x_advance;
    AFontChar->FAdvanceY = BExtents->y_advance;
    AFontChar->FBearingX = BExtents->x_bearing;
    AFontChar->FBearingY = BExtents->y_bearing;
    AFontChar->FWidth = BExtents->width;
    AFontChar->FHeight = BExtents->height;
  } else
  {
    printf("[ERROR] Fail to store extents.\n");
  };
  // 0.0 0.0 0.0 1.0
  //  A   R   G   B
  //  R   G   B   A
  cairo_move_to(BContext, -AFontChar->FBearingX, -AFontChar->FBearingY);
  cairo_show_text(BContext, BText);
  cairo_surface_flush(BSurface);
  free(BText);
  BData = cairo_image_surface_get_data(BSurface);
  
  glGenTextures(1, &AFontChar->FTexture);
  glBindTexture(GL_TEXTURE_2D, AFontChar->FTexture);
  
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  
  glTexImage2D(GL_TEXTURE_2D, 0, 4, AFont->FTextureSize, AFont->FTextureSize,
               0, GL_RGBA, GL_UNSIGNED_BYTE, BData);
  
  cairo_destroy(BContext);
  cairo_surface_destroy(BSurface);
  //free(BData);
  if (glIsTexture(AFontChar->FTexture) == GL_FALSE)
  {
    printf("[ERROR] Fail to create character texture of size %ix%i.\n", AFont->FTextureSize, AFont->FTextureSize);
  };
};

TGUIFont *Alloc_GUIFont(const char *AFontName, float AHeight, int ATextureSize)
{
  TGUIFont *BFont = (TGUIFont *)malloc(sizeof(TGUIFont));
  BFont->FFontChar = (TGUIFontChar *)malloc(sizeof(TGUIFontChar) * 256);
  BFont->FTextureSize = Get_NextP2(ATextureSize);
  BFont->FFontName = (char *)malloc(sizeof(char) * (strlen(AFontName) + 1));
  memset(BFont->FFontName, 0, strlen(AFontName) + 1);
  memcpy(BFont->FFontName, AFontName, wcslen(AFontName));
  
  BFont->FHeight = AHeight;
  
  printf("[MESSAGE] Font loaded to \'%s\'.\n", BFont->FFontName);
  unsigned char BChar = 0;
  for(BChar = 0; BChar < 255; BChar++)
  {
    GUIFont_MakeCharTexture(BFont, &BFont->FFontChar[BChar], BChar);
  };
  return BFont;
};

void GUIFont_Clear(TGUIFont *AFont)
{
  
};

int glTextWidth(const TGUIFont *AFont, const unsigned char *AText)
{        
  unsigned char *BChar = AText;
  TGUIFontChar *BFontChar = NULL;
  int BTextWidth = 0;
  
  while (*BChar != '\0')
  {
    if ((*BChar >= 32) && (*BChar <= 125))
    {
      BFontChar = &AFont->FFontChar[*BChar];
      BTextWidth = BTextWidth + BFontChar->FAdvanceX + BFontChar->FBearingX;
    };
    BChar++;
  };
  return BTextWidth;
};

int glTextHeight(const TGUIFont *AFont, const unsigned char *AText)
{        
  unsigned char *BChar = AText;
  TGUIFontChar *BFontChar = NULL;
  int BTextHeight = 0;
  
  while (*BChar != '\0')
  {
    if ((*BChar >= 32) && (*BChar <= 125))
    {
      BFontChar = &AFont->FFontChar[*BChar];
      if (BFontChar->FHeight >BTextHeight)
      {
        BTextHeight = BFontChar->FHeight;
      };
    };
    BChar++;
  };
  return BTextHeight;
};

void glPrint(const TGUIFont *AFont, int AX, int AY, const unsigned char *AText)
{        
  unsigned char *BChar = AText;
  TGUIFontChar *BFontChar = NULL;
  glPushMatrix();
  glTranslatef(AX, AY, 0.0);
  while (*BChar != '\0')
  {
    if ((*BChar >= 32) && (*BChar <= 125))
    {
      BFontChar = &AFont->FFontChar[*BChar];
      
      glPushMatrix();
      glTranslatef(0.0, -BFontChar->FHeight + (BFontChar->FHeight + BFontChar->FBearingY), 0.0);
      glBindTexture(GL_TEXTURE_2D, BFontChar->FTexture);
      //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
      //glColor4f(0.9, 0.0, 0.0, 0.0);
      glBegin(GL_QUADS);
      
      glTexCoord2f(0, 0);                                        glVertex3f(0.0, 0.0, 0.0);
      glTexCoord2f(1, 0.0);                      glVertex3f(AFont->FTextureSize, 0.0, 0.0);
      glTexCoord2f(1, 1);    glVertex3f(AFont->FTextureSize, AFont->FTextureSize, 0.0);
      glTexCoord2f(0.0, 1);                      glVertex3f(0.0, AFont->FTextureSize, 0.0);
      glTexCoord2f(0, 0);                                        glVertex3f(0.0, 0.0, 0.0);
      
      glEnd();
      glPopMatrix();
      glTranslatef(BFontChar->FAdvanceX + BFontChar->FBearingX, 0.0, 0.0);
    };
    BChar++;
  };
      glBindTexture(GL_TEXTURE_2D, NULL);
  glPopMatrix();
};