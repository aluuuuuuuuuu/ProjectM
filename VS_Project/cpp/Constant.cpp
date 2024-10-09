#include "Constant.h"
#include <fstream>
#include <sstream>
#include <cassert>

std::map<std::string, Constant::ConstantVariant> Constant::GetConstants()
{
	return Constants;
}

std::variant<int, float, bool, std::string> Constant::GetConstant(const std::string& name)
{
	// �萔�̌^�ɕϊ����ĕԂ�

	// int�̏ꍇ
	if (std::holds_alternative<int>(Constants[name])) {
		return std::get<int>(Constants[name]);
	}

	// float�̏ꍇ
	if (std::holds_alternative<float>(Constants[name])) {
		return std::get<float>(Constants[name]);
	}

	// bool 
	if (std::holds_alternative<bool>(Constants[name])) {
		return std::get<bool>(Constants[name]);
	}

	// string
	if (std::holds_alternative<std::string>(Constants[name])) {
		return std::get<std::string>(Constants[name]);
	}
}

void Constant::ReadCSV(const std::string& filename)
{
	// �t�@�C����ǂݍ���
	std::ifstream file(filename);

	// �ǂݍ��߂Ȃ�������G���[���o�͂���
	assert(file.is_open());

	// ���e���ꎞ�I�ɕۑ����Ă����ϐ�
	std::string line, no, name, type, value, content;

	// ��s�ڂ̃w�b�_�[���X�L�b�v
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::stringstream ss(line); // �s�𓾂�

		/*�萔���ƌ^�ƒl�̂�map�ɕۑ�����*/

		std::getline(ss, no, ',');  // �i���o�[
		std::getline(ss, name, ',');    // �萔��
		std::getline(ss, type, ',');    // �萔�^
		std::getline(ss, value, ',');   // �萔�̒l
		std::getline(ss, content, ','); // ����

		// ��O����
		try {
			switch (GetDataType(type)) {
				case _INT: {
					int intValue = std::stoi(value);
					Constants[name] = intValue;
					break;
				}
				case _FLOAT: {
					float floatValue = std::stof(value);
					Constants[name] = floatValue;
					break;
				}
				case _BOOL: {
					std::stringstream boolStream(value);
					bool boolValue;
					boolStream >> std::boolalpha >> boolValue;
					Constants[name] = boolValue;
					break;
				}
				case _STRING: {
					Constants[name] = value;
					break;
				}
			}
			//// �ϐ��̌^�𐄑�����
			//auto dataType = GetDataType(type);

			//// �^�ɂ���ď����𕪊򂳂���

			//if (dataType == _INT) {  // int

			//    // �������int�^�Ƃ��ēǂ݂Ƃ�
			//    int intValue = std::stoi(value);

			//    // map�ɕۑ�����
			//    Constants[name] = intValue;
			//}
			//else if (dataType == _FLOAT) {   // float

			//    // �������float�^�Ƃ��ēǂݎ��
			//    float floatValue = std::stof(value);

			//    // map�ɕۑ�����
			//    Constants[name] = floatValue;
			//}
			//else if (dataType == _BOOL) {    // bool

			//    // �������������������
			//    std::stringstream boolStream(value);
			//    bool boolValue;

			//    // boolalpha��true�Ȃǂ̕�����bool�ɕϊ�����
			//    boolStream >> std::boolalpha >> boolValue;

			//    // map�ɕۑ�����
			//    Constants[name] = boolValue;
			//} 
			//else if (dataType == _STRING) {  // string

			//    // �X�g�����O�͂��̂܂ܕۑ�����
			//    Constants[name] = value;
			//}
		}

		// ��O
		catch (const std::exception& e) {
			// �G���[���o�͂���
			//assert(false);
		}
	}
	file.close();
}

MyDataType Constant::GetDataType(const std::string& type)
{
	// ������ɉ����ĕϐ��^��Ԃ�
	if (type == "_INT") return _INT;
	if (type == "_FLOAT") return _FLOAT;
	if (type == "_BOOL") return _BOOL;
	if (type == "_STRING") return _STRING;
}
