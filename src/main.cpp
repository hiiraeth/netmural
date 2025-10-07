// netPcanvas.cpp : Defines the entry point for the application.
//

#include "netmural.h"
#include "DataSource.h"

int main()
{	
	std::atomic<bool> isRunning = false;
	float fHeight = 0;
	DataSource datasource;

	// create window
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "NETMURAL");
	window.setFramerateLimit(60);
	
	// create a bar
	sf::RectangleShape rect({50, 50});
	rect.setFillColor(sf::Color::Magenta);

	// create height var to update bar in window
	std::atomic<float> height = 0.f;

	isRunning = true;

	// thread to allow bar to update independently from any other future funcs
	std::thread dsThread(&DataSource::getValue, &datasource, &height, &isRunning);

	// run while window is open
	while (window.isOpen()) 
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) 
			{
				isRunning = false;
				window.close();				
			}
		}

		fHeight = height.load();

		// sets width and height is variable, to whatever value the datasource is returning
		rect.setSize({ 80.f, fHeight });

		window.clear(sf::Color::Black);
		window.draw(rect);
		window.display();
	}

	dsThread.join();
	return 0;
}
