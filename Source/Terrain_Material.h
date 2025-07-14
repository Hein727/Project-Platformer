#pragma once
#include "Geometry.h"
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include "AABBChecker.h"
#include <memory>

class Ground : public Geometry
{
public :
	Ground();
	virtual ~Ground() {};

	void Update(float elapsedTime);
	void Render(ID3D11DeviceContext* dc, Shader* shader);
	void SetPosition(DirectX::XMFLOAT3 pos) { this->position = pos; }
	void SetScale(DirectX::XMFLOAT3 scale) { this->scale = scale; }
	/*Ground(Ground&&) noexcept = default;
	Ground& operator=(Ground&&) noexcept = default;

	Ground(const Ground&) = delete;
	Ground& operator= (const Ground&) = delete;*/

protected :
	
	std::shared_ptr<Model> model;
	HitBox box;
};


class Block : public Ground
{
public :
	Block()
	{
		model = std::make_shared<Model>("Data/Model/Geometry/block.mdl");
	}
	~Block() {};
};

class Ground_Block : public Ground
{
public:
	Ground_Block()
	{
		model = std::make_shared<Model>("Data/Model/Geometry/Ground.mdl");
	}
	~Ground_Block() {};
};

class Slope : public Ground
{
public:
	Slope()
	{
		model = std::make_shared<Model>("Data/Model/Geometry/Ground_Slope.mdl");
	}
	~Slope() {};
};

class Spike : public Ground
{
public :
	Spike() 
	{
		model = std::make_shared<Model>("Data/Model/Geometry/Wooden_Spike.mdl");
	};
	~Spike() {};
};

class Flag : public Ground
{
public:
	Flag()
	{
		model = std::make_shared<Model>("Data/Model/Geometry/Flag.mdl");
	};
	~Flag() {};
};

class Archway : public Ground
{
public :
	Archway()
	{
		model = std::make_shared<Model>("Data/Model/Geometry/Archway.mdl");
	}
	~Archway() {};
};

class FloatingPlatform : public Geometry
{
public :
	FloatingPlatform()
	{
		model = std::make_shared<Model>("Data/Model/Geometry/Flag.mdl");
		box = LoadAABB(model.get());
	}
	~FloatingPlatform() {};

	void Update(float elapsedTime);

	void Render(ID3D11DeviceContext* dc, Shader* shader);

	void SetPosition(DirectX::XMFLOAT3 pos) { this->position = pos; }
	void SetScale(DirectX::XMFLOAT3 scale) { this->scale = scale; }

	/*FloatingPlatform(FloatingPlatform&&) noexcept = default;
	FloatingPlatform& operator=(FloatingPlatform&&) noexcept = default;

	FloatingPlatform(const FloatingPlatform&) = delete;
	FloatingPlatform& operator= (const FloatingPlatform&) = delete;*/
	
protected:

	std::shared_ptr<Model> model;
	HitBox box;
};

class Box : public Geometry
{
public :
	Box()
	{
		model = std::make_shared<Model>("Data/Model/Geometry/box.mdl");
		box = LoadAABB(model.get());
	}
	~Box() {};

	void Update(float elapsedTime);

	void Render(ID3D11DeviceContext* dc, Shader* shader);

	void SetPosition(DirectX::XMFLOAT3 pos) { this->position = pos; }
	void SetScale(DirectX::XMFLOAT3 scale) { this->scale = scale; }

	/*Box(Box&&) noexcept = default;
	Box& operator=(Box&&) noexcept = default;

	Box(const Box&) = delete;
	Box& operator= (const Box&) = delete;*/

protected :

	std::shared_ptr<Model> model;
	HitBox box;
};