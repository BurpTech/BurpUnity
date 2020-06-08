#include "List.hpp"
#include "Interface.hpp"

namespace BddUnity {
  namespace Entry {

    List::List() :
      head(nullptr),
      _tail(nullptr)
    {}

    void List::append(Interface * entry) {
      if (head) {
        _tail->_next = entry;
      } else {
        head = entry;
      }
      _tail = entry;
    }

    void List::append(List & source) {
      if (source.head) {
        if (head) {
          _tail->_next = source.head;
        } else {
          head = source.head;
        }
        _tail = source._tail;
        source.head = nullptr;
        source._tail = nullptr;
      }
    }

    void List::transfer(List & destination) {
      if (head) {
        _tail->_next = destination.head->_next;
        destination.head->_next = head;
        head = nullptr;
        _tail = nullptr;
      }
    }

    void List::prepend(Interface * entry) {
      if (head) {
        entry->_next = head;
      } else {
        _tail = entry;
      }
      head = entry;
    }

    void List::prepend(List & source) {
      if (source.head) {
        source._tail->_next = head;
        head = source.head;
        source.head = nullptr;
        source._tail = nullptr;
      }
    }

    const Error * List::freeHead() {
      if (head) {
        Interface * previous = head;
        head = previous->_next;
        return previous->free();
      }
      return nullptr;
    }

    const Error * List::freeAll() {
      const Error * ret = nullptr;
      while (head) {
        const Error * e = head->free();
        if (e) {
          ret = e;
        }
        head = head->_next;
      }
      _tail = nullptr;
      return ret;
    }

  }
}
