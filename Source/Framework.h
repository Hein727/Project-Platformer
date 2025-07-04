#pragma once

#include <windows.h>
#include "HighResolutionTimer.h"
#include "imgui.h"
#include "Audio/Audio.h"
#include "Graphics/Graphics.h"
#include "Input/input.h"
#include<DirectXMAth.h>

using namespace DirectX;

struct ImVec3
{
	float x, y, z;
	ImVec3() : x(0), y(0), z(0) {}
	ImVec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Transform {
	ImVec3 position = { 0, 0, 0 };
	ImVec3 rotation = { 0, 0, 0 };
	ImVec3 scale = { 1, 1, 1 };
};


struct AABB {
	XMFLOAT3 min;
	XMFLOAT3 max;
};


struct GameObject {
	Transform transform;
	AABB aabb;
};


class Framework
{
public:
	Framework(HWND hWnd);
	~Framework();

private:
	void Update(float elapsedTime/*Elapsed seconds from last frame*/);
	void Render(float elapsedTime/*Elapsed seconds from last frame*/);
	bool RayIntersectsAABB(const XMVECTOR& rayOrigin, const XMVECTOR& rayDir, const AABB& box, float& distanceOut);
	void ComputeMouseRay(XMVECTOR& rayOrigin, XMVECTOR& rayDir);

	void CalculateFrameStats();

public:
	int Run();
	LRESULT CALLBACK HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	const HWND				hWnd;
	HighResolutionTimer		timer;
	Audio					audio;
	Graphics				graphics;
	Input					input;
};

