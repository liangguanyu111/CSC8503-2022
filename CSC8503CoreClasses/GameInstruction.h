#pragma once
#include "PushdownMachine.h"
#include "PushdownState.h"
#include "Window.h"

using namespace NCL;
using namespace CSC8503;
using namespace NCL::CSC8503;

namespace NCL {
	namespace CSC8503 {
		class GameInstruction : public PushdownState
		{
		private:
		public:
			PushdownResult OnUpdate(float dt, PushdownState** newState) override {

				Debug::Print("1.Use WASD to controll the goat.", Vector2(0, 25), Vector4(1, 1, 1, 1));
				Debug::Print("2.The green Ai will help you collect bonus,", Vector2(0, 30), Vector4(1, 1, 1, 1));
				Debug::Print("the red Ai will destroy bonus.", Vector2(0, 35), Vector4(1, 1, 1, 1));
				Debug::Print("3.Get enough grade to enter next level.", Vector2(0, 40), Vector4(1, 1, 1, 1));
				Debug::Print("Back", Vector2(0, 55), Vector4(1, 0, 0, 1));

				if (Window::GetKeyboard()->KeyDown(KeyboardKeys::LEFT))
				{
					return PushdownResult::Pop;
				}

				return PushdownResult::Keep;
			};

			void OnAwake() override
			{

			}
		};
	}
}