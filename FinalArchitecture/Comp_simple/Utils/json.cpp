#include "../stdafx.h"
#include "json.h"
#include "../include/string.h"

// ***************************************************************************
// Carga de un fichero un objeto JSON.
// pszConfigFile [IN]  -> Fichero a cargar
// pszJSONString [OUT] -> Cadena que el llamante tiene que liberar cuando ya no
//                        necesit el objeto JSON
// doc:	[IN/OUT]			 -> Documento JSON donde se realizará el parseo
// retirn true si Ok, false si error
// ***************************************************************************
bool loadJSON(const char *pszConfigFile, char *&pszJSONString, rapidjson::Document &doc)
{
	bool bRet = false;

	String strFile = String::Read(pszConfigFile);
	if (strFile.ToCString())
	{
		unsigned long ulSize = strFile.Length();
		pszJSONString = NEW_ARRAY(char, ulSize + 1);

		if (pszJSONString)
		{
			pszJSONString[ulSize] = '\0';
			memcpy(pszJSONString, strFile.ToCString(), ulSize);
			doc.ParseInsitu<rapidjson::kParseInsituFlag>(pszJSONString);
			bRet = !doc.HasParseError();
			if (!bRet)
			{
				delete []pszJSONString;
				pszJSONString = NULL;
			}
		}
	}
	return bRet;
}