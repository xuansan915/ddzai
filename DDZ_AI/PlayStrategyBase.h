#pragma once
#include "SplitStrategy.h"
#include<memory>
/*
���������������Ӳ�ͬ��SplitStrategy
*/
class GameTable;//ǰ��������GameTable.hͷ�ļ�������cpp��
class PlayStrategyBase
{
protected:
	GameTable *m_table;
	std::shared_ptr<HandCards> m_handCards;
public:
	virtual void Init()=0;
	virtual CardStyle Play() = 0;
	virtual CardStyle Take(Identity::EIdentity_ lastIdentity, const CardStyle & lastStyle) = 0;
	virtual int Identity() = 0;
	PlayStrategyBase(int identity, const  std::vector<uint8_t>& cardsValue,GameTable *table);
	PlayStrategyBase(int identity, const  std::set<uint8_t, CardSetCompare>& cardsValue, GameTable *table);
	virtual ~PlayStrategyBase();
	virtual void Reset(const  std::vector<uint8_t>& cardsValue);
	virtual void Reset(const  std::set<uint8_t, CardSetCompare>& cardsValue);

	inline const HandCards& GetHandCards() {
		_ASSERT(m_handCards);
		return *m_handCards.get();
	}
};