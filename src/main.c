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
ALLEGRO_EVENT_QUEUE *event_queue = NULL;

int main (void )
{


	if ( SUCCESS != init() )
		goto exit;

	cls();
	al_draw_textf(font,MAGENTA,get_display_width(display)/2,get_display_height(display)/2,ALLEGRO_ALIGN_CENTRE,GAME_TITLE);

	al_flip_display();
	al_rest(5.0);

exit:
	destroy();

	return returnCode;

}

/* This method will initialize all the essential aspects of the game */
int init(void)
{
	// initializing allegro;
	if ( !al_init() )
	{
		al_show_native_message_box(NO_DISPLAY,GAME_TITLE,error,"Error in initializing Allegro!",NULL,NO_FLAGS);
		returnCode = AL_INIT_ERR;
		return returnCode;
	}

	// creating display;
	display = al_create_display(SCREEN_WIDTH,SCREEN_HEIGHT);
	if ( !display )
	{
		al_show_native_message_box(display,error,NULL,"Error in creating display!",NULL,NO_FLAGS);
		returnCode = AL_DISPLAY_ERR;
		return returnCode;
	}

	// initializing font and ttf addons;
	al_init_font_addon();
	al_init_ttf_addon();

	// loading font for the game;
	font = al_load_font(FONTPATH,FONT_SIZE,NO_FLAGS);
	if ( !font )
	{
		al_show_native_message_box(display,GAME_TITLE,warning,"Error in loading font!",NULL,NO_FLAGS);
		returnCode = AL_LOAD_FONT_WARN;
		return returnCode;
	}

	// install keyboard;
	if ( !al_install_keyboard() )
	{
		al_show_native_message_box(display,GAME_TITLE,warning,"Error in installing keyboard!",NULL,NO_FLAGS);
		returnCode = AL_INSTALL_KBD_WARN;
		return returnCode;
	}

	// create event queue for keyboard events;
	event_queue = al_create_event_queue ();
	if ( !event_queue )
	{
		al_show_native_message_box(display,GAME_TITLE,warning,"Error in creating event queue!",NULL,NO_FLAGS);
		returnCode = AL_CREATE_EVT_Q_WARN;
		return returnCode;
	}

	// register event source with the queue;
	al_register_event_source(event_queue, al_get_keyboard_event_source());


	return returnCode;
}

void destroy(void)
{
	if ( display != NULL )
		al_destroy_display(display);
}
