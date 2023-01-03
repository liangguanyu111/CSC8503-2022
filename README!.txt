GitHub Address : https://github.com/liangguanyu111/CSC8503-2022

****Game Introduction****
	1.In the menu page, you can see option of single game, mutiple game, and game introdction. use up and down key to swap between options,
	 and left and right to choose this option or back to previous menu(exp. Game introduction option).(mutile game is not working)
	2.In the game, use up,down,left,right to controll the goat to collect bonus on the map(green shpere), each bonus will add one score, you have
	180 seconds to collect 15 score to trigger actived barrier or lose the game. All the npc in the map will also collect bonus, the green one will add
	your score,but the red one will minus your socre. This is basic gameplay, When time runs out, you can check your score.

****Code****
1.Player MoveMent

	1.1please reference to TutorialGame::LockedObjectMovement() and Camera::UpdateCamera(float dt)

	Firstly,I achieved a TPS camera which will rotate aournd the goat and when the player press up/down/right/left the the model's direction will
 	rotate to the direction up/down/right/left of the camera and Continuously apply force on this direction.

2.Collision
	Most of the objects were AABB volumes due to some of the collisions in the game, but I tried to implement all of them, and a few did well,such as OBB-OBB, 
	but most collisions were not added to game flow to make it fewer bug.You can check them by looking at the collisions of specific objects. I put these objects in the mid sky, 
	press p to unlock the camera and the press q and left click to choose object(object will turn to green if be choosen), and right cilck to add force to make some collision.
	
	2.1please reference to collisionDetection.cpp,Including AABB-AABB,obb-obb,sphere-sphere,obb-shpere,AABB-sphere,sphere-Capsule, 
	COLLISONDETECTION::ObjectIntersection(), COLLISONDETECTION::AABBIntersection(),COLLISONDETECTION::SphereIntersection(),COLLISONDETECTION::AABBSphereIntersection()
	COLLISONDETECTION::OBBIntersection(),COLLISONDETECTION::OBBSphereIntersection(),COLLISONDETECTION::OBBSupport(),COLLISONDETECTION::SphereCapsuleIntersection().

	2.2 and also PhysicsSystem::ResolveSpringCollision() which apply Hooke's law to reslove spring issue. 
	2.3 LayerMask make sure some layers do not collide with each other, exp, Obstacle-Obstacle, i just skip it in dection.
3.AI
	3.1Menu
	the menu is achieve by PushDown Automata, and have IntroScreen state, GameScreen state, GameInstruction state, GameEnd state, each one have cpp file.
	3.2Grid
	The navigation of ai is achieved by grid, Check NavigationGrid::NavigationGrid(int nodeSize), the grid is declared here, Going through the grid, we will have 
	a square fence with two obstacles in the middle,and the ai can follow the point on the grid.
	3.2AI
	The green character ai is achieved by state machine,please check StateGameObject.cpp, which can patrol, ray dectect, respawn , the patrol destination is get ramdomly
	from the grid. The red character is achieved by BehaviourTree, please check BehaviourGameObject.cpp.
4Internet
	Only the Tutorial part on canvas has been completed.