#pragma once

class Bullet;
class BulletPool
{
	std::vector<Bullet*> _pool;
	int _maxSize = 10;
	int _next = 0;

public:
	static BulletPool& Get();
private:
	BulletPool();
public:
	virtual ~BulletPool();
	BulletPool(const BulletPool& other) = delete;
	BulletPool& operator=(const BulletPool& other) = delete;

	void Start();
	void Update(const float& deltaTime);
	void Draw();
	void OnDestroy();

	void ActivateNext(Transform transform_, std::string owner);
};

