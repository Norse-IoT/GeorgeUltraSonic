 //Import i2C lCD library
//#include <LiquidCrystal_I2C.h>
// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
const int trigPin = 16;
const int echoPin = 17;
const int trigPin1 = 32;
const int echoPin1 = 33;
int currentPeople = 0;
int timeoutCounter;
long duration;
long duration1;
float distanceCm;
float distanceInch;
float distanceInch1;
float intialDistance;
float intialDistance1;
float calcIntDistance;
String sequence = "";
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
//LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
void setup(){
  // initialize LCD
  //lcd.init();
  // turn on LCD backlight                      
  //lcd.backlight();
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  intialDistance = calcDistance(trigPin, echoPin);
  intialDistance1 = calcDistance(trigPin1, echoPin1);
}

void loop(){
  distanceInch = calcDistance(trigPin, echoPin);
  distanceInch1 = calcDistance(trigPin1, echoPin1);


  // Prints the distance in the Serial Monitor
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  Serial.print("Distance2 (inch): ");
  Serial.println(distanceInch1);


  if (distanceInch < intialDistance && sequence.charAt(0) != '1'){
    sequence += "1"; 
  }
  else if(distanceInch1 < intialDistance1 && sequence.charAt(0) != '2'){
    sequence += "2";
  }
  if(sequence.equals("12")){
    currentPeople++;  
    sequence="";
    delay(550);
  }
  else if(sequence.equals("21") && currentPeople > 0){
    currentPeople--;  
    sequence="";
    delay(550);
  }
  if(sequence.length() > 2 || sequence.equals("11") || sequence.equals("22") || timeoutCounter > 200){
    sequence="";  
  }
  if(sequence.length() == 1){ //
    timeoutCounter++;
  }else{
    timeoutCounter=0;
  }

  Serial.print("\nNumber of people that went in: ");
  Serial.println(currentPeople);

  // set cursor to first column, first row
  /*lcd.setCursor(0, 0);
  // print message
  lcd.print("Distance");
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print(distanceCm);
  lcd.print(" cm");
  delay(1000);
  lcd.clear(); */
}
int calcDistance(int trigPin, int echoPin){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  calcIntDistance = distanceCm * CM_TO_INCH;
  return calcIntDistance;
}