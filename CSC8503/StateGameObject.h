#pragma once
#include "GameObject.h"
#include "NavigationGrid.h"
#include "NavigationMesh.h"

namespace NCL {
    namespace CSC8503 {
        class StateMachine;
        class StateGameObject : public GameObject  {
        public:
            StateGameObject(NavigationGrid* grid);
            ~StateGameObject();
            
            void Update(float dt);

            void SetPlayer(Transform& transfom)
            {
                this->player = transfom;
            }

        protected:
            void MoveToPos(Vector3 pos);
            //Move to random point on the grid
            void Partorl(float dt);
            void DisplayPathfinding();
            //When the character is close to the player, they should run to oppsite direction.
            void Escape();

            StateMachine* stateMachine;

            float speed;

            NavigationGrid* grid;
            NavigationPath currentPath;
            Vector3 targetPosition;
            Vector3 nextPos;
            bool init = false;
            
            Transform player;
        };
    }
}
