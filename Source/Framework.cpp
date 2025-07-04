#include <memory>
#include <sstream>

#include "Graphics/Graphics.h"
#include "Input/Input.h"
#include "SceneGame.h"
#include "Framework.h"

static SceneGame sceneGame;

// ���������Ԋu�ݒ�
static const int syncInterval = 1;

// �R���X�g���N�^
Framework::Framework(HWND hWnd)
	: hWnd(hWnd)
	, input(hWnd)
	, graphics(hWnd)
{
	sceneGame.Initialize();
}

// �f�X�g���N�^
Framework::~Framework()
{
	sceneGame.Finalize();
}

// �X�V����
void Framework::Update(float elapsedTime/*Elapsed seconds from last frame*/)
{
	// ���͍X�V����
	input.Update();

	// �V�[���X�V����
	sceneGame.Update(elapsedTime);
}

// �`�揈��
void Framework::Render(float elapsedTime/*Elapsed seconds from last frame*/)
{
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();

	// IMGUI�t���[���J�n����
	graphics.GetImGuiRenderer()->NewFrame();

	// �V�[���`�揈��
	sceneGame.Render();

	// IMGUI�f���E�C���h�E�`��iIMGUI�@�\�e�X�g�p�j
	//ImGui::ShowDemoWindow();

	// IMGUI�`��
	graphics.GetImGuiRenderer()->Render(dc);

	// �o�b�N�o�b�t�@�ɕ`�悵�������ʂɕ\������B
	graphics.GetSwapChain()->Present(syncInterval, 0);
}

// �t���[�����[�g�v�Z
void Framework::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.
	static int frames = 0;
	static float time_tlapsed = 0.0f;

	frames++;

	// Compute averages over one second period.
	if ((timer.TimeStamp() - time_tlapsed) >= 1.0f)
	{
		float fps = static_cast<float>(frames); // fps = frameCnt / 1
		float mspf = 1000.0f / fps;
		std::ostringstream outs;
		outs.precision(6);
		outs << "FPS : " << fps << " / " << "Frame Time : " << mspf << " (ms)";
		SetWindowTextA(hWnd, outs.str().c_str());

		// Reset for next average.
		frames = 0;
		time_tlapsed += 1.0f;
	}
}

// �A�v���P�[�V�������[�v
int Framework::Run()
{
	MSG msg = {};

	HDC hDC = GetDC(hWnd);

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			timer.Tick();
			CalculateFrameStats();

			float elapsedTime = syncInterval == 0
				? timer.TimeInterval()
				: syncInterval / static_cast<float>(GetDeviceCaps(hDC, VREFRESH))
				;
			Update(elapsedTime);
			Render(elapsedTime);
		}
	}
	
	ReleaseDC(hWnd, hDC);

	return static_cast<int>(msg.wParam);
}

// ���b�Z�[�W�n���h��
LRESULT CALLBACK Framework::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (Graphics::Instance().GetImGuiRenderer()->HandleMessage(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostMessage(hWnd, WM_CLOSE, 0, 0);
		break;
	case WM_ENTERSIZEMOVE:
		// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
		timer.Stop();
		break;
	case WM_EXITSIZEMOVE:
		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
		// Here we reset everything based on the new window dimensions.
		timer.Start();
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

// --- ���C�����i�X�N���[�����W�����[���h��ԁj ---
void Framework::ComputeMouseRay(XMVECTOR& rayOrigin, XMVECTOR& rayDir)
{
	POINT p = input.GetMousePosition(hWnd);
	RECT rect;
	GetClientRect(hWnd, &rect);

	float mouseX = static_cast<float>(p.x) / (rect.right - rect.left) * 2.0f - 1.0f;
	float mouseY = static_cast<float>(p.y) / (rect.bottom - rect.top) * -2.0f + 1.0f;

	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 16.0f / 9.0f, 0.1f, 100.0f);
	XMMATRIX view = XMMatrixLookAtLH({ 0,0,-10 }, { 0,0,0 }, { 0,1,0 });

	XMMATRIX viewProjInv = XMMatrixInverse(nullptr, view * proj);

	XMVECTOR nearPoint = XMVectorSet(mouseX, mouseY, 0.0f, 1.0f);
	XMVECTOR farPoint = XMVectorSet(mouseX, mouseY, 1.0f, 1.0f);

	nearPoint = XMVector3TransformCoord(nearPoint, viewProjInv);
	farPoint = XMVector3TransformCoord(farPoint, viewProjInv);

	rayOrigin = nearPoint;
	rayDir = XMVector3Normalize(farPoint - nearPoint);
}

// --- ���C��AABB�̌�������i�ȈՔŁj ---
bool Framework::RayIntersectsAABB(const XMVECTOR& rayOrigin, const XMVECTOR& rayDir, const AABB& box, float& distanceOut)
{
	XMFLOAT3 origin, dir;
	XMStoreFloat3(&origin, rayOrigin);
	XMStoreFloat3(&dir, rayDir);

	XMFLOAT3 bmin = box.min;
	XMFLOAT3 bmax = box.max;

	float tmin = 0.0f;
	float tmax = 99999999.0f; // �������\���ɑ傫������ max() �̑�p

	for (int i = 0; i < 3; ++i)
	{
		float o = (i == 0) ? origin.x : (i == 1) ? origin.y : origin.z;
		float d = (i == 0) ? dir.x : (i == 1) ? dir.y : dir.z;
		float b0 = (i == 0) ? bmin.x : (i == 1) ? bmin.y : bmin.z;
		float b1 = (i == 0) ? bmax.x : (i == 1) ? bmax.y : bmax.z;

		if (fabs(d) < 1e-8f)
		{
			if (o < b0 || o > b1)
				return false;
		}
		else
		{
			float ood = 1.0f / d;
			float t1 = (b0 - o) * ood;
			float t2 = (b1 - o) * ood;

			// swap t1, t2 if needed�i�������ق��� t1 �Ɂj
			if (t1 > t2)
			{
				float temp = t1;
				t1 = t2;
				t2 = temp;
			}

			if (t1 > tmin) tmin = t1;
			if (t2 < tmax) tmax = t2;

			if (tmin > tmax)
				return false;
		}
	}

	distanceOut = tmin;
	return true;
}