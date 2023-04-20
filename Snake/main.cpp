#include "include.h"

// function prototypes

void menu_setup();
void menu_display(sf::RenderWindow& window);

int main() {
	
	// create window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT + TILE_SIZE), "Snake");
	menu_setup();
	menu_display(window);
	}
