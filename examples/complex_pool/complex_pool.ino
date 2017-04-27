#define FPS 100

#include <Pool.h>
#include <Tween.h>

Pool pool = Pool(45);

unsigned int length = 0;
unsigned int i = 0;


// this is to avoid circular reference compilation failure ("go was not declared in scope")
void go(void* obj);
// ================

void loop() {
  // reset i each loop
  i = 0;
  
  // call increment of the tweens
  pool.forward();

  // loop regulation
  delay(1000 / FPS);
}

void setup() {
  // open the serial plotter to see the result
  Serial.begin(9600);
  while(!Serial);

  // launch the example
  go(NULL);
}



void onprogress(float value, void* object) {
  Serial.print(value);

  if (++i < length) {
    Serial.print("\t");
  }
  else {
    Serial.print("\n");
  }
}

void wait(void* object = NULL) {
  // locally instanciate the tween by requesting from the pool
  Tween* tween = pool.get();

  // create a blank tween of 1s with no curve nor progress function, and when finished, call the `go` function
  tween->init(0.0, 1.0, 1000, Easing::linearTween, NULL, go);
}

void go(void* object = NULL) {
  length++;

  for (unsigned int j = 0; j < length; j++) {
    // locally instanciate the tween by requesting from the pool
    Tween* tween = pool.get();
  
    // set the progress function to display the value (with `onprogress`), then call `wait` when finished
    if (j < length - 1) {
      tween->init(0.0, (float)(j + 1), 1000, Easing::linearTween, onprogress); 
    }
    else {
      tween->init(0.0, (float)(j + 1), 1000, Easing::linearTween, onprogress, wait); 
    }
  }
}
