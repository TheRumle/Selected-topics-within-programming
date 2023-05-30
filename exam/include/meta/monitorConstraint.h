//
// Created by rasmus on 5/30/2023.
//

#ifndef LAMBDAS_MONITORCONSTRAINT_H
#define LAMBDAS_MONITORCONSTRAINT_H
#include <type_traits>
#include "reaction_network/reactionNetwork.h"
#include "reaction_network/monitor/monitor.h"

template <typename TMonitor>
concept MonitorConcept = std::is_base_of_v<Monitor, TMonitor> &&
                         requires(TMonitor monitor, double time, const ReactionNetwork::state& state) {
                             { monitor.handleStateChange(time, state) } -> std::same_as<void>;
                         };
#endif  // LAMBDAS_MONITORCONSTRAINT_H
