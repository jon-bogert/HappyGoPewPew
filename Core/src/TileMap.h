#pragma once
#include "GameObject.h"

class Tile;
class DoorKey;
class Enemy;
class Background;
class TileMap :
    public GameObject
{
    std::vector<Tile*> _map;
    std::vector<DoorKey*> _keys;
    std::vector<Enemy*> _enemies;
    int _width = 0;
    int _height = 0;

    Background* _bg = nullptr;

    sf::Sound _doorSound;

public:

    void Start() override;
    void Update(const float& deltaTime) override;
    void Draw() override;
    void OnDestroy() override;

    void Load(std::string path);
    std::vector<Tile*>& GetMap();
    std::vector<DoorKey*>& GetKeys();
    std::vector<Enemy*>& GetEnemies();
    Background* GetBackground();

    int GetWidth() const;
    int GetHeight() const;

    void PlayDoorSound();
};

