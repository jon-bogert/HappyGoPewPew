#pragma once

class GameObject
{
protected:
	sf::Vector2f _dimensions = { 1, 1 };
	std::string _tag{};
	bool _isActive = true;

public:
	Transform transform{};

	GameObject();
	virtual ~GameObject();

	virtual void Start() {};
	virtual void Update(const float& deltaTime) {};
	virtual void Draw() {};
	virtual void OnDestroy() {};

	virtual void OnCollision(GameObject* other) {}

	sf::Vector2f GetDimensions() const;
	void SetDimensions(const sf::Vector2f dimensions);
	float GetLeft() const;
	float GetTop() const;
	float GetRight() const;
	float GetBottom() const;

	std::string GetTag() const;
	bool GetIsActive() const;

	static void SetupSprite(std::string key, sf::Sprite& sprite);
	static void SetupSprite(std::string key, sf::Sprite& sprite, int pixelWidth, int pixelHeight);
};

