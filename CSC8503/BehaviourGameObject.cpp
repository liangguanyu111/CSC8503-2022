#include "BehaviourGameObject.h"
#include "PhysicsObject.h"
#include "Debug.h"

NCL::CSC8503::BehaviourGameObject::BehaviourGameObject()
{
	rootNode = new BehaviourSelector("root");

	BehaviourAction* openDoor = new BehaviourAction(" Open Door ",
		[&](float dt, BehaviourState state) -> BehaviourState
		{
			if (state == Initialise) {
			return Success;
		 }
		return state;
		}
	);

	//rootNode->AddChild(openDoor);
}

NCL::CSC8503::BehaviourGameObject::~BehaviourGameObject()
{
	delete rootNode;
}
