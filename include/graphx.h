void gfx_Begin();
void gfx_End(void);
void gfx_FillScreen(uint8_t index);
void gfx_SetDraw(uint8_t location);
typedef enum {
    gfx_screen = 0, /**< Screen */
    gfx_buffer      /**< Buffer */
} gfx_location_t;
#define gfx_SetDrawBuffer() \
gfx_SetDraw(gfx_buffer)
#define gfx_SetDrawScreen() \
gfx_SetDraw(gfx_screen)
void gfx_SetPalette(void *palette,
                    unsigned int size,
                    uint8_t offset);
void gfx_Blit(gfx_location_t src);
#define gfx_BlitScreen() \
gfx_Blit(gfx_screen)
#define gfx_BlitBuffer() \
gfx_Blit(gfx_buffer)
uint8_t gfx_SetColor(uint8_t index);
#define gfx_FillRectangle_NoClip gfx_FillRectangle
void gfx_FillRectangle(int x,
                       int y,
                       int width,
                       int height);
void gfx_Rectangle(int x,
                   int y,
                   int width,
                   int height);
typedef struct {
    uint8_t width;   /**< Width of the image  */
    uint8_t height;  /**< Height of the image */
    uint8_t data[1]; /**< Image data array    */
} gfx_sprite_t;
void gfx_Sprite(gfx_sprite_t *sprite, int x, int y);
void gfx_TransparentSprite(gfx_sprite_t *sprite, int x, int y);
void gfx_ScaledSprite_NoClip(gfx_sprite_t *sprite, uint24_t x, uint8_t y, uint8_t width_scale, uint8_t height_scale);
gfx_sprite_t *gfx_GetSprite(gfx_sprite_t *sprite_buffer, int x, int y);
#define gfx_TempSprite(name, width, height) \
uint8_t name##_data[2 + (width) * (height)] = { (width), (height) }; \
gfx_sprite_t *name = (gfx_sprite_t *)name##_data
#define gfx_UninitedSprite(name, width, height) \
uint8_t name##_data[2 + (width) * (height)]; \
gfx_sprite_t *name = (gfx_sprite_t *)name##_data
gfx_sprite_t *gfx_FlipSpriteY(gfx_sprite_t *sprite_in,
                              gfx_sprite_t *sprite_out);
gfx_sprite_t *gfx_RotateSpriteC(gfx_sprite_t *sprite_in,
                                gfx_sprite_t *sprite_out);
typedef enum {
    gfx_8bpp = 0x27 /**< Enable 8 bits per pixel mode */
} gfx_mode_t;
uint8_t gfx_SetTextFGColor(uint8_t color);
void gfx_SetTextScale(uint8_t width_scale, uint8_t height_scale);
void gfx_SetTextXY(int x, int y);
int gfx_GetTextX(void);
int gfx_GetTextY(void);
void gfx_PrintChar(char c);
void gfx_PrintString(const char *string);
void gfx_PrintStringXY(const char *string, int x, int y);
void gfx_PrintUInt(unsigned int n, uint8_t length);
unsigned int gfx_GetCharWidth(const char c);
unsigned int gfx_GetStringWidth(const char *string);

#define gfx_HorizLine_NoClip gfx_HorizLine
void gfx_HorizLine(int x,
                   int y,
                   int length);
#define gfx_VertLine_NoClip gfx_VertLine
void gfx_VertLine(int x,
                  int y,
                  int length);

extern uint16_t gfx_palette[256];
extern uint8_t gfx_vram[320*240*2];
#define gfx_vbuffer gfx_GetVBuffer()

uint8_t *gfx_GetVBuffer(void);
uint8_t *gfx_GetFBuffer(void);
uint8_t *gfx_GetBBuffer(void);
