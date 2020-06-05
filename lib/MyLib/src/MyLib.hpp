#pragma once

#include <functional>

class MyLib {

  public:

    using f_cb = std::function<void(int value)>;

    void loop() {
      if (_cb) {
        f_cb cb = _cb;
        _cb = nullptr;
        cb(_value);
      }
    }

    void callMeNextLoop(int value, f_cb cb) {
      _cb = cb;
      _value = value;
    }

  private:

    f_cb _cb = nullptr;
    int _value = 0;

};
