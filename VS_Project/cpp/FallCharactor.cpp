#include "FallCharactor.h"
#include "DxLib.h"
#include <ctime>
#include "SoundManager.h"

FallCharactor::FallCharactor() :
	_fallFlame(0)
{
	// ����������̏�����
	srand(static_cast<unsigned int>(time(nullptr)));

	// �����L�����̉摜�̃��[�h
	{
		_fallCharactorHandle[CHARACTER_1] = LoadGraph("data/image/Falling1.png");
		_fallCharactorHandle[CHARACTER_2] = LoadGraph("data/image/Falling2.png");
		_fallCharactorHandle[CHARACTER_3] = LoadGraph("data/image/Falling3.png");
		_fallCharactorHandle[CHARACTER_4] = LoadGraph("data/image/Falling4.png");
	}
}

FallCharactor::~FallCharactor()
{
	// �����L�����̉摜�̍폜
	for (int i = 0; i < 4; i++) {
		DeleteGraph(_fallCharactorHandle[i]);
	}
}

void FallCharactor::Update()
{
	// �t���[����i�߂�
	_fallFlame++;

	// �t���[����300�𒴂�����L�����N�^�[�̗������n�߂�
	if (_fallFlame >= 240) {
		// �t���[����100�Ŋ���؂�鐔�ɂȂ�����L�����N�^�[�𗎉�������
		if (_fallFlame % 60 == 0) {

			// �����_���ȍ��W�Ɗp�x�𐶐�
			float randomAngle = static_cast<float>(rand()) / RAND_MAX * 2 * DX_PI_F;
			bool rotateFlag = (rand() % 5 == 0);

			// �����L������ǉ�
			_fallCharactors.push_back({ _fallCharactorHandle[rand() % 4],Vec2{rand() % 1920,-100},randomAngle,rotateFlag });
			//SoundManager::GetInstance().RingSE(SE_SHOUT);
		}
	}

	// �����L�����̍X�V
	for (auto& character : _fallCharactors) {
		character._pos.y += 10;
		if (character._rotateFlag) {
			character._angle += 0.1;
		}
	}

	// ��ʊO�ɏo���L�����N�^�[���폜
	_fallCharactors.erase(std::remove_if(_fallCharactors.begin(), _fallCharactors.end(), [](const Character& characotr) {
		return characotr._pos.y > 1200;
		}), _fallCharactors.end());

}

void FallCharactor::Draw() const
{
	// �����L�����̕`��
	for (auto& characotr : _fallCharactors) {
		DrawRotaGraph(characotr._pos.intX(), characotr._pos.intY(), 0.3, characotr._angle, characotr._handle, true);
	}
}
