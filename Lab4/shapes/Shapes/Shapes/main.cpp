#include "Canvas.h"
#include "Circle.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Shape.h"
#include "Triangle.h"
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

const std::map<std::string, int> SHAPES_CODES = { { "LineSegment", 1 }, { "Circle", 2 }, { "Rectangle", 3 }, { "Triangle", 4 } };

bool ReadAndAddShape(int code, std::vector<Shape*>& shapes)
{
	double x1, x2, x3, y1, y2, y3, radius;
	uint32_t outlineColor, fillColor{};
	try
	{

		switch (code)
		{
		case 1:
			if (std::cin >> x1 >> y1 >> x2 >> y2 >> std::hex >> outlineColor)
			{
				shapes.push_back(new LineSegment(Point(x1, y1), Point(x2, y2), outlineColor));
				break;
			}
			return false;

		case 2:
			if (std::cin >> x1 >> y1 >> radius >> std::hex >> outlineColor >> std::hex >> fillColor)
			{
				shapes.push_back(new Circle(Point(x1, y1), radius, outlineColor, fillColor));
				break;
			}
			return false;

		case 3:
			if (std::cin >> x1 >> y1 >> x2 >> y2 >> std::hex >> outlineColor >> std::hex >> fillColor)
			{
				shapes.push_back(new Rectangle(Point(x1, y1), Point(x2, y2), outlineColor, fillColor));
				break;
			}
			return false;
		case 4:
			if (std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> std::hex >> outlineColor >> std::hex >> fillColor)
			{
				shapes.push_back(new Triangle(Point(x1, y1), Point(x2, y2), Point(x3, y3), outlineColor, fillColor));
				break;
			}
			return false;

		default:
			break;
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		return false;
	}
}

size_t FindShapeIndexWithMaxArea(std::vector<Shape*> shapes)
{
	size_t indexMaxAreaShape = 0;
	for (size_t i = 1; i < shapes.size(); ++i)
	{
		if (shapes.at(i)->GetArea() > shapes.at(indexMaxAreaShape)->GetArea())
		{
			indexMaxAreaShape = i;
		}
	}

	return indexMaxAreaShape;
}

size_t FindShapeIndexWithMaxPerimeter(std::vector<Shape*> shapes)
{
	size_t indexMaxPerimeterShape = 0;
	for (size_t i = 1; i < shapes.size(); ++i)
	{
		if (shapes.at(i)->GetPerimeter() > shapes.at(indexMaxPerimeterShape)->GetPerimeter())
		{
			indexMaxPerimeterShape = i;
		}
	}

	return indexMaxPerimeterShape;
}

void DrawShapes(std::vector<Shape*> shapes)
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "test");
	Canvas canvas(window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);

		for (auto shape : shapes)
		{
			shape->Draw(canvas);
		}

		window.display();
	}
}

void PrintMaxShapes(std::vector<Shape*> shapes)
{
	if (shapes.size() == 0)
	{
		return;
	}

	size_t indexMaxAreaShape = FindShapeIndexWithMaxArea(shapes);
	size_t indexMaxPerimeterShape = FindShapeIndexWithMaxPerimeter(shapes);
	SolidShape* solidShape1 = dynamic_cast<SolidShape*>(shapes.at(indexMaxAreaShape));
	SolidShape* solidShape2 = dynamic_cast<SolidShape*>(shapes.at(indexMaxPerimeterShape));

	std::cout << "Max area shape: " << shapes.at(indexMaxAreaShape)->ToString() << "\n"
			  << "Area: " << std::fixed << std::setprecision(3) << shapes.at(indexMaxAreaShape)->GetArea() << "\n"
			  << "Perimeter: " << std::fixed << std::setprecision(3) << shapes.at(indexMaxAreaShape)->GetPerimeter() << "\n"
			  << "Outline color: " << std::hex << shapes.at(indexMaxAreaShape)->GetOutlineColor() << "\n";

	if (solidShape1 != nullptr)
	{
		uint32_t fillColor = solidShape1->GetFillColor();
		std::cout << "Fill color: #" << std::hex << fillColor << "\n";
	}

	std::cout << "Max perimeter shape: " << shapes.at(indexMaxPerimeterShape)->ToString() << "\n"
			  << "Area: " << std::fixed << std::setprecision(3) << shapes.at(indexMaxPerimeterShape)->GetArea() << "\n"
			  << "Perimeter: " << std::fixed << std::setprecision(3) << shapes.at(indexMaxPerimeterShape)->GetPerimeter() << "\n"
			  << "Outline color: " << std::hex << shapes.at(indexMaxPerimeterShape)->GetOutlineColor() << "\n";

	if (solidShape2 != nullptr)
	{
		uint32_t fillColor = solidShape2->GetFillColor();
		std::cout << "Fill color: #" << std::hex << fillColor << "\n";
	}
}

int main()
{
	std::vector<Shape*> shapes{};
	std::string shapeName{};

	while (!std::cin.eof())
	{
		if (std::cin >> shapeName)
		{
			auto it = SHAPES_CODES.find(shapeName);
			if (it == SHAPES_CODES.end())
			{
				std::cout << "Error\n";
				continue;
			}

			if (!ReadAndAddShape(it->second, shapes))
			{
				std::cout << "Error\n";
			}
		}
	}

	PrintMaxShapes(shapes);

	/* Circle circle(Point(300, 300), 100, 0x000000, 0x777777);
	LineSegment ls(Point(100, 100), Point(200, 200), 0x000000);
	Rectangle rec(Point(300, 300), Point(400, 500), 0x000000, 0x777777);
	Triangle triangle(Point(500, 200), Point(700, 200), Point(600, 100), 0x000000, 0x777777);*/

	DrawShapes(shapes);

	return 0;
}
