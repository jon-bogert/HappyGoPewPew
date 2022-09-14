#pragma once
#include "GameObject.h"
class Tile : public GameObject
{
    sf::Sprite _sprite;
    int _id;

public:
    Tile(int id);

    void Start() override;
    void Update(const float& deltaTime) override;
    void Draw() override;
    void OnDestroy() override;

    int GetID() const;
};

