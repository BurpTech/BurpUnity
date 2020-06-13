#pragma once

#include <functional>

class Callback {
  public:

    using f_cb = std::function<void()>;

    Callback();
    void loop();
    void once(f_cb cb);

  private:

    f_cb _cb;

};
