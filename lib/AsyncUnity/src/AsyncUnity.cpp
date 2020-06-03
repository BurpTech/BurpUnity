#ifndef NATIVE
#include <Arduino.h>
#endif

#include "./AsyncUnity.hpp"

extern AsyncUnity::Root asyncUnityRoot;

void setup()
{
  asyncUnityRoot.setup();
}

void loop()
{
  asyncUnityRoot.loop();
}

int main()
{
  setup();
  while (asyncUnityRoot.running)
  {
    loop();
  }
  return asyncUnityRoot.status;
}
