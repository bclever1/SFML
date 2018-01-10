#include "stdafx.h"
#include "MyWindow.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

MyWindow::MyWindow()
{
}


MyWindow::~MyWindow()
{
}

int MyWindow::Display(std::string title)
{
#if 0
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
#endif

		sf::Window window;
		window.create(sf::VideoMode(600, 600), title, sf::Style::Default, sf::ContextSettings(32));
		window.setVerticalSyncEnabled(true);

		window.setActive(true);

		//glEnable(GL_TEXTURE_2D);

		bool running = true;
		while (running)
		{
			sf::Event e;
			while (window.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
				{
					running = false;
				}
			}


			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			window.display();
		}

		return 0;

}