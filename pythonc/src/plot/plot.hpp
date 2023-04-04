//
// Created by rasmu on 02/04/2023.
//

#ifndef PYTHONCTYPES_PLOT_H
#define PYTHONCTYPES_PLOT_H




#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBoxPlotSeries>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>
#include <QChartView>
#include <utility>
#include "Line.h"
#include "plot_interface.h"
#include "NamedLineSetUp.hpp"


QT_CHARTS_USE_NAMESPACE
class Plot: public term_t, std::enable_shared_from_this<Plot>{
private:
      
    Q_OBJECT
public:
    explicit Plot(const QString &title) {
        chart()->setTitle(title);
        chart()->createDefaultAxes();
        chart()->setDropShadowEnabled(false);
        // chart()->setAnimationOptions(QChart::SeriesAnimations); // cool but distracting

        chart()->legend()->setMarkerShape(QtCharts::QLegend::MarkerShapeFromSeries);
        chart()->legend()->setAlignment(Qt::AlignBottom);
    };

    NamedPlotSetUp* WithLinePlot(const QString &title) override{
        return new NamedLineSetUp{title, shared_from_this()};
    }
};




#endif //PYTHONCTYPES_PLOT_H
