#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/Keyboard.hpp>
#include <webots/GPS.hpp>
#include <webots/InertialUnit.hpp>



#define TIME_STEP 64
using namespace webots;

int main(int argc, char **argv) {
  Robot *robot = new Robot();
  Keyboard kb;
  DistanceSensor *ds[2];
  
  char dsNames[2][10] = {"ds_right", "ds_left"};
  for (int i = 0; i < 2; i++) {
    ds[i] = robot->getDistanceSensor(dsNames[i]);
    ds[i]->enable(TIME_STEP);
  }
  Motor *lr;
  lr=robot->getMotor("linear");
  Motor *lr2;
  lr2=robot->getMotor("linear2");
  Motor *lr3;
  lr3=robot->getMotor("linear3");


  

  Motor *wheels[4];
  char wheels_names[4][8] = {"wheel1", "wheel2", "wheel3", "wheel4"};
  for (int i = 0; i < 4; i++) {
    wheels[i] = robot->getMotor(wheels_names[i]);
    wheels[i]->setPosition(INFINITY);
    wheels[i]->setVelocity(0.0);
  }
  
  kb.enable(TIME_STEP);
  double leftSpeed = 0.0;
  double rightSpeed = 0.0;
  double linear=0.0;
  double linear2=0.0;
  //double linear3=0.0;
  while (robot->step(TIME_STEP) != -1) {
    int key=kb.getKey();
    
    if (key==315){
    leftSpeed = 3.0;
    rightSpeed = 3.0;
    } else if (key==317){
    leftSpeed = -3.0;
    rightSpeed = -3.0;
    }else if (key==316){
    leftSpeed = 1.5;
    rightSpeed = -1.5;
    }else if (key==314){
    leftSpeed = -1.5;
    rightSpeed = 1.5;
    }else {
    leftSpeed = 0.0;
    rightSpeed = 0.0;
    }
    // std::cout<<ds[0]->getValue()<<"=Right Sensor"<<std::endl;
    // std::cout<<ds[1]->getValue()<<"=Left Sensor"<<std::endl;
    wheels[0]->setVelocity(leftSpeed);
    wheels[1]->setVelocity(rightSpeed);
    wheels[2]->setVelocity(leftSpeed);
    wheels[3]->setVelocity(rightSpeed);
    if (key==87 && linear<0.19){
    linear += 0.005;
    } else if (key==83 && linear>0){
    linear += -0.005;
    }else {
    linear+=0;
    }
    lr->setPosition(linear);
    // std::cout<<key<<std::endl;
    if (key==65){
    linear2 += 0.005;
   
    } else if (key==68){
    linear2 += -0.005;
    
    }else {
    lr2+=0;
    }
    lr2->setPosition(linear2);
    lr3->setPosition(-1*linear2);
    
  }
  delete robot;
  return 0;  // EXIT_SUCCESS
}