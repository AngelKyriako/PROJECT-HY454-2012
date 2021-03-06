#ifndef BUBPROFILE_H
#define BUBPROFILE_H

#include <map>
#include "Metrics.h"

typedef unsigned int Lifes;
typedef int Points;

#define DFLT_STARTING_LIFES 5

typedef std::pair<bool, bool> BlastPowerUpPair_t;
typedef std::pair<bool, BlastPowerUpPair_t> BlastAnimationMapKey_t;
typedef std::map<BlastAnimationMapKey_t, std::string> BlastAnimationMap_t;

class BubProfile{

	public:
		BubProfile(Lifes startLifes, StartingAttributes_t startAttr);
		BubProfile();
		~BubProfile();

	private:
		void InitBlastAnimationMap(void);

	private:
		BlastAnimationMap_t blastAnimationMap;
		Coordinates startXY;
		bool startDirection;
		bool startGravity;
		Points score;
		Lifes lifes;
		unsigned int enemiesKilledOnPon;
		bool hasRedShoes;
		bool eatenYellowSweet;
		bool eatenBlueSweet;
		bool eatenPurpleSweet;
		unsigned int timesCrossedStage;
		unsigned int timesJumped;
		unsigned int timesBlastedBubble;
		unsigned int timesPonedBubble;
		bool isJumpOnMove;

	public:
		void SetStartingAttributes(StartingAttributes_t startAttr);
		int GetStartX(void);
		int GetStartY(void);
		bool GetStartDirection(void);
		bool GetStartGravity(void);

		void IncrScore(Points addedPoints);
		void SetScore(Points newScore);
		Points GetScore(void);

		void IncrLifes(void);
		void DecrLifes(void);
		Lifes GetLifes(void);

		void SetEnemiesKilledOnPon(unsigned int enemies);
		void IncrEnemiesKilledOnPon(void);
		unsigned int GetEnemiesKilledOnPon(void);

		void SetRedShoes(bool activate);
		bool GetRedShoes(void);

		void SetYellowSwt(bool activate);
		bool GetYellowSwt(void);

		void SetBlueSwt(bool activate);
		bool GetBlueSwt(void);

		void SetPurpleSwt(bool activate);
		bool GetPurpleSwt(void);

		void IncrTimesCrossedStage(void);
		unsigned int GetTimesCrossedStage(void);

		void IncrTimesJumped(void);
		unsigned int GetTimesJumped(void);

		void IncrTimesBlastedABubble(void);
		unsigned int GetTimesBlastedBubble(void);

		void IncrTimesPonedABubble(void);
		unsigned int GetTimesPonedBubble(void);

		const std::string GetBubbleBlastAnimation(bool goesLeft);
		const std::string GetBubWalkAnimation(bool goesLeft);
		const std::string GetBubOpenMouthWalkAnimation(bool goesLeft);
		const std::string GetBubJump(void);

		void SetJumpOnMove(bool j);
		bool IsJumpOnMove(void);
};

#endif