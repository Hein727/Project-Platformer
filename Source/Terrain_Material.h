#pragma once
#include "Geometry.h"
#include "Player.h"


class Block : public Geometry
{
public :
	Block() : Geometry("Data/Model/Geometry/Block.mdl") {};
	void Update(float elapsedTime)
	{
		Player& player = Player::Instance();

		HitBox playerBox = player.HitBoxGetter();

		if (HitCheckForJump(box, playerBox))
		{
			player.SetIsJumping(false);
		}

		Geometry::Update(elapsedTime);
	}
	~Block() {};
};

class Ground_Block : public Geometry
{
public:
	Ground_Block() : Geometry("Data/Model/Geometry/Ground.mdl") {};
	void Update(float elapsedTime)
	{
		Player& player = Player::Instance();

		HitBox playerBox = player.HitBoxGetter();

		if (HitCheckForJump(box, playerBox))
		{
			player.SetIsJumping(false);
		}

		Geometry::Update(elapsedTime);
	}
	~Ground_Block() {};
};

class Slope : public Geometry
{
public:
	Slope() : Geometry("Data/Model/Geometry/Ground_Slope.mdl") {};
	void Update(float elapsedTime)
	{
		Player& player = Player::Instance();

		HitBox playerBox = player.HitBoxGetter();

		if (HitCheckForJump(box, playerBox))
		{
			player.SetIsJumping(false);
		}

		Geometry::Update(elapsedTime);
	}
	~Slope() {};
};

class Spike : public Geometry
{
public :
	Spike() : Geometry("Data/Model/Geometry/Wooden_Spike.mdl") {};
	void Update(float elapsedTime)
	{
		Player& player = Player::Instance();

		HitBox playerBox = player.HitBoxGetter();

		if (HitCheck(box, playerBox))
		{
			player.DamageTaker();
		}

		Geometry::Update(elapsedTime);
	}
	~Spike() {};
};

class Flag : public Geometry
{
public:
	Flag() : Geometry("Data/Model/Geometry/Flag.mdl") {};
	~Flag() {};
};

class Archway : public Geometry
{
public :
	Archway() : Geometry("Data/Model/Geometry/Archway.mdl") {};
	~Archway() {};
};

class FloatingPlatform : public Geometry
{
public :
	FloatingPlatform() : Geometry("Data/Model/Geometry/Floating_Platform.mdl") {};
	~FloatingPlatform() {};
};

class Box : public Geometry
{
public :
	Box() : Geometry("Data/Model/Geometry/box.mdl") {}
	~Box() {};
};