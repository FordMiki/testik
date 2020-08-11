/*******************************************************************
  Simple program to implement Snake video game on MicroZed based 
  MZ_APO board designed by Petr Porazil at PiKRON

  Rectangle.h - class that implements game tiles

  (C) Copyright 2020 by Jiri Povolny and Marian Krotil
      e-mail:   povolji2@fel.cvut.cz, krotima1@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

class Rectangle
{
    public:
        int x, y, w, h;
        /*
        Constructor of rectangle
        @param
        	int startX - x coord of upper left corner of rectangle
        	int startY - y coord of upper left corner of rectangle
        	int width - width of rectangle
        	int height - height of rectangle
        */
        Rectangle(int startX, int startY, int width, int height)
        {
            x = startX;
            y = startY;
            w = width;
            h = height;
        }
        
        /*
        Check if passed rectangle intersects with current rectangle
        @param
        	Rectangle* rect - rectangle
        @return
        	if rectangles intersect than true, otherwise false
        */
        bool intersects(Rectangle *rect)
        {
            if (x > rect->x + rect->w || rect->x > x + w) 	
            {
                return false;
            }
            if (y > rect->y + rect->h || rect->y > y + h) 	
            {
                return false;
            }
            return true; 
        }
};
