#pragma once
#include "Singleton.h"
#include <map>
#include "Vec3.h"

constexpr int NORMAL_BULLET_EFFECT = 0;

constexpr int MAX_EFFECT_NUM = 1;

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

private:

	/// <summary>
	/// �w�肳�ꂽ�G�t�F�N�g�����[�h����
	/// </summary>
	/// <param name="effect">�G�t�F�N�g�̃L�[</param>
	void LoadEffect(int effect);

	// �G�t�F�N�g�}�b�v
	std::map<int, int> _effectMap;
};

