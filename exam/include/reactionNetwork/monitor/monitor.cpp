#include "monitor.h"
void MaxAgentValueMonitor::handleStateChange(double time, const ReactionNetwork::state& state)
{
    for (const auto& agent : state) {
        const auto prev = store.get(agent->getAgentName());

        if (!prev.has_value()){
            store.add(agent->getAgentName(), agent->getTotalAmountAgent());
            continue ;
        }

        if (prev.value() < agent->getTotalAmountAgent()){
            store.update(agent->getAgentName(), agent->getTotalAmountAgent());
        }
    }
}
void AllStateCopyMonitor::handleStateChange(double time, const ReactionNetwork::state& state)
{
    ReactionNetwork::state copies;
    for (const auto& agent : state)
    {
        const Agent copy = *agent;
        copies.emplace_back(std::make_shared<const Agent>(copy));
    }
    this->addObservationVector(time, copies);
}
std::pair<std::basic_string<char>, double> CovidHospitalizationMonitor::extractPeakHospitalized() const
{
    for (const auto& value : getObservedValues()) {
        if (value.first == "H") {
            return value;
        }
    }
    throw std::invalid_argument("The monitor never found an \"H\" value");
}
