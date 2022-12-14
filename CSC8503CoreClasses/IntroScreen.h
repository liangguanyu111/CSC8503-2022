#pragma once
#include "PushdownMachine.h"
#include "PushdownState.h"
#include "GameScreen.h"
#include "Window.h"

using namespace NCL;
using namespace CSC8503;

using namespace NCL::CSC8503;

namespace NCL {
	namespace CSC8503 {
		class IntroScreen : public PushdownState
		{
			PushdownResult OnUpdate(float dt,PushdownState** newState) override {

				Debug::Print("Start Single Game", Vector2(5, 50));
				Debug::Print("Start Mutiple Game", Vector2(5, 55));

 				if (Window::GetKeyboard()->KeyDown(KeyboardKeys::SPACE)) {
					*newState = new GameScreen();
					return PushdownResult::Push;
				}
				else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::ESCAPE)) {
					return PushdownResult::Pop;
				}

				return PushdownResult::NoChange;
			};

			void OnAwake() override {

			}

		};
	}
}