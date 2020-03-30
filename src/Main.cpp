#include "Platform/PlatformHelper.hpp"

int main()
{
	PlatformHelper platform;

	#if defined(_DEBUG)
		std::cout << "Hello World!" << std::endl;
	#endif

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(500.0f * screenScalingFactor, 500.0f * screenScalingFactor), "SFML works!");
	platform.setIcon(window.getSystemHandle());

	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(500, 500));
	shape.setFillColor(sf::Color::White);

	sf::Texture shapeTexture;
	shapeTexture.loadFromFile("content/bg.png");
	shape.setTexture(&shapeTexture);

	sf::Shader shader;
	if (!shader.loadFromFile("content/shader.frag", sf::Shader::Fragment))
	{
		throw "Shaders not available!";
	}
	shader.setUniform("screen", sf::Glsl::Vec2(500.0f, 500.0f));
	shader.setUniform("texture", shapeTexture);
	shader.setUniform("num_lights", 2);
	shader.setUniform("lights[0].position", sf::Glsl::Vec2(275.0f, 250.0f));
	shader.setUniform("lights[0].diffuse", sf::Glsl::Vec3(1.0, 1.0, 1.0));
	shader.setUniform("lights[0].power", 1.0f);
	shader.setUniform("lights[1].position", sf::Glsl::Vec2(150.0f, 0.0f));
	shader.setUniform("lights[1].diffuse", sf::Glsl::Vec3(1.0, 1.0, 1.0));
	shader.setUniform("lights[1].power", 5.0f);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape, &shader);
		window.display();
	}

	return 0;
}
