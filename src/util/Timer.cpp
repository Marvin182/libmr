#include "Timer.h"
#include "../common/assert.h"

namespace mr {
namespace util {

Timer::Timer(TimerState state) :
	state(state),
	stopwatchTime(0),
	started(clock_t::duration(0)),
	stopped(clock_t::duration(0))
{
	switch (state) {
		case TimerState::not_started:
			// nothing to do here
			break;
		case TimerState::started:
			started = now();
			break;
		case TimerState::started_but_paused:
			// nothing to do here
			break;
		case TimerState::stopped:
			started = now();
			stopped = started;
			break;
		default:
			assert_unreachable();
	}
}

void Timer::start() {
	assert_error(state == TimerState::not_started, "Timer was already started");
	restart();
}

void Timer::restart() {
	state = TimerState::started;
	stopwatchTime = clock_t::duration(0);
	started = now();
}

void Timer::stop() {
	assert_error(state == TimerState::started || state == TimerState::started_but_paused, "Timer wasn't running");
	stopped = now();
	if (state == TimerState::started_but_paused) {
		started = stopped;
	}
	state = TimerState::stopped;
}

void Timer::pause() {
	assert_error(state != TimerState::started_but_paused, "Timer is already paused.");
	assert_error(state == TimerState::started, "Can't pause stopped timer.");
	stopwatchTime = elapsed();
	state = TimerState::started_but_paused;
}

void Timer::resume() {
	assert_error(state != TimerState::stopped, "Timer was already stopped.");
	assert_error(state == TimerState::started_but_paused, "Timer wasn't paused.");
	state = TimerState::started;
	started = now();
}

Timer::clock_t::duration Timer::elapsed() const {
	switch (state) {
		case TimerState::not_started:
			assert_error(false, "Timer was never started.");
			return clock_t::duration(0);
		case TimerState::started:
			return std::chrono::duration_cast<clock_t::duration>(now() - started) + stopwatchTime;
		case TimerState::started_but_paused:
			return stopwatchTime;
		case TimerState::stopped:
			return std::chrono::duration_cast<clock_t::duration>(stopped - started) + stopwatchTime;
	}

	assert_unreachable();
	return clock_t::duration(0);
}

uint64_t Timer::elapsedSeconds() const {
	return std::chrono::duration_cast<std::chrono::duration<uint64_t, std::ratio<1, 1>>>(elapsed()).count();
}

uint64_t Timer::elapsedMilliseconds() const {
	return std::chrono::duration_cast<std::chrono::duration<uint64_t, std::milli>>(elapsed()).count();
}

uint64_t Timer::elapsedMicroseconds() const {
	return std::chrono::duration_cast<std::chrono::duration<uint64_t, std::milli>>(elapsed()).count();
}

uint64_t Timer::elapsedNanoseconds() const {
	return std::chrono::duration_cast<std::chrono::duration<uint64_t, std::nano>>(elapsed()).count();
}

Timer::clock_t::time_point Timer::now() const {
	return clock_t::now();
}

} // namespace util
} // namespace mr
