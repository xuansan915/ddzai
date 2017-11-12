#pragma once
#include "PlayStrategyBase.h"
class Farmer2PlayerStrategy :
	public PlayStrategyBase
{
public:
	~Farmer2PlayerStrategy();
	Farmer2PlayerStrategy(const CardVector & cardsValue, GameTable* table);
	Farmer2PlayerStrategy(const std::set<uint8_t, CardSetCompare>& cardsValue, GameTable* table);
	virtual CardStyle Play() override;
	virtual CardStyle Take(EIdentity::EIdentity_ lastIdentity, const CardStyle & lastStyle)override;
	virtual bool OtherCanTake(const CardStyle& style)const override;
	virtual bool IsSafeSituation(ESituationSafeLevel::ESituationSafeLevel_ level) const;
	virtual std::vector<ECardStyle::ECardStyle_> AvoidPlayStyle();
	virtual EIdentity::EIdentity_ Identity()const override;
	virtual void Init()override;
};

