#include <SFML/Graphics.hpp>
using namespace sf;
RenderWindow* window;
Mutex mutex;

ConvexShape* triangle;
CircleShape* circle;

void render()
{
    while (window->isOpen())
    {
        sleep(milliseconds(1));

        mutex.lock();
        window->setActive(true);

        window->clear(Color::White);
        window->draw(*circle);
        window->draw(*triangle);
        window->display();

        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                window->close();
            }
        }

        window->setActive(false);
        mutex.unlock();
    }
}


void triangleUpdate()
{
    for (int i = 0; i < 55; i++) {
        mutex.lock();
        window->setActive(true);
        triangle->move(10, 0);
        window->setActive(false);
        mutex.unlock();
        sleep(milliseconds(50));
    }
}

void circleUpdate()
{
    for (int i = 0; i < 35; i++) {
        mutex.lock();
        window->setActive(true);
        circle->move(-10, 0);
        window->setActive(false);
        mutex.unlock();
        sleep(milliseconds(100));
    }
}

int main()
{
    window = new RenderWindow(VideoMode(1080, 720), "Lab3");
    window->setFramerateLimit(60);

    triangle = new ConvexShape;
    triangle->setPointCount(3);
    triangle->setPoint(0, sf::Vector2f(0, 0));
    triangle->setPoint(1, sf::Vector2f(0, 100));
    triangle->setPoint(2, sf::Vector2f(150, 50));
    triangle->setPosition(100, 100);
    triangle->setFillColor(Color::Green);

    circle = new CircleShape();
    circle->setRadius(75);
    circle->setPosition(window->getSize().x*0.6, 300);
    circle->setFillColor(Color::Blue);

    window->clear(Color::White);
    window->draw(*circle);
    window->draw(*triangle);
    window->setActive(false);

    Thread triangleUpdateThread(&triangleUpdate);
    Thread circleUpdateThread(&circleUpdate);

    triangleUpdateThread.launch();
    circleUpdateThread.launch();

    render();
}

