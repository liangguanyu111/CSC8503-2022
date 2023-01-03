
#pragma once
#include "PushdownMachine.h"
#include "PushdownState.h"

#include "Window.h"
#include "PauseScreen.h"
#include "GameEnd.h"

using namespace NCL;
using namespace CSC8503;
using namespace NCL::CSC8503;


namespace NCL {
	namespace CSC8503 {
		class GameScreen : public PushdownState
		{
			PushdownResult OnUpdate(float dt, PushdownState** newState) override
			{
				Debug::Print("Time Left: " + std::to_string(TutorialGame::GameTimer), Vector2(30, 10), Vector4(1, 1, 1, 1));
				Debug::Print("Game Score: "+ std::to_string(TutorialGame::score), Vector2(30, 5), Vector4(1, 1, 1, 1));

				if (TutorialGame::GameTimer < 0)
				{
					TutorialGame::game_Start = false;
					*newState = new GameEnd();
					return PushdownResult::Push;
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



