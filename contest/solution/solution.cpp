#include "solution.hpp"

#include "vm/boc.h"
#include "block-auto.h"
#include "contest-validate-query.hpp"

void run_contest_solution(ton::BlockIdExt block_id, td::BufferSlice block_data, td::BufferSlice colldated_data,
                          td::Promise<td::BufferSlice> promise) {

  td::Promise<td::BufferSlice> wrapped_promise = [promise = std::move(promise)](td::Result<td::BufferSlice> result) mutable {
    // XXX: activate if can't change grader.cpp (will lose 0.03 - 0.05 sec)
    // vm::DataCell::use_temp_arena = false;
    promise.set_result(std::move(result));
  };

  // XXX: activate if can't change grader.cpp (will lose 0.03 - 0.05 sec)
  // This may be a bit harsh, but proper way is to pass this through all the initialization
  // vm::DataCell::reset_temp_arena();
  // vm::DataCell::use_temp_arena = true;

  // ^^^ these work, but ContestGrader::run_next_test still uses in-optimal cell allocator
  // Using TempArena in ContestGrader saves additional 0.03 - 0.05 seconds: 3.33~3.35 -> 3.30 (baseline about 5~5.05)

  // !!! It is NOT possible to enable temp arena here and just keep it enabled, because then ContestGrader will use
  // TempArena during preparation of input parameters, and resetting it will cause SIGSEGV
  // Not resetting it at all is also a bad idea, because that will cause memory to leak and grow
  // Therefore, reset and on / off moved to ContestGrader

  TRY_RESULT_PROMISE(promise, root, vm::std_boc_deserialize(block_data));

  block::gen::Block::Record rec;
  if (!block::gen::t_Block.cell_unpack(root, rec)) {
    return promise.set_error(td::Status::Error("failed to unpack block"));
  }
  TRY_RESULT_PROMISE(promise, res, vm::std_boc_serialize(rec.state_update));
  td::actor::create_actor<solution::ContestValidateQuery>(
      "validate", block_id, std::move(block_data), std::move(colldated_data), std::move(wrapped_promise)).release();

}
