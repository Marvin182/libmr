#ifndef MR_TIMER_H
#define MR_TIMER_H

#include <chrono>

namespace mr {
namespace util {

enum class TimerState {
	not_started,
	started,
	started_but_paused,
	stopped
};

class Timer {
public:
	using clock_t = std::chrono::high_resolution_clock;

	template <typename F>
	static uint64_t timeMs(F func);

	template <typename F>
	static uint64_t timeNs(F func);

	Timer(TimerState state = TimerState::not_started);

	void start();
	void restart();
	void stop();

	void pause();
	void resume();

	clock_t::duration elapsed() const;

	uint64_t elapsedSeconds() const;
	uint64_t elapsedMilliseconds() const;
	uint64_t elapsedMicroseconds() const;
	uint64_t elapsedNanoseconds() const;

private:
	TimerState state;
	clock_t::duration stopwatchTime;
	clock_t::time_point started;
	clock_t::time_point stopped;

	clock_t::time_point now() const;
};

template <typename F>
uint64_t Timer::timeMs(F func) {
	Timer t;
	t.start();
	func();
	t.stop();
	return t.elapsedMilliseconds();
}

template <typename F>
uint64_t Timer::timeNs(F func) {
	Timer t;
	t.start();
	func();
	t.stop();
	return t.elapsedNanoseconds();
}

} //namespace util
} // mr

#endif // MR_TIMER_H