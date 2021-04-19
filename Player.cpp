#include "Player.h"
#include <math.h>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight):
   animation(texture, imageCount, switchTime) {
   this->speed = speed;
   this->jumpHeight = jumpHeight;
   row = 0;
   faceRight = true;

   body.setSize(sf::Vector2f(100.f, 150.f));
   body.setOrigin(body.getSize() / 2.f);
   body.setPosition(206.f, 206.f);
   body.setTexture(texture);
}

Player::~Player() {}

void Player::Update(float deltaTime) {
   velocity.x *= 0.1f;

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      velocity.x -= speed;
   }
   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      velocity.x += speed;
   }

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {
      canJump = false;
      velocity.y = -sqrtf(2.f * 981.f * jumpHeight);
   }

   velocity.y += 981.f * deltaTime;

   if(velocity.x == 0.f) {
      row = 0;
   } else {
      row = 1;
      faceRight = velocity.x > 0.f;
   }

   animation.Update(row, deltaTime, faceRight);
   body.setTextureRect(animation.uvRect);
   body.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window) {
   window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction) {
   if(direction.x < 0.f) {
      velocity.x = 0.f;
   } else if(direction.x > 0.f) {
      velocity.x = 0.f;
   }
   if(direction.y < 0.f) {
      velocity.y = 0.f;
      canJump = true;
   } else if(direction.y > 0.f) {
      velocity.y = 0.f;
   }
}
