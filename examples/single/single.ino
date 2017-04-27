#define FPS 100

#include <Tween.h>
#include <Easing.h>

Tween q;

void loop() { 
  // call increment of the tween
  q.step();

  // display
  Serial.print(q.value);
  Serial.println();

  // loop regulation
  delay(1000 / FPS);
}

void setup() {
  // open the serial plotter to see the result
  Serial.begin(9600);
  while(!Serial);

  // instanciate the tween
  q = Tween();
  q.init(0.0, 10.0, 4000);
}


