const unsigned long onDurationMs = 900000; // 15 Minutes
const unsigned long offDurationMs = 10800000; // 3 Hours
unsigned long onTimeMs = 0; // Used to track how long the pump has been running
unsigned long offTimeMs = 0; //Used to track how long the pump has been off
int pumpState = LOW; //Set the pump to off to begin with
int relay = 12; // Plug the relay into Digital Pin 12

void setup(){
  Serial.begin(9600); //Serial Output for debugging
  pinMode(relay, OUTPUT); 
}

void loop(){
 if( pumpState ==LOW ){ 
   if( (millis()-offTimeMs) >= offDurationMs){
      pumpState = HIGH; // Turn Pump On
      onTimeMs=millis(); // Set time that pump was turned on
      digitalWrite(LED_BUILTIN,HIGH); // Turn Board LED On
      digitalWrite(relay, HIGH); // Turn the relay on

// BEGIN SERIAL DEBUG INFORMATION
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
      Serial.println(Pump On");
// END SERIAL DEBUG INFORMATION
     

   }
 }else{   
    if( (millis()-onTimeMs) >= onDurationMs){
      pumpState = LOW; //Turn Pump off
      offTimeMs=millis(); //Set time Pump went off
      digitalWrite(LED_BUILTIN,HIGH); // Turn Board LED Off
      digitalWrite(relay, LOW); // Turn the relay Off
      
      
// BEGIN SERIAL DEBUG INFORMATION
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
// END SERIAL DEBUG INFORMATION
      

    }
 }
   
}
