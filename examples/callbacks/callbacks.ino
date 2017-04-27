#define FPS 100

#include <Tween.h>
#include <Easing.h>

Tween q;

void loop() { 
  // call increment of the tween
  q.step();

  // loop regulation
  delay(1000 / FPS);
}

void setup() {
  // open the serial plotter to see the result
  Serial.begin(9600);
  while(!Serial);

  // instanciate the tween with onprogress/oncomplete custom callbacks
  q = Tween();
  q.init(0.0, 1.0, 1000, Easing::linearTween, onprogress, oncomplete);
}


void onprogress(float value, void* object) {
  // display
  Serial.println(q.value);
}

void oncomplete(void* object) {
  // send -1 to witness oncomplete callback
  Serial.println(-1);
}

