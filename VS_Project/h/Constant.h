#pragma once
#include <map>
#include <string>
#include <variant>
#include <tchar.h>

#define INT_ 0
#define FLOAT_ 0.0f
#define BOOL_ false

// �ϐ��^
enum DataType { _INT, _FLOAT, _BOOL, _STRING };

// �萔�Ǘ��N���X
class Constant
{
	// �萔���i�[���邽�߂̌^
	using ConstantVariant = std::variant<int, float, bool, std::string>;

public:

	/// <summary>
	/// �萔map�����̂܂ܕԂ�
	/// </summary>
	/// <returns>�萔map�z��</returns>
	std::map<std::string, ConstantVariant> GetConstants();

	/// <summary>
	/// int�^�̒萔��Ԃ�
	/// </summary>
	/// <param name="name">�萔��</param>
	/// <returns>�萔�̒l</returns>
	int GetConstantInt(std::string name);

	/// <summary>
	/// float�^�̒萔��Ԃ�
	/// </summary>
	/// <param name="name">�萔��</param>
	/// <returns>�萔�̒l</returns>
	float GetConstantFloat(std::string name);

	/// <summary>
	/// bool�^�̒萔��Ԃ�
	/// </summary>
	/// <param name="name">�萔��</param>
	/// <returns>�萔�̒l</returns>
	bool GetConstatBool(std::string name);

protected:

	/// <summary>
	/// CSV����萔��ǂݍ���
	/// </summary>
	/// <param name="filename">�t�@�C���p�X</param>
	void ReadCSV(const std::string& filename);

private:

	/// <summary>
	/// �����̕����񂩂�ϐ��^�𐄑�����
	/// </summary>
	/// <param name="type">_INT�Ȃǂ̌^���̕�����</param>
	/// <returns>DataType�̃f�[�^�^�̂����ꂩ</returns>
	DataType GetDataType(const std::string& type);

	// �萔���i�[����map�z��
	std::map<std::string, ConstantVariant> Constants;
};
