#include "Crater.h"
#include "ScreenSingleton.h"
#include <iostream>
#include "enums/CraterSize.h"

/*void Crater::Draw() const {
  if (width == SMALL_CRATER_SIZE) {
    ScreenSingleton::getInstance().GotoXY(x - 4, y + 1);
    std::cout << "==     ==";
    ScreenSingleton::getInstance().GotoXY(x - 2, y + 2);
    std::cout << "=====";
  }
}
*/
bool Crater::isInside(double xn) const {
  const double size_2 = width / 2.0;
  if (int(xn) > int(x - size_2) && xn <= int(x + size_2)) {
    return true;
  }

  return false;
}

void CommonCrater::Draw() const {
    if (width == SMALL_CRATER_SIZE) {
        ScreenSingleton::getInstance().GotoXY(x - 4, y + 1);
        std::cout << "==     ==";
        ScreenSingleton::getInstance().GotoXY(x - 2, y + 2);
        std::cout << "=====";
    }
}

void OtherCrater::Draw() const {
    if (width == SMALL_CRATER_SIZE) {
        ScreenSingleton::getInstance().GotoXY(x - 6, y + 1);
        std::cout << "--         --";
        ScreenSingleton::getInstance().GotoXY(x - 4, y + 2);
        std::cout << "--     --";
        ScreenSingleton::getInstance().GotoXY(x - 2, y + 3);
        std::cout << "-----";
    }
}
