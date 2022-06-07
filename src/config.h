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

#pragma once

#include "libs.h"
#include <nlohmann/json.hpp>

/// <summary>
/// Set of variables for setupJSONVariable function
/// </summary>
enum class VarType
{
	//unsigned int
	UNSIGNED = 0,

	//boolean
	BOOL = 1,

	//string
	STRING = 2
};


/// <summary>
/// Find and read json file and then configure config struct. If there is not json, function will return default config file.
/// </summary>
/// <param name="path">- path to file with config (by default it is looking for in the same place as program).</param>
nlohmann::json getConfigFromJSON(std::string path = "");

/// <summary>
/// Get all variables from JSON object and put it into new one.
/// </summary>
/// <param name="variable">- object in config file where are placed values.</param>
/// <returns></returns>
nlohmann::json setupConfig(nlohmann::json variable);

/// <summary>
/// Check does config have required variables properly set.
/// </summary>
/// <param name="config">- config you can get from getConfigFromJSON(). WARNING! That object need to be nearest parent of config variables else function will return config with default values.</param>
/// <returns></returns>
nlohmann::json checkConfig(nlohmann::json config);

/// <summary>
/// Check is string normal character or not, push it into char and return.
/// </summary>
/// <param name="jsonVar">- json variable.</param>
char getchar(nlohmann::json jsonVar);

/// <summary>
/// Check does JSON variable is properly set.
/// </summary>
/// <param name="variable">- JSON variable with stuff that function will put into config.</param>
/// <param name="varName">- name of variable.</param>
template<VarType>
bool checkJSON(nlohmann::json variable, const char *varName);

/// <summary>
/// Check does JSON variable is properly set.
/// </summary>
/// <param name="variable">- JSON variable with stuff that function will put into config.</param>
/// <param name="varName">- name of variable.</param>
template<>
bool checkJSON<VarType::UNSIGNED>(nlohmann::json variable, const char *varName);

/// <summary>
/// Check does JSON variable is properly set.
/// </summary>
/// <param name="variable">- JSON variable with stuff that function will put into config.</param>
/// <param name="varName">- name of variable.</param>
template<>
bool checkJSON<VarType::BOOL>(nlohmann::json variable, const char *varName);

/// <summary>
/// Check does JSON variable is properly set.
/// </summary>
/// <param name="variable">- JSON variable with stuff that function will put into config.</param>
/// <param name="varName">- name of variable.</param>
template<>
bool checkJSON<VarType::STRING>(nlohmann::json variable, const char *varName);


/// <summary>
/// Check does JSON variable is properly set.
/// </summary>
/// <param name="variable">- JSON variable with stuff that function will put into config.</param>
/// <param name="varName">- name of variable.</param>
template<VarType>
void setupJSONVariable(nlohmann::json originalConfig, nlohmann::json &config, const char *varName, const char* defaultValue);

/// <summary>
/// Setup JSON config from JSON variable.
/// </summary>
/// <param name="variable">- JSON variable with stuff that function will put into config.</param>
/// <param name="config">- JSON variable with future config.</param>
/// <param name="varName">- name of variable.</param>
template<>
void setupJSONVariable<VarType::UNSIGNED>(nlohmann::json originalConfig, nlohmann::json &config, const char *varName, const char* defaultValue);

/// <summary>
/// Setup JSON config from JSON variable.
/// </summary>
/// <param name="variable">- JSON variable with stuff that function will put into config.</param>
/// <param name="config">- JSON variable with future config.</param>
/// <param name="varName">- name of variable.</param>
template<>
void setupJSONVariable<VarType::BOOL>(nlohmann::json originalConfig, nlohmann::json &config, const char *varName, const char* defaultValue);

/// <summary>
/// Setup JSON config from JSON variable.
/// </summary>
/// <param name="variable">- JSON variable with stuff that function will put into config.</param>
/// <param name="config">- JSON variable with future config.</param>
/// <param name="varName">- name of variable.</param>
template<>
void setupJSONVariable<VarType::STRING>(nlohmann::json originalConfig, nlohmann::json &config, const char *varName, const char* defaultValue);