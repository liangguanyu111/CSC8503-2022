#pragma once

#include"GameObject.h"
#include "BehaviourSelector.h"
#include"BehaviourSequence.h"
#include "NavigationGrid.h"

namespace NCL {
    namespace CSC8503 {

        class BehaviourGameObject : public GameObject {
        public:
            BehaviourGameObject(NavigationGrid* grid);
            ~BehaviourGameObject();
            

            void Update(float dt);

            void SetPlayer(Transform& transfom)
            {
                this->player = transfom;
            }

        protected:

            void MoveToPos(Vector3 pos);
            void Partorl(float dt);
            //When the player is Close to the character, start chase player;
            void ChasePlayer();

            NavigationGrid* grid;
            NavigationPath currentPath;
            Vector3 targetPosition;
            Vector3 nextPos;
            BehaviourSelector* root;

            Transform player;
        };
    }
}

