// This file is part of the Acts project.
//
// Copyright (C) 2017-2019 CERN for the benefit of the Acts project
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cstdlib>
#include <memory>

#include "ActsExamples/Framework/Sequencer.hpp"
#include "ActsExamples/Options/CommonOptions.hpp"
#include "MyAlgorithm.hpp"

int main(int argc, char* argv[]) {
  // setup options
  // every component should have an associated option setup function
  // that should be called here.
  auto opt = ActsExamples::Options::makeDefaultOptions();
  ActsExamples::Options::addSequencerOptions(opt);
  // parse options from command line flags
  auto vm = ActsExamples::Options::parse(opt, argc, argv);
  // an empty varaibles map indicates an error
  if (vm.empty()) {
    return EXIT_FAILURE;
  }
  // extract some common options
  auto logLevel = ActsExamples::Options::readLogLevel(vm);
  
  // setup the sequencer first w/ config derived from options
  ActsExamples::Sequencer sequencer(ActsExamples::Options::readSequencerConfig(vm));
  
  // add HelloWorld algorithm that does nothing
  sequencer.addAlgorithm(std::make_shared<ActsExamples::MyAlgorithm>(logLevel));
  
  // Run all configured algorithms and return the appropriate status.
  return sequencer.run();
}
