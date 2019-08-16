//Standard library shit
#include <stdio.h>

//Engine Shit
#include "ww.h"

//sprites shit
#include "mc.h"

int main( int argc, char * argv[] ) {
	
	//initialization
	if(ww_window_create(argc, argv, "Pixarray", 1024, 576)) {
		printf("Closing..\n");
		return 1;
		
	}
	
	init_mc();
	mc->scale = .1;
	
	//primary loop
	while(!ww_window_received_quit_event()) {
	
		
			
		//movement
		if (keystate.w == 1) {
		mc->pad_y = mc->pad_y - 2;
		
		}
		
		if (keystate.s == 1) {
		mc->pad_y = mc->pad_y + 2;
		
		}
		
		if (keystate.d == 1) {
		mc->pad_x = mc->pad_x + 2;
		
		}
		
		if (keystate.a == 1) {
		mc->pad_x = mc->pad_x - 2;
		
		}	
		
		//movement animation
		if (keystate.d == 1 && mc->active_animation == 0){
			mc->active_animation = 1;
		}
		else if (keystate.d == 0){
			mc->active_animation = 0;
		}
		
		//update events
		ww_window_update_events();	
		
		//quit
		if (keystate.esc == 1){
			printf ("ESC pressed\n");
			ww_window_send_quit_event(); 
		}
		
		ww_draw_sprite(mc);
		
		//draw screen
		ww_window_update_buffer(); 
	}
		ww_free_sprite(mc); 
		
		//clean up and exit
		ww_window_destroy(); 
		return 0;
}
