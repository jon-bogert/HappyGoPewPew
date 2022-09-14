#include "Pch.h"
#include "Window.h"

Window& Window::Get()
{
	static Window instance;
	return instance;
}

Window::Window()
{
	if (_fullscreenMode)
	{
		_resolution = { (float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height };
		_window = new sf::RenderWindow(sf::VideoMode((int)_resolution.x, (int)_resolution.y), _title, sf::Style::Fullscreen );
	}
	else
		_window = new sf::RenderWindow(sf::VideoMode((int)_resolution.x, (int)_resolution.y), _title, sf::Style::Close );

	_scale = _resolution.y / _refResolution.y;
}

Window::~Window()
{
	delete _window;
	_window = nullptr;
}

sf::RenderWindow* Window::UnWrap()
{
	return Get()._window;
}

bool Window::GetIsOpen()
{
	return _window->isOpen();
}

void Window::CloseEventLoop()
{
	sf::Event winEvent;
	while (_window->pollEvent(winEvent))
	{
		if (winEvent.type == sf::Event::Closed /*|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)*/)
			_window->close();
	}
}

void Window::Draw(sf::Sprite& sprite, Transform transfrom)
{
	sprite.setPosition({
		(transfrom.position.x * Get()._pixelsPerUnit * Get()._scale) - (Get()._camera.x * Get()._pixelsPerUnit * Get()._scale),
		Get()._resolution.y - ((transfrom.position.y * Get()._pixelsPerUnit * Get()._scale) - (Get()._camera.y * Get()._pixelsPerUnit * Get()._scale)) });


	sprite.setScale(transfrom.scale.x * Get()._scale, transfrom.scale.y * Get()._scale);
	sprite.setRotation(transfrom.rotation.GetDeg());
	Get()._window->draw(sprite);
}

void Window::Draw(sf::Text& text, Transform transfrom)
{
	text.setPosition({
		(transfrom.position.x * Get()._pixelsPerUnit * Get()._scale) - (Get()._camera.x * Get()._pixelsPerUnit * Get()._scale),
		Get()._resolution.y - ((transfrom.position.y * Get()._pixelsPerUnit * Get()._scale) - (Get()._camera.y * Get()._pixelsPerUnit * Get()._scale)) });


	text.setScale(transfrom.scale.x * Get()._scale, transfrom.scale.y * Get()._scale);
	text.setRotation(transfrom.rotation.GetDeg());
	Get()._window->draw(text);
}

void Window::Draw(sf::RectangleShape& rect, Transform transfrom)
{
	rect.setPosition({
		(transfrom.position.x * Get()._pixelsPerUnit * Get()._scale) - (Get()._camera.x * Get()._pixelsPerUnit * Get()._scale),
		Get()._resolution.y - ((transfrom.position.y * Get()._pixelsPerUnit * Get()._scale) - (Get()._camera.y * Get()._pixelsPerUnit * Get()._scale)) });


	rect.setScale(transfrom.scale.x * Get()._scale, transfrom.scale.y * Get()._scale);
	rect.setRotation(transfrom.rotation.GetDeg());
	Get()._window->draw(rect);
}

void Window::DrawHUD(sf::Sprite& sprite, Transform transfrom)
{
	sprite.setPosition({
		(transfrom.position.x * Get()._pixelsPerUnit * Get()._scale),
		Get()._resolution.y - ((transfrom.position.y * Get()._pixelsPerUnit * Get()._scale)) });


	sprite.setScale(transfrom.scale.x * Get()._scale, transfrom.scale.y * Get()._scale);
	sprite.setRotation(transfrom.rotation.GetDeg());
	Get()._window->draw(sprite);
}

void Window::DrawHUD(sf::Text& text, Transform transfrom)
{
	text.setPosition({
		(transfrom.position.x * Get()._pixelsPerUnit * Get()._scale),
		Get()._resolution.y - ((transfrom.position.y * Get()._pixelsPerUnit * Get()._scale)) });


	text.setScale(transfrom.scale.x * Get()._scale, transfrom.scale.y * Get()._scale);
	text.setRotation(transfrom.rotation.GetDeg());
	Get()._window->draw(text);
}

void Window::DrawHUD(sf::RectangleShape& rect, Transform transfrom)
{
	rect.setPosition({
		(transfrom.position.x * Get()._pixelsPerUnit * Get()._scale),
		Get()._resolution.y - ((transfrom.position.y * Get()._pixelsPerUnit * Get()._scale))});


	rect.setScale(transfrom.scale.x * Get()._scale, transfrom.scale.y * Get()._scale);
	rect.setRotation(transfrom.rotation.GetDeg());
	Get()._window->draw(rect);
}

void Window::Clear()
{
	_window->clear({ 0, 0, 0, 255 });
}

void Window::Display()
{
	_window->display();
}

void Window::Close()
{
	Get()._window->close();
}

sf::Vector2f Window::GetResolution()
{
	return Get()._resolution;
}

void Window::ChangeResolution(const sf::Vector2f& resolution)
{
	_resolution = resolution;
	delete _window;
	_window = new sf::RenderWindow(sf::VideoMode((int)_resolution.x, (int)_resolution.y), _title);
	_scale = resolution.y / _refResolution.y;
}

float Window::GetScaling() const
{
	return _scale;
}

void Window::SetCameraPosition(sf::Vector2f position)
{
	Get()._camera = position;
}

void Window::AddCameraPosition(sf::Vector2f position)
{
	Get()._camera += position;
}

sf::Vector2f Window::GetCameraPosition()
{
	return Get()._camera;
}

int Window::GetPixelsPerUnit()
{
	return Get()._pixelsPerUnit;
}

float Window::GetScale()
{
	return Get()._scale;
}

float Window::WidthInUnits()
{
	return Get()._refResolution.x / Get()._pixelsPerUnit;
}

float Window::HeightInUnits()
{
	return Get()._refResolution.y / Get()._pixelsPerUnit;
}

void Window::SetCursorVis(const bool visible)
{
	Get()._window->setMouseCursorVisible(visible);
}
