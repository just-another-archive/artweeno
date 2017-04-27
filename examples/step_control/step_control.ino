#define FPS 100

#include <Tween.h>

Tween q;

int amount = 1;

void loop() { 
  // check if the tween hits almost the target value...
  if (q.value >= 9.0) {
    // ... if so, reverse the amount of incremental and add 1 to accelerate
    amount = -(abs(amount) + 1);    
  }
  // else, if the tween hits almost the initial value...
  else if (floor(q.value) == 1.0) {
    // ... then just reverse the amount of incremental
    amount = abs(amount);
  }

  // reset the amount after some time
  if (abs(amount) == 50) {
    amount = 1;
  }

  // call increment of the tween
  q.step(amount);

  // display
  Serial.print(amount);
  Serial.print("\t");
  Serial.println(q.value);

  // loop regulation
  delay(1000 / FPS);
}

void setup() {
  // open the serial plotter to see the result
  Serial.begin(9600);
  while(!Serial);

  // instanciate the tween
  q = Tween();
  q.init(1.0, 10.0, 4000);
}


