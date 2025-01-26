#include "metrics.h"

namespace m {
  uint64_t u1{0};
  uint64_t u2{0};
  uint64_t u3{0};
  double d1{0.0};
  double d2{0.0};
  std::atomic_uint64_t a1{0};
  std::atomic_uint64_t a2{0};
  std::atomic_uint64_t a3{0};

  void postprocess() {
    if (a1.load() != 0) {
      u1 = a1.load();
      u2 = a2.load();
      u3 = a3.load();
    }
    d1 = static_cast<double>(u2) / static_cast<double>(u1);
    d2 = static_cast<double>(u3) / static_cast<double>(u1);
  }
}