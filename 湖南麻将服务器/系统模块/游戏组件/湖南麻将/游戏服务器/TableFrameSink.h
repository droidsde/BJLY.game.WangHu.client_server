#ifndef TABLE_FRAME_SINK_HEAD_FILE
#define TABLE_FRAME_SINK_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "GameLogic.h"

//////////////////////////////////////////////////////////////////////////
//枚举定义

//效验类型
enum enEstimatKind
{
	EstimatKind_OutCard,			//出牌效验
	EstimatKind_GangCard,			//杠牌效验
};

enum enGangState
{
	STATE_NULL,
	STATE_GANG,
	STATE_BU

};
//杠牌得分
struct tagGangScore
{
	BYTE		cbGangCount;							//杠个数
	LONGLONG	lScore[MAX_WEAVE][GAME_PLAYER];			//每个杠得分
};

//////////////////////////////////////////////////////////////////////////

struct  HNMJGameRecordPlayer
{
	DWORD dwUserID;
	std::string kHead;
	std::string kNickName;
	std::vector<BYTE> cbCardData;
	void StreamValue(datastream& kData,bool bSend)
	{
		Stream_VALUE(dwUserID);
		Stream_VALUE(kHead);
		Stream_VALUE(kNickName);
		Stream_VECTOR(cbCardData);
	}
};

struct  HNMJGameRecordOperateResult
{
	enum Type
	{
		TYPE_NULL,
		TYPE_OperateResult,
		TYPE_SendCard,
		TYPE_OutCard,
		TYPE_ChiHu,
	};
	HNMJGameRecordOperateResult()
	{
		cbActionType = 0;
		wOperateUser = 0;
		wProvideUser = 0;
		cbOperateCode = 0;
		cbOperateCard = 0;
	}
	BYTE							cbActionType;
	WORD							wOperateUser;						//操作用户
	WORD							wProvideUser;						//供应用户
	DWORD							cbOperateCode;						//操作代码
	BYTE							cbOperateCard;						//操作扑克
	void StreamValue(datastream& kData,bool bSend)
	{
		Stream_VALUE(cbActionType);
		Stream_VALUE(wOperateUser);
		Stream_VALUE(wProvideUser);
		Stream_VALUE(cbOperateCode);
		Stream_VALUE(cbOperateCard);
	}
};
struct  HNMJGameRecord
{
	DWORD dwKindID;
	DWORD dwVersion;
	std::vector<HNMJGameRecordPlayer> kPlayers;
	std::vector<HNMJGameRecordOperateResult> kAction;
	void StreamValue(datastream& kData,bool bSend)
	{
		StructVecotrMember(HNMJGameRecordPlayer,kPlayers);
		StructVecotrMember(HNMJGameRecordOperateResult,kAction);
		Stream_VALUE(dwKindID);
		Stream_VALUE(dwVersion);
	}

};

struct MasterHandCardInfo
{
	int nChairId;
	std::vector<BYTE>    kMasterHandCard;

	void StreamValue(datastream& kData,bool bSend)
	{
		Stream_VALUE(nChairId);
		Stream_VECTOR(kMasterHandCard);
	}
};

struct MasterHandCard
{
	std::vector<MasterHandCardInfo>    kMasterHandCardList;
	void StreamValue(datastream& kData,bool bSend)
	{
		StructVecotrMember(MasterHandCardInfo,kMasterHandCardList);
	}
};

//////////////////////////////////////////////////////////////////////////
//游戏桌子类
class CTableFrameSink : public ITableFrameSink, public ITableUserAction
{
public:
	//是否是一炮多响(提供者)
	bool isDuoPao;
	//是否流局
	bool isGameOver;
	//是否荒庄
	bool m_bIsNullWin;

	//记住弃胡玩家
	//std::vector<WORD> qiHuPlayerVector;

	//弃牌玩家
	bool isQiPaiPlayer0;
	bool isQiPaiPlayer1;
	bool isQiPaiPlayer2;
	bool isQiPaiPlayer3;

	//局数
	int m_iGameCount;

	//游戏玩家中鸟个数
	int m_Player;
	int t_Player;
	int l_Player;
	int r_Player;
public:
	HNMJGameRecord					m_kGameRecord;
	BYTE							m_cbGameTypeIdex;	//游戏类型
	DWORD							m_dwGameRuleIdex;	//游戏规则
public:
	BYTE                            m_cbMasterCheckCard[GAME_PLAYER];
	BYTE                            m_cbMasterZhaNiao[GAME_PLAYER];

	//游戏变量
protected:
	WORD							m_wBankerUser;							//庄家用户
	LONGLONG						m_lGameScore[GAME_PLAYER];				//游戏得分
	BYTE							m_cbCardIndex[GAME_PLAYER][MAX_INDEX];	//用户扑克
	BYTE							m_cbChiHuCardData[GAME_PLAYER][2];		//吃胡牌
	tagGangCardResult				m_cbGangInfo[GAME_PLAYER];
	tagGangScore					m_GangScore[GAME_PLAYER];				//
	bool							m_bTrustee[GAME_PLAYER];				//是否托管
	WORD							m_wLostFanShu[GAME_PLAYER][GAME_PLAYER];//


	BYTE							m_cbCardDataNiao[MAX_NIAO_CARD];	// 鸟牌
	BYTE							m_cbNiaoCount;						//鸟牌个数
	BYTE							m_cbNiaoPick;						//中鸟个数
	LONGLONG						m_lNiaoScore;						//鸟分数	
	BYTE							m_cbChairIDNiaoCout[GAME_PLAYER];	//闲来规则扎鸟个数
	BYTE							m_cbVaildChairIDNiaoCout[GAME_PLAYER];	//闲来规则扎鸟个数-结果
	BYTE							m_wNiaoDuoPaoStartChairID;			//一炮多响抓鸟


	long							m_dFirstChickID;						//冲锋鸡用户ID
	long							m_dErrandChickID;						//责任鸡用户ID
	BYTE							m_cbChickID[4];							//4个鸡用户ID
	BYTE							m_cbChichCount;							//幺鸡出牌计数


	BYTE							m_cbCanHu[GAME_PLAYER];//是否能胡牌  过庄才能胡
	bool							m_bHasCSGang[GAME_PLAYER];//是否已经长沙杠
	WORD							m_FanShu;// 胡牌的番数
	//出牌信息
protected:
	WORD							m_wOutCardUser;							//出牌用户
	BYTE							m_cbOutCardCount;						//出牌数目
	BYTE							m_cbDiscardCount[GAME_PLAYER];			//丢弃数目
	BYTE							m_cbDiscardCard[GAME_PLAYER][60];		//丢弃记录

	//发牌信息
protected:
	WORD							m_wHaiDiCout;							//海底牌轮询问次数
	WORD							m_wHaiDiUser;							//海底牌用户
	BYTE							m_cbHaiDiSendCardData;					//发牌为海底牌
	BYTE							m_cbSendCardCount;						//发牌数目
	BYTE							m_cbLeftCardCount;						//剩余数目
	BYTE							m_cbRepertoryCard[MAX_REPERTORY_HZ];		//库存扑克


	//运行变量
protected:
	WORD							m_wResumeUser;							//还原用户
	WORD							m_wCurrentUser;							//当前用户
	WORD							m_wProvideUser;							//供应用户

	//状态变量
protected:
	int								m_bGangStatus;							//抢杆状态
	bool							m_bGangOutStatus;						//

	bool							m_bGangStatus_CS;						//长沙杠的状态
	WORD							m_wCSGangUser;							//当前用户

	//用户状态
public:
	struct UserActionStates 
	{
		bool							m_bResponse[GAME_PLAYER];				//响应标志
		DWORD							m_cbUserAction[GAME_PLAYER];			//用户动作
		BYTE							m_cbOperateCard[GAME_PLAYER];			//操作扑克
		DWORD							m_cbPerformAction[GAME_PLAYER];			//执行动作
		CChiHuRight						m_ChiHuRight[GAME_PLAYER];				//
		BYTE							m_cbProvideCard;						//供应扑克
		BYTE							m_cbOutCardData;						//出牌扑克
		BYTE							m_cbSendCardData;						//发牌扑克
	};
	UserActionStates					m_kUserActionStates1;
	UserActionStates					m_kUserActionStates2;

	LONGLONG						m_lStartHuScore[GAME_PLAYER];	//起手胡分数	
	CChiHuRight						m_StartHuRight[GAME_PLAYER];	//起手胡权位

	//组合扑克
protected:
	BYTE							m_cbWeaveItemCount[GAME_PLAYER];		//组合数目
	tagWeaveItem					m_WeaveItemArray[GAME_PLAYER][MAX_WEAVE];//组合扑克

	//结束信息
protected:
	WORD							m_wProvider[GAME_PLAYER];				//

	//组件变量
protected:
	CGameLogic						m_GameLogic;							//游戏逻辑
	ITableFrame						* m_pITableFrame;						//框架接口
	const tagGameServiceOption		* m_pGameServiceOption;					//配置参数

	//函数定义
public:
	//构造函数
	CTableFrameSink();
	//析构函数
	virtual ~CTableFrameSink();

public:
	//基础接口
public:
	//释放对象
	virtual VOID Release() { }
	//接口查询
	virtual void * QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//管理接口
public:
	//初始化
	virtual bool Initialization(IUnknownEx * pIUnknownEx);
	//复位桌子
	virtual VOID RepositionSink();

	//查询接口
public:
	//查询限额
	virtual SCORE QueryConsumeQuota(IServerUserItem * pIServerUserItem){  return 0; };
	//最少积分
	virtual SCORE QueryLessEnterScore(WORD wChairID, IServerUserItem * pIServerUserItem){ return 0; };
	//查询是否扣服务费
	virtual bool QueryBuckleServiceCharge(WORD wChairID){return true;}

	//比赛接口
public:
	//设置基数
	virtual void SetGameBaseScore(LONG lBaseScore){};

	//游戏事件
public:
	//游戏开始
	virtual bool OnEventGameStart();
	//游戏结束
	virtual bool OnEventGameConclude(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason);
	//发送场景
	virtual bool OnEventSendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret);

	void Shuffle(BYTE* RepertoryCard,int nCardCount); //洗牌
	void GameStart_ZZ();
	void GameStart_CS();

	//事件接口
public:
	bool isUseTuoGuan();
	void setActionTimeStart(bool bStart,bool Trustee);
	//定时器事件
	virtual bool OnTimerMessage(DWORD wTimerID, WPARAM wBindParam);
	//数据事件
	virtual bool OnDataBaseMessage(WORD wRequestID, VOID * pData, WORD wDataSize) { return false; }
	//积分事件
	virtual bool OnUserScroeNotify(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason) { return false; }

	//网络接口
public:
	//游戏消息处理
	virtual bool OnGameMessage(WORD wSubCmdID, VOID * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);
	//框架消息处理
	virtual bool OnFrameMessage(WORD wSubCmdID, VOID * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);

	//用户事件
public:
	//用户断线
	virtual bool OnActionUserOffLine(WORD wChairID,IServerUserItem * pIServerUserItem);
	//用户重入
	virtual bool OnActionUserConnect(WORD wChairID,IServerUserItem * pIServerUserItem);
	//用户坐下
	virtual bool OnActionUserSitDown(WORD wChairID,IServerUserItem * pIServerUserItem, bool bLookonUser);
	//用户起立
	virtual bool OnActionUserStandUp(WORD wChairID,IServerUserItem * pIServerUserItem, bool bLookonUser);
	//用户同意
	virtual bool OnActionUserOnReady(WORD wChairID,IServerUserItem * pIServerUserItem, void * pData, WORD wDataSize) { return true; }

	virtual void SetPrivateInfo(BYTE bGameTypeIdex,DWORD bGameRuleIdex);
	virtual void SetCreateUserID(DWORD	dwUserID);

	//游戏事件
protected:
	//用户出牌
	bool OnUserOutCard(WORD wChairID, BYTE cbCardData);
	//用户出牌
	bool OnUseHaiDiCard(WORD wChairID, BYTE cbUseHaiDi);
	//用户出牌
	bool OnUserOutCardCSGang(WORD wChairID, BYTE cbCardData1,BYTE cbCardData2,bool bNext = true);

	bool CanQiangGangHu();
	//用户操作
	bool OnUserOperateCard(WORD wChairID, DWORD cbOperateCode, BYTE cbOperateCard, BYTE cbCSGangIdex);

	bool OnUserOperateCardBeiDong(WORD wChairID, DWORD cbOperateCode,UserActionStates* pUserActionStates);

public:
	bool hasRule(BYTE cbRule);
	bool isHZGuiZe();
	DWORD AnalyseChiHuCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, BYTE cbCurrentCard, CChiHuRight &ChiHuRight);
	DWORD AnalyseChiHuCardZZ(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, BYTE cbCurrentCard, CChiHuRight &ChiHuRight,bool bSelfSendCard);
	DWORD AnalyseChiHuCardCS(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, BYTE cbCurrentCard, CChiHuRight &ChiHuRight,bool bSelfSendCard);
	DWORD AnalyseChiHuCardCS_XIAOHU(const BYTE cbCardIndex[MAX_INDEX], CChiHuRight &ChiHuRight);
	
	//辅助函数
protected:
	//发送操作
	bool SendOperateNotify(WORD wChairID = INVALID_CHAIR);
	//发送托管
	void setChairTrustee(WORD iChairID,bool bTrustee);
	//派发扑克
	void NoticeGangState(WORD iChairID,bool bSendNotice);
	void SendUseHaiDi(WORD wCurrentUser);
	bool DispatchCardData(WORD wCurrentUser,bool bHaiDi=false);
	bool DispatchCardData_CSGang(WORD wCurrentUser);
	//响应判断
	void EstimateUserRespond_Other(UserActionStates& kUserStates,WORD wUserChairID, BYTE cbCenterCard);
	bool EstimateUserRespond(WORD wCenterUser, BYTE cbCenterCard, enEstimatKind EstimatKind);
	bool EstimateUserRespondCSGang(WORD wCenterUser, BYTE cbCenterCard1,BYTE cbCenterCard2);

	//清除用户操作状态
	void clearUserActionStates(WORD cbChairID = INVALID_CHAIR);
	//
	void ProcessChiHuUser( WORD wChairId,CChiHuRight &chr,BYTE	cbProvideCard);
	//
	void FiltrateRight( WORD wChairId,CChiHuRight &chr );
	bool checkSelfGang(WORD wChairID,BYTE cbOperateCard,bool& bPublic);

	BYTE GetNiaoCardNum();
	int checkNiaoScore(CChiHuRight chr,BYTE iChairID,BYTE wProvideUser,LONGLONG lChiHuScore);

public:
	void starGameRecord();
	void addGameRecordAction(CMD_S_OperateResult kNetInfo);
	void addGameRecordAction(CMD_S_SendCard kNetInfo);
	void addGameRecordAction(CMD_S_OutCard kNetInfo);
	void addGameRecordAction(CMD_S_ChiHu kNetInfo);
public:
	void sendMasterHandCard();
	void sendMasterLeftCard(int nChairldID);
	BYTE getSendCardData(WORD dwSendUser);
public:
	void OnUserXiaoHu(WORD wChairID,DWORD dwCode);
	void getXiaoHuCard(WORD nChairldID,CMD_S_XiaoHu& kXiaoHu);
	int  getLeftCardNum();
};

//////////////////////////////////////////////////////////////////////////

#endif
