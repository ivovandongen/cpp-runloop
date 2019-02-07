#include <runloop.hpp>

#include <unistd.h>
#include <fcntl.h>

class Runloop::Impl {
public:
    Impl() {
        pipe(_pipe);
        fcntl(_pipe[0], F_SETFL, O_NONBLOCK);
    }

    void wait() {
        char c;
        while (read(_pipe[0], &c, 1) > 0);
    }

    void wake() {
        write(_pipe[1], "*", 1);
    }

private:
    int _pipe[2]{0};
};

Runloop::Runloop() : _impl(std::make_unique<Runloop::Impl>()) {
    current().set(this);
}

Runloop::~Runloop() {
    current().set(nullptr);
}

void Runloop::run() {
    _running = true;

    while (_running) {
        {
            std::lock_guard<std::recursive_mutex> lock(mutex);
            while (!_queue.empty()) {
                _queue.front()();
                _queue.pop();
            }
        }

        _impl->wait();
    }
}

void Runloop::stop() {
    invoke([this] {
        _running = false;
        wake();
    });
}

void Runloop::invoke(WorkTask &&fn) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    _queue.push(std::move(fn));
    wake();
}

void Runloop::wake() {
    _impl->wake();
}