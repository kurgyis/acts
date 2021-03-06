// This file is part of the Acts project.
//
// Copyright (C) 2020 CERN for the benefit of the Acts project
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "Acts/Geometry/GeometryContext.hpp"
#include "Acts/Utilities/Definitions.hpp"
#include <array>
#include <vector>

namespace Acts {
class BinUtility;
class Surface;
}  // namespace Acts

namespace ActsFatras {

/// The Channelizer splits a surface segment, i.e. after projection
/// onto the readout surface into channel segments.
///
struct Channelizer {
  /// Nested struct for stepping from one channel to the next.
  struct ChannelStep {
    /// This is the delta to the last step in bins
    std::array<int, 2> delta = {0, 0};
    /// The intersection with the channel boundary
    Acts::Vector2D intersect;
    /// The patlength from the start
    double path = 0.;

    /// Constructor with arguments for a ChannelStep.
    ///
    /// @param delta_ The bin delta for this step
    /// @param intersect_ The intersect with the channel boundary
    /// @param start The start of the surface segment, for path from origin
    ChannelStep(std::array<int, 2> delta_, Acts::Vector2D intersect_,
                const Acts::Vector2D& start)
        : delta(delta_),
          intersect(intersect_),
          path((intersect - start).norm()) {}

    /// Smaller operator for sorting the ChannelStep objects.
    ///
    /// @param cstep The other ChannelStep to be compared
    ///
    /// The ChannelStep objects can be compared with its path distance
    /// from the start (surface segment origin)
    bool operator<(const ChannelStep& cstep) const { return path < cstep.path; }
  };

  /// Nested struct for representing channel steps.
  struct ChannelSegment {
    /// The bin of this segment
    std::array<unsigned int, 2> bin = {0, 0};
    /// The segment start, end points
    std::array<Acts::Vector2D, 2> path2D;
    // The clipped path length
    double pathLength = 0.;

    /// Constructor with arguments
    ///
    /// @param bin_ The bin corresponding to this step
    /// @param path2D_ The start/end 2D position of the segement
    /// @param pathLength_ The segment length for this bin
    ChannelSegment(std::array<unsigned int, 2> bin_,
                   std::array<Acts::Vector2D, 2> path2D_, double pathLength_)
        : bin(std::move(bin_)),
          path2D(std::move(path2D_)),
          pathLength(pathLength_) {}
  };

  /// Divide the surface segment into channel segments.
  ///
  /// @note Channelizing is done in cartesian coordinates (start/end)
  /// @note The start and end cartesian vector is supposed to be inside
  /// the surface bounds (pre-run through the SurfaceMasker)
  /// @note The segmentation has to be 2-dimensional, even if the
  /// actual readout is 1-dimensional, in latter case one bin in the
  /// second coordinate direction is required.
  ///
  /// @param geoCtx The geometry context for the localToGlobal, etc.
  /// @param surface The surface for the channelizing
  /// @param segmentation The segmentation for the channelizing
  /// @param start The surface segment start (cartesian coordinates)
  /// @param end The surface segement end (cartesian coordinates)
  ///
  /// @return a vector of ChannelSegment objects
  std::vector<ChannelSegment> segments(const Acts::GeometryContext& geoCtx,
                                       const Acts::Surface& surface,
                                       const Acts::BinUtility& segmentation,
                                       const Acts::Vector2D& start,
                                       const Acts::Vector2D& end) const;
};

}  // namespace ActsFatras
