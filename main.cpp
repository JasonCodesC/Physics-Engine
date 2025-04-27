// main.cpp
#include "Physics.h"
#include "Ball.h"
#include "Vector2.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <sstream>
#include <iomanip>

int main() {
    const unsigned int windowW = 1200;
    const unsigned int windowH = 800;
    const float scale = 50.0f;

    //Our world: gravity, width and height
    Physics phys(Vector2(0.0f, -19.81f), windowW / scale, windowH / scale);

    //Create balls
    Ball b1(0.95f, 1.0f, Vector2(3.0f, 9.0f));
    Ball b2(0.95f, 1.0f, Vector2(18.0f, 9.0f));
    phys.addBall(&b1);
    phys.addBall(&b2);

    //SFML window
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(windowW, windowH)),"2D Physics Drag & Throw");
    //Set FPS 
    window.setFramerateLimit(60);
    
    //font for velocity display
    sf::Font font;
    bool fontLoaded = false;
    if (font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        fontLoaded = true;
    }
    
    // Thread synchronization
    std::mutex physicsMutex;
    std::atomic<bool> running(true);
    const float physicsDt = 1.0f / 60.0f;

    // Launch physics thread
    std::thread physicsThread([&] {
        while (running) {
            {
                std::lock_guard<std::mutex> lock(physicsMutex);
                phys.step(physicsDt);
            }
            std::this_thread::sleep_for(std::chrono::duration<float>(physicsDt));
        }
    });

    Ball* dragged = nullptr;
    Vector2 lastMouseWorldPos;
    Vector2 dragVel(0.0f, 0.0f);

    while (window.isOpen()) {
        // Event handling
        while (auto optEvt = window.pollEvent()) {
            const auto& evt = *optEvt;

            if (evt.is<sf::Event::Closed>()) {
                window.close();
            }

            //Mouse Clicked
            if (auto* mbp = evt.getIf<sf::Event::MouseButtonPressed>()) {
                if (mbp->button == sf::Mouse::Button::Left) {
                    Vector2 clickPos(mbp->position.x / scale, (windowH - mbp->position.y) / scale);
                    std::lock_guard<std::mutex> lock(physicsMutex);
                    if ((b1.getPosition() - clickPos).length() < b1.getRadius())
                        dragged = &b1;
                    else if ((b2.getPosition() - clickPos).length() < b2.getRadius())
                        dragged = &b2;
                    if (dragged)
                        lastMouseWorldPos = clickPos;
                }
            }

            //Mouse Released
            if (auto* mbr = evt.getIf<sf::Event::MouseButtonReleased>()) {
                if (mbr->button == sf::Mouse::Button::Left && dragged) {
                    {
                        std::lock_guard<std::mutex> lock(physicsMutex);
                        dragged->setVelocity(dragVel);
                    }
                    dragged = nullptr;
                }
            }
        }

        //Moving ball and changing velocity while ball is dragged
        if (dragged) {
            sf::Vector2i mp = sf::Mouse::getPosition(window);
            Vector2 worldPos(mp.x / scale, (windowH - mp.y) / scale);
            dragVel = (worldPos - lastMouseWorldPos) / physicsDt;
            {
                std::lock_guard<std::mutex> lock(physicsMutex);
                dragged->setPosition(worldPos);
            }
            lastMouseWorldPos = worldPos;
        }

        //Render
        Vector2 p1, p2, v1, v2;
        {
            std::lock_guard<std::mutex> lock(physicsMutex);
            p1 = b1.getPosition();
            p2 = b2.getPosition();
            v1 = b1.getVelocity();
            v2 = b2.getVelocity();
        }
        window.clear(sf::Color::Black);

        sf::CircleShape shape1(b1.getRadius() * scale);
        sf::CircleShape shape2(b2.getRadius() * scale);
        shape1.setFillColor(sf::Color::Blue);
        shape2.setFillColor(sf::Color::Yellow);
        shape1.setOrigin(sf::Vector2f(b1.getRadius()*scale, b1.getRadius()*scale));
        shape2.setOrigin(sf::Vector2f(b2.getRadius()*scale, b2.getRadius()*scale));
        shape1.setPosition(sf::Vector2f(p1.x*scale, windowH - p1.y*scale));
        shape2.setPosition(sf::Vector2f(p2.x*scale, windowH - p2.y*scale));
        window.draw(shape1);
        window.draw(shape2);

        //print ball velocities
        if (fontLoaded) {
            std::ostringstream oss1, oss2;
            oss1 << std::fixed << std::setprecision(2)
                << "Blue Velocity: X:"<<v1.x<<" Y:"<<v1.y<<"";

            oss2 << std::fixed << std::setprecision(2)
                << "Yellow Velocity: X:"<<v2.x<<" Y:"<<v2.y<<"";

            sf::Text textBlue(font);
            textBlue.setString(oss1.str());
            textBlue.setCharacterSize(14);
            textBlue.setFillColor(sf::Color::Blue);
            auto boundsBlue = textBlue.getLocalBounds();
            textBlue.setPosition(sf::Vector2f(windowW - boundsBlue.size.x - 10.f, 10.f));
            window.draw(textBlue);

            sf::Text textYellow(font);
            textYellow.setString(oss2.str());
            textYellow.setCharacterSize(14);
            textYellow.setFillColor(sf::Color::Yellow);
            auto boundsYellow = textYellow.getLocalBounds();
            textYellow.setPosition(sf::Vector2f(windowW - boundsYellow.size.x - 10.f, 10.f + boundsBlue.size.y + 5.f));
            window.draw(textYellow);
        }

        window.display();
    }

    //Join threads and return to exit safely
    running = false;
    physicsThread.join();
    return 0;
}
