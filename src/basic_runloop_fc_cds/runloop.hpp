#pragma once

#include <thread_local.hpp>

#include <cds/container/fcqueue.h>

#include <atomic>
#include <functional>
#include <iostream>

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

    cds::container::FCQueue<WorkTask> _queue;
    std::atomic_bool _running{false};
};