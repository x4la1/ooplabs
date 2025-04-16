#include "Canvas.h"
#include "Circle.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
	try
	{
		// Явная проверка VideoMode
		sf::VideoMode mode({ 800, 600 });
		if (!mode.isValid())
		{
			std::cerr << "Invalid video mode!" << std::endl;
			return -1;
		}

		// Создание окна с настройками
		sf::ContextSettings settings;
		settings.antiAliasingLevel = 8;

		sf::RenderWindow window = sf::RenderWindow(mode, "ale");
		if (!window.isOpen())
		{
			std::cerr << "Failed to create window!" << std::endl;
			return -1;
		}

		// Главный цикл
		while (window.isOpen())
		{
			for (auto event = window.pollEvent(); event; event = window.pollEvent())
			{
				if (event->is<sf::Event::Closed>())
				{
					window.close();
				}
			}
			window.clear(sf::Color::Black);
			window.display();
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return -1;
	}
	return 0;
	/* Canvas canvas(window);
	Circle circle(Point(200, 200), 100, 0x000000, 0x940a0a);
	LineSegment ls(Point(100, 100), Point(100, 200), 0x000000);
	Rectangle rec(Point(300, 300), Point(400, 500), 0x000000, 0x2cb30b);
	Triangle triangle(Point(500, 200), Point(700, 200), Point(600, 100), 0x000000, 0x0d79de);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{

			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear();

		circle.Draw(canvas);
		ls.Draw(canvas);
		rec.Draw(canvas);
		triangle.Draw(canvas);

		window.display();
	}

	return 0;*/
}
