#include <iostream>
#include <fstream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cmath>
#include <string>
#include <locale>
using namespace sf;
using namespace std;

double random(double min, double max)
{
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}

int main()
{
    sf::RenderWindow window(VideoMode::getDesktopMode(), "SFML works!");

    int flag_animation = -1;

    Texture back;
    back.loadFromFile("images/background.jpg"); // загружаем не односложный фон из файла
    Sprite background;
    background.setScale(0.8f, 0.8f);
    background.setTexture(back);
    float x0 = 800, y0 = 1000; // задаём стартовое положение ракеты
    // рисуем ракету относительно начальной точки
    VertexArray body(Triangles, 3);
    int i = 501;
    body[0].color = Color::Red;
    body[1].color = Color::Red;
    body[2].color = Color::Red;
    RectangleShape charge(Vector2f(40, 80));
    charge.setFillColor(Color::Black);
    CircleShape sparks;
    int explosion = 0;
    sparks.setFillColor(Color::Red);
    sparks.setRadius(5);
    sparks.setPosition(x0, 100);

    float move_speed = 0.5;
    float degree = 0.2;
    float high = 0.1;
    float fall_speed = 0.1;
    vector<CircleShape> sparksArray(100); // Создаем массив из 100 объектов CircleShape
    for (int i = 0; i < 100; ++i)
    {
        sparksArray[i].setFillColor(Color::Yellow);
        sparksArray[i].setRadius(5);
        sparksArray[i].setPosition(x0, 100);
    }
    while (window.isOpen())
    {
        if (!explosion)
        {
            body[0].position = Vector2f(x0 - 30, y0);
            body[1].position = Vector2f(x0 + 20, y0 - 70);
            body[2].position = Vector2f(x0 + 70, y0);
            charge.setPosition(x0, y0);
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        } 
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();
        if (i > 500)
        {
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                flag_animation *= -1; 
                i = 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                move_speed += 0.1;
                i = 200;
                fall_speed += 0.01;
            }
        }
        
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            if (move_speed - 0.2 > 0)
                move_speed -= 0.1;
            if (fall_speed - 0.02 > 0)
                fall_speed -= 0.01;
        }
         
        if (flag_animation == 1)
        {
            if (explosion)
            {
                high = fall_speed;
                for (int i = 0; i < 100; ++i)
                {
                    sparksArray[i].setPosition(sparksArray[i].getPosition().x - high, sparksArray[i].getPosition().y + fall_speed);
                    high -= (fall_speed / 35);
                }
            }
            else
                y0 -= move_speed;
        }

        if (y0 < 100)
            explosion = 1;

        window.clear();
        
        window.draw(background);
        
        if (!explosion)
        {
            window.draw(charge);
            window.draw(body);
        }
        else
            for (int i = 0; i < 100; i++)
                window.draw(sparksArray[i]);
        window.display();
        // счётчик создан для более комфортной работы с клавишами управления анимацией
        i++;
        if (i > 1000)
            i = 501;
    }

    return 0;
}