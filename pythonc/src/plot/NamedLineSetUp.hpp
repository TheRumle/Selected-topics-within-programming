//
// Created by rasmu on 02/04/2023.
//
#include <QtCharts/QChartView>
#include "plot_interface.h"

struct NamedLineSetUp : public NamedPlotSetUp{
private:
    const QString title;
    std::shared_ptr<term_t> plot;
public:
    NamedLineSetUp(QString title, std::shared_ptr<term_t> plot)
            :title{std::move(title)},plot{std::move(plot)}
    {}

    plottable CreatedFrom(std::vector<double> toPlot) override {
        auto line = Line{toPlot, plot};
        plot.get()->chart()->addSeries(line.getSeries().get());
        return line;
    }
};