#pragma once
#include <map>
#include <string>
#include <variant>

#define INT_ 0
#define FLOAT_ 0.0f
#define BOOL_ false

// 変数型
enum DataType { _INT, _FLOAT, _BOOL, _STRING };

// 定数管理クラス
class Constant
{
	// 定数を格納するための型
	using ConstantVariant = std::variant<int, float, bool, std::string>;

public:

	/// <summary>
	/// 定数mapをそのまま返す
	/// </summary>
	/// <returns>定数map配列</returns>
	std::map<std::string, ConstantVariant> GetConstants();

	/// <summary>
	/// int型の定数を返す
	/// </summary>
	/// <param name="name">定数名</param>
	/// <returns>定数の値</returns>
	int GetConstantInt(std::string name);

	/// <summary>
	/// float型の定数を返す
	/// </summary>
	/// <param name="name">定数名</param>
	/// <returns>定数の値</returns>
	float GetConstantFloat(std::string name);

	/// <summary>
	/// bool型の定数を返す
	/// </summary>
	/// <param name="name">定数名</param>
	/// <returns>定数の値</returns>
	bool GetConstatBool(std::string name);

protected:

	/// <summary>
	/// CSVから定数を読み込む
	/// </summary>
	/// <param name="filename">ファイルパス</param>
	void ReadCSV(const std::string& filename);

private:

	/// <summary>
	/// 引数の文字列から変数型を推測する
	/// </summary>
	/// <param name="type">_INTなどの型名の文字列</param>
	/// <returns>DataTypeのデータ型のいずれか</returns>
	DataType GetDataType(const std::string& type);

	// 定数を格納するmap配列
	std::map<std::string, ConstantVariant> Constants;
};
