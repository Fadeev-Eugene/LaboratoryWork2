#include "Player.h"
#include "SecurityRoom.h"

void Player::update(){
    if (!(sr->getAnimatronics().empty())){
        alive = false;    
    }

    if (energy_lost == 0) {
        left_door = true;
        sr->openLeftDoor();
        right_door = true;
        sr->openRightDoor();
        left_light = false;
        right_light = false;
        
    } else {
        if (!left_door) {
            if (energy_lost > 0){
                energy_lost -= 1;
            } 
        }
        if (!right_door) {
            if (energy_lost > 0){
                energy_lost -= 1;
            }  
        }
        if (left_light){
            if (energy_lost > 0){
                energy_lost -= 1;
            }         
        }
        if (right_light){
            if (energy_lost > 0){
                energy_lost -= 1;
            }  
        }
        if (energy_lost > 0){
            energy_lost -= 1;
        } 
    }
}


void Player::updateDoor(char key){
    if (key == '['){
        if (left_door){
            left_door = false;
            sr->closeLeftDoor();
        } else {
            left_door = true;
            sr->openLeftDoor();
        }        
    } else {
        if (right_door){
            right_door = false;
            sr->closeRightDoor();
        } else {
            right_door = true;
            sr->openRightDoor();
        } 
    }

}


void Player::updateLight(char key){
    if (key == '{'){
        if (left_light){
            left_light = false;    
        } else {
            left_light = true;
        }       
    } else {
        if (right_light){
            right_light = false;    
        } else {
            right_light = true;
        } 
    }   
}
