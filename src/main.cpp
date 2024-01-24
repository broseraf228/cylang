#include <time.h>

#include <string>
#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>

using namespace sf;


const int WINDOW_SIZE_X = 600;
const int WINDOW_SIZE_Y = 400;



int main()
{
    srand(time(NULL));
    RenderWindow window(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), L"Titul", Style::Default);

    //Массив точек
    VertexArray mypoint(Points, 3000000);
    for (int i = 0; i < 3000000; i++)
        mypoint[i].position = Vector2f(rand() % WINDOW_SIZE_X, rand() % WINDOW_SIZE_Y);

    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    float fps;

    while (window.isOpen())
    {

        start = std::chrono::high_resolution_clock::now();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();
        }

        window.clear(Color::Blue);
        window.draw(mypoint); // Точка

        window.display();

        end = std::chrono::high_resolution_clock::now();
        fps = (float)1e9 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        window.setTitle(std::to_string(fps));

    }
    return 0;
}