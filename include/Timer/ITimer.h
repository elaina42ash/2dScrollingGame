#pragma once

class ITimer
{
public:
	virtual  ~ITimer() = default;

	virtual void Start(double _duration) = 0;

	virtual void Update(double _deltaTime) = 0;

	virtual bool IsFinished() const = 0;

	virtual void Reset() = 0;

	virtual double GetElapsed() const = 0;

	virtual double GetRemaining() const = 0;

	virtual double GetProgress() const = 0;

};
