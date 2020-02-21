
#include <PS2X_lib.h>//include library code
//************************************************************


/*
  Select modes of PS2 controller:
  - pressures = analog reading of push-butttons
  - rumble    = motor rumbling
  uncomment 1 of the lines for each mode selection
*/
//const int rumble = false;
//const int pressures = false;

PS2X ps2x; //create PS2 Controller object
int error = 0; 
byte type = 0;
byte vibrate = 0;
int fspeed;//forward speed


int L_EN_FOR_ONE=2;
int R_EN_FOR_ONE=3;
int L_PWM_FOR_ONE=4;
int R_PWM_FOR_ONE=5;
int L_EN_FOR_TWO=6;
int R_EN_FOR_TWO=7;
int L_PWM_FOR_TWO=8;
int R_PWM_FOR_TWO=9;

void setup() {
 
  //sets all DC motors pins as OUTPUTs
 pinMode(L_EN_FOR_ONE,OUTPUT);
pinMode(R_EN_FOR_ONE,OUTPUT);
pinMode(L_PWM_FOR_ONE,OUTPUT);
pinMode(R_PWM_FOR_ONE,OUTPUT);
pinMode(L_EN_FOR_TWO,OUTPUT);
pinMode(R_EN_FOR_TWO,OUTPUT);
pinMode(L_PWM_FOR_TWO,OUTPUT);
pinMode(R_PWM_FOR_TWO,OUTPUT);

digitalWrite(L_EN_FOR_ONE,HIGH);
digitalWrite(R_EN_FOR_ONE,HIGH);
digitalWrite(L_EN_FOR_TWO,HIGH);
digitalWrite(R_EN_FOR_TWO,HIGH);


Serial.begin(57600);
  
 error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

 // Check for error
 if(error == 0){
  Serial.println("Found Controller, configured successful");

}
 else if(error == 1)
  Serial.println("No controller found, check wiring or reset the Arduino");
   
 else if(error == 2)
  Serial.println("Controller found but not accepting commands");
  
 else if(error == 3)
  Serial.println("Controller refusing to enter Pressures mode, may not support it.");
   
 // Check for the type of controller
 type = ps2x.readType();
 switch(type) {
  case 0:
    Serial.println("Unknown Controller type");
    break;
  case 1:
    Serial.println("DualShock Controller Found");
    break;
  case 2:
    Serial.println("GuitarHero Controller Found");
    break;
  }
}





void loop() {
  ps2x.read_gamepad();
  if (ps2x.Analog(PSS_LY) == 128) analogWrite(L_PWM_FOR_ONE, 0);
  
  if (ps2x.Analog(PSS_LY) == 128) analogWrite(R_PWM_FOR_ONE, 0);
  
  if (ps2x.Analog(PSS_LY) == 128) analogWrite(L_PWM_FOR_TWO, 0);
  
  if (ps2x.Analog(PSS_LY) == 128) analogWrite(R_PWM_FOR_TWO, 0);

if(ps2x.ButtonPressed(PSB_L1)) 
    {
      
      
      
     }
//if(ps2x.ButtonPressed(PSB_L2)) digitalWrite(8, LOW);//Turn off forward lights
//if(ps2x.ButtonPressed(PSB_R1)) digitalWrite(A2, HIGH);//Turn on buzzer
//if(ps2x.ButtonPressed(PSB_R2)) digitalWrite(A2, LOW);//Turn off buzzer


  fspeed = map(ps2x.Analog(PSS_LY), 0, 127, 255, 0);
  


  
  
  if (ps2x.Analog(PSS_LY) >128) { //MOVE BACK
    fspeed = map(ps2x.Analog(PSS_LY), 129, 255, 0, 255);
  analogWrite(R_PWM_FOR_ONE,fspeed);
  analogWrite(L_PWM_FOR_ONE,0);
  analogWrite(R_PWM_FOR_TWO,0);
  analogWrite(L_PWM_FOR_TWO,fspeed);
  Serial.println("BACK");
  Serial.println(fspeed);
  }



  if (ps2x.Analog(PSS_LY) < 128) { //MOVE FWD
    fspeed = map(ps2x.Analog(PSS_LY), 0, 127, 255, 0);
    analogWrite(R_PWM_FOR_ONE,0);
    analogWrite(L_PWM_FOR_ONE,fspeed);
    analogWrite(R_PWM_FOR_TWO,fspeed);
    analogWrite(L_PWM_FOR_TWO,0);
    Serial.println(fspeed);
    Serial.println("FORWARD");
  }


  
  if (ps2x.Analog(PSS_LX) < 128) { //TURN LEFT
    fspeed = map(ps2x.Analog(PSS_LX), 0, 127, 255, 0);
   analogWrite(R_PWM_FOR_ONE,0);
  analogWrite(L_PWM_FOR_ONE,fspeed);
  analogWrite(R_PWM_FOR_TWO,0);
  analogWrite(L_PWM_FOR_TWO,0);
   Serial.println("LEFT");
    Serial.println(fspeed);
  }


  
  if (ps2x.Analog(PSS_LX) > 128) { //TURN RIGHT
    fspeed = map(ps2x.Analog(PSS_LX), 129, 255, 0, 255);
    analogWrite(R_PWM_FOR_ONE,0);
  analogWrite(L_PWM_FOR_ONE,0);
  analogWrite(R_PWM_FOR_TWO,fspeed);
  analogWrite(L_PWM_FOR_TWO,0);
     Serial.println("RIGHT");
      Serial.println(fspeed);
  }


  
  if (ps2x.Analog(PSS_RX) > 128) { //TURN HARD RIGHT
    fspeed = map(ps2x.Analog(PSS_RX), 129, 255, 0, 255);
     
     analogWrite(R_PWM_FOR_ONE,0);
  analogWrite(L_PWM_FOR_ONE,fspeed);
  analogWrite(R_PWM_FOR_TWO,fspeed);
  analogWrite(L_PWM_FOR_TWO,0);
     
     Serial.println("HARD RIGHT");
      Serial.println(fspeed);
  }



  
  if (ps2x.Analog(PSS_RX) < 128) { //TURN HARD LEFT
    fspeed = map(ps2x.Analog(PSS_RX), 0, 127, 255, 0);
   
   analogWrite(R_PWM_FOR_ONE,0);
  analogWrite(L_PWM_FOR_ONE,fspeed);
  analogWrite(R_PWM_FOR_TWO,fspeed);
  analogWrite(L_PWM_FOR_TWO,0);
   Serial.println("HARD LEFT");
    Serial.println(fspeed);
  }



  
  if ((ps2x.Analog(PSS_RY) > 128) && (ps2x.Analog(PSS_RX) < 128)) { //TURN BACK LEFT
    fspeed = map(ps2x.Analog(PSS_RY), 129, 255, 0, 255);
            analogWrite(R_PWM_FOR_ONE,(fspeed/2));
            analogWrite(L_PWM_FOR_ONE,0);
            analogWrite(R_PWM_FOR_TWO,0);
            analogWrite(L_PWM_FOR_TWO,fspeed);
           
            Serial.println("BACK LEFT");
            Serial.println(fspeed);
  
  }


  
  if ((ps2x.Analog(PSS_RY) > 128) && (ps2x.Analog(PSS_RX) > 128)) { //TURN BACK RIGHT
    fspeed = map(ps2x.Analog(PSS_RY), 129, 255, 0, 255);
    
    analogWrite(R_PWM_FOR_ONE,fspeed);
    analogWrite(L_PWM_FOR_ONE,0);
    analogWrite(R_PWM_FOR_TWO,0);
    analogWrite(L_PWM_FOR_TWO,(fspeed/2));
    
    Serial.println("BACK RIGHT");
     Serial.println(fspeed);
  } 

   if(ps2x.ButtonPressed(PSB_L1)) 
    {
      
    analogWrite(R_PWM_FOR_ONE,0);
    analogWrite(L_PWM_FOR_ONE,fspeed);
    analogWrite(R_PWM_FOR_TWO,fspeed);
    analogWrite(L_PWM_FOR_TWO,0);
    Serial.println("HARD LEFT");
    Serial.println(fspeed);
      
    }

    
    if(ps2x.ButtonPressed(PSB_R1)) 
    {
      
      
     analogWrite(R_PWM_FOR_ONE,0);
     analogWrite(L_PWM_FOR_ONE,fspeed);
     analogWrite(R_PWM_FOR_TWO,fspeed);
     analogWrite(L_PWM_FOR_TWO,0);
     
      Serial.println("HARD RIGHT");
      Serial.println(fspeed);
      
    }



  
  if (fspeed < 40) { //STOP 
    analogWrite(R_PWM_FOR_ONE,0);
    analogWrite(L_PWM_FOR_ONE,0);
    analogWrite(R_PWM_FOR_TWO,0);
    analogWrite(L_PWM_FOR_TWO,0);

    Serial.println("STOP");
  }


  if(ps2x.Button(PSB_PAD_UP)) {
      
    analogWrite(R_PWM_FOR_ONE,0);
    analogWrite(L_PWM_FOR_ONE,255);
    analogWrite(R_PWM_FOR_TWO,255);
    analogWrite(L_PWM_FOR_TWO,0);
   
    Serial.println("FORWARD");
      }
      // TURN RIGHT
      if(ps2x.Button(PSB_PAD_RIGHT)){

      analogWrite(R_PWM_FOR_ONE,0);
      analogWrite(L_PWM_FOR_ONE,0);
      analogWrite(R_PWM_FOR_TWO,255);
      analogWrite(L_PWM_FOR_TWO,0);
      Serial.println("RIGHT");

      }
      // TURN LEFT
      if(ps2x.Button(PSB_PAD_LEFT)){
       
      analogWrite(R_PWM_FOR_ONE,0);
      analogWrite(L_PWM_FOR_ONE,255);
      analogWrite(R_PWM_FOR_TWO,0);
      analogWrite(L_PWM_FOR_TWO,0);
      Serial.println("LEFT");
      
      }
      // MOVE BACK
      if(ps2x.Button(PSB_PAD_DOWN)){
         
          analogWrite(R_PWM_FOR_ONE,255);
          analogWrite(L_PWM_FOR_ONE,0);
          analogWrite(R_PWM_FOR_TWO,0);
          analogWrite(L_PWM_FOR_TWO,255);
          Serial.println("BACK");
          
      }  
      if (!ps2x.Button(PSB_PAD_DOWN) && !ps2x.Button(PSB_PAD_UP) && !ps2x.Button(PSB_PAD_RIGHT) && !ps2x.Button(PSB_PAD_LEFT)) {
        analogWrite(L_PWM_FOR_ONE, 0);
        analogWrite(R_PWM_FOR_ONE, 0);

        analogWrite(L_PWM_FOR_TWO, 0);
        analogWrite(R_PWM_FOR_TWO, 0);
        
      }

 
  delay(50);
}
