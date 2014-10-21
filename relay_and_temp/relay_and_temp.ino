#include <RFduinoBLE.h>

int led1=2;
int led2=3;

void setup() {
  Serial.begin(9600);
  Serial.print("begin");
  
  RFduinoBLE.advertisementData="relay,temp";
  RFduinoBLE.deviceName="3PG relay";
  
  // (generated with http://www.uuidgenerator.net)
  //RFduinoBLE.customUUID = "2600";
  
  for(int i=2;i<7;i++)
    {
        pinMode(i, OUTPUT);
    }
  
  // start BLE stack
  RFduinoBLE.begin();

}

void loop() {
  //sample once per second
  RFduino_ULPDelay( SECONDS(1));
  readTemperature();
}

void RFduinoBLE_onConnect(){
  Serial.println("connected, bring led to white");
}

void RFduinoBLE_onDisconnect(){
  Serial.println("on disconnect");
}

void RFduinoBLE_onReceive(char *data,int len){
  Serial.print("data");
  
    uint8_t d=data[0];

    Serial.print(" command:");
    Serial.println(d);
    
    if(d>0){
      digitalWrite(led1,HIGH);
      digitalWrite(led2,LOW);
    }else{
      digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);      
    }
  
}

void readTemperature(){
  float temp=RFduino_temperature(CELSIUS);
  
  //send data
  RFduinoBLE.sendFloat(temp);
}
