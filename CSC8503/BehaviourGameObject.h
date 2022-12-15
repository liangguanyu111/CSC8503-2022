#pragma once
#include "GameObject.h"
#include "BehaviourAction.h"
#include"BehaviourSelector.h"
#include"BehaviourSequence.h"
namespace NCL {
    namespace CSC8503 {

        class BehaviourGameObject : public GameObject {
        public:
            BehaviourGameObject();
            ~BehaviourGameObject();
            

        protected:
           BehaviourSelector* rootNode;
        };
    }
}

