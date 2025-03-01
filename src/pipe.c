typedef struct {
	Rectangle rectangle;
	bool is_touched;
} Checkpoint;

typedef struct {
	Rectangle blocks[PIPE_LENGTH];
	Checkpoint checkpoint;
} Pipe;

void init_pipe(Pipe *p_pipe);
void spawn_pipe(Pipe *p_pipe);
void update_pipe(Pipe *p_pipe, float delta_time);
void draw_pipe(Pipe *p_pipe);
bool is_offscreen(Pipe *p_pipe);

/* LINE BREAK */

void init_pipe(Pipe *p_pipe) {
	for (int i = 0; i < PIPE_LENGTH; i++) {
		p_pipe->blocks[i].width = PIPE_SIZE;
		p_pipe->blocks[i].height = PIPE_SIZE;
		
		p_pipe->blocks[i].x = -PIPE_SIZE;
		p_pipe->blocks[i].y = (i * PIPE_SIZE) + (PIPE_PADDING + (i * PIPE_PADDING));
	}
	
	p_pipe->checkpoint.rectangle.width = CHECKPOINT_SIZE;
	p_pipe->checkpoint.rectangle.height = (PIPE_SIZE * 2) + PIPE_PADDING;
	p_pipe->checkpoint.rectangle.x = -PIPE_SIZE;
	p_pipe->checkpoint.rectangle.y = -PIPE_SIZE;
	p_pipe->checkpoint.is_touched = false;
}

void spawn_pipe(Pipe *p_pipe) {
	int open_gap_index = rand() % (7 - 2 + 1) + 2;
	
	for (int i = 0; i < PIPE_LENGTH; i++) {
		if (i == open_gap_index || i == open_gap_index + 1) {
			p_pipe->blocks[i].x = -PIPE_SIZE;
			p_pipe->checkpoint.rectangle.x = (SCREEN_WIDTH + PIPE_SIZE) + (CHECKPOINT_SIZE / 2);
			p_pipe->checkpoint.rectangle.y = p_pipe->blocks[open_gap_index].y;
		} else {
			p_pipe->blocks[i].x = SCREEN_WIDTH + PIPE_SIZE;
		}
	}
	
	p_pipe->checkpoint.is_touched = false;
}

void update_pipe(Pipe* p_pipe, float delta_time) {
	p_pipe->checkpoint.rectangle.x -= PIPE_SPEED * delta_time;

	for (int i = 0; i < PIPE_LENGTH; i++) {
		p_pipe->blocks[i].x -= PIPE_SPEED * delta_time;
		
	}
}

void draw_pipe(Pipe *p_pipe) {
	for (int i = 0; i < PIPE_LENGTH; i++) {
		if (p_pipe->blocks[i].x > -(PIPE_SIZE + PIPE_PADDING))
			DrawRectangleRec(p_pipe->blocks[i], NOKIA_LIGHT);
	}
	
	// DrawRectangleRec(p_pipe->checkpoint.rectangle, p_pipe->color);
}

bool is_offscreen(Pipe *p_pipe) {
	return p_pipe->blocks[0].x < -(PIPE_SIZE + PIPE_PADDING);
}
