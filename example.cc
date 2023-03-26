// Copyright 2010-2022 Google LLC
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ortools/sat/cp_model.h"
#include "ortools/sat/cp_model.pb.h"
#include "ortools/sat/cp_model_solver.h"
#include "ortools/util/sorted_interval_list.h"

namespace operations_research {
namespace sat {

int SimpleSatProgram(uint8_t *requestData, size_t requestSize) {
  // unmarshal model from protobuf data
  operations_research::sat::CpModelProto model;
  if (!model.ParseFromArray(requestData, requestSize)) {
    return -3;
  }

  // solve model
  const CpSolverResponse response = Solve(model);

  if (response.status() == CpSolverStatus::OPTIMAL || response.status() == CpSolverStatus::FEASIBLE) {
    CpModelBuilder builder;
    builder.CopyFrom(model);

    auto x = builder.GetIntVarFromProtoIndex(0);
    auto y = builder.GetIntVarFromProtoIndex(1);
    auto z = builder.GetIntVarFromProtoIndex(2);

    return (SolutionIntegerValue(response, x) * 100) 
         + (SolutionIntegerValue(response, y) * 10) 
         +  SolutionIntegerValue(response, z);
  } 
  else {
    return -2;
  }
  
  return -1;
}
}  // namespace sat
}  // namespace operations_research

__attribute__((export_name("solve")))
int solve(uint8_t *requestData, size_t requestSize) {
  return operations_research::sat::SimpleSatProgram(requestData, requestSize);
}