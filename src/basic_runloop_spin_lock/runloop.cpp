#include <runloop.hpp>

#include <unistd.h>
#include <fcntl.h>

class SpinLock {
public:
    class Guard {
    public:
        Guard(std::atomic_bool &locked) : _locked(locked) {
            while (_locked) {
                // Spin!
            }
            _locked = true;
        }

        ~Guard() {
            _locked = false;
        }

    private:
        std::atomic_bool &_locked;
    };

    inline Guard acquire() {
        return {_locked};
    }

private:
    std::atomic_bool _locked{false};
};

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

    SpinLock &lock() {
        return _lock;
    }

private:
    int _pipe[2]{0};
    SpinLock _lock;
};

Runloop::Runloop() : _impl(std::make_unique<Runloop::Impl>()) {
    current().set(this);
}

Runloop::~Runloop() {
    current().set(nullptr);
}

void Runloop::run() {
    _running = true;

    std::queue<std::shared_ptr<WorkTask>> tmp;
    std::shared_ptr<WorkTask> task;

    while (_running) {
        {
            auto guard = _impl->lock().acquire();
            tmp.swap(_queue);
        }

        while (!tmp.empty()) {
            if ((task = tmp.front())) {
                (*task)();
            }
            tmp.pop();
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
    auto guard = _impl->lock().acquire();
    _queue.push(std::make_shared<WorkTask>(std::move(fn)));
    wake();
}

void Runloop::wake() {
    _impl->wake();
}