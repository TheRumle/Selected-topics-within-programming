#ifndef PYTHONCTYPES_PLOTTABLE_H
#define PYTHONCTYPES_PLOTTABLE_H

#include <utility>
#include <vector>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QXYSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

using QtCharts::QScatterSeries;
using QtCharts::QXYSeries;
using QtCharts::QLineSeries;
using QtCharts::QXYSeries;

class plottable{
protected:
    std::shared_ptr<QXYSeries> series;

public:
    std::shared_ptr<QXYSeries> getSeries(){
        return series;
    }
};

#endif