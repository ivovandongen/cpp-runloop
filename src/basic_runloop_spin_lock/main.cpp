
#include <thread_local.hpp>
#include <runloop.hpp>

#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <memory>


class Task {
public:
    Task(Runloop &loop)
            : _loop(loop),
              alive(true),
              thread(
                      [this]() {
                          std::cout << "Task: Doing some work" << std::endl;
                          std::this_thread::sleep_for(std::chrono::seconds(2));
                          onDone();
                      }) {

    }

    ~Task() {
        std::cout << "Task::~Task" << std::endl;
        std::lock_guard<std::mutex> lock(mutex);
        alive = false;
        thread.detach();
    }

    void onDone() {
        std::cout << "Task::~onDone" << std::endl;
        std::lock_guard<std::mutex> lock(mutex);
        if (alive) {
            _loop.invoke([] {
                std::cout << "Done" << std::endl;
            });
        }
    }

private:
    Runloop &_loop;
    std::atomic_bool alive;
    std::mutex mutex;
    std::thread thread;
};

int main() {

    std::cout << "Starting loop on: " << std::this_thread::get_id() << std::endl;
    Runloop runloop;

    std::vector<std::unique_ptr<Task>> tasks;

    for (size_t i = 0; i < 500; i++) {
        tasks.push_back(std::make_unique<Task>(runloop));
    }

    runloop.invoke([&] {
        std::cout << "Doing some heavy processing" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));

        std::cout << "Canceling outstanding tasks" << std::endl;
        tasks.clear();

        std::cout << "Stopping runLoop" << std::endl;
        runloop.stop();
    });

    runloop.run();

    std::cout << "End of loop" << std::endl;
}