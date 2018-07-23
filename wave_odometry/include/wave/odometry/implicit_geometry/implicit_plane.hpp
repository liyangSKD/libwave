#ifndef WAVE_IMPLICIT_PLANE_HPP
#define WAVE_IMPLICIT_PLANE_HPP

#include <Eigen/Core>
#include <ceres/ceres.h>
#include "wave/odometry/implicit_geometry/assign_jacobians.hpp"
#include "wave/odometry/feature_track.hpp"

namespace wave {

template <int... states>
class ImplicitPlaneResidual : public ceres::SizedCostFunction<1, 6, states...> {
 public:
    virtual ~ImplicitPlaneResidual() {}

    ImplicitPlaneResidual(const uint32_t &pt_id,
                          const uint32_t &feat_idx,
                          const FeatureTrack *track,
                          const std::vector<std::vector<std::shared_ptr<Eigen::Map<MatXf>>>> *feat_points) :
            pt_id(pt_id), feat_idx(feat_idx), track(track), feat_points(feat_points) {}

    virtual bool Evaluate(double const *const *parameters, double *residuals, double **jacobians) const;

 private:
    const uint32_t pt_id, feat_idx;
    const FeatureTrack *track;
    const std::vector<std::vector<std::shared_ptr<Eigen::Map<MatXf>>>> *feat_points;
};
}

#include "impl/implicit_plane_impl.hpp"

#endif //WAVE_IMPLICIT_PLANE_HPP
