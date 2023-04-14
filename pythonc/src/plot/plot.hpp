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



QT_CHARTS_USE_NAMESPACE
class Plot : public QChartView {
private:
    std::vector<QXYSeries*> allDataSets = std::vector<QXYSeries*>{};

    void addValues(const QString &title, QXYSeries* series, const std::vector<double>& toPlot){
        series->setName(title);
        for (int i = 0; i < toPlot.size(); ++i)
            series->append(i, toPlot.at(i));
        chart()->addSeries(series);
        allDataSets.push_back(series);
    }
    
    
    
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

    Plot* AddLine(const QString &title, const std::vector<double>& toPlot){
        auto* pLineSeries = new QLineSeries();
        addValues(title, pLineSeries, toPlot);
        return this;
    }

    Plot* AddScatter(const QString &title, const std::vector<double>& toPlot){
        auto* scatter = new QScatterSeries();
        addValues(title, scatter, toPlot);
        return this;
    }
    
    Plot * addBoxPlots(const QString &title, const std::vector<double>& toPlot){
        auto* boxes = new QBoxPlotSeries();
        boxes->setName(title);
        
        auto mm = std::minmax_element(toPlot.begin(), toPlot.end());
        auto mean = std::accumulate(toPlot.begin(), toPlot.end(), 0.0) / toPlot.size();
        auto lq = (mean + *mm.first) / 2;
        auto uq = (mean + *mm.second) / 2;
        boxes->append(new QBoxSet(*mm.first, lq, mean, uq, *mm.second));
        
 
        chart()->addSeries(boxes);
        return this;
    }
};




#endif //PYTHONCTYPES_PLOT_H
