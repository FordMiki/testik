#define _POSIX_C_SOURCE 200112L

#include "Render.h"
#include "font_types.h"
#include "input.h"

#define LCD_WIDTH 480
#define LCD_HEIGHT 320
#define GAME_WIDTH 320
#define GAME_HEIGHT 320


//VARIABLES USED IN WHOLE GAME
/*
Variable that holds array of LCD display to render
*/
uint16_t *fb;

/*
Variables that holds phys adress of mz_apo board
*/
unsigned char *parlcd_mem_base;
unsigned char *mem_base;

//VARIABLES USED IN GAME LOOP
/*
Enum that has states of game
*/
/*enum game_state
{
	Game,
	Menu,
	Demo,
	Standard,
	Options,
	GameOver,
	End
};*/
//enum game_state gm_state;

/*
It is self-descriptive, :D
*/
//bool game_running;

/*
dir - direction of player's snake that is set by pressed keys on PC keyboard 
	in STANDARD mode 
*/
//enum Snake_Tile::Direction dir;
//Game_Properties game_properties{GAME_WIDTH, GAME_HEIGHT, SIZE_OF_SQUARE, LCD_WIDTH, LCD_HEIGHT, SPEED, SNAKE_1_COLOR, SNAKE_2_COLOR};

//FUNCTIONS USED IN GAME LOOP
/*
update_demo_mode, it is called if game state equals DEMO state. It creates two 
	snakes with simple AI and lets them play. There is a while loop in which 
	game states are updated and	then are rendered. Demo mode ends if any snake 
	died or	if [x] is pressed.
@params 
	Score - to save score of snakes
	Game_Properties - to know game properties
*/
//void update_demo_mode(Score* score, Game_Properties game_properties);

/*
Input, it sets global variable dir (direction of snake)	based on pressed key on
	PC keyboard. This function is called only in Standard mode and only snake 
	ONE can be controled by this Input. [W] = UP, [S] = DOWN, [D] = RIGHT, 
	[A] = LEFT, [X] Ends the Standard game mode.
*/
//void input();

/*
update_standard_mode, it is called if game state equals STANDARD state.	It 
	creates two snakes, one with AI and other controled by player input. There 
	is a while loop in which game states are updated and then are rendered. 
	Standard mode ends if any snake died or	if [x] is pressed.
@params 
	Score - to save score of snakes
	Game_Properties - to know game properties
*/
//void update_standard_mode(Score* score, Game_Properties game_properties);

/*
update_menu_option, it is called if game state equals MENU or OPTIONS state. In 
	menu there are four buttons that can be selected: [1] DEMO mode, 
	[2] STANDARD mode, [3] OPTIONS and [4] QUIT. [1] Starts demo mode, 
	[2] starts standard mode, [3] opens options	in which some parameters of game
	can be changed. [4] Ends game.
	In options there are five buttons: [1] Speed - sets speed (from 1 to 5)	of 
	moves in game (one second to 200 miliseconds). [2] - sets size of Snake 
	tiles in pixels [16..20..32]. [3] - sets color of first snake. [4] - sets
	color of second snake. [5] back to menu (back to menu is also represented
	by pressing key [X]).
	In both Menu and Options selection is represented by pressing keys [W] = up,
	[S] = down, [F] = SELECT, [X] = Back (in options) / End (in menu).
@params 
	Game_Menu - to save previous selection
	Menu_Options - to save previous selection
*/
//void update_menu_option(Game_Menu* menu, Menu_Options* menu_options);

/*
update_menu_option, it is called if game state equals GameOver state. It renders
	statistics of snakes: their score and their color. To skip this and return 
	to Menu press [X] or [F].
@params 
	Score - to use its parameteres to render
*/
//void update_game_over(Score* score);

/*
update_end_scene starts at the end of game.	To skip this press [X].
*/
//void update_end_scene();

/*
loading function starts at the beggining of game and is there just for fun. To 
	skip this press [F].
*/
void running(); //funkce na vypis

//MAIN**************************************
/*
	Main FUNCTION 
*/
int main(int argc, char *argv[])
{
	//iniicializace-???
	parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
	if (parlcd_mem_base == NULL)
	{
		fprintf(stderr, "Error, parlcd_mem_base map_phys_adress doesn't work!\n");
		exit(1);
	}
	parlcd_hx8357_init(parlcd_mem_base);

	mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
	if (mem_base == NULL)
	{
		fprintf(stderr, "Error, mem_base map_phys_adress doesn't work!\n");
		exit(1);
	}

	fb = (uint16_t *)malloc(LCD_WIDTH * LCD_HEIGHT * sizeof(uint16_t));
	if (fb == NULL)
	{
		fprintf(stderr, "Error, fb array can't be allocated!\n");
		exit(1);
	}

	//to prepare keyboard - input.c/.h - je to doporuceny soubor of Pisi.
	PrepareKeyboardTtySettings();

	//led_RGB2(LED_PINK, mem_base);
	//led_RGB1(LED_PINK, mem_base);
	//led_line(LED_LINE_0, mem_base);

	running();

	//led_RGB2(LED_BLACK, mem_base);
	//led_RGB1(LED_BLACK, mem_base);

	free(fb);
	return 0;
}

//END OF MAIN*********************************

void running()
{
	//int xTile = (LCD_WIDTH / 8) - 35, yTile = 3 * (LCD_HEIGHT / 16);
	int xTile = 0, yTile = 0;
	char wsad_str[] = "WSAD/sipky:posun bloku"; //stringy
	char f2_str[] = "F2:Nova hra |F10:Ukoncit hru";
	
	int size_of_str = 0;
	while (wsad_str[size_of_str] != 0)
	{
		size_of_str++;
	}
	char *begin = wsad_str;
	draw_string(xTile, yTile, BRIGHT_WHITE, begin, size_of_str, fb); //funkce na vypis na lcd. Jeste existuje draw pixel. Ten nejspis bude potreba k vykresu hraciho pole
	// 
	//	draw(parlcd_mem_base, fb);

	xTile = 0, yTile = 15;
	size_of_str = 0;
	while (f2_str[size_of_str] != 0)
	{
		size_of_str++;
	}
	begin = f2_str;
	draw_string(xTile, yTile, BRIGHT_WHITE, begin, size_of_str, fb);
	//	draw(parlcd_mem_base, fb);

	printf("START\n");
	//parlcd_delay(50);

	bool end = true;
	while (end)
	{
		if (kbhit() && getch() == 'x') //input read - vypise "Konec Hry!"
		{
			printf("QUIT\n"); //vustup do terminalu
			char konec_str[] = "K o n e c  h r y ! ";
			xTile = 50, yTile = 80;
			size_of_str = 0;
			while (konec_str[size_of_str] != 0)
			{
				size_of_str++;
			}
			begin = konec_str;
			draw_string(xTile, yTile, BRIGHT_WHITE, begin, size_of_str, fb); 
			end = false;
		}

		draw(parlcd_mem_base, fb);

		parlcd_delay(50);
	}
	draw(parlcd_mem_base, fb);
}
