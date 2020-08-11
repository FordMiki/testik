/*******************************************************************
  Simple program to implement Snake video game on MicroZed based 
  MZ_APO board designed by Petr Porazil at PiKRON

  Render.cpp - Functions that work with the Peripherals of MZ_APO

  (C) Copyright 2020 by Jiri Povolny and Marian Krotil
      e-mail:   povolji2@fel.cvut.cz, krotima1@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include "Render.h"

int char_width(font_descriptor_t* fdes, int ch) 
{
	int width = 0;
	if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) 
	{
		ch -= fdes->firstchar;
		if (!fdes->width) 
		{
			width = fdes->maxwidth;
		} 
		else 
		{
			width = fdes->width[ch];
		}
	}
	return width;
}

void draw_pixel(int xTile, int yTile, uint16_t colour, uint16_t* pixels) 
{
	if (xTile >= 0 && xTile < LCD_WIDTH / SIZE_OF_PIXEL && yTile >= 0 && 
		yTile < LCD_HEIGHT / SIZE_OF_PIXEL) 
	{	
		for (int i = yTile * SIZE_OF_PIXEL; 
			i < SIZE_OF_PIXEL * yTile + SIZE_OF_PIXEL; i++)
		{
			for (int j = xTile * SIZE_OF_PIXEL; 
				j < SIZE_OF_PIXEL * xTile + SIZE_OF_PIXEL; j++)
			{
				pixels[LCD_WIDTH * i + j] = colour;
			}
		}
	}
}

void draw_lineX(int xTile, int yTile, int size, uint16_t colour, uint16_t* pixels)
{
	for (int i = 0; i < size; i++)
	{
		draw_pixel(xTile + i, yTile, colour, pixels);
	}
}

void draw_lineY(int xTile, int yTile, int size, uint16_t colour, uint16_t* pixels)
{
	for (int i = 0; i < size; i++)
	{
		draw_pixel(xTile, yTile + i, colour, pixels);
	}
}

void draw_char(int xTile, int yTile, font_descriptor_t* fdes, int ch, 
			uint16_t colour, uint16_t* pixels) 
{
	int w, bw, i;
	unsigned int j;
	const uint16_t* b;
	unsigned patt = 0;
	
	ch -= fdes->firstchar;
	if (!fdes->width)
	{
		w = fdes->maxwidth;
	}
	else
	{
		w = fdes->width[ch];
	}
	bw = (w + 15) / 16;
	
	if (!fdes->offset)
	{
		b = fdes->bits + ch * bw * fdes->height;
	}
	else
	{
		b = fdes->bits + fdes->offset[ch];
	}
	
	for (j = 0; j < fdes->height; j++)
	{
		for (i = 0; i < w; i++)
		{
			if (!(i & 15))
			{
				patt = *(b++);
			}
			if (patt & 0x8000 || 1)
			{
				draw_pixel(xTile + i, yTile + j, patt & 0x8000 ? colour : 0, 
						pixels);
			}
			patt <<= 1;
		}
	}
}

void draw_string(int xTile, int yTile, uint16_t colour, char* ch, 
				int size_of_string, uint16_t* pixels)
{
	font_descriptor_t* fdes = &font_rom8x8;

	for (int i = 0; i < size_of_string; i++) 
	{
		draw_char(xTile, yTile, fdes, *ch, colour, pixels);
		xTile += char_width(fdes, *ch);
		ch++;
	}
}

void draw_rect(int x, int y, int width, int height, int border, uint16_t color, 
			uint16_t* fb)
{
	if (y <= LCD_HEIGHT && y >= 0 && x <= LCD_WIDTH && x >= 0)
	{
		for (int i = y; i < y + border; i++) 
		{
			for (int j = x; j < x + width; j++) 
			{
				fb[LCD_WIDTH * i + j] = color;
			}
		}
		for (int i = y; i < y + height; i++) 
		{
			for (int j = x; j < x + border; j++) 
			{
				fb[LCD_WIDTH * i + j] = color;
			}
		}
		for (int i = y; i < y + height; i++) 
		{
			for (int j = x + width - border; j < x+ width; j++) 
			{
				fb[LCD_WIDTH * i + j] = color;
			}
		}
		for (int i = y + height - border; i < y + height; i++) 
		{
			for (int j = x; j < x + width; j++) 
			{
				fb[LCD_WIDTH * i + j] = color;
			}
		}
	}
}

void draw_filled_rect(int x, int y, int width, int height, uint16_t color, 
					uint16_t* pixels)
{
	if (y <= LCD_HEIGHT && y >= 0 && x <= LCD_WIDTH && x >= 0)
	{
		for (int i = y; i < y + height; i++) 
		{
			for (int j = x; j < x + width; j++) 
			{
				pixels[LCD_WIDTH * i + j] = color;
			}
		}
	}
}

void draw_sinus(int x, int y, int size, uint16_t color, uint16_t* fb)
{
	for (int i = x; i < x + size; i++)
	{
		draw_pixel(i, (int)(-round(10 * sin(2 * (i * M_PI / 45)))) + y, color, fb);
	}
}

void clear_array(uint16_t colour, uint16_t* pixels)
{
	for (size_t i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++)
	{
		pixels[i] = colour;
	}
}

void draw(unsigned char* parlcd_mem_base, uint16_t* pixels)
{
	parlcd_write_cmd(parlcd_mem_base, 0x2c);
	for (int i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++) 
	{
		parlcd_write_data(parlcd_mem_base, pixels[i]);
	}
}

void led_line(uint32_t val_line, unsigned char* mem_base)
{
	*(volatile uint32_t*)(mem_base + SPILED_REG_LED_LINE_o) = val_line;
}

void led_RGB1(uint32_t colour, unsigned char* mem_base)
{
	*(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = colour;
}

void led_RGB2(uint32_t colour, unsigned char* mem_base)
{
	*(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = colour;
}



