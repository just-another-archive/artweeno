#include <Arduino.h>
#include <Easing.h>

#include "Tween.h"

  #ifndef FPS
    #define FPS 100
  #endif

byte Tween::fps = FPS;

Tween::Tween() {
  this->recycle();
}

void Tween::init(float from, float to, unsigned int duration, float (* ease)(float a, float b, float c, float d), void (* onprogress)(float value, void* object), void (* oncomplete)(void* object)) {
  this->init(NULL, from, to, duration, ease, onprogress, oncomplete);
}

void Tween::init(void* object, float from, float to, unsigned int duration, float (* ease)(float a, float b, float c, float d), void (* onprogress)(float value, void* object), void (* oncomplete)(void* object)) {
  this->recycle();

  this->object = object;
  this->_from = from;
  this->_to = to;
  this->_duration = duration;

  this->ease = ease;
  this->onprogress = onprogress;
  this->oncomplete = oncomplete;

  this->_activate();
}

bool Tween::active() { return this->_active; }

void Tween::_activate() {
  this->value = this->_from;
  this->_increment = 1 / (float)(this->_duration / (1000 / this->_fps));
  this->_active = true;
}

void Tween::play() { this->_active = true; }
void Tween::pause() { this->_active = false; }

void Tween::step(int amount) {
  if (this->_active == false) {
    return;
  }

  // determine movement
  unsigned int iterations = abs(amount);
  int direction = amount / (int)iterations;

  // apply the iterations
  for (unsigned int i = 0; i < iterations; i++) {
    this->_progress += direction * this->_increment;
  }

  // force map value to range 0 -> 1
  this->_progress = constrain(this->_progress, 0.0, 1.0);

  // express value change
  float diff = 0.0;

  if (this->_from == this->_to) { this->value = this->_to; }
  else {
    if (this->_from < this->_to) {
      diff = this->_to - this->_from;
      this->value = this->_from + this->ease(this->_progress, 0.0, diff, 1.0);
    }
    else if (this->_from > this->_to) {
      diff = this->_from - this->_to;
      this->value = this->_from - this->ease(this->_progress, 0.0, diff, 1.0);
    }
  }

  // progression callback
  if (this->onprogress != NULL) {
    this->onprogress(this->value, this->object);
  }

  // completion callback
  if (this->_progress >= 1.0) {
    this->_active = false;

    if (this->oncomplete != NULL) {
      this->oncomplete(this->object);
    }
  }
}

void Tween::recycle() {
  this->_fps = Tween::fps;
  this->_active = false;
  this->object = NULL;
  this->_from = 0;
  this->_to = 1;
  this->_duration = 1000;
  this->_progress = 0;

  this->ease = Easing::linearTween;
  this->onprogress = NULL;
  this->oncomplete = NULL;
}
