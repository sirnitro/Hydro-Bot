const unsigned long onDurationMs = 900000; // 15 Minutes
const unsigned long offDurationMs = 10800000; // 3 Hours
unsigned long onTimeMs = 0; //Used to keep track of on time for pump
unsigned long offTimeMs = 0; //Used to keep track of off time for pump
int pumpState = HIGH; //Set pump to on to begin with
int relay = 12; // Plug the relay into Digital Pin 12
int DEBUG = 1; // 1 enables serial debug, 0 disables serial debug

void setup(){
  Serial.begin(9600); //Enabling serial communication for debug purposes
  pinMode(relay, OUTPUT); //Setting the relay pin (12) to output mode
}

void loop(){
 // Check to see if pump is off
 if( pumpState ==LOW ){ 
   if( DEBUG == 1){Serial.println("Pump Off"); }//DEBUG CODE

   // Check to see how long pump has been off, if three hours turn it on
   if( (millis()-offTimeMs) >= offDurationMs){
      pumpState = HIGH; 
      onTimeMs=millis(); // Set time for tracking the amount of time on
      digitalWrite(LED_BUILTIN,pumpState); // Turn Onboard LED On
      digitalWrite(relay, HIGH); // Turn the relay on

   //BEGIN DEBUG CODE
   if( DEBUG == 1){ 
      unsigned long onTimeSecs = onTimeMs/1000;
      unsigned long onTimeMins = onTimeSecs/60;
      unsigned long onTimeHrs = onTimeMins/60; 
      Serial.print(millis());
      Serial.print(":");
      Serial.print(onTimeSecs);
      Serial.print(":");
      Serial.print(onTimeMins);
      Serial.print(":");
      Serial.print(onTimeHrs);
      Serial.println("  Pump On");
   }
   //END DEBUG CODE 
   
   }
 //If pump is not off do the following 
 }else{   
    if( DEBUG == 1){Serial.println("Pump On");} //DEBUG CODE
// Check to see how long pump has been running, if 15 mins turn it off
    if( (millis()-onTimeMs) >= onDurationMs){
      pumpState = LOW; 
      offTimeMs=millis(); // Set time for tracking the amount of time on
      digitalWrite(LED_BUILTIN,pumpState); // Turn Onboard LED On
      digitalWrite(relay, LOW); // Turn the relay on

if( DEBUG == 1){
    //BEGIN DEBUG CODE  
      unsigned long offTimeSecs = offTimeMs/1000;
      unsigned long offTimeMins = offTimeSecs/60;
      unsigned long offTimeHrs = offTimeMins/60;
      Serial.print(millis());
            Serial.print(":");
      Serial.print(offTimeSecs);
            Serial.print(":");
      Serial.print(offTimeMins);
            Serial.print(":");
      Serial.print(offTimeHrs);
      Serial.println("  Pump Off");
    //END DEBUG CODE
}

    }
 }
   
}
