#include "comun.hpp"
#include "Yumi.hpp"
#include <memory>

class MeetYumi {
    std::unique_ptr<Yumi> y1, y2;
  public:
    MeetYumi(const unsigned n, const unsigned m, const std::array<Punto, c_CHECKPOINTS + 1>& arr);
    unsigned resolver();
};
