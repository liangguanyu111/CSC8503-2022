#pragma once

using namespace NCL::Maths;

using std::vector;

namespace NCL {
	namespace CSC8503 {
		class Transform
		{
		public:
			Transform();
			~Transform();

			Transform& SetPosition(const Vector3& worldPos);
			Transform& SetScale(const Vector3& worldScale);
			Transform& SetOrientation(const Quaternion& newOr);

			Vector3 GetPosition() const {
				return position;
			}

			Vector3 GetScale() const {
				return scale;
			}

			Quaternion GetOrientation() const {
				return orientation;
			}

			Matrix4 GetMatrix() const {
				if (parent != nullptr)
				{
					return matrix * parent->GetMatrix();
				}
				else
				{
					return matrix;
				}
			}

			void SetParent(Transform* parent)
			{
				this->parent = parent;
				parent->children.push_back(this);
			}
			
			Vector3 GetForward()
			{
				return (orientation * Vector3(0, 0, -1)).Normalised();
			}

			void Rotate(Vector3 angle)
			{
				Vector3 selfAngle =GetOrientation().ToEuler();
				SetOrientation(Quaternion::EulerAnglesToQuaternion(selfAngle.x + angle.x, selfAngle.y + angle.y, selfAngle.z + angle.z));
			}

			void RotateTo(Vector3 direction)
			{

				float temp = Vector3::Dot(GetForward(), direction) / (GetForward().Length() * direction.Length());
				temp = temp > 1 ? 1 : temp;
				temp = temp < -1 ? -1 : temp;

				float degree = (acos((temp))) / 3.1415926 * 180;
				if (Vector3::Cross(GetForward(), direction).y > 0)
				{
					degree = -degree;
				}
				Rotate(Vector3(0, -degree, 0));
			}

			void UpdateMatrix();
		protected:
			Matrix4		matrix;
			Quaternion	orientation;
			Vector3		position;


			Vector3		scale;
			Transform* parent;
			std::vector<Transform*> children;
		};
	}
}

