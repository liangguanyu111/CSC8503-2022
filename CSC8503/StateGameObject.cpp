#include "StateGameObject.h"
#include "StateTransition.h"
#include "StateMachine.h"
#include "State.h"
#include "PhysicsObject.h"
#include "Debug.h"
#include "GameWorld.h"
using namespace NCL;
using namespace CSC8503;

StateGameObject::StateGameObject(NavigationGrid* grid)  {

	stateMachine = new StateMachine();

	this->grid = grid;
	speed = 0.1f;

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
			Vector3 playerPos = Vector3(player.GetPosition().x, 0, player.GetPosition().z);
			Vector3 selfPos = Vector3(this->GetTransform().GetPosition().x, 0, this->GetTransform().GetPosition().z);
			float distance = Vector3::Distance(playerPos, selfPos);
			if (distance<=20)
			{
				speed = 0.2f;
				return true;
			}
			return false;
		}
	));
	stateMachine-> AddTransition(new StateTransition(stateB, stateA,[&]()-> bool
		{
			if (Vector3::Distance(player.GetPosition(), this->GetTransform().GetPosition()) >= 30)
			{
				speed = 0.1f;
				return true;
			}
			return false;
		}
	));
}

StateGameObject::~StateGameObject() {
	delete stateMachine;
}

void StateGameObject::Update(float dt) {
	stateMachine -> Update(dt);
	RayDetect();
}




void StateGameObject::MoveToPos(Vector3 pos)
{
	if (Vector3::Distance(this->transform.GetPosition(), pos) > 0.1f)
	{
		Vector3 direction = (pos - this->transform.GetPosition()).Normalised();
		direction.y = 0;
	
		this->transform.SetPosition(this->transform.GetPosition() + direction * speed);
	}

}

void NCL::CSC8503::StateGameObject::Partorl(float dt)
{
	Vector3 tempPos = Vector3(this->transform.GetPosition().x, 0, this->transform.GetPosition().z);
	if (!init)
	{
		init = true;
		initPos = transform.GetPosition();
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
		
		if (tempPos != nextPos)
		{
			Vector3 direction = nextPos - tempPos;
			this->transform.RotateTo(direction);
		}
	
	}
	
	if (Vector3::Distance(tempPos, nextPos) >= 0.1f)
	{
		MoveToPos(nextPos);
	}
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

void NCL::CSC8503::StateGameObject::Escape()
{

}

void NCL::CSC8503::StateGameObject::ReSpawn()
{
	transform.SetPosition(initPos);
}

void NCL::CSC8503::StateGameObject::RayDetect()
{
	RayCollision closestCollision;
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::K)) {
		Vector3 rayPos;
		Vector3 rayDir;

		rayDir = GetTransform().GetOrientation() * Vector3(0, 0, -1);

		rayPos = GetTransform().GetPosition();

		Ray r = Ray(rayPos, rayDir);

		if (GameWorld->Raycast(r, closestCollision, true, this)) {
			GameObject* objClosest = (GameObject*)closestCollision.node;
			std::cout << this->name << " detected " << objClosest->GetName() << " in front of it." << std::endl;
			if (objClosest->GetLayer()== Obstcale)
			{
				ReSpawn();
			}
			delete objClosest;
		}
	}

}
