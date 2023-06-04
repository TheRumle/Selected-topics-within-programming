#ifndef EXAM2023_MONITOR_H
#define EXAM2023_MONITOR_H

#include "reactionNetwork/reactionNetwork.h"

struct Monitor
{
private:
    SymbolTable<double, ReactionNetwork::state> _observations;
protected:
    inline void addObservationVector(double time, 
                               const ReactionNetwork::state& agents) {
        _observations.storeOrUpdate(time,agents);
    }
    
public:
    using observations = std::vector<std::pair<double, ReactionNetwork::state>>;
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


//REQ 7
class MaxAgentValueMonitor : public Monitor
{
    SymbolTable<std::string, double> store{};
public:
    
    void handleStateChange(double time, const ReactionNetwork::state &state) override;

    std::vector <std::pair<std::string, double>> getObservedValues() const{
        return store.toPairVector();
    }
};

//REQ 7
struct CovidHospitalizationMonitor : public MaxAgentValueMonitor{
    
    std::pair<std::basic_string<char>, double> extractPeakHospitalized() const;
    
    double extractPeakHospitalizedValue() const{
        return extractPeakHospitalized().second;
    }
};

#endif  // EXAM2023_MONITOR_H
