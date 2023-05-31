//
// Created by rasmus on 5/30/2023.
//

#ifndef EXAM2023_MONITOR_H
#define EXAM2023_MONITOR_H

#include "reaction_network/reactionNetwork.h"

struct Monitor
{
private:
    symbol_table<double, ReactionNetwork::state> _observations;
protected:
    inline void addObservationVector(double time, 
                               const ReactionNetwork::state& agents) {
        _observations.storeOrUpdate(time,agents);
    }
    
public:
    using observations = std::vector<std::pair<double, std::vector<std::shared_ptr<const Agent>>>>;
    std::vector<std::pair<double, std::vector<std::shared_ptr<const Agent>>>> getObservations() const {
        return _observations.toPairVector();
    }
    
    virtual void handleStateChange(double time, const ReactionNetwork::state& state) = 0;
    virtual ~Monitor() = default;
};

class AllStateCopyMonitor : public Monitor
{
                                        
public:
    void handleStateChange(double time, const ReactionNetwork::state &state) override;
};


class MaxAgentValueMonitor : public Monitor
{
    symbol_table<std::string, double> store{};
public:
    
    void handleStateChange(double time, const ReactionNetwork::state &state) override;

    std::vector <std::pair<std::string, double>> getObservedValues() const{
        return store.toPairVector();
    }
};

struct CovidHospitalizationMonitor : public MaxAgentValueMonitor{
    
    std::pair<std::basic_string<char>, double> extractPeakHospitalized() const;
    
    double extractPeakHospitalizedValue() const{
        return extractPeakHospitalized().second;
    }
};

#endif  // EXAM2023_MONITOR_H
