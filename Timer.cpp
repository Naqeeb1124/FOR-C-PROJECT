#include "Timer.h"

Timer::Timer() : isRunning(false) {}

void Timer::start(std::chrono::seconds seconds, std::function<void()> callback) {
    startTime = std::chrono::steady_clock::now();
    duration = std::chrono::seconds(seconds);
    timeoutCallback = callback;
    isRunning = true;
}

void Timer::stop() {
    isRunning = false;
}

bool Timer::isTimerRunning() const {
    return isRunning;
}

std::chrono::seconds Timer::getRemainingTime() const {
    if (!isRunning) {
        return std::chrono::seconds(0);
    }

    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = currentTime - startTime;

    if (elapsedTime >= duration) {
        return std::chrono::seconds(0);
    }

    return std::chrono::duration_cast<std::chrono::seconds>(duration - elapsedTime);
}
