#pragma once
#include "PlayStrategyHandle.h"
class HandleBoomTake :
	public PlayStrategyHandle
{
public:
	HandleBoomTake()=default;
	~HandleBoomTake();
	virtual bool Handle(PlayStrategyBase* playStrategy, SplitStrategy * splitStrategy, CardStyle & result)override;
	HandleBoomTake(const HandleBoomTake&) = delete;
};

