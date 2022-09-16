// Inspired by https://codetrips.com/2020/07/26/modern-c-writing-a-thread-safe-queue/
#include <mutex>
#include <queue>
#include "Troon.h"

class ThreadSafePQ {
private:
    struct TroonComparison {
        bool operator()(const Troon *a, const Troon *b) const {
            return a->id > b->id;
        }
    };

    mutable std::mutex mtx;
    std::priority_queue<Troon *, std::deque<Troon *>, TroonComparison> troonPq;

public:
    void push(Troon* troon) {
        std::lock_guard<std::mutex> lock(mtx);
        troonPq.push(troon);
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx);
        return troonPq.empty();
    }

    Troon* top() {
        std::lock_guard<std::mutex> lock(mtx);
        return troonPq.top();
    }

    void pop() {
        std::lock_guard<std::mutex> lock(mtx);
        troonPq.pop();
    }
};
