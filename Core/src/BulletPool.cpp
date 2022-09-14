#include "Pch.h"
#include "BulletPool.h"
#include "Bullet.h"

BulletPool& BulletPool::Get()
{
    static BulletPool instance;
    return instance;
}

BulletPool::BulletPool()
{
}

BulletPool::~BulletPool()
{
}

void BulletPool::Start()
{
    for (int i = 0; i < _maxSize; i++)
        _pool.push_back(new Bullet);
    for (int i = 0; i < _maxSize; i++)
        _pool[i]->Start();
}

void BulletPool::Update(const float& deltaTime)
{
    for (int i = 0; i < _maxSize; i++)
        _pool[i]->Update(deltaTime);
}

void BulletPool::Draw()
{
    for (int i = 0; i < _maxSize; i++)
        _pool[i]->Draw();
}

void BulletPool::OnDestroy()
{
    for (int i = 0; i < _maxSize; i++)
        _pool[i]->OnDestroy();
    for (int i = 0; i < _maxSize; i++)
        delete _pool[i];
    _pool.clear();
}

void BulletPool::ActivateNext(Transform transform_, std::string owner)
{
    _pool[_next]->Activate(transform_, owner);
    _next = (_next + 1) % _maxSize;
}
