#pragma once

namespace nu
{
	constexpr float Pi = 3.14159265358979323846f;
	constexpr float TwoPi = 6.28318530717958647692f;
	constexpr float HalfPi = 1.57079632679489661923f;

	constexpr float RadToDeg = 180.0f / Pi;
	constexpr float DegToRad = Pi / 180.0f;

	template <typename T>
	T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template <typename T>
	T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}
	
	template <typename T>
	T Wrap(T min, T max, T value)
	{
		if (value > max) { value = min; }
		if (value < min) { value = max; }

		return value;
	}

	template <typename T>
	T Clamp (T min, T max, T value)
	{
		if (value < min) { value = min;  }
		if (value > max) { value = max; }

		return value;
	}
}
