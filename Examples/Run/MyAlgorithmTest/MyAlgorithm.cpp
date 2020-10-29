// This file is part of the Acts project.
// 
// Copyright (C) 2020 CERN for the benefit of the Acts project
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "MyAlgorithm.hpp"
#include "ActsExamples/Framework/WhiteBoard.hpp"

ActsExamples::MyAlgorithm::MyAlgorithm(Acts::Logging::Level level)
    : ActsExamples::BareAlgorithm("MyAlgorithm", level) {}

ActsExamples::ProcessCode ActsExamples::MyAlgorithm::execute(
    const AlgorithmContext& /*ctx*/) const {

  return ActsExamples::ProcessCode::SUCCESS;
}
