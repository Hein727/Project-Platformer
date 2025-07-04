#pragma once

#include "Input/GamePad.h"
#include "Input/Mouse.h"

// �C���v�b�g
class Input
{
public:
	Input(HWND hWnd);
	~Input() {}

public:
	// �C���X�^���X�擾
	static Input& Instance() { return *instance; }

	// �X�V����
	void Update();

	// �ǉ��F�}�E�X�̎Q�Ǝ擾
	const Mouse& GetMouse() const { return mouse; }

	// �ǉ��F�}�E�X�̌��݈ʒu�擾
	POINT GetMousePosition(HWND hWnd) const;

	// �Q�[���p�b�h�擾
	GamePad& GetGamePad() { return gamePad; }

	// �}�E�X�擾
	Mouse& GetMouse() { return mouse; }

private:
	static Input*		instance;
	GamePad				gamePad;
	Mouse				mouse;
};
