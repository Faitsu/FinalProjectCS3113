#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#include "Map.h"

enum EntityType { PLAYER, PROJECTILE, PLATFORM, ENEMY, BACKGROUND, PROP, LIVES };
enum EnemyType { NONE, SLEEPER, JUMPER, STALKER, WALKER, BOSS };

class Entity {
	public:  
		int *animRight = NULL;
		int *animLeft = NULL;
		int *animRightFly = NULL;
		int *animLeftFly = NULL;
		int *animIdle = NULL;
		int *animCharm = NULL;
		int *animDeath = NULL;
		int *animIndices = NULL;

		int animFrames = 0;
		int animIndex = 0;
		float animTime = 0.0f;
		float animTimer = 0.25f;

		int animCols = 0;
		int animRows = 0;

		float width = 1;
		float height = 1;

		bool fly = false;
		float flyheight = 0;
		int maxjumpcount = 1;
		int jumpcount = 0;
		float timer = 0; //for keeping track of time for things such as resets and load times

		bool idle = true;
		bool goLeft = false;
		bool isActive =true;
		bool player = false;
		bool airborne = false;
		bool recover = false;

		//for enemy to player collision
		bool collidedTop = false;
		bool collidedBottom = false;
		bool collidedLeft = false;
		bool collidedRight = false;

		//AI collision
		bool colTop = false;
		bool colTopLeft =false;
		bool colTopRight =false;
		bool colBot=false;
		bool colBotLeft=false;
		bool colBotRight=false;
		bool colLeft = false;
		bool colRight = false;

		//states for fail and success
		bool fail = false;
		bool success = false;

		//other AI stuff
		int hp = 3;
		bool chase = false;
		bool shoot = false;


		//Type of Entity (determines how we update it and such)
		EntityType entityType;
		EnemyType enemyType = NONE;

		glm::vec3 position;   
		glm::vec3 movement;
		glm::vec3 velocity;
		glm::vec3 acceleration;
		float speed = 0;      
		
		GLuint textureID; 
		
		glm::mat4 modelMatrix;
		
		Entity();       
		
		bool CheckCollision(Entity* other);
		void CheckCollisionsY(Entity *objects, int objectCount);
		void CheckCollisionsX(Entity* objects, int objectCount);

		void CheckCollisionsX(Map *map); 
		void CheckCollisionsY(Map *map);

		void CollisionMap(Map *map);

		void Shoot(Entity* player);


		void Update(float deltaTime,Entity* player, Entity *objects, int objectCount, Map *map);
		void DrawSpriteFromTextureAtlas(ShaderProgram *program, GLuint textureID, int index);
		void Render(ShaderProgram *program);
		void AI(Entity* player);
		void AIWalker();
		void AIBoss(Entity* player);
		void AIStalker(Entity* player);

};
		