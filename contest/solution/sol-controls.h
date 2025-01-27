#pragma once
// Turn on or off some optimizations - a control panel for the contest solution optimizations. Handle with care.

// =====================================================================================================================
// Enable blast processing for Bag of Cells deserialization (comment for better CPU time... hopefully):
#define BOC_DS_BLAST_PROCESSING
// WTF: Using Actor Workers results in quite lower overall time, but significantly higher Total CPU time
// I hope it would be possible to submit both variants...
// However, for me using BP with actors allowed to break sub 3.00 barrier (about 2.92 against ~5.05 baseline)
#define BOC_DS_BP_USE_ACTORS
// N.B. It seems that for profiling need to disable BP OR use Actors
// =====================================================================================================================
// Maximum number of threads to use with BOC DS BP without Actors (with threads / pthreads). 4u seems to be optimal.
#define BOC_DS_BP_THR_NUM 4u

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
// #define CVQ_CHECK_TX_WITH_ACTORS
// ^^^ Threads seem to be noticeably faster for this task

// =====================================================================================================================
#ifdef CVQ_CHECK_TX_PARALLEL
// CUT mutex required if transactions are executed in parallel - different accounts may share same cells / CUTs
#define CELL_USAGE_TREE_MUTEX
#endif