#include "PhysicsObject.h"
#include "PhysicsSystem.h"
#include "Transform.h"
using namespace NCL;
using namespace CSC8503;

PhysicsObject::PhysicsObject(Transform* parentTransform, const CollisionVolume* parentVolume)	{
	transform	= parentTransform;
	volume		= parentVolume;

	inverseMass = 1.0f;
	elasticity	= 0.8f;
	friction	= 0.8f;


	isStatic = false;
}

PhysicsObject::~PhysicsObject()	{

}

void PhysicsObject::ApplyAngularImpulse(const Vector3& force) {
	isStatic = false;
	angularVelocity += inverseInteriaTensor * force;
}

void PhysicsObject::ApplyLinearImpulse(const Vector3& force) {
	isStatic = false;
	linearVelocity += force * inverseMass;
}

void PhysicsObject::AddForce(const Vector3& addedForce) {
	isStatic = false;
	force += addedForce;
}

void PhysicsObject::AddForceAtPosition(const Vector3& addedForce, const Vector3& position) {
	isStatic = false;
	Vector3 localPos = position - transform->GetPosition();

	force  += addedForce;
	torque += Vector3::Cross(localPos, addedForce);
}

void PhysicsObject::AddTorque(const Vector3& addedTorque) {
	isStatic = false;
	torque += addedTorque;
}

void PhysicsObject::ClearForces() {
	force				= Vector3();
	torque				= Vector3();
}

void PhysicsObject::InitCubeInertia() {
	Vector3 dimensions	= transform->GetScale();

	Vector3 fullWidth = dimensions * 2;

	Vector3 dimsSqr		= fullWidth * fullWidth;

	inverseInertia.x = (12.0f * inverseMass) / (dimsSqr.y + dimsSqr.z);
	inverseInertia.y = (12.0f * inverseMass) / (dimsSqr.x + dimsSqr.z);
	inverseInertia.z = (12.0f * inverseMass) / (dimsSqr.x + dimsSqr.y);
}

void PhysicsObject::InitSphereInertia() {
	float radius	= transform->GetScale().GetMaxElement();
	float i			= 2.5f * inverseMass / (radius*radius);

	inverseInertia	= Vector3(i, i, i);
}

void PhysicsObject::UpdateInertiaTensor() {
	Quaternion q = transform->GetOrientation();
	
	Matrix3 invOrientation	= Matrix3(q.Conjugate());
	Matrix3 orientation		= Matrix3(q);

	inverseInteriaTensor = orientation * Matrix3::Scale(inverseInertia) *invOrientation;
}


//待优化
void PhysicsObject::CheckObjectStatic(Vector3 pos, Vector3 velocity)
{
	if (latestPoss.size() == 0&& latestVelocitys.size()==0)
	{
		lastFramePos = this->transform->GetPosition();
		lastFrameVelocity = this->GetLinearVelocity();
	}

	if (latestPoss.size() < 6 || latestVelocitys.size() < 6)
	{
		latestPoss.push(pos-lastFramePos);
		latestVelocitys.push(velocity-lastFrameVelocity);
		return;
	}
	Vector3 posOffset(0, 0, 0);
	Vector3 velocitysOffset(0, 0, 0);
	latestPoss.pop();
	latestPoss.push(pos-lastFramePos);
	latestVelocitys.pop();
	latestVelocitys.push(velocity-lastFrameVelocity);

	for (int i = 0; i < latestPoss.size(); i++)
	{
		posOffset += latestPoss.front();
		latestPoss.push(latestPoss.front());
		latestPoss.pop();
	}
	
	for (int i = 0; i < latestVelocitys.size(); i++)
	{
		velocitysOffset += latestVelocitys.front();
		latestVelocitys.push(latestVelocitys.front());
		latestVelocitys.pop();
	}
	lastFramePos = pos;
	lastFrameVelocity = velocity;

	//?5
	if (posOffset.y >= -0.003&& posOffset.y <= -0.002&& lastFrameVelocity.y>=0)
	{
		isStatic = true;
	}
}