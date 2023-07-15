const unsigned long onDurationMs = 900000; // 15 Minutes
//const unsigned long onDurationMs = 10000; // 10 Seconds
//unsigned long onDurationSecs = onDurationMs/1000;
//unsigned long onDurationMins = onDurationSecs/60;

const unsigned long offDurationMs = 10800000; // 3 Hours
//const unsigned long offDurationMs = 15000; // 15 Seconds
//unsigned long offDurationSecs = offDurationMs/1000;
//unsigned long offDurationMins = offDurationSecs/60;

unsigned long onTimeMs = 0;
unsigned long offTimeMs = 0;
int pumpState = LOW;
int relay = 12; // Plug the relay into Digital Pin 12

void setup(){
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
}

void loop(){
 if( pumpState ==LOW ){ 
   if( (millis()-offTimeMs) >= offDurationMs){
      pumpState = HIGH;
      onTimeMs=millis();
      
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
      
      digitalWrite(LED_BUILTIN,pumpState);
      digitalWrite(relay, HIGH); // Turn the relay on
   }
 }else{   
    if( (millis()-onTimeMs) >= onDurationMs){
      pumpState = LOW;
      offTimeMs=millis();
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
      
      digitalWrite(LED_BUILTIN,pumpState);
      digitalWrite(relay, LOW); // Turn the relay Off
    }
 }
   
}
