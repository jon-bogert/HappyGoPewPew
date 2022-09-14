#include "Debug.h"
#include "Pch.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "windows.h"
//#include <chrono>

#include <fstream>
#include <string>

#pragma warning(disable : 4996)

namespace xe
{
	enum class MsgType { Info, Warn, Err };

	struct Message
	{
		MsgType type;
		std::tm time;
		std::string contents;

		Message(MsgType type, std::string contents)
			: type(type), contents(contents)
		{
			std::time_t t = std::time(0);
			time = *std::localtime(&t);
		}


	};
}

std::vector<xe::Message> activeMessages;
std::ofstream file;
std::string fileName;

sf::RenderWindow* window = nullptr;
unsigned short maxActiveMsgs = 10;
sf::Font* font = nullptr;

float spacing = 12;
float fontSize = 12;

sf::Color bgColor = { 20, 20, 20, 255 };
sf::Color infoColor = { 200, 200, 200, 255 };
sf::Color warnColor = { 255, 205, 67, 255 };
sf::Color errColor = { 255, 0, 0, 255 };

std::string DoubleDigit(int num);
std::string ParseTime(tm time);
void Draw();
void Save();

void xe::Debug::Setup(bool DEBUG_MODE)
{ 
	DEBUG_MODE;

	std::time_t t = std::time(0);
	std::tm now = *std::localtime(&t);

	fileName = "log/";
	fileName.append(ParseTime(now));
	fileName.append(".log");
	
	/*file.open(fileName);
	assert(file.is_open(), "Could not create log file");
	file.close();*/

	if (DEBUG_MODE)
	{
		window = new sf::RenderWindow(sf::VideoMode(800, 600), "XephEngine - Debug Window", sf::Style::Titlebar);
		window->setPosition({0, 0});

		font = new sf::Font;
		font->loadFromFile("Assets/xephengine/JetBrainsMono.ttf");
	}

	Draw();
}

void xe::Debug::ShutDown()
{
	delete font;
	font = nullptr;
	delete window;
	window = nullptr;
}

std::string DoubleDigit(int num)
{
	std::string str;
	if (num < 10)
		str = "0";
	str.append(std::to_string(num));
	return str;
}

std::string ParseTime(tm time)
{
	std::string str;
	str.append(std::to_string(time.tm_year + 1900));
	str.push_back('-');
	str.append(DoubleDigit(time.tm_mon + 1));
	str.push_back('-');
	str.append(DoubleDigit(time.tm_mday));
	str.push_back(' ');
	str.append(DoubleDigit(time.tm_hour));
	str.push_back('.');
	str.append(DoubleDigit(time.tm_min));
	str.push_back('.');
	str.append(DoubleDigit(time.tm_sec));

	return str;
}

void Draw()
{
	if (window != nullptr)
	{
		window->clear(bgColor);
		float yOffset = 0;
		for (xe::Message m : activeMessages)
		{
			sf::Text text;
			std::string str = "[";
			text.setFont(*font);
			text.setCharacterSize(fontSize);
			text.setPosition({ 0, yOffset });

			switch (m.type)
			{
			case xe::MsgType::Info:
				text.setFillColor(infoColor);
				str.append("INFO");
				break;
			case xe::MsgType::Warn:
				text.setFillColor(warnColor);
				str.append("WARN");
				break;
			case xe::MsgType::Err:
				text.setFillColor(errColor);
				str.append("ERR");
				break;
			}
			str.append("][" + ParseTime(m.time) + "] ");
			str.append(m.contents);
			text.setString(str);

			window->draw(text);
			yOffset += spacing;
		}
		window->display();
	}
}

void Save()
{
	auto msg = activeMessages.rbegin();
	file.open(fileName, std::ios_base::app);
	
	switch (msg->type)
	{
	case xe::MsgType::Info:
		file << "[INFO]";
		break;
	case xe::MsgType::Warn:
		file << "[WARN]";
		break;
	case xe::MsgType::Err:
		file << "[ERR]";
		break;
	}
	file << "[" << ParseTime(msg->time) << "] " << msg->contents << std::endl;

	file.close();
}

void xe::Debug::Log(const char* fmt, ...)
{
	char buffer[4096];
	va_list args;
	va_start(args, fmt);
	(void)vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	activeMessages.push_back(Message(MsgType::Info, buffer));
	Draw();
	Save();
}

void xe::Debug::LogWarn(const char* fmt, ...)
{
	char buffer[4096];
	va_list args;
	va_start(args, fmt);
	(void)vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	activeMessages.push_back(Message(MsgType::Warn, buffer));
	Draw();
	Save();
}

void xe::Debug::LogErr(const char* fmt, ...)
{
	char buffer[4096];
	va_list args;
	va_start(args, fmt);
	(void)vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	activeMessages.push_back(Message(MsgType::Err, buffer));
	Draw();
	Save();
}


