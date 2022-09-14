#pragma once

enum class GameState {Game, MainMenu, Win, Lose, Instructions};

struct Rotator
{
private:
	float _value = 0.f;

	void Fix()
	{
		while (_value < 0.f) _value += 360.f;
		while (_value >= 360.f) _value -= 360.f;
	}
public:
	Rotator() = default;
	Rotator(float degrees)
	{
		_value = degrees;
		Fix();
	}
	float GetRad() const
	{
		return _value * (3.14159f / 180.f);
	}
	float GetDeg() const
	{
		return _value;
	}
	void SetRad(const float& value)
	{
		_value = value * (180.f / 3.14159);
		Fix();
	}
	void SetDeg(const float& value)
	{
		_value = value;
		Fix();
	}
	void AddRad(const float& value)
	{
		_value += value * (180.f / 3.14159);
		Fix();
	}
	void AddDeg(const float& value)
	{
		_value += value;
		Fix();
	}
};

struct Transform
{
	sf::Vector2f position{};
	Rotator rotation{ 0 };
	sf::Vector2f scale{1.f, 1.f};
};