#include "Pch.h"
#include "Collision.h"
#include "GameObject.h"
#include "Player.h"
#include "TileMap.h"
#include "Tile.h"
#include "Key.h"

const float COLLISION_OFFSET = 0.001f;

bool AABB(GameObject obj1, GameObject obj2)
{
	bool trig = (obj1.GetLeft() < obj2.GetRight() &&
		obj1.GetRight() > obj2.GetLeft() &&
		obj1.GetTop() > obj2.GetBottom() &&
		obj1.GetBottom() < obj2.GetTop());
	return trig;
}

void Collision::PlayerWorld(Player& player, TileMap& world)
{
	sf::Vector2f finalPosition = player.GetDestination();
	bool hasCollisionX = false;
	bool hasCollisionY = false;
	for (int i = 0; i < world.GetMap().size(); i++)
	{
		Tile* tile = world.GetMap()[i];
		GameObject testPlayer;
		testPlayer.SetDimensions(player.GetDimensions());
		testPlayer.transform.position = player.GetDestination();

		if (AABB(testPlayer, *tile) /*&& tile->GetID() >= 0*/)
		{
			testPlayer.transform.position = { player.GetDestination().x, player.transform.position.y };
			hasCollisionX = AABB(testPlayer, *tile);

			testPlayer.transform.position = { player.transform.position.x, player.GetDestination().y };
			hasCollisionY = AABB(testPlayer, *tile);

			if (hasCollisionX && (player.GetDestination().x - player.transform.position.x) > 0.f) // Positive X
				finalPosition.x = tile->transform.position.x - (tile->GetDimensions().x * 0.5f) - (player.GetDimensions().x * 0.5f) - COLLISION_OFFSET;
			else if (hasCollisionX) // Negative X
				finalPosition.x = tile->transform.position.x + (tile->GetDimensions().x * 0.5f) + (player.GetDimensions().x * 0.5f) + COLLISION_OFFSET;

			if (hasCollisionY && (player.GetDestination().y - player.transform.position.y) > 0.f) // Positive Y
				finalPosition.y = tile->transform.position.y - (tile->GetDimensions().y * 0.5f) - (player.GetDimensions().y * 0.5f) - COLLISION_OFFSET;
			else if (hasCollisionY) // Negative Y
				finalPosition.y = tile->transform.position.y + (tile->GetDimensions().y * 0.5f) + (player.GetDimensions().y * 0.5f) + COLLISION_OFFSET;

			player.OnCollision(tile);
		}
	}
	player.ConfirmDestination(finalPosition);

	//Check Keys
	for (int i = 0; i < world.GetKeys().size(); i++)
	{
		DoorKey* key = world.GetKeys()[i];
		if (AABB(player, *key)) // Key Overlap
		{
			player.AddKeyCount();
			key->OnDestroy();
			delete key;
			world.GetKeys().erase(world.GetKeys().begin() + i);

			//Check all keys found
			if (world.GetKeys().size() == 0)
			{
				//Find Door
				for (int j = 0; j < world.GetMap().size(); j++)
				{
					if (world.GetMap()[j]->GetID() == 3)
					{
						world.PlayDoorSound();
						world.GetMap()[j]->OnDestroy();
						delete world.GetMap()[j];
						world.GetMap().erase(world.GetMap().begin() + j);
					}
				}
			}
			break;
		}
	}
}

void Collision::Check(GameObject& obj1, GameObject& obj2)
{
	if (AABB(obj1, obj2) && obj1.GetIsActive() && obj2.GetIsActive())
	{
		obj1.OnCollision(&obj2);
		obj2.OnCollision(&obj1);
	}
}
