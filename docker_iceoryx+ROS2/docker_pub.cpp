#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <iceoryx_posh/popo/publisher.hpp>
#include <iceoryx_posh/popo/subject.hpp>
#include <iceoryx_posh/runtime/posh_runtime.hpp>
#include <iceoryx_posh/popo/consumer.hpp>

int main() {
    // Initialize Iceoryx runtime
    iox::runtime::PoshRuntime::initRuntime("cpp_iox_example");

    // Create a publisher on a specific topic
    iox::popo::Publisher<int> publisher({"Example", "Topic", "Publisher"});

    // Publish a message every second
    std::atomic<int> count(1);
    while (true) {
        // Publish the current count value
        publisher.publish(count++);
        std::cout << "Published: " << count - 1 << std::endl;

        // Sleep for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
