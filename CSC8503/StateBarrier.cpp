#include "StateGameObject.h"
#include "StateTransition.h"
#include "StateMachine.h"
#include "State.h"
#include"StateBarrier.h"

NCL::CSC8503::StateBarrier::StateBarrier()
{
	active = false;
	moveDirection = true;
	stateMachine = new StateMachine();
	moveSpeed = 0.1f;

	State* idleState = new State([&](float dt) -> void
		{
			
		}
	);
	State* activeState = new State([&](float dt) -> void
		{
			Active();
		}
	);

	stateMachine->AddState(idleState);
	stateMachine->AddState(activeState);
	stateMachine->AddTransition(new StateTransition(idleState, activeState, [&]()-> bool
		{
			return active;
		}
	));

}


NCL::CSC8503::StateBarrier::~StateBarrier()
{
	delete stateMachine;
}

void NCL::CSC8503::StateBarrier::Active()
{
	
	if (moveDirection)
	{
		if (Vector3::Distance(transform.GetPosition(), startPos) >= 0.15f)
		{
			Vector3 direction = (startPos - transform.GetPosition()).Normalised();
			Vector3 pos = transform.GetPosition() + direction * moveSpeed;
			transform.SetPosition(pos);
		}
		else
		{
			moveDirection = !moveDirection;
		}
	}
	else
	{
		if(Vector3::Distance(transform.GetPosition(), endPos) >= 0.15f)
		{
			Vector3 direction = (endPos - transform.GetPosition()).Normalised();
			transform.SetPosition(transform.GetPosition() + direction * moveSpeed);
		}
		else
		{
			moveDirection = !moveDirection;
		}
	}
}

void NCL::CSC8503::StateBarrier::ActiveBarrier(Vector3 start, Vector3 end)
{
	startPos = start;
	endPos = end;
	active = true;
}



void NCL::CSC8503::StateBarrier::Update(float dt)
{
	stateMachine->Update(dt);
}