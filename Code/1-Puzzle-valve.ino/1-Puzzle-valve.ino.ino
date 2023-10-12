#include <Servo.h>
#include <Random.h>

# minValValve 0 //min value of valve 
# maxValValve 0 //max value of valve
# minValFlowmeter 0 //min value to output to flowmeter
# maxValFlowmeter 250 //max value to output to flowmeter
# lock 12 //lock pin for the solution

byte psw[4]={165,200,130,40}; //this is an array which have the valve values for the solution
//You can change these values to change the code sequence


bool check[4]={false,false,false,false};  //this array check which valve is in correct position
int val[4]; //this aaray stores the analog read of each valve
byte lasers[4]={2,3,4,5}; //these are the pins of the laser emmitters
byte photodiodes[4]={A0,A1,A2,A3};  //these are the pins of the photodiodes
byte flowmeter[4]={6,7,8,9};  //these are the pins of the flowmeters (output of valves)

Servo myservo[4]; // define how many servos you're gonna use


//this function is here to setup the values before the mainprogram starts
void setup() {
  
  for(int i=0;i<4;i++){
    if(psw[i]>maxValFlowmeter){
      randomSeed(analogRead(11));
      psw[i]=random(minValFlowmeter,maxValFlowmeter);
    }
  }
  
  
  for(int i=0;i<4;i++){
    myservo[i].attach(flowmeter[i]);
    myservo[i].write(0);
  } 



  pinMode(lock,OUTPUT);
  digitalWrite(lock,LOW);

  pinMode(lasers[0],OUTPUT);
  pinMode(lasers[1],OUTPUT);
  pinMode(lasers[2],OUTPUT);
  pinMode(lasers[3],OUTPUT);
  
  digitalWrite(lasers[0],HIGH);
  digitalWrite(lasers[1],HIGH);
  digitalWrite(lasers[2],HIGH);
  digitalWrite(lasers[3],HIGH);
  

  pinMode(photodiodes[0],INPUT);
  pinMode(photodiodes[1],INPUT);
  pinMode(photodiodes[2],INPUT);
  pinMode(photodiodes[3],INPUT);
  
  pinMode(flowmeter[0],OUTPUT);
  pinMode(flowmeter[1],OUTPUT);
  pinMode(flowmeter[2],OUTPUT);
  pinMode(flowmeter[3],OUTPUT);
  
  Serial.println("System Setup...");
  delay(20);
  Serial.println("Start Process...");

  Serial.begin(9600);

}


//This is where the program starts
void loop() {
  for(int i=0;i<4;i++){
    val[i]=analogRead(photodiodes[i]);
    val[i]=map(val[i],minValValve,maxValValve,minValFlowmeter,maxValFlowmeter);
    myservo[i].write(val[i]);  
    if(val[i]==psw[i]){
      check[i]=true;
    }else{
      check[i]=false;
    }
    delay(10);
  }
  if(check[0] && check[1] && check[2] && check[3]){
    digitalWrite(lock,HIGH);
  }
  delay(20);
}
