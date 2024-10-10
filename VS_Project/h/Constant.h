#pragma once
#include <map>
#include <string>
#include <variant>

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

	// 定数を取得する
	std::variant<int, float, bool, std::string> GetConstant(const std::string& name);

	// 定数を格納するmap配列
	std::map<std::string, ConstantVariant> Constants;
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

};
