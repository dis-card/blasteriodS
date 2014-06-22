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

/* clears the screen */
void cls (void)
{
	al_clear_to_color(BLACK);

}
/* gets width of the display */
int get_display_width (ALLEGRO_DISPLAY *display)
{
	return al_get_display_width(display);
}

/* gets height of the display */
int get_display_height( ALLEGRO_DISPLAY *display)
{
	return al_get_display_height(display);
}
