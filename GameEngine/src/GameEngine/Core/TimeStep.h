#pragma once

namespace GameEngine {

	class TimeStep
	{
	public:
		TimeStep(float time = 0.0f)
			: time(time)
		{

		}

		operator float() const { return this->time; };

		float getTime() const { return this->time ; }
		float getMs() const { return this->time * 0.001f; }
	private:
		float time;
	};
}