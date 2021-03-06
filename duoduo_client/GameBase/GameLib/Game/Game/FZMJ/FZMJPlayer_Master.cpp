#include "FZMJPlayer.h"
#include "FZMJGameLogic.h"
#include "FZMJSoundFun.h"

void FZMJPlayer::setHandCard_EX(std::vector<BYTE> kCardList)
{
	int nCardCount = kCardList.size();
	ASSERT(nCardCount <= MAX_COUNT);
	for (int i=0;i<nCardCount;i++)
	{
		m_kHandCardData[i] = kCardList[i];
	}
	m_kHandCardCout = nCardCount;
}
void FZMJPlayer::setMaskHandCard(std::vector<MasterHandCardInfo> kMasterHandCardInfo)
{
	for (int i=0;i<(int)kMasterHandCardInfo.size();i++)
	{
		if (GetChairID() == kMasterHandCardInfo[i].nChairId)
		{
			setHandCard_EX(kMasterHandCardInfo[i].kMasterHandCard);
		}
	}
}
void FZMJPlayer::setMingPai(bool bValue)
{
	m_bMingPai = bValue;
}