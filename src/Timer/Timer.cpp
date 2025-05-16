#include "Timer/Timer.h"

void Timer::Start(double _duration)
{
	duration_ = _duration;
	elapsed_ = 0.0;
	running_ = true;
}

void Timer::Update(double _deltaTime)
{
	if (!running_)
		return;

	elapsed_ += _deltaTime;

	if (elapsed_ >= duration_)
	{
		running_ = false;
		elapsed_ = duration_;
	}
}

bool Timer::IsFinished() const
{
	return !running_;
}

void Timer::Reset()
{
	elapsed_ = 0.0;
	running_ = false;
}

double Timer::GetElapsed() const
{
	return elapsed_;
}

double Timer::GetRemaining() const
{
	return duration_ - elapsed_;
}

double Timer::GetProgress() const
{
	return duration_ > 0 ? elapsed_ / duration_ : 1.0;
}
