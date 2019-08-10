//Standard library shit
#include <stdio.h>

//Engine Shit
#include "ww.h"

//sprites shit
#include "face.h"
#include "rocket.h"

int main( int argc, char * argv[] ) {

	
	//initialization
	if(ww_window_create(argc, argv, "Pixarray", 1024, 576)) {
		printf("Closing..\n");
		return 1;
	}
	
	init_face();
	init_rocket();
		
	int x_direction = 3; 
	int y_direction = 3;
	
	//primary loop
	while(!ww_window_received_quit_event()) {
				
		//update events
		ww_window_update_events();	
		
		//quit
		if (keystate.esc == 1){
			printf ("ESC pressed\n") ;
			ww_window_send_quit_event() ; 
		}
		
		
		//move rocket 
		
		if (keystate.s == 1) {
			rocket->pad_y =  rocket->pad_y + 1 ;
		}
		if (keystate.d == 1) {
			rocket->pad_x = rocket->pad_x + 1; 
		}
		if (keystate.w == 1) {
			rocket->pad_y =  rocket->pad_y - 1;
		}
		if (keystate.a == 1) {
			rocket->pad_x =  rocket->pad_x - 1; 
		}
		
				
		// move x
		face->pad_x = face->pad_x + x_direction;
		
		// change direction
		if (face->pad_x > 500 ){
			x_direction = x_direction * -1;			
		}
		if (face->pad_y < 0){
			x_direction = x_direction * -1;
		}
		
		// move y		
		face->pad_y = face->pad_y + y_direction;
		
		// change direction
		if (face->pad_y > 500 ){
			y_direction = y_direction * -1;			
		}
		if (face->pad_y < 0){
			y_direction = y_direction * -1;
		}
	
		
		ww_draw_sprite(face) ; 
		ww_draw_sprite(rocket) ;
		
		printf ("rcoket->pad_y: %d\n", rocket->pad_y); 
		printf ("rocket->pad_x: %d\n", rocket->pad_x);
		//draw screen
		ww_window_update_buffer() ; 
	}
	
		ww_free_sprite(face) ; 
		ww_free_sprite(rocket) ; 
		
		//clean up and exit
		ww_window_destroy() ; 
		return 0;
}
