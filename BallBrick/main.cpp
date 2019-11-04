#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

bool intersecting(sf::Shape& _ball, sf::Shape& _brick)
{
	return _ball.getGlobalBounds().intersects(_brick.getGlobalBounds());
}
template<typename T>
int sign(T _val)
{
	return (_val > 0) ? 1 : ((_val < 0) ? -1 : 0);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(5.0f);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100.0f, 180.0f);

	sf::Vector2f shapeVeloc{ -3.0f, -2.0f };


	sf::RectangleShape brick;
	brick.setSize(sf::Vector2f{ 20.0f, 18.0f });
	brick.setOrigin(10.0f, 9.0f);
	brick.setPosition(sf::Vector2f{100, 100});
	brick.setFillColor(sf::Color::Magenta);

	float elapsed{ 0.0f };
	float fps{ 60.0f };
	float frametime{ 1.0f / 60.0f };
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		

		if (elapsed >= frametime)
		{
			std::cout << "FPS: " << 1.0f / elapsed << std::endl;
			if (intersecting(shape, brick))
			{
				auto delta = shape.getPosition() - brick.getPosition();
				if (abs(delta.x) >= abs(delta.y))
				{
					if (sign(-shapeVeloc.x) == sign(delta.x))
					{
						shapeVeloc.x = -shapeVeloc.x;
					}
				}
				else
				{
					// scaled delta y was larger than delta x. This is a vertical hit.
					if (sign(-shapeVeloc.y) == sign(delta.y))
					{
						shapeVeloc.y = -shapeVeloc.y;
					}
				}
			}
			
			
			shape.move(shapeVeloc);
			if (shape.getGlobalBounds().left <= 0) shapeVeloc.x = -shapeVeloc.x;
			if (shape.getGlobalBounds().left + shape.getGlobalBounds().width >= 200) shapeVeloc.x = -shapeVeloc.x;
			if (shape.getGlobalBounds().top <= 0) shapeVeloc.y = -shapeVeloc.y;
			if (shape.getGlobalBounds().top + shape.getGlobalBounds().height >= 200) shapeVeloc.y = -shapeVeloc.y;
			elapsed -= frametime;
		}

		

		window.clear();
		window.draw(shape);
		window.draw(brick);
		window.display();
		elapsed += clock.restart().asSeconds();
	}

	return 0;
}

/*
sf::Vector2f delta = (shape.getposition() - brick.getPosition());
// apply aspect ratio via the scaleFactor vector
// For a horizontal block twice a wide as high, use Vector3(0.5f, 1f, 1f)
// For a vertical block twice as high as wide, use Vector3(1f, 0.5f, 1f)
// For a square block, use Vector3(1f, 1f, 1f), and so forth.
delta.Scale(scaleFactor); 
if(Mathf.Abs(delta.x) >= Mathf.Abs(delta.y))
{
    // scaled delta x was larger than delta y. This is a horizontal hit.
    if(Mathf.Sign(-direction.x) == Mathf.Sign(delta.x))
    {
        ballDirection.x = -ballDirection.x;
        ScoreBlockHit();
    }
}
else
{
    // scaled delta y was larger than delta x. This is a vertical hit.
    if(Mathf.Sign(-direction.y) == Mathf.Sign(delta.y))
    {
        ballDirection.y = -ballDirection.y;
        ScoreBlockHit();
    }
}*/