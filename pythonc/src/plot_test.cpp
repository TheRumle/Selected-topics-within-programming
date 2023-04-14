//
// Created by rasmu on 31/03/2023.
//

#include <random>
#include <algorithm>

static std::vector<double> makeRand(int capacity){
    static auto gen = std::mt19937{std::random_device{}()};
    static auto dist = std::uniform_real_distribution<double>{1, 9};
    static auto data = std::vector<double>();
    for (auto x = 0; x < capacity; x++) {
        data.push_back(dist(gen));
    }
    return data;
}


#include "plot/plot.hpp"
int main(int argc, char* argv[])
{
    QApplication a{argc, argv};  // make sure to initialize it first before any other widget

    auto vals = makeRand(15);
    auto *plot = new Plot("some text");
    plot->AddLine("LinePlot", vals)->AddScatter("my scatter", vals)->addBoxPlots("boxes", vals);

    auto window = QMainWindow{};
    window.setWindowTitle("Qt5 Scatterplot Test");
    window.setCentralWidget(plot);
    window.resize(800, 600);
    window.show();



    return a.exec();
}

