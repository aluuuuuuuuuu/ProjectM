#pragma once
#include <map>
#include <string>
#include <variant>

// �ϐ��^
enum MyDataType { _INT, _FLOAT, _BOOL, _STRING };

// �萔�Ǘ��N���X
class Constant
{
	// �萔���i�[���邽�߂̌^
	using ConstantVariant = std::variant<int, float, bool, std::string>;

public:

	// �萔map�𓾂�
	std::map<std::string, ConstantVariant> GetConstants();
	
	// �萔���擾����
	std::variant<int, float, bool, std::string> GetConstant(const std::string& name);

	// �萔���i�[����map�z��
	std::map<std::string, ConstantVariant> Constants;
protected:

	// CSV����萔��ǂݍ���
	void ReadCSV(const std::string& filename);

	
private:
	

	// �����̕����񂩂�ϐ��^�𐄑�����
	MyDataType GetDataType(const std::string& type);

};
