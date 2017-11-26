//
//  Physics.h
//  CEngine
//
//  Created by Sravan Karuturi on 10/31/17.
//

#ifndef Physics_h
#define Physics_h

#include <vector>
#include "glm/glm.hpp"

/* Small 2D Physics Component */

class PhysicsComponent{
  
    float mass = 1.0f;
    
    float sizeX = 1.0f;
    float sizeY = 1.0f;
    
    glm::vec2 position;
    
    bool affectedByGravity = true;
    // We are using a gravity of -10.0f;
    
private:
    
    glm::vec2 velocity;
    glm::vec2 acceleration;
    
public:
    
    /* Constructor. */
    
    PhysicsComponent(float _mass, float _sizeX, float _sizeY, float _posX, float _posY){
        
        mass = _mass;
        
        sizeX = _sizeX;
        sizeY = _sizeY;
        
        position = glm::vec2(_posX, _posY);
        
        velocity = glm::vec2(0.0f, 0.0f);
        
        if ( affectedByGravity ){
            acceleration = glm::vec2(0.0f, -10.0f);
        }else{
            acceleration = glm::vec2(0.0f, 0.0f);
        }
        
    }
    
    ~PhysicsComponent(){
        
    }
    
    void Update(float deltaTime){
        
        // Check if it collides with another physicsbody here.. and update it only when it doesn't.
        
        velocity += acceleration * deltaTime;
        position += velocity * deltaTime;
        
    }
    
    void ApplyForce(float _forceX, float _forceY){
        
        glm::vec2 force = glm::vec2(_forceX, _forceY);
        acceleration += force/mass;
        
    }
    
    
    
};

class Physics{
  
    // A singleton class for the Physics world.
    // We call Physics .. Update on every tick.
    // We have a pointer to Entity class in the Physics.
    
    static Physics * world;
    
    std::vector<PhysicsComponent *> bodies;
    
private:
    
    Physics(){
        if ( nullptr == world ){
            world = this;
        }else{
            // World already exists... This shouldn't be called.
        }
    }
    
public:
    
    void Update(float deltaTime){
        
        // We update everything by the delta time.
        
        // We can maybe thread this.. And sync at the end.. But is it worth it?
        for ( std::vector<PhysicsComponent *>::iterator it = bodies.begin(); it != bodies.end(); it++ ){
            
            (*it)->Update(deltaTime);
            
        }
        
    }
    
};

#endif /* Physics_h */
