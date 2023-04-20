#include "include.h"

sf::Text menu_screen;
sf::Text play;
sf::Text options;

sf::Text select_head_color;
sf::Text head_choice;

sf::Text select_body_color;
sf::Text body_choice;

sf::Text select_screen_wrap;
sf::Text wrap_choice;

sf::Text select_length_increase;
sf::Text length_choice;

sf::Font arcade_font;
sf::Texture cursor;
sf::Sprite selected;

int head_color = 0;
int body_color = 0;
int screen_wrapping = 0;
int length_increase = 1;
int cursor_location = 0;

bool menu = true;
bool options_menu = false;
bool playing = false;
bool key_press = false;

void play_snake(sf::RenderWindow& window, sf::Event& evnt, int& head_color, int& body_color, int& background_style, int& length_increase);
void options_setup();
void options_display();
void main_menu();

void menu_setup() {

	arcade_font.loadFromFile("Required\\arcade_font.ttf");
	menu_screen.setFont(arcade_font);
	menu_screen.setString("SNAKE");
	menu_screen.setCharacterSize(TILE_SIZE * 2);
	menu_screen.setPosition(WINDOW_WIDTH / 2 - TILE_SIZE * 5, TILE_SIZE * 2);

	play.setFont(arcade_font);
	play.setString("PLAY");
	play.setCharacterSize(TILE_SIZE);
	play.setPosition(WINDOW_WIDTH / 2 - TILE_SIZE * 2, WINDOW_HEIGHT / 2);

	options.setFont(arcade_font);
	options.setString("OPTIONS");
	options.setCharacterSize(TILE_SIZE);
	options.setPosition(WINDOW_WIDTH / 2 - TILE_SIZE * 3.5, WINDOW_HEIGHT / 2 + 1.5 * TILE_SIZE);

	cursor.loadFromFile("Required\\selected.png");
	selected.setTexture(cursor);
	selected.setPosition(WINDOW_WIDTH / 2 - TILE_SIZE * 5, WINDOW_HEIGHT / 2);

}

void menu_display(sf::RenderWindow& window) {
	while (window.isOpen()) {

		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == evnt.Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
		}

		if (menu) {
			main_menu();
			window.clear();
			window.draw(menu_screen);
			window.draw(play);
			window.draw(options);
			window.draw(selected);
			window.display();
		}

		if (options_menu) {
			options_display();
			window.clear();
			window.draw(select_head_color);
			window.draw(head_choice);
			window.draw(select_body_color);
			window.draw(body_choice);
			window.draw(select_screen_wrap);
			window.draw(wrap_choice);
			window.draw(select_length_increase);
			window.draw(length_choice);
			window.draw(selected);
			window.display();
		}

		if (playing) play_snake(window, evnt, head_color, body_color, screen_wrapping, length_increase);
		
	}
}

void main_menu() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		selected.setPosition(WINDOW_WIDTH / 2 - TILE_SIZE * 5, WINDOW_HEIGHT / 2);
		cursor_location = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		selected.setPosition(WINDOW_WIDTH / 2 - TILE_SIZE * 5, WINDOW_HEIGHT / 2 + 1.5 * TILE_SIZE);
		cursor_location = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		if (cursor_location == 0) {
			options_menu = false;
			menu = false;
			playing = true;
		}
		else {
			// load options
			options_setup();
			options_menu = true;
			menu = false;
			playing = false;
		}
	}
}

void options_setup() {
	select_head_color.setFont(arcade_font);
	select_head_color.setString("SELECT HEAD COLOR");
	select_head_color.setPosition(TILE_SIZE * 4, TILE_SIZE * 2);

	head_choice.setFont(arcade_font);
	head_choice.setPosition(TILE_SIZE * 4, TILE_SIZE * 3);
	if (head_choice.getString().isEmpty()) head_choice.setString("MAGENTA");

	select_body_color.setFont(arcade_font);
	select_body_color.setString("SELECT BODY COLOR");
	select_body_color.setPosition(TILE_SIZE * 4, TILE_SIZE * 6);

	body_choice.setFont(arcade_font);
	body_choice.setPosition(TILE_SIZE * 4, TILE_SIZE * 7);
	if (body_choice.getString().isEmpty()) body_choice.setString("MAGENTA");

	select_screen_wrap.setFont(arcade_font);
	select_screen_wrap.setString("SCREEN WRAPPING");
	select_screen_wrap.setPosition(TILE_SIZE * 4, TILE_SIZE * 10);

	wrap_choice.setFont(arcade_font);
	wrap_choice.setString("OFF");
	wrap_choice.setPosition(TILE_SIZE * 4, TILE_SIZE * 11);
	
	select_length_increase.setFont(arcade_font);
	select_length_increase.setString("LENGTH INCREASE");
	select_length_increase.setPosition(TILE_SIZE * 4, TILE_SIZE * 14);

	length_choice.setFont(arcade_font);
	length_choice.setPosition(TILE_SIZE * 4, TILE_SIZE * 15);
	if (length_increase == 1) length_choice.setString("1");

	// reset cursor
	selected.setPosition(TILE_SIZE * 3, TILE_SIZE);
	cursor_location = 0;
	key_press = true;
}

void options_display() {

	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		&& !(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		&& !(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		&& !(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		&& !(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) key_press = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !key_press) {
		cursor_location--;
		key_press = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !key_press) {
		cursor_location++;
		key_press = true;
	}

	if (cursor_location < 0) cursor_location = 0;
	if (cursor_location > 3) cursor_location = 3;

	if (cursor_location == 0)
		selected.setPosition(TILE_SIZE * 3, TILE_SIZE * 2);
	if (cursor_location == 1)
		selected.setPosition(TILE_SIZE * 3, TILE_SIZE * 6);
	if (cursor_location == 2)
		selected.setPosition(TILE_SIZE * 3, TILE_SIZE * 10);
	if (cursor_location == 3)
		selected.setPosition(TILE_SIZE * 3, TILE_SIZE * 14);

	if (cursor_location == 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !key_press) {
			head_color++;
			key_press = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !key_press) {
			head_color--;
			key_press = true;
		}

		// wrapping
		if (head_color < 0) head_color = 4;
		if (head_color > 4) head_color = 0;

		if (head_color == 0) {
			head_choice.setString("MAGENTA");
		}
		if (head_color == 1) {
			head_choice.setString("GREEN");
		}
		if (head_color == 2) {
			head_choice.setString("RED");
		}
		if (head_color == 3) {
			head_choice.setString("YELLOW");
		}
		if (head_color == 4) {
			head_choice.setString("BLUE");
		}
	}
	if (cursor_location == 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !key_press) {
			body_color++;
			key_press = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !key_press) {
			body_color--;
			key_press = true;
		}

		// wrapping
		if (body_color < 0) body_color = 4;
		if (body_color > 4) body_color = 0;
		if (body_color == 0) {
			body_choice.setString("MAGENTA");
		}
		if (body_color == 1) {
			body_choice.setString("GREEN");
		}
		if (body_color == 2) {
			body_choice.setString("RED");
		}
		if (body_color == 3) {
			body_choice.setString("YELLOW");
		}
		if (body_color == 4) {
			body_choice.setString("BLUE");
		}
	}

	if (cursor_location == 2) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !key_press) {
			screen_wrapping++;
			key_press = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !key_press) {
			screen_wrapping--;
			key_press = true;
		}

		if (screen_wrapping < 0) screen_wrapping = 1;
		if (screen_wrapping > 1) screen_wrapping = 0;

		if (screen_wrapping == 0)
			wrap_choice.setString("OFF");
		if (screen_wrapping == 1)
			wrap_choice.setString("ON");
	}

	if (cursor_location == 3) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !key_press) {
			length_increase++;
			key_press = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !key_press) {
			length_increase--;
			key_press = true;
		}

		if (length_increase < 1) length_increase = 3;
		if (length_increase > 3) length_increase = 1;

		if (length_increase == 1)
			length_choice.setString("1");
		if (length_increase == 2)
			length_choice.setString("2");
		if (length_increase == 3)
			length_choice.setString("3");
	}

		// start game on enter
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !key_press) {
			menu = false;
			options_menu = false;
			playing = true;
		}
}