#pragma once

#include <Utilities/Types.h>

_FLUID_ENGINE_BEGIN

/*
* Frame
*	a structure of frame infos
*/
class Frame final {
public:
	uint index = 0;
	real timeInterval = (real)1 / (real)60;

	Frame(const uint& newIndex, const real& newTimeInterval);

	real currentTime() const;
	void advance(uint delta = 1);

	/* Advance single frame (prefix) */
	Frame& operator++();
	/* Advance single frame (postfix) */
	Frame operator++(int);
};

class Animation {
public:
	Animation() = default;
	virtual ~Animation() = default;

	/* Updates this animation to given frame by calling onUpdate */
	void update(const Frame& frame);

protected:
	/* Advances this animation to given frame */
	virtual void onUpdate(const Frame& frame) = 0;
};

class PhysicsAnimation : public Animation {
private:
	/* Maximal time step for physics calculation */
	Frame _currentFrame;
	const real _maxDt = .01;

	virtual void onUpdate(const Frame& frame) final;

public:
	PhysicsAnimation(const Frame& currentFrame, const real& maxDt);

protected:
	/*
	* Advances this physics animation by timeInterval.
	* This function should advance the physics animation by calling onAdvance.
	* It should cut timeInterval into rather small pieces according to certian
	* laws such as CFL-condition, which depends on specific demos.
	*/
	virtual void advance(const real timeInterval);
	/* Does actual physics calculation */
	virtual void onAdvance(const real dt) = 0;
};

_FLUID_ENGINE_END