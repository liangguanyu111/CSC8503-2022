#pragma once
#include"TutorialGame.h"
#include"GameObject.h"


namespace NCL 
{
    namespace CSC8503
    {
        class Player : public GameObject 
        {
        public:
            Player();
            ~Player();

            void Update(float dt);

            void OnCollisionBegin(GameObject* otherObject) {
                if (otherObject->GetName() == "Bonus")
                {
                    otherObject->SetActive(false);
                    NCL::CSC8503::TutorialGame::AddScore();
                }
            }

        };
    }
}