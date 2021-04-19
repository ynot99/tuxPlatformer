#include "Collider.h"

Collider::Collider(sf::RectangleShape& body):
   body(body) {}

Collider::~Collider() {}

bool Collider::CheckCollision(Collider& other, sf::Vector2f& direction, float push) {
   sf::Vector2f otherPosition = other.GetPosition();
   sf::Vector2f otherHalfSize = other.GetHalfSize();
   sf::Vector2f thisPosition = GetPosition();
   sf::Vector2f thisHalfSize = GetHalfSize();

   float deltaX = otherPosition.x - thisPosition.x;
   float deltaY = otherPosition.y - thisPosition.y;

   float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
   float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

   if(intersectX < 0.f && intersectY < 0.f) {
      push = std::min(std::max(push, 0.f), 1.f);

      if(abs(intersectX) < abs(intersectY)) {
         if(deltaX > 0.f) {
            Move(intersectX * (1.f - push), 0.f);
            other.Move(-intersectX * push, 0.f);
            direction.x = 1.f;
            direction.y = 0.f;
         } else {
            Move(-intersectX * (1.f - push), 0.f);
            other.Move(intersectX * push, 0.f);
            direction.x = -1.f;
            direction.y = 0.f;
         }
      } else {
         if(deltaY > 0.f) {
            Move(0.f, intersectY * (1.f - push));
            other.Move(0.f, -intersectY * push);
            direction.x = 0.f;
            direction.y = 1.f;
         } else {
            Move(0.f, -intersectY * (1.f - push));
            other.Move(0.f, intersectY * push);
            direction.x = 0.f;
            direction.y = -1.f;
         }
      }

      return true;
   }

   return false;
}
