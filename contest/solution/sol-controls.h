#pragma once
// Turn on or off some optimizations - a control panel for the contest solution optimizations. Handle with care.

// Disable parallel executions, they significantly sacrifice CPU time for total time
// #define OPTIMIZE_FOR_CPU_TIME

// Enable actor workers for accounts (transactions) checking
// #define OPTIMIZE_FOR_PROFILING

// =====================================================================================================================
// Enable blast processing for Bag of Cells deserialization (comment for better CPU time... hopefully):
#define BOC_DS_BLAST_PROCESSING
// WTF: Using Actor Workers results in quite lower overall time, but significantly higher Total CPU time
// I hope it would be possible to submit both variants...
// However, for me using BP with actors allowed to break sub 3.00 barrier (about 2.92 against ~5.05 baseline)
#define BOC_DS_BP_USE_ACTORS
// N.B. It seems that for profiling need to disable BP OR use Actors
// =====================================================================================================================
// Maximum number of threads to use with BOC DS BP without Actors (with threads / pthreads). 5u seems to be optimal.
#define BOC_DS_BP_THR_NUM 5u

// Threads:    1        2        3        4     ** 5 **     6        7      Actor
// Timing:  1.09358  0.91969  0.84247  0.65114  0.55378  0.73100  0.93146  0.49190

// Uses "Deprecated" but significantly faster SHA256_... OpenSSL methods
#define OPENSSL_FAST_SHA256

// Uses aforementioned SHA256_... methods directly in DataCell for better performance
#define DATA_CELL_DIRECT_SHA256

// Use deallocatable and reusable Temp Arena to optimize cell memory operations
#define CELL_DATA_TEMP_ARENA

// Size of memory slab allocated in one piece. Set to 4 MB for better locality.
#define TEMP_ARENA_BATCH_SIZE 1 << 22

// Check accounts (transactions) in parallel
#define CVQ_CHECK_TX_PARALLEL

// Enable CUT mutex manually (auto enabled if needed) - to measure perf
#define CELL_USAGE_TREE_MUTEX

// Use Actor Workers multithreading for accounts (transactions) checking
#define CVQ_CHECK_TX_WITH_ACTORS
// ^^^ Threads seem to be noticeably faster for this task - now not really??
// But may be useful for profiling to prevent mess

// ----------------------- 2.72 / 4.53 / 5.05 - Normal opt
// ----------------------- 3.39 / 3.33 / 5.05 - CPU Time opt

// Enable the parallel DFS pipeline for efficient creation of cells
#define MERKLE_TREE_DFS_PIPELINE

// =====================================================================================================================
#ifdef OPTIMIZE_FOR_CPU_TIME
#undef BOC_DS_BLAST_PROCESSING
#undef CVQ_CHECK_TX_PARALLEL
// #undef MERKLE_TREE_DFS_PIPELINE // ???
// #undef MERKLE_TREE_DFS_UT_PIPELINE // ???
#endif

#ifdef CVQ_CHECK_TX_PARALLEL
// CUT mutex required if transactions are executed in parallel - different accounts may share same cells / CUTs
#define CELL_USAGE_TREE_MUTEX
// Surprisingly enough, in fact, Merkle Tree parallel pipelines do NOT require CUT Mutex
#endif

#ifdef OPTIMIZE_FOR_PROFILING
#define BOC_DS_BP_USE_ACTORS
#define CVQ_CHECK_TX_WITH_ACTORS
#endif
