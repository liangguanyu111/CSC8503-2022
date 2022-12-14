#include "StateGameObject.h"
#include "StateTransition.h"
#include "StateMachine.h"
#include "State.h"
#include "PhysicsObject.h"

using namespace NCL;
using namespace CSC8503;

StateGameObject::StateGameObject() {

	counter = 0.0f;
	stateMachine = new StateMachine();
	State * stateA = new State([&](float dt) -> void
	{
		Partorl(dt);
	}
	);
	State * stateB = new State([&](float dt) -> void
		{
			
		}
	);
	
	stateMachine-> AddState(stateA);
	stateMachine-> AddState(stateB);
	stateMachine-> AddTransition(new StateTransition(stateA, stateB, [&]()-> bool
		{
			return false;
		}
	));
	stateMachine-> AddTransition(new StateTransition(stateB, stateA,[&]()-> bool
		{
			return false;
		}
	));
}

StateGameObject::~StateGameObject() {
	delete stateMachine;
}

void StateGameObject::Update(float dt) {
	stateMachine -> Update(dt);
}



void StateGameObject::MoveToPos(Vector3 pos)
{
	if (Vector3::Distance(this->transform.GetPosition(), pos) > 0.2f)
	{
		float speed = 3.0f;
		Vector3 direction = pos - this->transform.GetPosition();
		this->GetPhysicsObject()->AddForce(direction * speed);
	}
	else
	{
		this->GetPhysicsObject()->ClearForces();
	}
}

void NCL::CSC8503::StateGameObject::Partorl(float dt)
{
	if (!init)
	{
		init = true;
		targetPosition = this->transform.GetPosition();
	}
	if (init && Vector3::Distance(this->transform.GetPosition(), targetPosition) < 0.2f)
	{
		grid = NavigationGrid(2);
		grid.PrintAllNode();
		//grid.ReturnSamplePoint(targetPosition);
		if (grid.FindPath(Vector3(2,0,2), Vector3(30,0,30), currentPath))
		{
			
		}
	}
}



void StateGameObject::MoveLeft(float dt) {
	GetPhysicsObject() -> AddForce({ -100 , 0 , 0 });
	counter += dt;
}

void StateGameObject::MoveRight(float dt) {
	GetPhysicsObject() -> AddForce({ 100 , 0 , 0 });
	counter -= dt;
}