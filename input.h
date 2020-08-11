/*******************************************************************
  Simple program to implement video game Snake on MicroZed based 
  MZ_APO board designed by Petr Porazil at PiKRON

  input.h - changing stdin mode to RAW, implementation used from 
  https://github.com/capiman/lpc21isp/blob/master/lpc21isp.c#L516, as
  advised by Dr. Pavel Pisa on APO CourseWare forum

  (C) Copyright 2003-2013 by Martin Maurer <Martin.Maurer@clibb.de>
  (C) Portions Copyright 2004 by Aeolus Development

 *******************************************************************/

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>

/*
Change stdin mode to RAW.
*/
void PrepareKeyboardTtySettings();

/*
Indicates if there are chars to be read from the console.
@returns
	1 if there is char from the console ready to be read otherwise 0.
*/
int kbhit();

/*
Reads a single unbuffered char from the keyboard.
@returns
	char read from the keyboard.
*/
char getch();
