#include "LedControlMS.h"
#define NBR_MTX 2 
LedControl lc=LedControl(12,11,10, NBR_MTX);
int snakeLength = 3;
int values = snakeLength * 2;
int snakeValues[6];
//up
int btnx1 = 2;
//down
int btnx0 = 4;
//right
int btny1 = 3;
//left
int btny0 = 5;
int matrix = 8; 
int delayTime = 350;
int fx;
int fy;
int xv1 = 1;
int xv0 = 0;
int yv1 = 0;
int yv0 = 0;

int topPosX = 4;
int topPosY = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  Serial.println("Setup");
  pinMode(btnx1,INPUT_PULLUP);
  pinMode(btnx0,INPUT_PULLUP);
  pinMode(btny0,INPUT_PULLUP);
  pinMode(btny1,INPUT_PULLUP);
for (int i=0; i< NBR_MTX; i++){
    lc.shutdown(i,false);
  /* Set the brightness to a medium values */
    lc.setIntensity(i,8);
  /* and clear the display */
    lc.clearDisplay(i);
    
  }
  randomSeed(analogRead(0));
}

void movement(){
      // skubber alle værdier i arrayet en plads ned
    for (int i = snakeLength*2;i>2;i= i-2){
        snakeValues[i] = snakeValues[i-2];
        snakeValues[i-1] = snakeValues[i-3];
 
    }
    if(topPosX > 7){topPosX = 0;}
    if (topPosY > 7){topPosY = 0;}
    if(topPosX < 0){topPosX = 7;}
    if (topPosY < 0){topPosY = 7;}
    if (topPosY == fy && topPosX == fx){
    makeFruit();
    if (delayTime > 0){
    delayTime -= 10;
    }
    }
    snakeValues[1] = topPosX;
    Serial.print("topPos changed in movement");
    Serial.println("");
    snakeValues[2] = topPosY;

  }

void printscr(){
  // prints the position of the snake to the matrix
    for (int i = snakeLength*2;i > 0;i = i - 2){
        lc.setLed(0,snakeValues[i],snakeValues[i-1],true);
        
}
lc.setLed(0,fy,fx,true);
}

void changeDir(){
    // reset the directions
    xv1 = 0;
    xv0 = 0;
    yv1 = 0;
    yv0 = 0;
    //check which button is pressed down and update direction accordenly
 
    if(digitalRead(btnx1)==!HIGH){
    topPosX = topPosX + 1;
    xv1 = 1;
    Serial.println("X1 KNAPPEN ER NEDE");
    }
    if(digitalRead(btnx0)==!HIGH){
    topPosX = topPosX - 1;
    xv0 = 1;
    Serial.println("X0 KNAPPEN ER NEDE");
    }
    if(digitalRead(btny1)==!HIGH){
    topPosY = topPosY + 1;
    yv1 = 1;
    Serial.println("Y1 KNAPPEN ER NEDE");
    }
    if(digitalRead(btny0)==!HIGH){
    topPosY = topPosY - 1;
    yv0 = 1;
    Serial.println("Y0 KNAPPEN ER NEDE");
    }
}

void noPress(){
  // change the values in the direction we are moving, if no button is pressed
    if(xv1 == 1){
      topPosX+=1;
      Serial.print("topPosX changed to: ");
      Serial.println(topPosX);
      }
    if(xv0 == 1){
      topPosX-=1;
      Serial.print("topPosX changed to: ");
      Serial.println(topPosX);
    }
    if(yv1 == 1){
      topPosY+=1;
      Serial.print("topPosY changed to: ");
      Serial.println(topPosY);
    }
    if(yv0 == 1){
      topPosY-=1;
      Serial.print("topPosY changed to: ");
      Serial.println(topPosY);
      }
    
        
}

void makeFruit(){
  // Define the position of the new "objective"
  fx = random(7);
  fy = random(7);
  }

void loop() {
  //Move the snake to a new position
    movement();
  //Update the screen
    printscr();
    // change the direction if a button is pressed
    if(digitalRead(btnx1)==!HIGH || digitalRead(btnx0)==!HIGH ||digitalRead(btny1)==!HIGH||digitalRead(btny0)==!HIGH){
    changeDir();
    }
    else{
    // noPress makes sure to keep the snake moving, even when no button is pressed.
    noPress();
    }
    // determines the speed of the game
    delay(delayTime + 100);
    lc.clearDisplay(0);

}
