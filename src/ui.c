typedef struct {
	Rectangle rectangle;
	Color color;
} Border;

Border top;
Border bottom;

void init_borders();
void draw_borders();
const char* get_score_text(int score);
void draw_ui(int score);

void init_borders() {
	top.rectangle.x = 0.0;
	top.rectangle.y = 0.0;
	top.rectangle.width = SCREEN_WIDTH;
	top.rectangle.height = 64.0;
	
	top.color = NOKIA_LIGHT;
	
	/* LINE BREAK */
	
	bottom.rectangle.x = 0.0;
	bottom.rectangle.y = SCREEN_HEIGHT - 64.0;
	bottom.rectangle.width = SCREEN_WIDTH;
	bottom.rectangle.height = 64.0;
	
	bottom.color = NOKIA_LIGHT;
}

void draw_borders() {
	DrawRectangleRec(top.rectangle, top.color);
	DrawRectangleRec(bottom.rectangle, bottom.color);
}

const char* get_score_text(int score) {
	return TextFormat("%d", score);
}

const char* get_final_score(int score) {
	return TextFormat("Your final score\nis %d", score);
}

void draw_ui(int score) {
	draw_borders();
	DrawText(get_score_text(score), 16.0, 12.0, 48, NOKIA_DARK);
}

void draw_title() {
	DrawText("HOPPY\nCIRCLE", 32.0, 100.0, 64, NOKIA_LIGHT);
	DrawText("Click to start", 32.0, 392.0, 32, NOKIA_LIGHT);
}

void draw_game_over(int score) {
	DrawText("GAME\nOVER", 32.0, 180.0, 64, NOKIA_LIGHT);
	DrawText(get_final_score(score), 32.0, 340.0, 32, NOKIA_LIGHT);
	DrawText("Click to Reset", 32.0, 456.0, 32, NOKIA_LIGHT);
}
