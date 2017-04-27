#ifndef artweeno_pool
  #define artweeno_pool

  #include "Tween.h"

  class Pool {
    public:
      Pool(int length);

      Tween* get();

      void flush();

      void step(int amount);
      void forward();
      void backward();

    private:
      Tween* _tweens;
      int    _length;
  };

#endif
