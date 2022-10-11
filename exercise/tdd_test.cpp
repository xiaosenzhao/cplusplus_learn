#include <iostream>
#include <string>
#include <tuple>

enum class Direction {
  N,
  S,
  E,
  W
};

class MarsCar {
 public:
  MarsCar(int x, int y, int X, int Y, const Direction& direction) :
      x_(x),
      y_(y),
      X_(X),
      Y_(Y),
      direction_(direction){}

  std::tuple<int, int, Direction> process(const std::string& orders) {
    int x = x_;
    int y = y_;
    Direction direction = direction_;

    for (auto order : orders) {
      switch (order) {
        case 'l':
        case 'r':
          direction = turn(direction, order);
          break;
        case 'f':
          move(x, y, direction);
          break;
        default:
          break;
      }
    }
    return std::make_tuple(x, y, direction);
  }

 private:
  Direction turn(const Direction& now, char order) {
    Direction result = now;
    switch(order) {
      case 'l' :
        switch(now) {
          case Direction::N:
            result = Direction::W;
            break;
          case Direction::S:
            result = Direction::E;
            break;
          case Direction::E:
            result = Direction::N;
            break;
          case Direction::W:
            result = Direction::S;
            break;
        }
      case 'r':
        switch(now) {
          case Direction::N:
            result = Direction::E;
            break;
          case Direction::S:
            result = Direction::W;
            break;
          case Direction::E:
            result = Direction::S;
            break;
          case Direction::W:
            result = Direction::N;
            break;
        }
        break;
      default :
        break;
    }
    return result;
  }

  void move(int& x, int& y, const Direction& direction) {
    int xEnd = x;
    int yEnd = y;
    switch(direction) {
      case Direction::N :
        y += 1;
        break;
      case Direction::S :
        y -= 1;
        break;
      case Direction::E :
        x += 1;
        break;
      case Direction::W :
        x -= 1;
        break;
    }
    if (!isOutOfBound(xEnd, yEnd)) {
      x = xEnd;
      y = yEnd;
    }
  }

  bool isOutOfBound(int x, int y) {
    if (x > X_ || y > Y_) {
      return false;
    }
    return true;
  }

 private:
  int x_;
  int y_;
  int X_;
  int Y_;
  Direction direction_;
};

