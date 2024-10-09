#pragma once
#include <map>
#include <string>
#include <variant>

// •Ï”Œ^
enum MyDataType { _INT, _FLOAT, _BOOL, _STRING };

// ’è”ŠÇ—ƒNƒ‰ƒX
class Constant
{
	// ’è”‚ğŠi”[‚·‚é‚½‚ß‚ÌŒ^
	using ConstantVariant = std::variant<int, float, bool, std::string>;

public:

	// ’è”map‚ğ“¾‚é
	std::map<std::string, ConstantVariant> GetConstants();
	
	// ’è”‚ğæ“¾‚·‚é
	std::variant<int, float, bool, std::string> GetConstant(const std::string& name);

	// ’è”‚ğŠi”[‚·‚émap”z—ñ
	std::map<std::string, ConstantVariant> Constants;
protected:

	// CSV‚©‚ç’è”‚ğ“Ç‚İ‚Ş
	void ReadCSV(const std::string& filename);

	
private:
	

	// ˆø”‚Ì•¶š—ñ‚©‚ç•Ï”Œ^‚ğ„‘ª‚·‚é
	MyDataType GetDataType(const std::string& type);

};
