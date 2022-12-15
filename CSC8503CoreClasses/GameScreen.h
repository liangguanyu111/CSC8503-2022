
#pragma once
#include "PushdownMachine.h"
#include "PushdownState.h"

#include "Window.h"
#include "PauseScreen.h"

using namespace NCL;
using namespace CSC8503;
using namespace NCL::CSC8503;


namespace NCL {
	namespace CSC8503 {
		class GameScreen : public PushdownState
		{
			PushdownResult OnUpdate(float dt, PushdownState** newState) override
			{
				return PushdownResult::NoChange; 
			}
			void OnAwake() override
			{
				std::cout << "开始游戏" << std::endl;
			}
		protected:
		};
	}
}



