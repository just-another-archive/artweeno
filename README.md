# artweeno

A minimal non blocking tween engine with curves and callbacks.

### why

I needed to interpolate HSL values for led animations, with curves and all.

### how

1. Include Tween.h `#Include <Tween.h>`
2. Create a Tween _object_ : `Tween tween = Tween()`
3. Initialize it with a "from" float value, "to" float value, "duration" unsigned int value (ms). Optional parameters are an easing curve, and an onprogress/oncomplete callback.

### and

There is a `<Pool.h>` object, which is a basic object pooling material to work with. I found it easier to work with a limited set of tweens and recycle them because of the arduino memory size i was working on.

To use it, just create a new pool `Pool pool = Pool()` and request tweens from the pool instead of creating them with `Tween* tween = pool->get()`. If you want to animate multiple tweens from that pool altogether, you can use the handy `pool->forward()` call within your `loop()` to update all the active tweens of the pool at once.