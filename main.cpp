#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 512.f;
 
void ResizeWindow(sf::RenderWindow& window, sf::View& view) {
   sf::Vector2f vector(window.getSize());
   float aspectRatio = float(vector.x) / float(vector.y);
   view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
   std::cout << "debug" << std::endl;
   sf::RenderWindow window(sf::VideoMode(512, 512), "SFML works!", sf::Style::Close | sf::Style::Resize);
   window.setFramerateLimit(30);

   sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

   sf::Texture playerTexture;
   playerTexture.loadFromFile("tux_from_linux.png");

   Player player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.f, 200);

   std::vector<Platform> platforms;

   platforms.push_back(Platform(nullptr, sf::Vector2f(400.f, 200.f), sf::Vector2f(500.f, 200.f)));
   platforms.push_back(Platform(nullptr, sf::Vector2f(400.f, 200.f), sf::Vector2f(500.f, 0.f)));
   platforms.push_back(Platform(nullptr, sf::Vector2f(1000.f, 200.f), sf::Vector2f(500.f, 500.f)));

   float deltaTime = 0.f;
   sf::Clock clock;

   long frameCounter = 0;
   while (window.isOpen())
   {
      std::cout << frameCounter++ << std::endl;

      deltaTime = clock.restart().asSeconds();
      if(deltaTime > 1.f / 20.f) {
         deltaTime = 1.f / 20.f;
      }

      sf::Event evnt;
      while (window.pollEvent(evnt))
      {
         switch(evnt.type) {
            case sf::Event::Closed:
               window.close();
               break;
            case sf::Event::Resized:
               ResizeWindow(window, view);
               break;
         }
      }

      player.Update(deltaTime);

      sf::Vector2f direction;
              
      // Collider playerCollider = player.GetCollider();
      // for(Platform& platform : platforms) {
      //    if(platform.GetCollider().CheckCollision(playerCollider, direction, 1.f)) {
      //       player.OnCollision(direction);
      //    }
      // }

      view.setCenter(player.GetPosition());

      window.clear(sf::Color::Blue);
      window.setView(view);
      player.Draw(window);
      for(Platform& platform : platforms) {
         platform.Draw(window);
      }
      window.display();
   }

   return 0;
}
