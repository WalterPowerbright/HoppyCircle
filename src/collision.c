bool is_colliding_player_borders(Player *p_player) {
	return (
		CheckCollisionCircleRec(p_player->position, p_player->radius, top.rectangle) ||
		CheckCollisionCircleRec(p_player->position, p_player->radius, bottom.rectangle)
	);
}

bool is_colliding_player_pipe(Player *p_player, Pipe *p_pipe) {
	for (int i = 0; i < PIPE_LENGTH; i++) {
		if (CheckCollisionCircleRec(p_player->position, p_player->radius, p_pipe->blocks[i]))
			return true;
	}
	
	return false;
}

bool is_colliding_player_checkpoint(Player *p_player, Pipe *p_pipe) {
	if (CheckCollisionCircleRec(p_player->position, p_player->radius, p_pipe->checkpoint.rectangle) && !p_pipe->checkpoint.is_touched) {
		p_pipe->checkpoint.is_touched = true;
		return true;
	} else {
		return false;
	}
}

bool is_colliding_player_all_pipes(Player *p_player) {
	for (int i = 0; i < MAX_PIPE_NUM; i++) {
		if (is_offscreen(&pipes[i]))
			continue;
		
		if (is_colliding_player_pipe(p_player, &pipes[i]))
			return true;
	}
	
	return false;
}

bool is_colliding_player_all_checkpoints(Player *p_player) {
	for (int i = 0; i < MAX_PIPE_NUM; i++) {
		if (is_offscreen(&pipes[i]))
			continue;
		
		if (is_colliding_player_checkpoint(p_player, &pipes[i]))
			return true;
	}
	
	return false;
}
