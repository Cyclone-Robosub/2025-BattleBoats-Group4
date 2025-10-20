// C++ code
//

/* hi! this code is embarassing, so read at your own disgression
plz feel free to fix any gross things, thanks*/

//Global Var deffinitions
//definition of the vars assigned to the front distance and side distance
int cm = 0;
int side = 0;
//defitinion of the vars assigned to the threasholds
int turn = 20; //front threshold (how close is close enough to the front wall to make a turn)
int sideWallRange = 30; //side threshold (should the side reading be less than this threshold, it's ok to make a left turn)
int tooClose = 5; //to be implemented (do we want the boat to go backwards when it's too close to a front wall?)

//assigning the pins to the motor driver action
int starFor = 12; //pin D12 on the nano, in1 on the motor driver
int starBack = 11; //pin D11 on the nano, in2 on the motor driver
int portFor = 10; //pin D10 on the nano, in3 on the motor driver
int portBack = 9; //pin D9 on the nano, in4 on the motor driver


//Someone else's code (either tinker cad, or leadership's. I forgor)
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

//Motion command functions
void leftTurn()
{
  digitalWrite(starFor,HIGH);
  digitalWrite(starBack,LOW);
  digitalWrite(portFor,LOW);
  digitalWrite(portBack,HIGH);
}
void rightTurn()
{
  digitalWrite(starFor,LOW);
  digitalWrite(starBack,HIGH);
  digitalWrite(portFor,HIGH);
  digitalWrite(portBack,LOW);
}
void forwardMotion()
{
  digitalWrite(starFor,HIGH);
  digitalWrite(starBack,LOW);
  digitalWrite(portFor,HIGH);
  digitalWrite(portBack,LOW);
}
void backwardsMotion()
{
  digitalWrite(starFor,LOW);
  digitalWrite(starBack,HIGH);
  digitalWrite(portFor,LOW);
  digitalWrite(portBack,HIGH);
}

void setup()
{
  //Input1 (starbord motor, forward) pin D12 to in1
  pinMode(starFor,OUTPUT);
  //Input2 (starbord motor, backwards) pin D11 to in2
  pinMode(starBack,OUTPUT);
  //Input3 (port motor, forward) pin D10 to in3
  pinMode(portFor,OUTPUT);
  //Input4 (port motor, backwards) pin D9 to in4
  pinMode(portBack,OUTPUT);
  //Serial Monitor set up for sensor testing purposes
  Serial.begin(9600);
}


//Main loop
void loop()
{
  //The reading code (it also prints for testing purposes)
  delay(100);// measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(3, 2); //call to front sensor
  Serial.print(cm);
  Serial.print("cm, ");
  side = 0.01723 * readUltrasonicDistance(5,4); //call to starboard sensor
  Serial.print(side);
  Serial.println("cm");
  
  //The motion code
  //The turning code assumes that the sensor is starbord (it is)
  if(cm < turn) //we're close enough to a forward wall to make a turn
  {
    if(side > sideWallRange) //the starbord sensor "sees" a wall on the right side
    {
      leftTurn();
    }
    else //the starboard sensor does not "see" a wall on the right side
    {
      rightTurn();
    }
    
  }
  else //there's no immenant forward wall
  {
    forwardMotion();
  }
  
}
