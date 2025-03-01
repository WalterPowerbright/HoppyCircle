typedef struct {
	Vector2 velocity;
	Vector2 position;
	float radius;
} Player;

void init_player(Player *p_player);
void player_jump(Player *p_player);
void apply_player_gravity(Player *p_player, float delta_time);
void draw_player(Player *p_player);

/* LINE BREAK */

void init_player(Player* p_player) {
	p_player->radius = 16.0;
	p_player->position.x = 64.0;
	p_player->position.y = (SCREEN_HEIGHT / 2) - 8.0;
	
	p_player->velocity.x = 0.0;
	p_player->velocity.y = 0.0;
}

void player_jump(Player *p_player) {
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		p_player->velocity.y = PLAYER_JUMP_FORCE;
	}
}

void apply_player_gravity(Player* p_player, float delta_time) {
	p_player->velocity.y += GRAVITY * delta_time;
	p_player->position.y += p_player->velocity.y;
}

void draw_player(Player *p_player) {
	DrawCircle(p_player->position.x, p_player->position.y, p_player->radius, NOKIA_LIGHT);
}
