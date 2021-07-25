#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <thread>

void BubbleSort(std::vector<sf::RectangleShape>& Shapes);

int main()
{
	// Объект, который, собственно, является главным окном приложения
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML Works!");


	std::vector<sf::RectangleShape> Shapes;

	for (int i = 0; i < 250; i++) {
		Shapes.push_back(sf::RectangleShape(sf::Vector2f(2.f,10.f)));
	}
	
	for (int i = 0; i < Shapes.size(); i++)
	{
		Shapes[i].setSize(sf::Vector2f(Shapes[i].getSize().x, rand() % 150));
	}

	for (int i = 0; i < Shapes.size(); i++) {

		Shapes[i].setPosition( Shapes[i].getSize().x *i, window.getSize().y - Shapes[i].getSize().y);
	}

	std::thread thr(BubbleSort, std::ref(Shapes));
	
	thr.detach();

	while (window.isOpen())
	{
		
		// Обрабатываем очередь событий в цикле
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == sf::Event::Closed)
				// тогда закрываем его
				window.close();
		}

		for (int i = 0; i < Shapes.size(); i++) {
			
			window.draw(Shapes[i]);
		}
		
		window.display();
		window.clear();
	}

	return 0;
}

void BubbleSort(std::vector<sf::RectangleShape> &Shapes) {
	for (int i = 0; i < Shapes.size(); i++) {
		for (int j = Shapes.size()-1; j > i; j--) {
			if (Shapes[j - 1].getSize().y > Shapes[j].getSize().y) {
				int xOfShapeOne = Shapes[j - 1].getPosition().x;
				Shapes[j - 1].setPosition(Shapes[j].getPosition().x, Shapes[j - 1].getPosition().y);
				Shapes[j].setPosition(xOfShapeOne, Shapes[j].getPosition().y);
				std::swap(Shapes[j - 1], Shapes[j]);
				sf::sleep(sf::milliseconds(1));
			}
		}
	}
}
