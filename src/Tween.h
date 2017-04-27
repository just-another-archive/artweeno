#ifndef artweeno_tween
  #define artweeno_tween

  #include <Arduino.h>
  #include <Easing.h>

  class Tween {
    public:
      static byte fps;

      float value;
      void* object;

      float (* ease)(float t, float b, float c, float d);

      void (* onprogress)(float value, void* object = NULL);
      void (* oncomplete)(void* object = NULL);

      Tween();

      void init(float from, float to, unsigned int duration, float (* ease)(float a, float b, float c, float d) = Easing::linearTween, void (* onprogress)(float value, void* object = NULL) = NULL, void (* oncomplete)(void* object) = NULL);

      void init(void* object, float from, float to, unsigned int duration, float (* ease)(float a, float b, float c, float d) = Easing::linearTween,
void (* onprogress)(float value, void* object) = NULL, void (* oncomplete)(void* object) = NULL);

      bool active();

      void play();
      void pause();

      void step(int amount = 1);

      void recycle();

    private:
      byte _fps;
      bool _active;
      bool _complete;

      float _from;
      float _to;
      unsigned int _duration;

      float _increment;
      float _progress;

      void _activate();
  };
#endif
