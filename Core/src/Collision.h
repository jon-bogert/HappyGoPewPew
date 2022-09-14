#pragma once

class GameObject;
class Player;
class TileMap;
namespace Collision

{
	void PlayerWorld(Player& player, TileMap& world);
	void Check(GameObject& obj1, GameObject& obj2);
};

