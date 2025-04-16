#pragma once
#include "Singleton.h"
#include "Constant.h"

namespace
{
	constexpr const char* WINDOW_NAME = "OtoshiKing";
};

class Application:
	public Singleton<Application>,
	public Constant
{
public:

	/// <summary>
	/// ����������
	/// </summary>
	/// <returns>�����������t���O</returns>
	bool Init();

	/// <summary>
	/// ���C������
	/// </summary>
	void Run();

private:

	/// <summary>
	/// �I������
	/// </summary>
	void Terminate();

};
