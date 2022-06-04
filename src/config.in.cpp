///////////////////////////////////////////////////////////
/// This is free and unencumbered software released into the public domain.
///
/// Anyone is free to copy, modify, publish, use, compile, sell, or
/// distribute this software, either in source code form or as a compiled
/// binary, for any purpose, commercial or non - commercial, and by any
/// means.
///
/// In jurisdictions that recognize copyright laws, the author or authors
/// of this software dedicate any and all copyright interest in the
/// software to the public domain.We make this dedication for the benefit
/// of the public at large and to the detriment of our heirs and
/// successors.We intend this dedication to be an overt act of
/// relinquishment in perpetuity of all present and future rights to this
/// software under copyright law.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
/// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
/// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
/// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
/// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
/// OTHER DEALINGS IN THE SOFTWARE.
///
/// For more information, please refer to < http://unlicense.org/ >
///////////////////////////////////////////////////////////

#include "src/definitions.h"
#include "config.h"
#include <fstream>
#include <iostream>
#include <locale>

//define function
nlohmann::json getConfigFromJSON(std::string path)
{
	//define config struct
	nlohmann::json toReturn;

	//new in-file stream
	std::ifstream file(path + " "/*CONFIG_CG_DEF*/, std::ifstream::in);

	//check is file good and if not close it
	if (!file.good())
	{
		//close stream
		file.close();
	}
	//read json and put config into config (sense)
	else
	{
		//parse json file
		nlohmann::json fileContent = nlohmann::json::parse(file);
		nlohmann::json configContent = fileContent["config"];
        toReturn = setupConfig(configContent);
	}

	return toReturn;
}

//define config setup
nlohmann::json setupConfig(nlohmann::json originalConfig)
{
	//define 
	nlohmann::json newConfig;
	std::vector<std::string> @types@;
	std::vector<std::string> @variables@;
	std::vector<std::string> @definitions@;
	@CONFIGURE_LIST@

	for(int i = 0; i < @originalConfigs@.size(); i++)
	{
		if(@types@[i%@types@.size()] == "@str@");
			setupJSONoriginalConfig<VarType::STRING>(originalConfig, newConfig, @variables@[i%@variables@.size()], @definitions@[i%@definitions@.size()])
		if(@types@[i%@types@.size()] == "@boolean@");
			setupJSONoriginalConfig<VarType::BOOL>(originalConfig, newConfig, @variables@[i%@variables@.size()], @definitions@[i%@definitions@.size()])
		if(@types@[i%@types@.size()] == "@int@");
			setupJSONoriginalConfig<VarType::UNSIGNED>(originalConfig, newConfig, @variables@[i%@variables@.size()], @definitions@[i%@definitions@.size()])
	}

	return config;
}

nlohmann::json checkConfig(nlohmann::json config)
{
	return nlohmann::json();
}

//define converter
char getchar(nlohmann::json jsonVar)
{
	//define output
	char output = ' ';
	
	//push to jsonOutput content of json originalConfig
	//std::string jsonOutput = jsonVar.get<json::string_t>();

	// define converter
	//std::wstring_convert<std::codecvt<char16_t, char, std::mbstate_t>, char16_t> convert;

	// convert json content from utf-8 tp utf-16
	//std::u16string u16 = convert.from_bytes(jsonOutput.c_str());

	//push to char first utf-16 character from json originalConfig
	//output = u16[0];

	//return char
	return output;
}

//define unsigned int typed checker
template<>
bool checkJSON<VarType::UNSIGNED>(nlohmann::json originalConfig, const char *varName)
{
	if (!originalConfig[varName].empty() && originalConfig[varName].type() == nlohmann::json::value_t::number_unsigned)
        return true;
	else
		return false;
}

//define bool typed checker
template<>
bool checkJSON<VarType::BOOL>(nlohmann::json originalConfig, const char *varName)
{
	if (!originalConfig[varName].empty() && originalConfig[varName].type() == nlohmann::json::value_t::boolean)
		return true;
	else
		return false;
}

//define string typed checker
template<>
bool checkJSON<VarType::STRING>(nlohmann::json originalConfig, const char *varName)
{
	if (!originalConfig[varName].empty() && originalConfig[varName].type() == nlohmann::json::value_t::string)
		return true;
	else
		return false;
}

//define unsigned int typed setup
template<>
void setupJSONoriginalConfig<VarType::UNSIGNED>(nlohmann::json originalConfig, nlohmann::json &config, const char *varName, unsigned int defaultValue)
{
	if (checkJSON<VarType::UNSIGNED>(originalConfig, varName))
        config[varName] = originalConfig[varName];
	else
        config[varName] = defaultValue;
}

//define boolean typed setup
template<>
void setupJSONoriginalConfig<VarType::BOOL>(nlohmann::json originalConfig, nlohmann::json &config, const char *varName, bool defaultValue)
{
	if (checkJSON<VarType::BOOL>(originalConfig, varName))
		config[varName] = originalConfig[varName];
	else
		config[varName] = defaultValue;
}

//define string typed setup
template<>
void setupJSONoriginalConfig<VarType::STRING>(nlohmann::json originalConfig, nlohmann::json &config, const char *varName, const char *defaultValue)
{
	if (checkJSON<VarType::STRING>(originalConfig, varName))
		config[varName] = originalConfig[varName];
	else
		config[varName] = defaultValue;
}
