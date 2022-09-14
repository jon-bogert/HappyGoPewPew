#include "Pch.h"
#include "TileMap.h"
#include "Tile.h"
#include "Key.h"
#include "Enemy.h"
#include "Background.h"
#include "AssetManager.h"

void TileMap::Start()
{
	_bg = new Background();
	//Load("assets/maps/level1.map");
	_doorSound.setBuffer(*AssetManager::Get().GetSound("door"));

	_bg->Start();
	for (Tile* tile : _map)
		tile->Start();
	for (DoorKey* key : _keys)
		key->Start();
	for (Enemy* enemy : _enemies)
		enemy->Start();
}

void TileMap::Update(const float& deltaTime)
{
	_bg->Update(deltaTime);
	for (Tile* tile : _map)
		tile->Update(deltaTime);
	for (DoorKey* key : _keys)
		key->Update(deltaTime);
	for (Enemy* enemy : _enemies)
		enemy->Update(deltaTime);
}

void TileMap::Draw()
{
	_bg->Draw();
	for (Tile* tile : _map)
		tile->Draw();
	for (DoorKey* key : _keys)
		key->Draw();
	for (Enemy* enemy : _enemies)
		enemy->Draw();
}

void TileMap::OnDestroy()
{
	_bg->OnDestroy();
	for (Tile* tile : _map)
		tile->OnDestroy();
	for (DoorKey* key : _keys)
		key->OnDestroy();
	for (Enemy* enemy : _enemies)
		enemy->OnDestroy();

	delete _bg;
	for (Tile* tile : _map)
		delete tile;
	for (DoorKey* key : _keys)
		delete key;
	for (Enemy* enemy : _enemies)
		delete enemy;

	_bg = nullptr;
	_map.clear();
	_keys.clear();
	_enemies.clear();
}

void TileMap::Load(std::string path)
{
	int old_width = _width, old_height = _height;
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cout << "[ERROR] Unable to open file at " << path << std::endl;
		return;
	}
	std::string data;
	//Get Width
	getline(file, data);
	data.erase(0, 6);
	_width = atoi(data.c_str());

	//Get Height
	getline(file, data);
	data.erase(0, 7);
	_height = atoi(data.c_str());

	if ((old_width != _width || old_height != _height) && _map.size() > 0)
		std::cout << "Width or Height does not match previous dimensions!" << std::endl;

	for (int i = 0; i < _width * _height; i++)
	{
		file >> data;
		int id = atoi(data.c_str());
		if (id == 4)
		{
			DoorKey* key = new DoorKey();
			_keys.push_back(key);
			key->transform.position = { (i % _width) + 0.5f, _height - 1 - (i / _width) + 0.5f };
		}
		else if (id == 5)
		{
			Enemy* enemy = new Enemy();
			_enemies.push_back(enemy);
			enemy->transform.position = { (i % _width) + 0.5f, _height - 1 - (i / _width) + 0.5f };
		}
		else if (id >= 0)
		{
			Tile* tile = new Tile(id);
				_map.push_back(tile);

			tile->transform.position = { (i % _width) + 0.5f, _height - 1 - (i / _width) + 0.5f };
			//TODO - add to collision
		}
	}
	file.close();
}

std::vector<Tile*>& TileMap::GetMap()
{
	return _map;
}

std::vector<DoorKey*>& TileMap::GetKeys()
{
	return _keys;
}

std::vector<Enemy*>& TileMap::GetEnemies()
{
	return _enemies;
}

Background* TileMap::GetBackground()
{
	return _bg;
}

int TileMap::GetWidth() const
{
	return _width;
}

int TileMap::GetHeight() const
{
	return _height;
}

void TileMap::PlayDoorSound()
{
	_doorSound.play();
}
