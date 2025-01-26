#pragma once
#include <atomic>
#include <cstdint>

#define MM_CELL_HASH 1
#define MM_BOC_HASH_REF 2
#define MM_BOC_SIZE_SPEC 3
#define MM_BOC_BLAST_MT 4

// #define METRICS_MEASURE MM_BOC_BLAST_MT

// #define METRICS_PER_ITERATION

namespace m {
  extern uint64_t u1;
  extern uint64_t u2;
  extern uint64_t u3;
  extern double d1; // = u2 / u1
  extern double d2; // = u3 / u1
  extern std::atomic_uint64_t a1;
  extern std::atomic_uint64_t a2;
  extern std::atomic_uint64_t a3;

  void postprocess();
}

#ifdef METRICS_MEASURE
  #define METRICS_ENABLE
#endif
