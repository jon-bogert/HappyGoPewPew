#include "Pch.h"
#include "AssetManager.h"

AssetManager& AssetManager::Get()
{
    static AssetManager instance;
    return instance;
}

AssetManager::AssetManager()
{
    AddTexture("assets/textures/test.png", "test");
    AddTexture("assets/textures/player.png", "player");
    AddTexture("assets/textures/spritesheet.png", "spritesheet");
    AddTexture("assets/textures/crosshair.png", "crosshair");
    AddTexture("assets/textures/bullet_temp.png", "bullet");
    AddTexture("assets/textures/background.png", "background");
    AddTexture("assets/textures/instructions.png", "instructions");
    AddTexture("assets/textures/heart.png", "heart");

    AddFont("assets/fonts/PixelSplitter-Bold.ttf", "default");

    AddSound("assets/audio/menu-hover.wav", "menuHover");
    AddSound("assets/audio/menu-select.wav", "menuSelect");
    AddSound("assets/audio/jump.wav", "jump");
    AddSound("assets/audio/shot-player.wav", "shotPlayer");
    AddSound("assets/audio/shot-enemy.wav", "shotEnemy");
    AddSound("assets/audio/player-hit.wav", "playerHit");
    AddSound("assets/audio/key.wav", "key");
    AddSound("assets/audio/door.wav", "door");
}

AssetManager::~AssetManager()
{
    for (auto texture : _textures)
        delete texture.second;

    for (auto font : _fonts)
        delete font.second;

    for (auto sound : _sounds)
        delete sound.second;
}

sf::Texture* AssetManager::GetTexture(std::string key)
{
    for (auto texture : Get()._textures)
    {
        if (texture.first == key)
            return texture.second;
    }
    return nullptr;
}

sf::Font* AssetManager::GetFont(std::string key)
{
    for (auto font : Get()._fonts)
    {
        if (font.first == key)
            return font.second;
    }
    return nullptr;
}

sf::SoundBuffer* AssetManager::GetSound(std::string key)
{
    for (auto sound : Get()._sounds)
    {
        if (sound.first == key)
            return sound.second;
    }
    return nullptr;
}

void AssetManager::AddTexture(std::string path, std::string key)
{
    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(path);
    _textures.push_back({ key, texture });
}

void AssetManager::AddFont(std::string path, std::string key)
{
    sf::Font* font = new sf::Font();
    font->loadFromFile(path);
    _fonts.push_back({ key, font });
}

void AssetManager::AddSound(std::string path, std::string key)
{
    sf::SoundBuffer* sound = new sf::SoundBuffer();
    sound->loadFromFile(path);
    _sounds.push_back({ key, sound });
}
