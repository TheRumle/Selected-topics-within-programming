//
// Created by rasmus on 2/12/2023.
//

#ifndef SESSION2_TIMER_H
#define SESSION2_TIMER_H


#include <chrono>

class timer {
public:
    void start();
    double stop();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};



#endif //SESSION2_TIMER_H
