#ifndef R_H
#define R_H

#include <stdio.h>
#include <math.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"

#define DAY_MODE
//#define NIGHT_MODE

#define LCD_WIDTH			480
#define LCD_HEIGHT			320
#define GAME_WIDTH			320
#define GAME_HEIGHT			320

#define SIZE_OF_PIXEL		2 //velikost jednoho pixlu

#define BRIGHT_RED 			0xf800
#define BRIGHT_GREEN 		0x07e0
#define BRIGHT_BLUE 		0x001f

#define DARK_RED 			0x7800
#define DARK_GREEN	 		0x01e0
#define DARK_BLUE 			0x000f

#define BRIGHT_WHITE		0xffff
#define DARK_WHITE			0x5555
#define BLACK 				0x0000

#define PURPLE				0x780f
#define PINK                0xf81f
#define CYAN                0x07ff
#define YELLOW  			0xffe0
#define ORANGE              0xfd20

#define LED_LINE_0			0x00000000
#define LED_LINE_1			0xff000000
#define LED_LINE_2			0xffff0000
#define LED_LINE_3			0xffffff00
#define LED_LINE_4			0xffffffff

#define LED_RED				0xff0000
#define LED_GREEN			0x00ff00
#define LED_BLUE			0x0000ff
#define LED_BLACK			0x000000
#define LED_PINK            0xec00f8
#define LED_PURPLE          0x8600FF

#ifdef NIGHT_MODE
#define SNAKE_1_COLOR DARK_GREEN
#define SNAKE_2_COLOR DARK_BLUE 
#define SELECT_COLOR BRIGHT_RED
#define BASE_COLOR DARK_RED
#define FOOD_COLOR DARK_RED
#endif

#ifdef DAY_MODE
#define SNAKE_1_COLOR BRIGHT_GREEN
#define SNAKE_2_COLOR BRIGHT_BLUE
#define SELECT_COLOR BRIGHT_WHITE
#define BASE_COLOR DARK_WHITE
#define FOOD_COLOR BRIGHT_RED
#endif

/*
returns width of char as defined in font descriptor
@param
	font_descriptor_t* fdes - font descriptor
	int ch - char
@return
	width of char as defined in font descriptor
*/
int char_width(font_descriptor_t* fdes, int ch);

/*
fills pixel in array with colour
@param
	int xTile - x coord of pixel
	int yTile - y coord of pixel
	uint16_t colour - colour
	uint16_t* pixels - render array
*/
void draw_pixel(int xTile, int yTile, uint16_t colour, uint16_t* pixels);

/*
fills pixels that represent char in array with colour
@param
	int xTile - x coord of upper left corner of char bitmap
	int yTile - y coord of upper left corner of char bitmap
	font_descriptor_t* fdes - font descriptor
	int ch - char
	uint16_t colour - colour
	uint16_t* pixels - render array
*/
void draw_char(int xTile, int yTile, font_descriptor_t* fdes, int ch, 
			uint16_t colour, uint16_t* pixels);

/*
fills pixels that represent string in array with colour
@param
	int xTile - x coord of upper left corner of char bitmap
	int yTile - y coord of upper left corner of char bitmap
	uint16_t colour - colour
	char* ch - pointer to the beggining of the string
	int size_of_string - size of string
	uint16_t* pixels - render array
*/
void draw_string(int xTile, int yTile, uint16_t colour, char* ch, 
				int size_of_string, uint16_t* pixels);

/*
fills borders of rectangle in array with colour
@param
	int x - x coord of upper left corner of rectangle
	int y -	y coord of upper left corner of rectangle
	int width - width of rectangle
	int height - height of rectangle
	int border - size of border
	uint16_t colour - colour
	uint16_t* pixels - render array
*/
void draw_rect(int x, int y, int width, int height, int border, uint16_t colour, 
			uint16_t* pixels);

/*
fills pixels that represent portion of sinus function in array with colour
@param
	int x - x coord of sinus
	int y - y coord of sinus
	int size - size of portion of sinus
	uint16_t colour - colour
	uint16_t* pixels - render array
*/
void draw_sinus(int x, int y, int size, uint16_t colour, uint16_t* pixels);

/*
fills pixels that represent horizontal line in array with colour
@param
	int xTile - x coord of the line's left boundary
	int yTile - y coord of the line's left boundary
	int size - size of line
	uint16_t colour - colour
	uint16_t* pixels - render array
*/
void draw_lineX(int xTile, int yTile, int size, uint16_t colour, uint16_t* pixels);

/*
fills pixels that represent vertical line in array with colour
@param
	int xTile - x coord of the line's down boundary
	int yTile - y coord of the line's down boundary
	int size - size of line
	uint16_t colour - colour
	uint16_t* pixels - render array
*/
void draw_lineY(int xTile, int yTile, int size, uint16_t colour, uint16_t* pixels);

/*
fills rectangle in array with colour
@param
	int x - x coord of upper left corner of rectangle
	int y -	y coord of upper left corner of rectangle
	int width - width of rectangle
	int height - height of rectangle
	uint16_t colour - colour
	uint16_t* pixels - render array
*/
void draw_filled_rect(int x, int y, int width, int height, uint16_t colour, 
					uint16_t* pixels);

/*
fills the whole array with colour
@param
	uint16_t colour - colour
	uint16_t* pixels - render array
*/
void clear_array(uint16_t colour, uint16_t* pixels);

/*
draws from render array to LCD display
@param
	unsigned char* parlcd_mem_base - phys address of LCD display
	uint16_t* pixels - render array
*/
void draw(unsigned char* parlcd_mem_base, uint16_t* pixels);

/*
turns on specified LEDs on LED line
@param
	uint32_t val_line - binary number representing state of each LED
	unsigned char *mem_base - phys address of Peripherals
*/
void led_line(uint32_t val_line, unsigned char* mem_base);

/*
changes colour of first LED diode
@param
	uint32_t colour - LED colour
	unsigned char *mem_base - phys address of Peripherals
*/
void led_RGB1(uint32_t colour, unsigned char* mem_base);

/*
changes colour of second LED diode
@param
	uint32_t colour - LED colour
	unsigned char *mem_base - phys address of Peripherals
*/
void led_RGB2(uint32_t colour, unsigned char* mem_base);

#endif
