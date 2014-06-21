/*
 * main.c
 *
 *  Created on: Jun 21, 2014
 *
 *      Author: dis-card
 *
 *	   Purpose: Main file, contains main function;
 *
 */

#include	<allegro5/allegro.h>
#include	<allegro5/allegro_native_dialog.h>
#include	<allegro5/allegro_font.h>
#include	<allegro5/allegro_ttf.h>
#include	<stdio.h>

#include	"headers/return_code.h"
#include	"headers/functions.h"
#include	"headers/constants.h"
#include	"headers/colors.h"
int returnCode = SUCCESS;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_FONT *font = NULL;
int screen_w = 0;
int screen_h = 0;
int init(void);
void destroy(void);

int main (void )
{


	init();

	cls();
	al_draw_textf(font,MAGENTA,get_screen_width(display)/2,get_screen_height(display)/2,ALLEGRO_ALIGN_CENTRE,GAME_TITLE);

	al_flip_display();
	al_rest(5.0);
	destroy();

	return returnCode;

}

/* This method will initialize all the essential aspects of the game */
int init(void)
{
	if ( !al_init() )
	{
		al_show_native_message_box(NO_DISPLAY,GAME_TITLE,error,"Error in initializing Allegro!",NULL,NO_FLAGS);
		returnCode = AL_INIT_ERR;
		return returnCode;
	}

	display = al_create_display(SCREEN_WIDTH,SCREEN_HEIGHT);

	if ( !display )
	{
		al_show_native_message_box(display,error,NULL,"Error in creating display!",NULL,NO_FLAGS);
		returnCode = AL_DISPLAY_ERR;
		return returnCode;
	}
	screen_w = al_get_display_width(display);
	screen_h = al_get_display_height(display);

	al_init_font_addon();
	al_init_ttf_addon();
	font = al_load_font(FONTPATH,FONT_SIZE,NO_FLAGS);
	if ( !font )
	{
		al_show_native_message_box(display,GAME_TITLE,warning,"Error in loading font!",NULL,NO_FLAGS);
		returnCode = AL_LOAD_FONT_WARN;
		return returnCode;
	}
}

void destroy(void)
{
	al_destroy_display(display);
}
