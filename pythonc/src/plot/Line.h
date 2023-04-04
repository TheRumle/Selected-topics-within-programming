//
// Created by rasmu on 02/04/2023.
//

#ifndef PYTHONCTYPES_LINE_H
#define PYTHONCTYPES_LINE_H


#include <utility>
#include <vector>
#include "plot_interface.h"
#include "plottable.hpp"
#include <QtCharts/QScatterSeries>
#include <QtCharts/QXYSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

using QtCharts::QScatterSeries;
using QtCharts::QXYSeries;
using QtCharts::QLineSeries;
using QtCharts::QXYSeries;

class Line : public plottable
{

public:
    explicit Line(const std::vector<double>& toPlot, const std::shared_ptr<term_t> plot){
        series = std::make_shared<QLineSeries>(new QLineSeries());
        for (int i = 0; i < toPlot.size(); ++i)
            series->append(i, toPlot.at(i));
    }
    
};


#endif //PYTHONCTYPES_LINE_H
