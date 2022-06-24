#include <vector>

template <typename T, int N>
struct Point{
  Point(std::initializer_list<T> initList): coord(initList){}
  std::vector<T> coord;
};

int main(){
  Point<int, 3> point1{1, 2, 3};
  Point<int, 3> point2{4, 5, 6};
  point1 = point2;
  auto doubleValue = 2.2;
  auto intValue = 2;
  doubleValue = intValue;
  Point<double, 3> point3{1.1, 2.2, 3.3};
  // no known conversion from 'Point<int, [...]>' to 'const Point<double, [...]>' for 1st argument
  point3 = point2;
  return 0;
}
