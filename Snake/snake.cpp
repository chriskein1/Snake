#include "include.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <queue>

// store direction
int current_direction = -1;

// text and font variables to display the length and high score
sf::Text display_length;
sf::Font display_font;

sf::Text display_high_score;

// variable to check if the player is dead
bool dead = false;

// variable to check if a key has been pressed
bool key_pressed = false;

// store movement to allow for smoother turns
std::queue<int> movement_queue;

// movement vector
sf::Vector2f movement = { INITIAL_X, INITIAL_Y };

// create snake head
sf::RectangleShape snake(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2));

// create snake body and a container
std::vector<sf::RectangleShape> snake_body;
sf::RectangleShape body(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2));

// create fruit
sf::RectangleShape fruit(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2));

void get_head_color(int head_color, sf::RectangleShape& snake);
void get_body_color(int body_color, sf::RectangleShape& body);
void increase_length(int length_increase);
void move_snake(int screen_wrapping);
sf::Vector2f spawn_fruit();

void play_snake(sf::RenderWindow& window, sf::Event& evnt, int& head_color, int& body_color, int& screen_wrapping, int& length_increase) {

	static int high_score = 0;

	// seed time for random number generation
	std::srand(time(NULL));

	get_head_color(head_color, snake);

	get_body_color(body_color, body);
	
	fruit.setFillColor(sf::Color::Red);

	// set random position of fruit
	sf::Vector2f random_location = spawn_fruit();
	fruit.setPosition(random_location.x * TILE_SIZE, random_location.y * TILE_SIZE);

	// set the text to a font
	display_font.loadFromFile("Required\\arcade_font.ttf");
	display_length.setFont(display_font);

	display_high_score.setFont(display_font);
	if (high_score < 100) display_high_score.setPosition(TILE_SIZE * 17, 0);
	else display_high_score.setPosition(TILE_SIZE * 16, 0);
	


	while (window.isOpen()) {
		while (window.pollEvent(evnt)) {
			if (evnt.type == evnt.Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
		}

		// check for collision with fruit
		if (movement.x == random_location.x && movement.y == random_location.y) {
			// add to the body	
			increase_length(length_increase);

			// update random location
			random_location = spawn_fruit();

			// set new position for fruit
			fruit.setPosition(random_location.x * TILE_SIZE, random_location.y * TILE_SIZE);
		}

		move_snake(screen_wrapping);

		// update the snake's position if the snake is still alive
		if (!dead) snake.setPosition(movement.x * TILE_SIZE, movement.y * TILE_SIZE);

		// restart upon death
		if (dead) {
			window.clear();
			dead = false;
			current_direction = -1;
			if (snake_body.size() + 1 > high_score) high_score = snake_body.size() + 1;
			if (high_score > 999) high_score = 999;
			snake_body.clear();
			movement = { 12, 13 };
			snake.setPosition(movement.x * TILE_SIZE, movement.y * TILE_SIZE);

			// update random location
			random_location = spawn_fruit();

			// set new position for fruit
			fruit.setPosition(random_location.x * TILE_SIZE, random_location.y * TILE_SIZE);
		}

		// update score
		display_length.setString("LENGTH: " + std::to_string(snake_body.size() + 1));



		window.clear();
		window.draw(fruit);
		window.draw(display_length);
		if (high_score > 0)
			if (high_score > 0){
				display_high_score.setString("HIGH: " + std::to_string(high_score));
				window.draw(display_high_score);
	}
		window.draw(snake);
		// loop through each tile of the snake's body and draw
		for (int i = 0; i < snake_body.size(); i++) {
			if (snake_body[i].getPosition().y != 0) {
				window.draw(snake_body[i]);
			}
		}
		window.display();

		sf::sleep(sf::milliseconds(80));
	}
}

void get_head_color(int head_color, sf::RectangleShape& snake) {
	if (head_color == 0) {
		snake.setFillColor(sf::Color::Magenta);
	}
	if (head_color == 1) {
		snake.setFillColor(sf::Color::Green);
	}
	if (head_color == 2) {
		snake.setFillColor(sf::Color::Red);
	}
	if (head_color == 3) {
		snake.setFillColor(sf::Color::Yellow);
	}
	if (head_color == 4) {
		snake.setFillColor(sf::Color::Blue);
	}
}

void get_body_color(int body_color, sf::RectangleShape& body) {
	if (body_color == 0) {
		body.setFillColor(sf::Color::Magenta);
	}
	if (body_color == 1) {
		body.setFillColor(sf::Color::Green);
	}
	if (body_color == 2) {
		body.setFillColor(sf::Color::Red);
	}
	if (body_color == 3) {
		body.setFillColor(sf::Color::Yellow);
	}
	if (body_color == 4) {
		body.setFillColor(sf::Color::Blue);
	}
}

void increase_length(int length_increase) {
	if (length_increase == 1)
		snake_body.push_back(body);

	if (length_increase == 2) {
		snake_body.push_back(body);
		snake_body.push_back(body);
	}
	if (length_increase == 3) {
		snake_body.push_back(body);
		snake_body.push_back(body);
		snake_body.push_back(body);
	}
}

void move_snake(int screen_wrapping) {

	// move snake based on key press and ensure that they aren't going the opposite direction
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && current_direction != 1 && !key_pressed) {
		current_direction = 0;
		key_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && current_direction != 0 && !key_pressed) {
		current_direction = 1;
		key_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && current_direction != 3 && !key_pressed) {
		current_direction = 2;
		key_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && current_direction != 2 && !key_pressed) {
		current_direction = 3;
		key_pressed = true;
	}

	// add to the queue
	movement_queue.push(current_direction);

	if (sf::Event::KeyReleased) key_pressed = false;

	// move based on first input in queue
	if (movement_queue.front() == 0) movement.y -= 1;
	if (movement_queue.front() == 1) movement.y += 1;
	if (movement_queue.front() == 2) movement.x -= 1;
	if (movement_queue.front() == 3) movement.x += 1;

	// remove first element from queue
	if (movement_queue.size() > 0) movement_queue.pop();

	if (screen_wrapping == 0) {
		// kill player if outside bounds
		if (movement.x < 0 || movement.y < 1 || movement.x > GRID_WIDTH - 1 || movement.y > GRID_HEIGHT) dead = true;
	}
	else {
		if (movement.x < 0) movement.x = GRID_WIDTH - 1;
		if (movement.x > GRID_WIDTH - 1) movement.x = 0;
		if (movement.y < 1) movement.y = GRID_HEIGHT;
		if (movement.y > GRID_HEIGHT) movement.y = 1;
	}


	if (snake_body.size() > 0) {
		for (int i = snake_body.size() - 1; i > 0; i--) {
			// set the current body tile to the body tile in front of it
			snake_body[i].setPosition(snake_body[i - 1].getPosition());
			// kill the player and end loop if there is collision between any body tile and the head
			if (snake_body[i].getPosition() == snake.getPosition()) {
				dead = true;
				break;
			}
		}
		snake_body[0].setPosition(snake.getPosition());
	}
}

sf::Vector2f spawn_fruit() {

	sf::Vector2f random_location;

	// flag set to true to loop to see if there is actually collision
	bool collision = true;

	while (collision) {
		// if there is no collision, it will stay false
		collision = false;
		// set spawn location based on time elapsed (cheap way to make random numbers)
		random_location.x = rand() % GRID_WIDTH;
		random_location.y = rand() % GRID_HEIGHT + 1;

		// make sure x and y isn't the same as the snake's current x and y
		if (random_location.x == movement.x && random_location.y == movement.y) collision = true;

		// make sure x and y isn't the same as snake body's current x and y
		for (int i = 0; i < snake_body.size(); i++) {
			if ((snake_body[i].getPosition().x / TILE_SIZE) == random_location.x && (snake_body[i].getPosition().y / TILE_SIZE) == random_location.y) {
				collision = true;
				break;
			}
		}
	}

	// return the vector
	return random_location;
}