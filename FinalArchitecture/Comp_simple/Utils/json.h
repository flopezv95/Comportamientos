#ifndef ___JSON___
#define ___JSOM___

#include "rapidjson/document.h"

bool loadJSON(const char *pszConfigFile, char *&pszJSONString, rapidjson::Document &doc);

#endif