#pragma once
#include "GameObject.h"
#include "NavigationGrid.h"
#include "NavigationMesh.h"

namespace NCL {
    namespace CSC8503 {
        class StateMachine;
        class StateGameObject : public GameObject  {
        public:
            StateGameObject();
            ~StateGameObject();
            
            void Update(float dt);


        protected:
            void MoveLeft(float dt);
            void MoveRight(float dt);
            void MoveToPos(Vector3 pos);
            void Partorl(float dt);

            StateMachine* stateMachine;
            float counter;


            NavigationGrid grid;
            NavigationPath currentPath;
            Vector3 targetPosition;
            bool init = false;
            
            
        };
    }
}
