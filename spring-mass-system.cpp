#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <ctime>
#define height 900
#define width 1200

//this class represents a bob with certain mass, certain original position, position of its anchor (parent mass)
class Mass {
public:
	sf::Vector2f original_pos;
	sf::Vector2f pos; //current position of bob
	sf::Vector2f parent_pos;
	//mass, upward velocity, acceleration, force, extension, radius of mass, length of string that connects this bob to its anchor
	float m = 1, v = 0, a = 0, f = 0, k = 1, e = 0, radius = 30, length = 50;
	sf::Color color;
	sf::CircleShape circle;
	sf::Vertex line[2]; //the line that connects this bob and its anchor
	Mass() {
		parent_pos = sf::Vector2f(width / 2, 20);
		m = 10;
		k = 1;
		e = 100;
		original_pos = sf::Vector2f(width / 2, parent_pos.y + 400);
		pos = sf::Vector2f(width / 2, original_pos.y + e);
		color = sf::Color::Green;
		circle.setRadius(radius);
		circle.setFillColor(color);
		circle.setPosition(pos);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		line[0] = sf::Vector2f(parent_pos);
		line[1] = sf::Vector2f(pos);
	}
	//constructor takes mass, parent position(anchor), length of string from this bob to its anchor, spring constant, extension, color
public: Mass(float mass, sf::Vector2f par, float len, float spring_const, float ext, sf::Color col) {
	parent_pos = par;
	m = mass;
	k = spring_const;
	e = ext;
	original_pos = sf::Vector2f(width / 2, parent_pos.y + len);
	pos = sf::Vector2f(width / 2, original_pos.y + e);
	color = col;
	circle.setRadius(radius);
	circle.setFillColor(col);
	circle.setPosition(pos);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	line[0] = sf::Vector2f(parent_pos);
	line[1] = sf::Vector2f(pos);
}
	  void update() {
		  f = -k * e; //Hooke's law
		  a = f / m; //calculating acceleration
		  v = v + a; //calculating velocity
		  pos.y = pos.y + v; //calculating current position
		  e = pos.y - original_pos.y; //claculating new extension
		  v = v * 0.985f; //adding some damping
		  circle.setPosition(pos); //setting new position to the bob
		  line[1] = sf::Vector2f(circle.getPosition()); //updating the position in line array
	  }
};
int main() {
	srand(unsigned int(time(0)));
	sf::RenderWindow window(sf::VideoMode(width, height), "My Window");
	sf::Vector2f parent; // main anchor
	parent.x = width / 2;
	parent.y = 20;
	sf::CircleShape anchor;
	anchor.setRadius(10.0f);
	anchor.setPosition(parent);
	anchor.setOrigin(anchor.getRadius(), anchor.getRadius());
	anchor.setFillColor(sf::Color::Blue);
	Mass m;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		Sleep(100);
		window.clear(sf::Color::Black);
		window.draw(m.line, 2, sf::Lines);
		window.draw(m.circle);
		window.draw(anchor);
		window.display();
		m.update();
	}
}
