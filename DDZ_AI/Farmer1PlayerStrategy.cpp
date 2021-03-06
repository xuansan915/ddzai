#include "stdafx.h"
#include "Farmer1PlayerStrategy.h"
#include "GameTable.h"
#include"SplitStrategy.h"
#include "MinStepSplitStrategy.h"
#include "HandleLetFarmer2WinPlay.h"

CardStyle Farmer1PlayerStrategy::takeLord(const CardStyle & lastStyle)
{
	CardStyle ret;
	if (m_handlerOptimiumTake->Handle(this, m_minStepSplitStrategy.get(), ret)) {//有最小步数可接牌的情况
		DEBUG_LOG("HandleOptimiumTake  " + ret.ToString());
		return ret;
	}
	if (m_handlerBoomTake->Handle(this, m_minStepSplitStrategy.get(), ret)) {
		DEBUG_LOG("HandleBoomTake  " + ret.ToString());
		return ret;
	}
	if (m_handlerAvailableTake->Handle(this, m_minStepSplitStrategy.get(), ret)) {
		DEBUG_LOG("HandleAvailableTake  " + ret.ToString());
		return ret;
	}
	DEBUG_LOG("不接");
	return CardStyle::Invalid;
}

CardStyle Farmer1PlayerStrategy::takeFarmer(const CardStyle & lastStyle)
{
	if (lastStyle.IsBigCard()) {
		return CardStyle::Invalid;
	}
	//因为Farmer2已经经过了地主要不起的情况，所以不需要再对其进行防止。需要防止的就是该玩家新出的牌会导致地主获胜
	//不压的情况
	//1.要不起
	//2.Farmer2 出牌会让地主压死
	//3.Farmer2 无法取得胜利，例如全是5张（单只+对子）
	auto& optTakeStyle = m_minStepSplitStrategy->GetOptimiumStyle();
	//auto& optBoomTakeStyle = m_minStepSplitStrategy->GetOptimiumBoomStyle();
	if (optTakeStyle.size() == 0) {
		DEBUG_LOG("没有最佳接法，不接");
		return CardStyle::Invalid;
	}
	const SplitType& minStepSplit = GetStrategyPtr(EIdentity::Farmer2)->m_minStepSplitStrategy->MinStepSplit();
	auto allStyles = minStepSplit.GetAllSplitStyle();

	if (allStyles.size() == 1) {
		DEBUG_LOG("农民2能一步走完，不接");
		return CardStyle::Invalid;
	}
	auto f2_handcards = GetStrategyPtr(EIdentity::Farmer2)->GetHandCards();
	auto lord_handcards = GetStrategyPtr(EIdentity::Lord)->GetHandCards();

	int beatedCount = 0;//可被压制但是f2无法压制的Style个数，如果超过1个，那么我就选择接牌，否则不接
	for (auto &v : allStyles) {
		CardStyle ret;
		bool lordCanTake = lord_handcards->CanTake(v, ret);//如果地主可以接牌，而且f2无法接住地主压得牌，那么添加一个被压制的个数
		if (lordCanTake && !f2_handcards->CanTake(ret)) {
			++beatedCount;
		}
	}
	if (allStyles.size() - beatedCount > 1) {
		DEBUG_LOG("接农民2的牌，采用OptmiumTake");
		return	optTakeStyle[0];
	}

	DEBUG_LOG("不接");
	return CardStyle::Invalid;
}

Farmer1PlayerStrategy::~Farmer1PlayerStrategy()
{
}

Farmer1PlayerStrategy::Farmer1PlayerStrategy(const CardVector & cardsValue, GameTable* table) : PlayStrategyBase(Identity(), cardsValue, table)
{
}

Farmer1PlayerStrategy::Farmer1PlayerStrategy(const std::set<uint8_t, CardSetCompare>& cardsValue, GameTable* table) : PlayStrategyBase(Identity(), cardsValue, table)
{
}

CardStyle Farmer1PlayerStrategy::Play()
{
	CardStyle ret;
	m_minStepSplitStrategy->Split();
	if (m_handlerLastShotPlay->Handle(this, m_minStepSplitStrategy.get(), ret)) {
		DEBUG_LOG("HandleLastShotPlay  " + ret.ToString());
		return ret;
	}
	if (m_handlerLetFarmer2WinPlay->Handle(this, m_minStepSplitStrategy.get(), ret)) {
		DEBUG_LOG("HandleLetFarmer2WinPlay  " + ret.ToString());
		return ret;
	}
	if (m_handlerTwoStepPlay->Handle(this, m_minStepSplitStrategy.get(), ret)) {
		DEBUG_LOG("HandleTwoStepPlay  " + ret.ToString());
		return ret;
	}
	if (m_handlerAvoidOtherWinPlay->Handle(this, m_minStepSplitStrategy.get(), ret)) {
		DEBUG_LOG("HandleAvoidOtherWinPlay  " + ret.ToString());
		return ret;
	}

	m_handlerMinValuePlay->Handle(this, m_minStepSplitStrategy.get(), ret);
	DEBUG_LOG("HandleMinValuePlay  " + ret.ToString());
	return ret;
}

CardStyle Farmer1PlayerStrategy::Take(EIdentity::EIdentity_ lastIdentity, const CardStyle & lastStyle)
{
	m_minStepSplitStrategy->Split();
	m_minStepSplitStrategy->OptimiumTake(lastStyle);
	m_minStepSplitStrategy->AvailableTake(lastStyle);
	if (m_minStepSplitStrategy->GetAvailableStyle().size() == 0) {
		return CardStyle::Invalid;
	}
	std::vector<CardStyle> x;
	bool isWin = CheckIfWin(m_minStepSplitStrategy.get(), lastStyle, true, x);
	if (isWin) {
		DEBUG_LOG("CheckIfWin=true  " + lastStyle.ToString());
		return x[0];
	}
	if (lastIdentity == EIdentity::Lord) {
		return takeLord(lastStyle);
	}
	else {
		return takeFarmer(lastStyle);
	}
}

bool Farmer1PlayerStrategy::OtherCanTake(const CardStyle & style) const
{
	return m_table->GetHandCard(EIdentity::Lord)->CanTake(style);
}

bool Farmer1PlayerStrategy::OtherBiggestCardValue(int compareCount) const
{
	return m_table->BiggestCardValue(EIdentity::Lord, compareCount);
}

bool Farmer1PlayerStrategy::IsSafeSituation(ESituationSafeLevel::ESituationSafeLevel_ level, int param1, void* param2) const
{
	return false;
}

std::vector<ECardStyle::ECardStyle_> Farmer1PlayerStrategy::AvoidPlayStyle()
{
	std::vector<ECardStyle::ECardStyle_> r;
	auto lordCardsCount = m_table->CardCount(EIdentity::Lord);

	if (lordCardsCount == 1) {
		r.push_back(ECardStyle::Single);
	}
	if (lordCardsCount == 2) {
		r.push_back(ECardStyle::Double);
	}
	if (lordCardsCount == 3) {
		r.push_back(ECardStyle::Triple_Zero);
	}
	return r;
}

EIdentity::EIdentity_ Farmer1PlayerStrategy::Identity()const
{
	return EIdentity::EIdentity_::Farmer1;
}

void Farmer1PlayerStrategy::Init()
{
	PlayStrategyBase::Init();
	m_handlerLetFarmer2WinPlay = std::make_unique<HandleLetFarmer2WinPlay>();
}
