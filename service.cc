#include "ortools/sat/cp_model.h"
#include "ortools/sat/cp_model.pb.h"
#include "ortools/sat/cp_model_solver.h"

int main() {
  return 0;
}

__attribute__((export_name("solve")))
void* solve(const void* requestData, int requestSize) {
  operations_research::sat::CpModelProto model;
  if (!model.ParseFromArray(requestData, requestSize)) {
    return NULL;
  }

  operations_research::sat::SatParameters parameters;
  parameters.set_max_time_in_seconds(45);

  operations_research::sat::CpSolverResponse response = SolveWithParameters(model, parameters);

  int32_t responseSize = response.ByteSizeLong();
  uint8_t* responseData = new uint8_t[responseSize + 8];
  if (!response.SerializeToArray(responseData + 8, responseSize)) {
    return NULL;
  }

  int32_t preamble = 74099;
  memcpy(responseData + 0, &preamble, 4);
  memcpy(responseData + 4, &responseSize, 4);

  return responseData;
}