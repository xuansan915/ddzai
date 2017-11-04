#pragma once
#include "SplitStrategyBase.h"
#include <functional>
//ÿһ���̳е����ฺ������Split��Ϣ�������ڵ����������Լ����ƱȽ϶��ʱ��
//��ȡMinStepSplitStrategy ,���Ƶ�ʱ���������Ĳ�ֲ��ԣ���Ҫ����Ҫ�ӵ��Ƹ�����ȥ
class SplitStrategy :
	public SplitStrategyBase
{
protected:
	std::vector<SplitType> m_splitTypeVector;
	std::vector<size_t> m_splitMinStepVector;
	std::vector<CardStyle> m_optimiumStyle;
	std::vector<CardStyle> m_availableStyle;
	void sortSplitType();
public:
	virtual void Reset();
	const SplitType& MinStepSplit()const;
	virtual void Split();
	virtual void OptimiumTake(const CardStyle & style);
	virtual void AvailableTake(const CardStyle & style);
	inline const std::vector<CardStyle>& GetOptimiumStyle() { return m_optimiumStyle; }
	inline const std::vector<CardStyle>& GetAvailableStyle() { return m_availableStyle; }
	SplitStrategy(std::shared_ptr< HandCards>cards);
	virtual ~SplitStrategy();
};