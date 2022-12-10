#include <ps4.h>
#include <PS4Controller.h>
#include <ps4_int.h>

unsigned long lastTimeStamp = 0;

void notify()
{
  char messageString[200];
  sprintf(messageString, "%4d,%4d,%4d,%4d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d",
  PS4.LStickX(),
  PS4.LStickY(),
  PS4.RStickX(),
  PS4.RStickY(),
  PS4.Left(),
  PS4.Down(),
  PS4.Right(),
  PS4.Up(),
  PS4.Square(),
  PS4.Cross(),
  PS4.Circle(),
  PS4.Triangle(),
  PS4.L1(),
  PS4.R1(),
  PS4.L2(),
  PS4.R2(),  
  PS4.Share(),
  PS4.Options(),
  PS4.PSButton(),
  PS4.Touchpad(),
  PS4.Charging(),
  PS4.Audio(),
  PS4.Mic(),
  PS4.Battery());

  //Only needed to print the message properly on serial monitor. Else we dont need it.
  /*if (millis() - lastTimeStamp > 50)
  {
    Serial.println(messageString);
    lastTimeStamp = millis();
  }*/

  controls();
}

void onConnect()
{
  Serial.println("Connected!.");
}

void onDisConnect()
{
  Serial.println("Disconnected!.");    
}

void setup() 
{
  Serial.begin(115200);
  PS4.attach(notify);
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();
  Serial.println("Ready.");
}

void loop() 
{
  
}

void controls(){
  if(PS4.Cross()){
    Serial.println("X");
    }
  if(PS4.Circle()){
    Serial.println("O");
    }
  if(PS4.Square()){
    Serial.println("▢");
    }
  if(PS4.Triangle()){
    Serial.println("△");
    }
  if(PS4.Up()){
    Serial.println("↑");
    }
  if(PS4.Down()){
    Serial.println("↓");
    }
  if(PS4.Left()){
    Serial.println("←");
    }
  if(PS4.Right()){
    Serial.println("→");
    }
  if(PS4.L1()){
    Serial.println("L1");
    }
  if(PS4.R1()){
    Serial.println("R1");
    }
  if(PS4.L2()){
    Serial.println("L2");
    }
  if(PS4.R2()){
    Serial.println("R2");
    }
  if(PS4.Touchpad()){
    Serial.println("Touchpad");
    }
  if(PS4.Share()){
    Serial.println("Share");
    }
  if(PS4.Options()){
    Serial.println("Options");
    }
  if(PS4.PSButton()){
    Serial.println("PS Button");
    }
  }
