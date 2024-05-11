#pragma once
#include <chrono>
#include <functional>

class Timer {
private:
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::duration duration;
    std::function<void()> timeoutCallback;
    bool isRunning;

public:
    Timer();
    void start(std::chrono::seconds seconds, std::function<void()> callback);
    void stop();
    bool isTimerRunning() const;
    std::chrono::seconds getRemainingTime() const;
};

