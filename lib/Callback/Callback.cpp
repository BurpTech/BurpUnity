#include "Callback.hpp"

Callback::Callback() :
  _cb(nullptr)
{}

void Callback::loop() {
  if (_cb) {
    _cb();
    _cb = nullptr;
  }
}

void Callback::once(f_cb cb) {
  _cb = cb;
}
