// C++ code
//

/* hi! this code is embarassing, so read at your own disgression
plz feel free to fix any gross things, thanks*/

//Global Var deffinitions
//definition of the vars assigned to the front distance and side distance
int cm = 0;
int side = 0;
//defitinion of the vars assigned to the threasholds
int wallAproach = 40; //front threshold to begin to slow down when front reading is 20cm
int turn = 20; //front threshold (how close is close enough to the front wall to make a turn)
int sideWallRange = 30; //side threshold (should the side reading be less than this threshold, it's ok to make a left turn)
int tooClose = 5; //to be implemented (do we want the boat to go backwards when it's too close to a front wall?)

//assigning arduino pins to the motor driver action
int starFor = 12; //pin D12 on the nano, in1 on the motor driver
int starBack = 11; //pin D11 on the nano, in2 on the motor driver
int portFor = 10; //pin D10 on the nano, in3 on the motor driver
int portBack = 9; //pin D9 on the nano, in4 on the motor driver
int enA = 5; //pin D5 on the nano, enA on the motor driver
int enB = 6; //pin D6 on the nano, enB on the motor driver

//assigning arduino pins to sensors
int frontTrig = 3;
int frontEcho = 2;
int starTrig = 8;
int starEcho = 7;

//Someone else's code (either tinker cad)
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

//Motion command functions (helped out with leadership examples and the last minute engineers)
void leftTurn(int speed)
{
  digitalWrite(starFor,HIGH);
  digitalWrite(starBack,LOW);
  digitalWrite(portFor,LOW);
  digitalWrite(portBack,HIGH);

  analogWrite(enA,speed);
  analogWrite(enB,speed);
}
void rightTurn(int speed)
{
  digitalWrite(starFor,LOW);
  digitalWrite(starBack,HIGH);
  digitalWrite(portFor,HIGH);
  digitalWrite(portBack,LOW);

  analogWrite(enA,speed);
  analogWrite(enB,speed);
}
void forwardMotion(int speed)
{
  digitalWrite(starFor,HIGH);
  digitalWrite(starBack,LOW);
  digitalWrite(portFor,HIGH);
  digitalWrite(portBack,LOW);

  analogWrite(enA,speed);
  analogWrite(enB,speed);
}
void backwardsMotion(int speed)
{
  digitalWrite(starFor,LOW);
  digitalWrite(starBack,HIGH);
  digitalWrite(portFor,LOW);
  digitalWrite(portBack,HIGH);

  analogWrite(enA,speed);
  analogWrite(enB,speed);
}

void stopMotion()
{
  digitalWrite(starFor,LOW);
  digitalWrite(starBack,LOW);
  digitalWrite(portFor,LOW);
  digitalWrite(portBack,LOW);

  analogWrite(enA,0);
  analogWrite(enB,0);
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
  //Enable A (port motor speed control) pin D5
  pinMode(enA,OUTPUT);
  //Enable B (starbord motor control) pin D6
  pinMode(enB,OUTPUT);
  //Serial Monitor set up for sensor testing purposes
  Serial.begin(9600);
}


//Main loop
void loop()
{
  //The reading code (it also prints for testing purposes)
  delay(100);// measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(frontTrig,frontEcho); //call to front sensor
  Serial.print(cm);
  Serial.print("cm, ");
  side = 0.01723 * readUltrasonicDistance(starTrig,starEcho); //call to starboard sensor
  Serial.print(side);
  Serial.println("cm");


  //The motion code
  //The turning code assumes that the sensor is starbord (it is)
  //Range for speed: 255 (top speed), 0 (lowest speed)
  if(cm < wallAproach && cm > turn) //wall is in 40 cm, cut to 75% power and slow to zero one at 20cm
  {
      forwardMotion(cm*5.625-2240/cm);
  }
  else //there's no immenant forward wall
  {
    forwardMotion(255);
  }
  if(cm < turn) //we're close enough to a forward wall to make a turn
  {
    if(side > sideWallRange) //the starbord sensor "sees" a wall on the right side
    {
      leftTurn(100);
    }
    else //the starboard sensor does not "see" a wall on the right side
    {
      rightTurn(100);
    }
    
  }
  
}
