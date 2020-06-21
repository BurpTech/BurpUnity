#include "List.hpp"
#include "Interface.hpp"

namespace BurpUnity {
  namespace Entry {

    List::List() :
      head(nullptr),
      _tail(nullptr),
      _length(0)
    {}

    void List::append(Interface * entry) {
      if (head) {
        _tail->_next = entry;
      } else {
        head = entry;
      }
      _tail = entry;
      _length++;
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
        _length += source._length;
        source._length = 0;
      }
    }

    void List::transfer(List & destination) {
      if (head) {
        // check if the destination has only 1 entry
        if (destination.head->_next) {
          _tail->_next = destination.head->_next;
        } else {
          destination._tail = _tail;
        }
        destination.head->_next = head;
        head = nullptr;
        _tail = nullptr;
        destination._length += _length;
        _length = 0;
      }
    }

    void List::prepend(Interface * entry) {
      if (head) {
        entry->_next = head;
      } else {
        _tail = entry;
      }
      head = entry;
      _length++;
    }

    void List::prepend(List & source) {
      if (source.head) {
        source._tail->_next = head;
        head = source.head;
        source.head = nullptr;
        source._tail = nullptr;
        _length += source._length;
        source._length = 0;
      }
    }

    const Error * List::freeHead() {
      if (head) {
        Interface * previous = head;
        head = previous->_next;
        if (!head) _tail = nullptr;
        _length--;
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
      _length = 0;
      return ret;
    }

  }
}
