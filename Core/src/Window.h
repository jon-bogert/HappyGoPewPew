#pragma once

class Window
{
	sf::RenderWindow* _window = nullptr;

	sf::Vector2f _camera{};

	std::string _title = "Happy Go Pew-Pew";
	sf::Vector2f _resolution = { 1920, 1080 };
	sf::Vector2f _refResolution = { 1280, 720 };
	float _scale = 1.f;

	int _pixelsPerUnit = 32;

	bool _fullscreenMode = true; // false for debug

public:
	static Window& Get();

private:
	Window();

public:
	~Window();
	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;

	static sf::RenderWindow* UnWrap();

	bool GetIsOpen();
	void CloseEventLoop();
	static void Draw(sf::Sprite& sprite, Transform transfrom);
	static void Draw(sf::Text& text, Transform transfrom);
	static void Draw(sf::RectangleShape& rect, Transform transfrom);

	static void DrawHUD(sf::Sprite& sprite, Transform transfrom);
	static void DrawHUD(sf::Text& text, Transform transfrom);
	static void DrawHUD(sf::RectangleShape& rect, Transform transfrom);

	void Clear();
	void Display();
	static void Close();

	static sf::Vector2f GetResolution();
	void ChangeResolution(const sf::Vector2f& resolution);
	float GetScaling() const;

	static void SetCameraPosition(sf::Vector2f position);
	static void AddCameraPosition(sf::Vector2f position);
	static sf::Vector2f GetCameraPosition();

	static int GetPixelsPerUnit();
	static float GetScale();

	static float WidthInUnits();
	static float HeightInUnits();

	static void SetCursorVis(const bool visible);
};

