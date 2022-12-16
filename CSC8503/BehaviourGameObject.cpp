#include "BehaviourGameObject.h"
#include"BehaviourAction.h"

NCL::CSC8503::BehaviourGameObject::BehaviourGameObject(NavigationGrid* grid)
{
	this->grid = grid;

	root = new BehaviourSelector("root");

	BehaviourAction* Partrol = new BehaviourAction("Partrol",
		[&](float dt, BehaviourState state) -> BehaviourState
		{
			if (state == Initialise)
			{
				Vector3 tempPos = Vector3(this->transform.GetPosition().x, 0, this->transform.GetPosition().z);
				targetPosition = tempPos;
				nextPos = tempPos;
				return Ongoing;
			}
			if (state == Ongoing)
			{
				Partorl(dt);
			}
		return state;
		}
	);

	BehaviourAction* goBed = new BehaviourAction("Go to Bed",
		[&](float dt, BehaviourState state) -> BehaviourState
		{
			if (state == Initialise)
			{
				std::cout << "Go to Bed" << std::endl;
				return Ongoing;
			}
			if (state == Ongoing)
			{
				std::cout << "Sleeping" << std::endl;
			}
			return state;
		}
	);

	root->AddChild(Partrol);
	root->AddChild(goBed);
}

void NCL::CSC8503::BehaviourGameObject::MoveToPos(Vector3 pos)
{
	if (Vector3::Distance(this->transform.GetPosition(), pos) > 0.1f)
	{
		Vector3 direction = (pos - this->transform.GetPosition()).Normalised();
		direction.y = 0;

		this->transform.SetPosition(this->transform.GetPosition() + direction / 10);
	}

}
void NCL::CSC8503::BehaviourGameObject::Partorl(float dt)
{
	Vector3 tempPos = Vector3(this->transform.GetPosition().x, 0, this->transform.GetPosition().z);



	if ( Vector3::Distance(tempPos, targetPosition) < 0.2f)
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

NCL::CSC8503::BehaviourGameObject::~BehaviourGameObject()
{
	delete root;
}

void NCL::CSC8503::BehaviourGameObject::Update(float dt)
{
	root->Execute(dt);
}
