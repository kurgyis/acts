// This file is part of the Acts project.
//
// Copyright (C) 2020 CERN for the benefit of the Acts project
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "ActsExamples/Framework/BareAlgorithm.hpp"

namespace ActsExamples {

  /// A simple empty algorithm
  // edited from vsCode
  class MyAlgorithm : public ActsExamples::BareAlgorithm
  {
    public:
      MyAlgorithm(Acts::Logging::Level level);

      /// The framework execut mehtod
      /// @param ctx The Algorithm context for multithreading/          
      ActsExamples::ProcessCode execute(const AlgorithmContext& ctx) const final override;
  };

}  // namespace FW
