#pragma once
#include "PushdownMachine.h"
#include "PushdownState.h"

#include "Window.h"


using namespace NCL;
using namespace CSC8503;
using namespace NCL::CSC8503;


namespace NCL {
	namespace CSC8503 {
		class GameEnd : public PushdownState
		{
			PushdownResult OnUpdate(float dt, PushdownState** newState) override
			{
							
				Debug::Print("Your Score is: " + std::to_string(TutorialGame::score), Vector2(30, 50), Vector4(1, 1, 1, 1));
				if (TutorialGame::score <= 30)
				{
					Debug::Print("Sorry,You lose!" + std::to_string(TutorialGame::score), Vector2(30, 45), Vector4(1, 0, 0, 1));
				}
				else
				{
					Debug::Print("You Win!" + std::to_string(TutorialGame::score), Vector2(35, 45), Vector4(0, 1, 0, 1));
				}
				return PushdownResult::Keep;
			}
			void OnAwake() override
			{

			}
		protected:
		};
	}
}

