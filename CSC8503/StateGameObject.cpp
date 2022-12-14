#include "StateGameObject.h"
#include "StateTransition.h"
#include "StateMachine.h"
#include "State.h"
#include "PhysicsObject.h"
#include "Debug.h"

using namespace NCL;
using namespace CSC8503;

StateGameObject::StateGameObject(NavigationGrid* grid)  {

	counter = 0.0f;
	stateMachine = new StateMachine();

	this->grid = grid;

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
	if (Vector3::Distance(this->transform.GetPosition(), pos) > 0.1f)
	{
		float speed = 30.0f;
		//std::cout << "Current Pos:"<<this->transform.GetPosition() << std::endl;
		Vector3 direction = pos - this->transform.GetPosition();
		direction.y = 0;
		//this->GetPhysicsObject()->SetLinearVelocity(direction * speed);
		this->GetPhysicsObject()->AddForce(direction * speed);
	}
	else
	{
		this->GetPhysicsObject()->ClearForces();
	}
}

void NCL::CSC8503::StateGameObject::Partorl(float dt)
{
	Vector3 tempPos = Vector3(this->transform.GetPosition().x, 0, this->transform.GetPosition().z);
	if (!init)
	{
		init = true;
		targetPosition = tempPos;
		nextPos = tempPos;
	}
	if (init && Vector3::Distance(tempPos, targetPosition) < 0.2f)
	{
		grid->ReturnSamplePoint(targetPosition);
		if (grid->FindPath(this->transform.GetPosition(), targetPosition, currentPath))
		{
			std::cout << "New path" << std::endl;
		}
	}
	if (Vector3::Distance(tempPos, nextPos) < 0.1f)
	{
		currentPath.PopWaypoint(nextPos);
	}
	
	if (Vector3::Distance(tempPos, nextPos) >= 0.1f)
	{
		MoveToPos(nextPos);
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

void StateGameObject::DisplayPathfinding()
{
	vector<Vector3> testNodes;
	Vector3 pos;
	while (currentPath.PopWaypoint(pos))
	{
		testNodes.push_back(pos);
	}
	for (int i = 1; i < testNodes.size(); ++i) {
		Vector3 a = testNodes[i - 1];
		Vector3 b = testNodes[i];
		Debug::DrawLine(a, b, Vector4(0, 1, 0, 1));
	}
}