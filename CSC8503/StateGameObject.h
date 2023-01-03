#pragma once
#include "GameObject.h"
#include "NavigationGrid.h"
#include "NavigationMesh.h"
#include "TutorialGame.h"

namespace NCL 
{
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

            void OnCollisionBegin(GameObject* otherObject) 
            {
                if (otherObject->GetName() == "Bonus")
                {
                    TutorialGame::score++;
                    otherObject->SetActive(false);
              
                }
            }

            GameWorld* GameWorld;

        protected:
            void MoveToPos(Vector3 pos);
            //Move to random point on the grid
            void Partorl(float dt);
            void DisplayPathfinding();
            //When the character is close to the player, they should run to oppsite direction.
            void Escape();

            void AvoidObstacle();
            void ReSpawn();
            void RayDetect(); //print the information of object in front of this gameObject

            StateMachine* stateMachine;

            float speed;

            NavigationGrid* grid;
            NavigationPath currentPath;
            Vector3 targetPosition;
            Vector3 nextPos;
            Vector3 initPos;
            bool init = false;
            
            Transform player;

        };
    }
}
