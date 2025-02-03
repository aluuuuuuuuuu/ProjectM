#pragma once
#include "Singleton.h"
#include <map>
#include "Vec3.h"

constexpr int NORMAL_BULLET_EFFECT = 0;
constexpr int BOMB_BULLET_EFFECT = 1;
constexpr int GRAPPLE_BULLET_EFFECT = 2;
constexpr int BLOCK_DESTROY_EFFECT = 3;
constexpr int JUMP_EFFECT = 4;
constexpr int WIN_EFFECT = 5;
constexpr int SHOT_DOWN_EFFECT = 6;

constexpr int MAX_EFFECT_NUM = 7;

class EffectManager:
	public Singleton<EffectManager>
{
public:

	/// <summary>
	/// ����������
	/// </summary>
	void Init();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() const;

	/// <summary>
	/// �I������
	/// </summary>
	void Terminate();

	/// <summary>
	/// �G�t�F�N�g�̃n���h�����擾����
	/// </summary>
	/// <param name="effect">�G�t�F�N�g�̃L�[</param>
	/// <returns>�n���h���擾</returns>
	int& GetEffectHandle(int effect);

	/// <summary>
	/// ���ׂẴG�t�F�N�g�n���h�����폜����
	/// </summary>
	void DeleteEffect();

private:

	/// <summary>
	/// �w�肳�ꂽ�G�t�F�N�g�����[�h����
	/// </summary>
	/// <param name="effect">�G�t�F�N�g�̃L�[</param>
	void LoadEffect(int effect);

	// �G�t�F�N�g�}�b�v
	std::map<int, int> _effectMap;
};

