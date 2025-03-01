Pipe pipes[MAX_PIPE_NUM];

int pipe_spawn_timer = 0;

void init_all_pipes(void);
void update_all_pipes(float delta_time);
void draw_all_pipes(void);
void draw_all_checkpoints(void);
void spawn_available_pipe(void);
void run_pipe_spawner(void);

/* LINE BREAK */

void init_all_pipes(void) {
	for (int i = 0; i < MAX_PIPE_NUM; i++) {
		init_pipe(&pipes[i]);
	}
}

void update_all_pipes(float delta_time) {
	for (int i = 0; i < MAX_PIPE_NUM; i++) {
		if (is_offscreen(&pipes[i]))
			continue;
		
		update_pipe(&pipes[i], delta_time);
	}
}

void draw_all_pipes(void) {
	for (int i = 0; i < MAX_PIPE_NUM; i++) {
		if (is_offscreen(&pipes[i]))
			continue;
		
		draw_pipe(&pipes[i]);
	}
}

void spawn_available_pipe(void) {
	for (int i = 0; i < MAX_PIPE_NUM; i++) {
		if (is_offscreen(&pipes[i])) {
			spawn_pipe(&pipes[i]);
			return;
		}
	}
}

void run_pipe_spawner(void) {
	pipe_spawn_timer++;

	if (pipe_spawn_timer >= PIPE_SPAWN_TIME) {
		pipe_spawn_timer = 0;
		
		spawn_available_pipe();
	}
}
