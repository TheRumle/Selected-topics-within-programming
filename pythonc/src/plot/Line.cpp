//
// Created by rasmu on 02/04/2023.
//
#include <QChartView>
#include <QLineSeries>

#include "Line.h"
#include "plot_interface.h"

using QtCharts::QLineSeries;
WithData Line::withData(const std::shared_ptr<term_t>& plot) {
    auto line = std::make_shared<QLineSeries>(new QLineSeries());
    for (int i = 0; i < values.size(); ++i)
        line->append(i, values.at(i));
    return WithData{line, plot};
}
