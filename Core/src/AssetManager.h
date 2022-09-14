#pragma once
class AssetManager
{
	std::vector<std::pair<std::string, sf::Texture*>> _textures;
	std::vector<std::pair<std::string, sf::Font*>> _fonts;
	std::vector<std::pair<std::string, sf::SoundBuffer*>> _sounds;

public:
	static AssetManager& Get();
private:
	AssetManager();
public:
	~AssetManager();
	AssetManager(const AssetManager& other) = delete;
	AssetManager& operator=(const AssetManager& other) = delete;

	static sf::Texture* GetTexture(std::string key);
	static sf::Font* GetFont(std::string key);
	static sf::SoundBuffer* GetSound(std::string key);

private:
	void AddTexture(std::string path, std::string key);
	void AddFont(std::string path, std::string key);
	void AddSound(std::string path, std::string key);

};

