#pragma once
#include "PlayStrategyHandle.h"

class HandleLastShotPlay :
	public PlayStrategyHandle
{
public:
	HandleLastShotPlay()=default;
	virtual bool Handle(PlayStrategyBase* playStrategy, SplitStrategy * splitStrategy, CardStyle & result)override;
	HandleLastShotPlay(const HandleLastShotPlay&) = delete;
};

