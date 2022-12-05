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
			PushdownResult OnUpdate(float dt,
				PushdownState** newState) override {
				if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::SPACE)) {
					*newState = new GameScreen();
					return PushdownResult::Push;
				}
				if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::ESCAPE)) {
					return PushdownResult::Pop;
				}
				return PushdownResult::NoChange;
			};

			void OnAwake() override {
				std::cout << " Welcome to a really awesome game !\n";
				std::cout << " Press Space To Begin or escape to quit !\n";
			}

		};
	}
}