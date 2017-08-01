#pragma once
#include "cocos2d.h"
#include "Game/FV/FvSingleton.h"
#include "Game/Widget/WidgetDefine.h"
#include "Platform/PFKernel/CGPAddRankMission.h"

class SCAddRankScence
	:public cocos2d::Node
	,public CGAddRankMissionSink
	,public FvSingleton<SCAddRankScence> 
{
public:
	SCAddRankScence();
	~SCAddRankScence();
public:
	virtual bool init();
public:
	void HideAll();
	void upPlayerInfo();
	void setRankItemInfo(cocos2d::Node* pNode,std::string kName,int iFaceID,int iUserPoint,int iRank);
public:
	virtual void onGPAwardInfoResult(CMD_GP_BackAddBankAwardInfo* pNetInfo);
	virtual void onGPBackAddBankResult(CMD_GP_BackAddBank* pNetInfo);
public:
	void Button_AddRanScence(cocos2d::Ref*,WidgetUserInfo*);
	void Button_GetRank(cocos2d::Ref*,WidgetUserInfo*);
private:
	byte m_cbTakeTimes;
	SCORE m_lScoreCondition;
	CGPAddRankMission m_kAddRankMission;
};