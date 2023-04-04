//
// Created by rasmu on 02/04/2023.
//

#ifndef PYTHONCTYPES_SETUP_INTERFACE_H
#define PYTHONCTYPES_SETUP_INTERFACE_H

#include "plottable.hpp"

class NamedPlotSetUp{
    public:
    virtual plottable CreatedFrom(std::vector<double> toPlot) = 0;
    ~NamedPlotSetUp() noexcept = default;
    
};

#endif //PYTHONCTYPES_SETUP_INTERFACE_H
