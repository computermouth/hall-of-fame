//Standard library shit
#include <stdio.h>

//Engine Shit
#include "ww.h"

//sprites shit
#include "face.h"

int main( int argc, char * argv[] ) {
	
	//initialization
	if(ww_window_create(argc, argv, "Pixarray", 1024, 576)) {
		printf("Closing..\n");
		return 1;
	}
	
	init_face();
	
	// make a copy of face and set its position
	ww_sprite_t * new_face = ww_clone_sprite(face);
	new_face->pad_x = 300;
	new_face->pad_y = 300;
	
	// make five copies of face, set their position
	// and scale in proportion to their position [i] in the array
	ww_sprite_t * five_faces[5];
	for(int i = 0; i < 5; i++){
		five_faces[i] = ww_clone_sprite(face);
		five_faces[i]->pad_x = i * 100;
		five_faces[i]->pad_y = i * 100;
		five_faces[i]->scale = i * .2;
	}
	

	//primary loop
	while(!ww_window_received_quit_event()) {
		
		//update events
		ww_window_update_events();	
		
		//quit
		if (keystate.esc == 1){
			printf ("ESC pressed\n") ;
			ww_window_send_quit_event() ; 
		}	
		
		ww_draw_sprite(face);
		ww_draw_sprite(new_face);
		
		// draw all the sprites in five_faces
		// in the order in which they appear in the array
		// (fifth face is on top, first face is on bottom)
		for(int i = 0; i < 5; i++){
			ww_draw_sprite(five_faces[i]);
		}
		
		//draw screen
		ww_window_update_buffer(); 
	}
		
		ww_free_sprite(new_face);
		ww_free_sprite(face); 
		
		// free all the cloned faces
		for(int i = 0; i < 5; i++){
			ww_free_sprite(five_faces[i]);
		}
		
		//clean up and exit
		ww_window_destroy(); 
		return 0;
}
