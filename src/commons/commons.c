/*
 * commons.c

 *
 *  Created on: Jun 22, 2014
 *
 *      Author: dis-card
 *
 *	   Purpose: Helper methods are here.
 *
 */

#include	"../headers/colors.h"
#include	<allegro5/allegro_primitives.h>

void cls (void)
{
	al_clear_to_color(BLACK);

}

int get_screen_width (ALLEGRO_DISPLAY *display)
{
	return al_get_display_width(display);
}

int get_screen_height( ALLEGRO_DISPLAY *display)
{
	return al_get_display_height(display);
}
