#include "Animation.h"
#include <Utilities/Constants.h>

_FLUID_ENGINE_BEGIN

Frame::Frame(const uint& newIndex, const real& newTimeInterval) :
	index(newIndex), timeInterval(newTimeInterval)
{
}

real Frame::currentTime() const
{
	return timeInterval * index;
}

void Frame::advance(uint delta)
{
	index += delta;
	return;
}

Frame& Frame::operator++()
{
	advance();
	return *this;
}

Frame Frame::operator++(int)
{
	Frame lastFrame = *this;
	advance();
	return lastFrame;
}

void Animation::update(const Frame& frame)
{
	// TODO: pre-updating works such as logging

	onUpdate(frame);

	// TODO: post-updating works such as logging
	return;
}

void PhysicsAnimation::onUpdate(const Frame& frame)
{
	if (frame.index > _currentFrame.index) {
		for (uint i = frame.index; i < _currentFrame.index; ++i)
			advance(frame.timeInterval);
		_currentFrame = frame;
	}
	return;
}

PhysicsAnimation::PhysicsAnimation(const Frame& currentFrame, const real& maxDt) :
	_currentFrame(currentFrame), _maxDt(maxDt)
{
}

void PhysicsAnimation::advance(const real timeInterval)
{
	real remainingTime = timeInterval;
	while (remainingTime >= _maxDt) {
		// TODO: log info before onAdvance
		onAdvance(_maxDt);
		remainingTime -= _maxDt;
		// TODO: log info after onAdvance
	}
	if (remainingTime >= eps) {
		// TODO: log info before onAdvance
		onAdvance(remainingTime);
		// TODO: log info after onAdvance
	}
	return;
}

_FLUID_ENGINE_END
