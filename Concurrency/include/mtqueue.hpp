#ifndef CONCURRENCY_MTQUEUE_H
#define CONCURRENCY_MTQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class mtqueue {
    std::condition_variable cond{};
    std::mutex mutex{};
	std::queue<T> container; // TODO: benchmark other containers
public:
	void put(T&& item) {
        std::lock_guard<std::mutex> lock(mutex);
        container.emplace(std::move(item));
	}
	void put(const T& item) {
        std::lock_guard<std::mutex> lock(mutex);
        container.push(item);
	}
    
	T get(){
        std::unique_lock<std::mutex> lock{mutex};
        
        //block and wait for elements to be available
        if (container.empty())
            cond.wait(lock, [&container=container](){return !container.empty();});
        
        auto a = container.front();
        container.pop();
        return a;
	}
};

#endif	// CONCURRENCY_MTQUEUE_H
