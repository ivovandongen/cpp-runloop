
#include <thread_local.hpp>
#include <runloop.hpp>

#include <thread>
#include <iostream>
#include <string>


auto printer(Runloop& loop, const std::string &message, int interval) {
    return [&loop, message, interval] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        while (loop.running()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            loop.invoke([&message] {
                std::cout << message << std::this_thread::get_id() << std::endl;
            });
        }
    };
}

int main() {

    std::cout << "Starting loop on: " << std::this_thread::get_id() << std::endl;
    Runloop runloop;

    std::thread t1(printer(runloop, "A: ", 5));
    std::thread t2(printer(runloop, "B: ", 2));
    std::thread t3(printer(runloop, "B: ", 1));

    std::thread ts([&] {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        runloop.stop();
    });

    runloop.run();

    std::cout << "End of loop" << std::endl;
    t1.join();
    t2.join();
    t3.join();
    ts.join();
}