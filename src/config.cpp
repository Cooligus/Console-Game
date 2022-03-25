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
#include <locale>

//using json
using json = nlohmann::json;

//define function
nlohmann::json getConfigFromJSON(std::string path)
{
	//define config struct
	nlohmann::json toReturn;

	//new in-file stream
	std::ifstream file(path + CONFIG_CG_DEF, std::ifstream::in);

	//check is file good and if not close it
	if (!file.good())
	{
		//close stream
		file.close();
	}
	//else read json and put config into config (sense)
	else
	{
		//parse json file
		json fileContent = json::parse(file);


		json configContent = fileContent["config"];

        toReturn = setupConfig(configContent);
	}

	return toReturn;
}

//define config setup
nlohmann::json setupConfig(nlohmann::json variable)
{
	//define 
	nlohmann::json config;

	//set integers
    setupJSONVariable<VarType::UNSIGNED>(variable, config, SIZE_X);
	setupJSONVariable<VarType::UNSIGNED>(variable, config, SIZE_Y);
	setupJSONVariable<VarType::UNSIGNED>(variable, config, PLAYER_POSITION_X);
	setupJSONVariable<VarType::UNSIGNED>(variable, config, PLAYER_POSITION_Y);
	setupJSONVariable<VarType::UNSIGNED>(variable, config, ENEMIES_AMOUNT);

    //set booleans
	setupJSONVariable<VarType::BOOL>(variable, config, ADD_FRAMES);
	setupJSONVariable<VarType::BOOL>(variable, config, REPLACE_SPACE);

	//set characters
	setupJSONVariable<VarType::STRING>(variable, config, SPACE_CHAR);
	setupJSONVariable<VarType::STRING>(variable, config, FRAME_CHAR);
	setupJSONVariable<VarType::STRING>(variable, config, PLAYER_SPRITE);
	setupJSONVariable<VarType::STRING>(variable, config, POINT_SPRITE);
	setupJSONVariable<VarType::STRING>(variable, config, ENEMY_SPRITE);

	return config;
}

nlohmann::json checkConfig(nlohmann::json config)
{
	return nlohmann::json();
}

//define converter
cchar_t getCchar_t(json jsonVar)
{
	//define output
	cchar_t output = ' ';
	
	//push to jsonOutput content of json variable
	std::string jsonOutput = jsonVar.get<json::string_t>();

	// define converter
	std::wstring_convert<std::codecvt<char16_t, char, std::mbstate_t>, char16_t> convert;

	// convert json content from utf-8 tp utf-16
	std::u16string u16 = convert.from_bytes(jsonOutput.c_str());

	//push to cchar_t first utf-16 character from json variable
	output = u16[0];

	//return cchar_t
	return output;
}

//define unsigned int typed checker
template<>
bool checkJSON<VarType::UNSIGNED>(nlohmann::json variable, const char *varName)
{
	if (!variable[varName].empty() && variable[varName].type() == json::value_t::number_unsigned)
        return true;
	else
		return false;
}

//define bool typed checker
template<>
bool checkJSON<VarType::BOOL>(nlohmann::json variable, const char *varName)
{
	if (!variable[varName].empty() && variable[varName].type() == json::value_t::boolean)
		return true;
	else
		return false;
}

//define string typed checker
template<>
bool checkJSON<VarType::STRING>(nlohmann::json variable, const char *varName)
{
	if (!variable[varName].empty() && variable[varName].type() == json::value_t::string)
		return true;
	else
		return false;
}

//define unsigned int typed setup
template<>
void setupJSONVariable<VarType::UNSIGNED>(nlohmann::json variable, nlohmann::json &config, const char *varName)
{
	if (checkJSON<VarType::UNSIGNED>(variable, varName))
        config[varName] = variable[varName];
	else
        config[varName] = std::string(varName).append(DEFAULT_PREPOSITION);
}

//define boolean typed setup
template<>
void setupJSONVariable<VarType::BOOL>(nlohmann::json variable, nlohmann::json &config, const char *varName)
{
	if (checkJSON<VarType::BOOL>(variable, varName))
		config[varName] = variable[varName];
	else
        config[varName] = std::string(varName).append(DEFAULT_PREPOSITION);
}

//define string typed setup
template<>
void setupJSONVariable<VarType::STRING>(nlohmann::json variable, nlohmann::json &config, const char *varName)
{
	if (checkJSON<VarType::STRING>(variable, varName))
		config[varName] = variable[varName];
	else
		config[varName] = std::string(varName).append(DEFAULT_PREPOSITION);
}


