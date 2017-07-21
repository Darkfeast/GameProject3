﻿#include "stdafx.h"
#include "SceneXmlMgr.h"

CSceneXmlManager::CSceneXmlManager()
{

}

CSceneXmlManager::~CSceneXmlManager()
{
	
}

CSceneXmlManager* CSceneXmlManager::GetInstancePtr()
{
	static CSceneXmlManager _StaticValue;

	return &_StaticValue;
}

rapidxml::xml_document<char>* CSceneXmlManager::GetXmlDocument(std::string strXmlName)
{
	std::map<string, rapidxml::xml_document<char>*>::iterator itor = m_mapDocument.find(strXmlName);
	if (itor != m_mapDocument.end())
	{
		return itor->second;
	}


	FILE* pFile = fopen(strXmlName.c_str(), "rb");
	if (pFile == NULL)
	{
		return NULL;
	}

	char buff[204800] = {0};
	fseek (pFile , 0 , SEEK_END);
	INT32 nSize = ftell (pFile);
	rewind (pFile);
	fread(buff, nSize, 1, pFile);
	fclose(pFile);
	buff[nSize+1] = 0;

	rapidxml::xml_document<char>* pXMLDoc = new rapidxml::xml_document<char>();

	pXMLDoc->parse<0>(buff);

	m_mapDocument.insert(std::make_pair(strXmlName, pXMLDoc));

	return pXMLDoc;
}

BOOL CSceneXmlManager::Init()
{
	return TRUE;
}

BOOL CSceneXmlManager::Uninit()
{
	return TRUE;
}

