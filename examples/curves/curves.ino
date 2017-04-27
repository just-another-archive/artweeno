#define FPS 100

#include <Tween.h>
#include <Easing.h>

Tween q;
Tween w;
Tween e;
Tween r;

void loop() { 
  // call increment of the tweens
  q.step();
  w.step();
  e.step();
  r.step();
  
  // display
  Serial.print(q.value);
  Serial.print("\t");
  Serial.print(w.value);
  Serial.print("\t");
  Serial.print(e.value);
  Serial.print("\t");
  Serial.print(r.value);
  Serial.println();

  // loop regulation
  delay(1000 / FPS);
}

void setup() {
  // open the serial plotter to see the result
  Serial.begin(9600);
  while(!Serial);

  // instanciate the tweens with different easing curves
  q = Tween();
  q.init(0.0, 10.0, 4000, Easing::easeOutSine);

  w = Tween();
  w.init(0.0, 10.0, 4000, Easing::easeOutQuad);

  e = Tween();
  e.init(0.0, 10.0, 4000, Easing::easeOutQuart);

  r = Tween();
  r.init(0.0, 10.0, 4000, Easing::easeOutQuint);
}


