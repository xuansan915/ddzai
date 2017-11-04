#include "stdafx.h"
#include "LordPlayStrategy.h"
#include"MinStepSplitStrategy.h"
#include "GameTable.h"

CardStyle LordPlayStrategy::Play()
{
	CardStyle r;
	m_minStepSplitStrategy->Split();
	m_handlerMinStepPlay->Handle(m_minStepSplitStrategy.get(), r);
	return r;
}

CardStyle LordPlayStrategy::Take(Identity::EIdentity_ lastIdentity, const CardStyle & lastStyle)
{
	m_minStepSplitStrategy->Split();
	m_minStepSplitStrategy->OptimiumTake(lastStyle);
	m_minStepSplitStrategy->AvailableTake(lastStyle);
	//���ж�ʹ����һ�ֲ�ֲ��ԣ�����һ��ʼ�������SplitStrategy��Ȼ���ٴ��벻ͬ��Handle������д���
	CardStyle ret(CardStyle::Invalid);

	if (m_handlerOptimiumTake->Handle(m_minStepSplitStrategy.get(), ret)) {//����С�����ɽ��Ƶ����
		return ret;
	}

	if (m_handlerOptimiumTake->Handle(m_keepBigSplitStrategy.get(), ret)) {//�б������ƿɽ��Ƶ����
		return ret;
	}

	if (m_handlerCanTake->Handle(m_minStepSplitStrategy.get(), ret)) {//���ϲ����� ���ǿ��Խ��ƣ����к����ж�

	}
	//�������Ͼ�ѡ�񲻽�
	return ret;
}


int LordPlayStrategy::Identity()
{
	return Identity::Lord;
}

LordPlayStrategy::LordPlayStrategy(const std::vector<uint8_t>& cardsValue, GameTable* table) : PlayStrategyBase(Identity(), cardsValue, table)
{
	m_handCards = std::make_shared<HandCards>(cardsValue);
	m_minStepSplitStrategy = std::make_shared<MinStepSplitStrategy>(m_handCards);
}

LordPlayStrategy::LordPlayStrategy(const std::set<uint8_t, CardSetCompare>& cardsValue, GameTable* table) : PlayStrategyBase(Identity(), cardsValue, table)
{
	m_handCards = std::make_shared<HandCards>(cardsValue);
	m_minStepSplitStrategy = std::make_shared<MinStepSplitStrategy>(m_handCards);
}

void LordPlayStrategy::Init()
{
	m_handlerCanTake = std::make_unique<HandleCanTakeCard>();
	m_handlerOptimiumTake = std::make_unique<HandleCanOptimiumTakeCard>();
	m_handlerMinStepPlay = std::make_unique<HandleMinValuePlay>();

	//����������װ����ͷβ������һ����һ��  
	//m_handlerCanTake->setNextStrategy(m_handlerOptimiumTake.get());
	//m_handlerOptimiumTake->setNextStrategy(m_handlerMinStepPlay.get());

}


LordPlayStrategy::~LordPlayStrategy()
{

}