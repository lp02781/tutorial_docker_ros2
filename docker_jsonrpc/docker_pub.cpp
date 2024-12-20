#include <iostream>
#include <json/json.h>
#include <httplib.h>  // For HTTP server
#include <thread>      // For threading
#include <chrono>      // For time functions

// Global variable to store the count
int count = 1;

// Function to get the hello message
std::string get_hello_message(int count) {
    return "Hello, world! Count: " + std::to_string(count);
}

// Background function to increment count every second
void increment_count() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Wait for 1 second
        count++;  // Increment the count every second
    }
}

int main() {
    // Start the background thread to increment count every second
    std::thread increment_thread(increment_count);
    increment_thread.detach();  // Run the thread independently

    httplib::Server svr;

    // Handle the /jsonrpc endpoint
    svr.Post("/jsonrpc", [](const httplib::Request& req, httplib::Response& res) {
        Json::Value root;
        root["jsonrpc"] = "2.0";
        root["method"] = "getHello";
        root["params"] = Json::arrayValue;
        root["id"] = 1;
        root["result"] = get_hello_message(count);  // Get the hello message with the current count
        res.set_content(root.toStyledString(), "application/json");
    });

    // Start the server to listen on port 8080
    svr.listen("0.0.0.0", 8080);  // Listen on all IP addresses at port 8080

    return 0;
}
