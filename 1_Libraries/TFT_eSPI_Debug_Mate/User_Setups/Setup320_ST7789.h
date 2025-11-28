// ST7789 135 x 240 display with no chip select line
#define USER_SETUP_ID 240

#define ST7789_DRIVER     // Configure all registers
#define INIT_ST7789P3
// #define INIT_SEQUENCE_3
#define HASSPI 1
#define SPICOM SPI
#define TFT_SPI_MODE SPI_MODE0

// #define TFT_WIDTH  320
// #define TFT_HEIGHT 240

// 方向反了 - work
#define TFT_WIDTH  240
#define TFT_HEIGHT 320

// #define CGRAM_OFFSET      // Library will add offsets required

#define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue
//#define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red
#define TFT_BACKLIGHT_ON LOW

#define TFT_SDA_READ      // This option is for ESP32 ONLY, tested with ST7789 display only

//#define TFT_INVERSION_ON
//#define TFT_INVERSION_OFF

// RP2350
#define TFT_BL    2

#define TFT_DC    4 // 7
#define TFT_CS    5 // 8
#define TFT_SCLK  6 // 9
#define TFT_MOSI  7 // 10
#define TFT_MISO  -1 // no used
#define TFT_RST   11


#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
//#define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT


// #define SPI_FREQUENCY  40000000
#define SPI_FREQUENCY  20000000

#define SPI_READ_FREQUENCY  20000000

#define SPI_TOUCH_FREQUENCY  2500000

// #define SUPPORT_TRANSACTIONS
