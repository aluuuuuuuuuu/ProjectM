#pragma once
#include <map>
#include <string>
#include <variant>

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

	// �萔���擾����
	std::variant<int, float, bool, std::string> GetConstant(const std::string& name);

	// �萔���i�[����map�z��
	std::map<std::string, ConstantVariant> Constants;
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

};
