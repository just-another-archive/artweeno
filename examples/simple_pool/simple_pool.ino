#define FPS 100

#include <Pool.h>
#include <Tween.h>

Pool pool = Pool(5);

// this is to avoid circular reference compilation failure ("go was not declared in scope")
void go(void* obj);
// ================

void loop() { 
  // call increment of the tweens
  pool.forward();

  // this is used to keep the plotter running while the wait tween runs
  Serial.print("\t");
  Serial.print(0);

  // new frame for plotter
  Serial.println("");

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
}

void wait(void* object = NULL) {
  // locally instanciate the tween by requesting from the pool
  Tween* tween = pool.get();

  // create a blank tween of 1s with no curve nor progress function
  tween->init(0.0, 1.0, 1000);

  // when finished, call the `go` function
  tween->oncomplete = go;
}

void go(void* object = NULL) {
  // locally instanciate the tween by requesting from the pool
  Tween* tween = pool.get();

  // set the progress function to display the value (with `onprogress`), then call `wait` when finished
  tween->init(0.0, 1.0, 1000, Easing::linearTween, onprogress, wait);
  Serial.print(0);
}

