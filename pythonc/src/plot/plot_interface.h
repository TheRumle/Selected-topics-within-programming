//
// Created by rasmu on 02/04/2023.
//

#ifndef PYTHONCTYPES_PLOT_INTERFACE_H
#define PYTHONCTYPES_PLOT_INTERFACE_H


#include "setup_interface.hpp"


QT_CHARTS_USE_NAMESPACE
class term_t : public QChartView{
protected:
Q_OBJECT
public:
    ~term_t() noexcept override = default;
    virtual NamedPlotSetUp*  WithLinePlot(const QString &title) = 0;
};



#endif //PYTHONCTYPES_PLOT_INTERFACE_H
