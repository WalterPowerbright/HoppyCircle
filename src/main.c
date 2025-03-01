#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "constants.h"

#include "pipe.c"
#include "pipe_spawner.c"
#include "player.c"
#include "ui.c"
#include "collision.c"

typedef enum game_state {
	GAME_START,
	GAME_GAMEPLAY,
	GAME_END
} GameState;

GameState current_game_state;

int score = 0;

Player player;

void initialize(void);
void update(float delta_time);
void draw(void);
void check_collisions(void);
void update_draw_frame(void);

int main() {
	srand( (unsigned int) time(NULL) );

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hoppy Circle");
	
	initialize();

	
	
	#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(update_draw_frame, 60, 1);
	#else
	SetTargetFPS(60);
	
	while (!WindowShouldClose()) {
		update_draw_frame();
	}
	#endif
	
	CloseWindow();

	return 0;
}

/* LINE BREAK */

void initialize(void) {
	current_game_state = GAME_START;
	score = 0;

	init_player(&player);
	init_all_pipes();
	
	init_borders();
}

void update(float delta_time) {
	switch(current_game_state) {
		case GAME_START: {
			player_jump(&player);
			
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				current_game_state = GAME_GAMEPLAY;
			}
			
			break;
		}
		case GAME_GAMEPLAY: {
			player_jump(&player);
			apply_player_gravity(&player, delta_time);
			run_pipe_spawner();
			update_all_pipes(delta_time);
			check_collisions();
			break;
		}
		case GAME_END: {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				initialize();
			}
			break;
		}
	}
}

void draw(void) {
	ClearBackground(NOKIA_DARK);

	switch(current_game_state) {
		case GAME_START: {
			draw_player(&player);
			draw_ui(score);
			draw_title();
			break;
		}
		case GAME_GAMEPLAY: {
			draw_player(&player);
			draw_all_pipes();
			draw_ui(score);
			break;
		}
		case GAME_END: {
			draw_game_over(score);
			break;
		}
	}
}

void check_collisions(void) {
	if (is_colliding_player_borders(&player) ||
is_colliding_player_all_pipes(&player)) {
		current_game_state = GAME_END;
	}
	
	if (is_colliding_player_all_checkpoints(&player)) {
		score++;
	}
}

void update_draw_frame(void) {
	float delta_time = GetFrameTime();
	
	BeginDrawing();
	update(delta_time);
	draw();
	EndDrawing();
}
