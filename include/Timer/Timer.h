#pragma once
#include "ITimer.h"

class Timer : public ITimer
{
private:
	double duration_ = 0.0;
	double elapsed_ = 0.0;
	bool running_ = true;

public:
	Timer() = default;

	void Start(double _duration) override;

	void Update(double _deltaTime) override;

	bool IsFinished() const override;

	void Reset() override;

	double GetElapsed() const override;

	double GetRemaining() const override;

	double GetProgress() const override;
};
