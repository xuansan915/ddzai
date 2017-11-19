#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Split
{
	TEST_CLASS(UnitTest4)
	{
	public:
		TEST_METHOD_INITIALIZE(SetUp)
		{
			srand((unsigned)time(NULL));
			Logger::WriteMessage("Test initialized.\n"); //用于输出信息  
		}
		TEST_METHOD_CLEANUP(TearDown)
		{
			Logger::WriteMessage("Test completed.\n");
		}
		TEST_METHOD(TestSplitStrategyBase)
		{
			for (int i = 0; i < 100; i++) {//约是0.8ms
			//CardSet set;
			//auto& extraCards = set.RandomFillLeft();
			//HandCards *cards = set.PlayerCardSet[0];
				//HandCards *cards = new HandCards(std::vector<uint8_t>{ 0x34, 0x44, 0x15, 0x45, 0x26, 0x46, 0x47, 0x18, 0x38, 0x49, 0x1a, 0x1b, 0x2c, 0x2d, 0x4d, 0x3d, 0x1d }, true);
				//auto s = cards->ToString();
				//Logger::WriteMessage(s.c_str());
				SplitStrategyBase strategy(std::make_shared<HandCards>(std::vector<uint8_t>{ 0x34, 0x44, 0x15, 0x45, 0x26, 0x46, 0x47, 0x18, 0x38, 0x49, 0x1a, 0x1b, 0x2c, 0x2d, 0x4d, 0x3d, 0x1d }, true));
				strategy.SplitIsolate();
				strategy.SplitBoom();
				strategy.SplitDoubleChain();
				strategy.SplitTripleChain();
				strategy.SplitSingleChain();
				strategy.SplitTriple();
				strategy.SplitIsolate();
				//int minStep = strategy._Split_Ptr()->MinStepCount();
				//auto t = strategy._Split_Ptr()->MinValueCardStyle().ToString();
			}
		}
		TEST_METHOD(TestSplitTwoSingleChain)
		{
			CardSet set;
			auto& extraCards = set.RandomFillLeft();
			std::shared_ptr< HandCards >cards = std::make_shared<HandCards>(set.PlayerCardSet[0]->Data());
			//HandCards *cards = new HandCards(std::vector<uint8_t>{0x33, 0x44, 0x15, 0x45, 0x26, 0x46,0x37, 0x47, 0x18, 0x38, 0x49, 0x1a, 0x1b, 0x2c, 0x2d, 0x4d, 0x3d, 0x1d }, true);
			auto s = cards->ToString();
			Logger::WriteMessage(s.c_str());
			SplitStrategyBase strategy(cards);

			strategy.SplitIsolate();
			strategy.SplitBoom();
			strategy.SplitIntersectChain();
			strategy.SplitDoubleChain();
			strategy.SplitTripleChain();
			strategy.SplitSingleChain();
			strategy.SplitTriple();
			strategy.SplitIsolate();
			SplitType type = *(strategy._Split_Ptr());
			s = type.ToString();

			Logger::WriteMessage(s.c_str());
			size_t minStep = type.MinStepCount();
			size_t cardCount = type.CardCount();
			auto t = strategy._Split_Ptr()->MinValueCardStyle().ToString();
		}
		TEST_METHOD(TestSplitStrategy)
		{
			CardSet set;
			auto& extraCards = set.RandomFillLeft();
			//HandCards *cards = set.PlayerCardSet[0];
			//auto s = cards->ToString();
			//Logger::WriteMessage(s.c_str());
			MinStepSplitStrategy strategy(std::make_shared<HandCards>(std::vector<uint8_t>{0x33, 0x44, 0x15, 0x45,
				0x26, 0x46, 0x37, 0x47, 0x18, 0x38, 0x49, 0x1a, 0x1b, 0x2c, 0x2d, 0x4d, 0x3d, 0x1d ,0x1,0x2}, true));
			strategy.Split();
			auto&minStepSplitType = strategy.MinStepSplit();
		}
		TEST_METHOD(TestGameTable)
		{
			CardSet set;
			set.DealIndex(0, CardIndex_2, 2);
			set.DealIndex(0, CardIndex_LargeJoker, 1);
			set.DealIndex(0, CardIndex_SmallJoker, 1);
			set.DealIndex(0, CardIndex_4, 1);
			set.DealChain(0, CardIndex_3, CardIndex_6,2);
			//set.DealIndex(0, CardIndex_4, 2);
			set.DealIndex(2, CardIndex_7, 2);
			set.DealIndex(1, CardIndex_A, 1);
			set.DealIndex(1, CardIndex_9, 1);
			set.DealIndex(1, CardIndex_J, 3);
			set.DealIndex(2, CardIndex_Q, 1);
			set.DealIndex(2, CardIndex_K, 2);
			set.Update();
			//auto& extraCards = set.RandomFillLeft();
			
			GameTable table(set);
			CardVector lastPlayCard({ 0x16,0x36,});
			//CardStyle lastPlayStyle = CardStyle::DoubleChainStyle(CardIndex_3, CardIndex_5);
			CardStyle lastPlayStyle = CardStyle::FromCardsValue(lastPlayCard);
			EIdentity::EIdentity_ lastPlayIdentity = EIdentity::Farmer1;
			EIdentity::EIdentity_ curPlayIdentity = EIdentity::Farmer2;
			auto thisStyle= table.Take(curPlayIdentity, lastPlayIdentity, lastPlayStyle);
			auto cards = table.GetHandCard(curPlayIdentity)->GetCardsByStyle(thisStyle);

			OpenCVEntry *cv = new OpenCVEntry(L"D:\\CommondCode\\DDZ_AI\\DDZ_AI\\CardsImage");
			cv->ShowPlay(
				table.GetHandCard(EIdentity::Lord)->ToCardValues(),
				table.GetHandCard(EIdentity::Farmer1)->ToCardValues(), 
				table.GetHandCard(EIdentity::Farmer2)->ToCardValues()
				, lastPlayIdentity, curPlayIdentity, lastPlayCard, cards);
			//cv->ShowCard(opt);
			cv->Wait(30000);
		}
	};
}