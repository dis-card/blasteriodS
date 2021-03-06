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
bool game_over = false;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_FONT *font = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
enum {
	UP, DOWN, LEFT, RIGHT
};
int main(void) {
	int pos_x = 0;
	int pos_y = 0;
	bool redraw = false;

	// track the state of four keys whether they are pressed or unpressed. False mean unpressed.
	bool keys[4] = { false, false, false, false };

	if ( SUCCESS != init())
		goto exit;
	pos_x = get_display_width(display) / 2;
	pos_y = get_display_height(display) / 2;
	al_start_timer(timer);
	while (!game_over) {
		ALLEGRO_EVENT evt;
		al_wait_for_event(event_queue, &evt);
		if (evt.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (evt.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			}
		} else if (evt.type == ALLEGRO_EVENT_KEY_UP) {
			switch (evt.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			}
			if (evt.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				game_over = true;
			}
		} else if (evt.type == ALLEGRO_EVENT_TIMER) {

			pos_y = pos_y - keys[UP] * 5;
			pos_y = pos_y + keys[DOWN] * 5;
			pos_x = pos_x - keys[LEFT] * 5;
			pos_x = pos_x + keys[RIGHT] * 5;
			redraw = true;
		}
		if (redraw && al_is_event_queue_empty(event_queue)) {
			cls();
			al_draw_textf(font, MAGENTA, pos_x, pos_y, ALLEGRO_ALIGN_CENTRE,
			GAME_TITLE);
			al_flip_display();
		}

	}

	exit: destroy();

	return returnCode;

}

/* This method will initialize all the essential aspects of the game */
int init(void) {
	// initializing allegro;
	if (!al_init()) {
		al_show_native_message_box(NO_DISPLAY, GAME_TITLE, error,
				"Error in initializing Allegro!", NULL, NO_FLAGS);
		returnCode = AL_INIT_ERR;
		return returnCode;
	}

	// creating display;
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display) {
		al_show_native_message_box(display, error, NULL,
				"Error in creating display!", NULL, NO_FLAGS);
		returnCode = AL_DISPLAY_ERR;
		return returnCode;
	}

	// initializing font and ttf addons;
	al_init_font_addon();
	al_init_ttf_addon();

	// loading font for the game;
	font = al_load_font(FONTPATH, FONT_SIZE, NO_FLAGS);
	if (!font) {
		al_show_native_message_box(display, GAME_TITLE, warning,
				"Error in loading font!", NULL, NO_FLAGS);
		returnCode = AL_LOAD_FONT_WARN;
		return returnCode;
	}

	// install keyboard;
	if (!al_install_keyboard()) {
		al_show_native_message_box(display, GAME_TITLE, warning,
				"Error in installing keyboard!", NULL, NO_FLAGS);
		returnCode = AL_INSTALL_KBD_WARN;
		return returnCode;
	}

	// create event queue for keyboard events;
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(display, GAME_TITLE, warning,
				"Error in creating event queue!", NULL, NO_FLAGS);
		returnCode = AL_CREATE_EVT_Q_WARN;
		return returnCode;
	}

	// register keyboard event source with the queue;
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	// create timer;
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		al_show_native_message_box(display, GAME_TITLE, warning,
				"Error in creating the timer!", NULL, NO_FLAGS);
		returnCode = AL_CREATE_TIMER_WARN;
		return returnCode;
	}

	// register timer event source with the queue;
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	return returnCode;
}

/*	free the resources used by allegro.	*/
void destroy(void) {
	if (display != NULL)
		al_destroy_display(display);
}
