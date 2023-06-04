#ifndef EXAM2023_MONITORCONSTRAINT_H
#define EXAM2023_MONITORCONSTRAINT_H
#include <type_traits>
#include "reactionNetwork/reactionNetwork.h"
#include "reactionNetwork/monitor/monitor.h"


//REQ 7
template <typename TMonitor>
concept MonitorConcept = std::is_base_of_v<Monitor, TMonitor> &&
                         requires(TMonitor monitor, double time, const ReactionNetwork::state& state) {
                             { monitor.handleStateChange(time, state) } -> std::same_as<void>;
                         };
#endif  // EXAM2023_MONITORCONSTRAINT_H
