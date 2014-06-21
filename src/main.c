/*
 * test.c
 *
 *  Created on: Jun 21, 2014
 *
 *      Author: dis-card
 *
 *	   Purpose: 
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
#define		SCREEN_WIDTH		800
#define		SCREEN_HEIGHT		600
int returnCode = SUCCESS;
ALLEGRO_DISPLAY *display = NULL;

int init(void);
void destroy(void);

int main (void )
{


	init();
	al_rest(5.0);
	destroy();

	return returnCode;

}

/* This method will initialize all the essential aspects of the game */
int init(void)
{
	if ( !al_init() )
	{
		al_show_native_message_box(NULL,error,NULL,"Error in initializing Allegro!",NULL,NULL);
		returnCode = AL_INIT_ERR;
		return returnCode;
	}

	display = al_create_display(SCREEN_WIDTH,SCREEN_HEIGHT);

	if ( !display )
	{
		al_show_native_message_box(NULL,error,NULL,"Error in creating display!",NULL,NULL);
		returnCode = AL_DISPLAY_ERR;
		return returnCode;
	}

	al_init_font_addon();
	al_init_ttf_addon();
}

void destroy(void)
{
	al_destroy_display(display);
}
