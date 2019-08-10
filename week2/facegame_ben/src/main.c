
// standard library shit
#include <stdio.h>
//~ #include <stdlib.h>
#include <time.h>

// engine shit
#include "ww.h"

// sprites
#include "dude.h"
#include "sky.h"
#include "ground.h"
#include "grass_decoration.h"

typedef enum { DOWN, LEFT, RIGHT, UP } direction;
typedef enum { IDLE, WALK } movement;

int main( int argc, char * argv[] ) {

	srand(time(0));
	
	// initialization
	if(ww_window_create(argc, argv, "Pixarray", 1024, 576)) {
		printf("Closing..\n");
		return 1;
	}
	
	init_dude();
	init_sky();
	init_ground();
	init_grass_decoration();
	
	// clone sprite
	ww_sprite_t * other_dude = ww_clone_sprite(dude);
	other_dude->pad_x = 0;
	other_dude->pad_y = 0;
	
	// set sprite scale
	other_dude->scale = .3;
	
	direction dir = DOWN;
	movement  mov = IDLE;
	
	// pause ground animation when mov = IDLE
	ground->paused = 1;
	
	char anim = dir;
	
	if (mov == WALK)
		anim += 4;
	
	dude->pad_x = 360;
	dude->pad_y = 80;
	
	// creating 10 x 3 grid
	char ground_slots[10][3];
	
	// sprites in grid
	ww_sprite_t * ground_sprites[10][3];
	
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 3; j++){
			// initialize one sprite in grid
			ground_sprites[i][j] = ww_clone_sprite(grass_decoration);
			// pad at different positions
			ground_sprites[i][j]->pad_x = i * 100;
			ground_sprites[i][j]->pad_y = (j * 83);
			// randomize between animation 1/2/3/NONE
			ground_slots[i][j] = rand() % 34 - 30;
			if (ground_slots[i][j] <= 0){
				ground_slots[i][j] = 0;
			} else {
				ground_sprites[i][j]->active_animation = ground_slots[i][j] - 1;
			}
		}
	}
	
	int x_prog = 10;
	int y_prog = 10;
	
	// primary loop
	while(!ww_window_received_quit_event()) {
		
		// update events
		ww_window_update_events();
		
		// quit
		if(keystate.esc == 1){
			printf("ESC pressed\n");
			ww_window_send_quit_event();
		}
		
		char old_anim = anim;
		
		if(keystate.w || keystate.a || keystate.s || keystate.d){
			mov = WALK;
		} else {
			mov = IDLE;
		}
		
		if(keystate.w){
			dir = UP;
			y_prog--;
		}
		
		if(keystate.a){
			dir = LEFT;
			x_prog--;
		}
		
		if(keystate.s){
			dir = DOWN;
			y_prog++;
		}
		
		if(keystate.d){
			dir = RIGHT;
			x_prog++;
		}
		
		if (x_prog == -10) { // moved left
			x_prog = 0;
			
			for(int i = 9; i > 0; i--){
				for(int j = 0; j < 3; j++){
					ground_slots[i][j] = ground_slots[i - 1][j];
					ground_sprites[i][j]->active_animation = ground_slots[i][j] - 1;
				}
			}
			
			for(int i = 0; i < 3; i++){
				ground_slots[0][i] = rand() % 34 - 30;
				if(ground_slots[0][i] < 0){
					ground_slots[0][i] = 0;
				} else {
					ground_sprites[0][i]->active_animation = ground_slots[0][i] - 1;
				}
			}
		}
		
		if (x_prog == 10) { // moved right
			x_prog = 0;
			
			for(int i = 0; i < 9; i++){
				for(int j = 0; j < 3; j++){
					ground_slots[i][j] = ground_slots[i + 1][j];
					ground_sprites[i][j]->active_animation = ground_slots[i][j] - 1;
				}
			}
			
			for(int i = 0; i < 3; i++){
				ground_slots[9][i] = rand() % 34 - 30;
				if(ground_slots[9][i] < 0){
					ground_slots[9][i] = 0;
				} else {
					ground_sprites[9][i]->active_animation = ground_slots[9][i] - 1;
				}
			}
		}
		
		if (y_prog == -10) { // moved up
			y_prog = 0;
			
			for(int j = 2; j > 0; j--){
				for(int i = 0; i < 10; i++){
					ground_slots[i][j] = ground_slots[i][j - 1];
					ground_sprites[i][j]->active_animation = ground_slots[i][j] - 1;
				}
			}
			
			for(int i = 0; i < 10; i++){
				ground_slots[i][0] = rand() % 34 - 30;
				if(ground_slots[i][0] < 0){
					ground_slots[i][0] = 0;
				} else {
					ground_sprites[i][0]->active_animation = ground_slots[i][0] - 1;
				}
			}
		}
		
		if (y_prog == 10) { // moved down
			y_prog = 0;
			
			for(int j = 0; j < 3; j++){
				for(int i = 0; i < 10; i++){
					ground_slots[i][j] = ground_slots[i][j + 1];
					ground_sprites[i][j]->active_animation = ground_slots[i][j] - 1;
				}
			}
			
			for(int i = 0; i < 10; i++){
				ground_slots[i][2] = rand() % 34 - 30;
				if(ground_slots[i][2] < 0){
					ground_slots[i][2] = 0;
				} else {
					ground_sprites[i][2]->active_animation = ground_slots[i][2] - 1;
				}
			}
		}
		
		anim = dir;
		if (mov == WALK){
			anim += 4;
			ground->paused = 0;
		} else {
			ground->paused = 1;
		}
		
		if(old_anim != anim){
			ww_animation_t * active_dude = dude->animations[dude->active_animation];
			active_dude->active_frame = 0;
			active_dude->d_progress = active_dude->delay[0];
			
			ww_animation_t * active_other_dude = other_dude->animations[other_dude->active_animation];
			active_other_dude->active_frame = 0;
			active_other_dude->d_progress = active_other_dude->delay[0];
		}
		
		dude->active_animation = anim;
		other_dude->active_animation = (anim + 1) % 8;
		
		ww_draw_sprite(sky);
		ww_draw_sprite(ground);
		
		for(int i = 0; i < 10; i++){
			for(int j = 0; j < 3; j++){
				if (ground_slots[i][j] != 0){
					ww_draw_sprite(ground_sprites[i][j]);
				}
			}
		}
		
		ww_draw_sprite(dude);
		ww_draw_sprite(other_dude);
		
		// draw screen
		ww_window_update_buffer();
	}
	
	ww_free_sprite(dude);
	ww_free_sprite(other_dude);
	ww_free_sprite(sky);
	
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 3; j++){
			ww_free_sprite(ground_sprites[i][j]);
		}
	}
	
	// cleanup and exit
	ww_window_destroy();
	return 0;
}
