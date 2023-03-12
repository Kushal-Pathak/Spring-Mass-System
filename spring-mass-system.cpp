#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <ctime>
#define height 900
#define width 1200

class Mass {
public:
	sf::Vector2f original_pos;
	sf::Vector2f pos;
	sf::Vector2f parent_pos;
	float m = 1, v = 0, a = 0, f = 0, k = 1, e = 0, de = 0, radius = 7, length = 50;
	sf::Color color;
	sf::CircleShape circle;
	sf::Vertex line[2];
	Mass() {

	}
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
		  f = -k * e;
		  a = f / m;
		  v = v + a;
		  pos.y = pos.y + v;
		  e =  pos.y - original_pos.y;
		  v = v * 0.975f;
		  circle.setPosition(pos);
		  line[1] = sf::Vector2f(circle.getPosition());
	  }
};
int main() {
	srand(unsigned int(time(0)));
	sf::RenderWindow window(sf::VideoMode(width, height), "My Window");
	sf::Vector2f parent;
	parent.x = width / 2;
	parent.y = 0;
	Mass masses[10];
	masses[0] = Mass(5, parent, 50, 1, 10, sf::Color::Red);
	int temp_len, temp_ext;
	for (int i = 1; i < 10; i++) {
		temp_len = 20 + rand() % 51;
		temp_ext = 10 + rand() % 50;
		masses[i] = Mass(5, masses[i - 1].pos,(float) temp_len, 1,(float) temp_ext, sf::Color::Green);
	}
	//mass, anchor_position, length, spring_const, extension, color
	Mass m1(5, parent, 50, 1, 10, sf::Color::Red);

	while (window.isOpen()) {
		for (int i = 0; i < 10; i++) {
			masses[i].update();
			if (i > 0) {
				masses[i].parent_pos = masses[i - 1].pos;
				masses[i].line[0] = sf::Vector2f(masses[i - 1].pos);
			}
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		Sleep(100);
		window.clear(sf::Color::Black);
		//window.draw(m1.line, 2, sf::Lines);
		//window.draw(m1.circle);
		for (int i = 0; i < 10; i++) {
			window.draw(masses[i].line, 2, sf::Lines);
		}
		for (int i = 0; i < 10; i++) {
			window.draw(masses[i].circle);
		}
		window.display();
	}
}
