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
  while (asyncUnityRoot.isRunning())
  {
    loop();
  }
  return asyncUnityRoot.status;
}
