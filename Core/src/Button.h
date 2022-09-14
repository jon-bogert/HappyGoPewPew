#pragma once
#include "GameObject.h"
class Button : public GameObject
{
	sf::RectangleShape _plate;
	sf::Text _text;
	sf::Sound _hoverSound;
	sf::Sound _selectSound;

	float _fontSize = 20.f;
	sf::Color _activeColor = {180, 180, 180, 127};
	sf::Color _inactiveColor = { 127, 127, 127, 127 };

	float _width;
	float _height;
	bool _hoverTrigger = false;

public:
	Button(std::string text, int width, int height);

	void Start() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
	void OnDestroy() override;

	bool GetPressEvent();

private:
	bool CheckHover();
};

