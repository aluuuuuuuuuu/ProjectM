#pragma once
#include "Singleton.h"
#include "Constant.h"

// �A�v���P�[�V�����S�̂̊Ǘ����s���V���O���g���N���X
class Application :
	public Singleton<Application>,
	public Constant
{
	friend class Singleton<Application>;

public:
	// ��������
	bool Init();

	// ���C������
	void Run();

private:
	// �v���C�x�[�g�R���X�g���N�^
	Application() {};

	// �I�������̓p�u���b�N�ł͌ĂׂȂ�
	void Terminate();
};
