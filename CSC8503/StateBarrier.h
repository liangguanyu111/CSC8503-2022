#pragma once
#include"GameObject.h"

namespace NCL {
    namespace CSC8503 {
        class StateMachine;
        class StateBarrier : public GameObject {
        public:
            StateBarrier();
            ~StateBarrier();

            void Update(float dt);

            void ActiveBarrier(Vector3 start, Vector3 end);

            bool active;
        protected:
            StateMachine* stateMachine;
            void Active();
            Vector3 startPos;
            Vector3 endPos;
            bool moveDirection;
            float moveSpeed;
        };
    }
}
