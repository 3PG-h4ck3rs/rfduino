#include <RFduinoBLE.h>

int led1=2;
int led2=3;
int led3=4;

void setup() {
  Serial.begin(9600);
  Serial.print("begin");
  
  RFduinoBLE.advertisementData="temp,rgb";
  RFduinoBLE.deviceName="3PG temp/led";
  
  // (generated with http://www.uuidgenerator.net)
  //RFduinoBLE.customUUID = "2600";
  
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  
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
  analogWrite(led1,255);
  analogWrite(led2,255);
  analogWrite(led3,255);
}

void RFduinoBLE_onDisconnect(){
  Serial.println("on disconnect");
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

}

void RFduinoBLE_onReceive(char *data,int len){
  Serial.print("data");
  
  if(len>=3){
    uint8_t r=data[0];
    uint8_t g=data[1];
    uint8_t b=data[2];

    Serial.print(" r:");
    Serial.print(r);
    Serial.print(" g:");
    Serial.print(g);
    Serial.print(" b:");
    Serial.println(b);
    
    analogWrite(led1,r);
    analogWrite(led2,g);
    analogWrite(led3,b);
  }
}

void readTemperature(){
  float temp=RFduino_temperature(CELSIUS);
  
  //send data
  RFduinoBLE.sendFloat(temp);
}
