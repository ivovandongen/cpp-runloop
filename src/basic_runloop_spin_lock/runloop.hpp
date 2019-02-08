#pragma once

#include <thread_local.hpp>

#include <atomic>
#include <functional>
#include <iostream>
#include <queue>

class Runloop {
public:
    using WorkTask = std::function<void()>;

    static Runloop *Get() {
        return current().get();
    }

    Runloop();

    ~Runloop();

    void run();

    void wake();

    void stop();

    void invoke(WorkTask &&fn);

    bool running() {
        return _running;
    }

private:
    static ThreadLocal<Runloop> &current() {
        static ThreadLocal<Runloop> runloop;
        return runloop;
    }

private:
    class Impl;

    std::unique_ptr<Impl> _impl;

    std::queue<std::shared_ptr<WorkTask>> _queue;
    std::atomic_bool _running{false};
};