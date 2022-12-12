#pragma once

using std::vector;

using namespace NCL::Maths;

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

			void SetForWard(Vector3 dir)
			{

			}

			void UpdateMatrix();
		protected:
			Matrix4		matrix;
			Quaternion	orientation;
			Vector3		position;
			Vector3     forward;


			Vector3		scale;
			Transform* parent;
			std::vector<Transform*> children;
		};
	}
}

