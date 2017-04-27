#include <Arduino.h>

#include "Pool.h"
#include "Tween.h"

Pool::Pool(int length) {
  this->_length = abs(length);

  this->_tweens = (Tween*) calloc(this->_length, sizeof(Tween));
  for(unsigned int i = 0; i < this->_length; i++) { this->_tweens[i] = Tween(); }
}

Tween* Pool::get() {
//  Serial.print("Pool length:" + (String)this->_length);

  for(int i = 0; i < this->_length; i++) {
    if (!this->_tweens[i].active()) {
      this->_tweens[i].recycle();
      return &this->_tweens[i];
    }
  }

  return NULL;
}

void Pool::flush() {
  for(int i = 0; i < this->_length; i++) {
    this->_tweens[i].recycle();
  }
}

void Pool::step(int amount) {
  for(int i = 0; i < this->_length; i++) {
    if (this->_tweens[i].active()) {
      this->_tweens[i].step(amount);
    }
  }
}

void Pool::forward() {
  this->step(1);
}

void Pool::backward() {
  this->step(-1);
}
