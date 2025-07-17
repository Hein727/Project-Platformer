#pragma once
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include "AABBChecker.h"
#include <memory>
#include <DirectXMath.h>
#include <memory>


class Geometry
{
public:
    Geometry(const char* modelPath)
    {
        model = std::make_shared<Model>(modelPath);
        box = LoadAABB(model.get());
        box = UpdateHitBox(box, position, scale);
    }

    virtual ~Geometry() = default;

    void Update(float elapsedTime)
	{
		UpdateTransform();

		model->UpdateTransform(transform);
	}
    void UpdateTransform();

    virtual void Render(ID3D11DeviceContext* dc, Shader* shader)
    {
        if (!model) return;
        shader->Draw(dc, model.get());
    }

    void SetPosition(const DirectX::XMFLOAT3& pos) { position = pos; box = UpdateHitBox(box, position, scale);}
    void SetScale(const DirectX::XMFLOAT3& scale) { this->scale = scale; box = UpdateHitBox(box, position, this->scale);}
    void SetRotation(const DirectX::XMFLOAT3& rotation) { this->rotation = rotation;}

    auto GetPosition() const { return position; }
    auto GetRotation() const { return rotation; }
    auto GetScale() const { return scale; }

    HitBox getHitBox() { return this->box; }

protected:
    std::shared_ptr<Model> model;
    HitBox box;
    DirectX::XMFLOAT3 position = { 0,0,0 };
    DirectX::XMFLOAT3 rotation = { 0,0,0 };
    DirectX::XMFLOAT3 scale = { 1,1,1 };
    DirectX::XMFLOAT4X4 transform = {
                    1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1
    };
};
