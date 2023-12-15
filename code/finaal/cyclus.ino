#include "SerialCommand.h"
#include "EEPROMAnything.h"
#include "SoftwareSerial.h"

//#define SerialPort Serial
#define SerialPort bluetooth
#define Baudrate 9600

#define MotorLeftForward 5
#define MotorLeftBackward 3
#define MotorRightForward 9
#define MotorRightBackward 6

#define TX 11
#define RX 10
SoftwareSerial bluetooth = SoftwareSerial(RX,TX);     // The SoftwareSerial Object

SerialCommand sCmd(bluetooth);	
//SerialCommand sCmd(SerialPort);
bool debug;
bool run;
int led = 12;
unsigned long previous, calculationTime;
const int sensor[] = {A0, A1, A2, A3, A4, A5};
int z = 0;

long normalised[6];
float debugPosition;
float iTerm;
float lastErr;

struct param_t
{
  unsigned long cycleTime;
  float power;
  float diff;
  float kp;
  float ki;
  float kd;
  int black[6];
  int white[6];
  /* andere parameters die in het eeprom geheugen moeten opgeslagen worden voeg je hier toe ... */
} params;
    
void setup()
{
  SerialPort.begin(Baudrate);
  sCmd.addCommand("set", onSet);
  sCmd.addCommand("debug", onDebug);
  sCmd.addCommand("calibrate", onCalibrate);
  sCmd.addCommand("run", onRun);
  sCmd.addCommand("stop", onStop);
  sCmd.setDefaultHandler(onUnknownCommand);

  pinMode(led, OUTPUT);
  pinMode(7, INPUT);
  attachInterrupt(4, ISR_test, RISING);

  EEPROM_readAnything(0, params);
  SerialPort.println("ready");

  pinMode(13, OUTPUT);
}

void loop()
{
  sCmd.readSerial();
  digitalWrite(led, HIGH);
  unsigned long current = micros();
  if (current - previous >= params.cycleTime)
  {
    previous = current;
    if (run == true) z = 1;
    else if (run == false) z = 0;

    //NORMALISATIE
    for (int i = 0; i < 6; i++)
    {
      long value = analogRead(sensor[i]);
      normalised[i] = map(value, params.black[i], params.white[i], 0, 1000);
    }

    //INTERPOLATIE
    int index = 0;
    for (int i = 1; i < 6; i++) if (normalised[i] < normalised[index]) index = i;

    //if (normalised[index] > 800) run = false; //stoppen wanneer er geen zwarte lijn wordt gezien

    float position;
    if (index == 0) position = -30;
    else if (index == 5) position = 30;
    else {
    long sZero = normalised[index];
    long sMinusOne = normalised[index-1];
    long sPlusOne = normalised[index+1];
    //SerialPort.println(index);

    float b = ((float) (sPlusOne - sMinusOne)) / 2;
    float a = sPlusOne - b - sZero;

    position = -b / (2 * a);  
    position += index;
    position -= 2.5; 

    position *= 15;  //sensor distance in mm
    }
    debugPosition = position;

    //PROPORTIONEEL
    float error = -position; //eigenlijk staat hier setpoint - position, maar setpoint = 0, error is input voor regelaar
    float output = error * params.kp;

    //INTEGREREN
    iTerm += params.ki * error;
    iTerm = constrain(iTerm, -510, 510);
    output += iTerm;

    //DIFFERENTIËREN
    output += params.kd * (error - lastErr);
    lastErr = error;

    output = constrain(output, -510, 510);

    int powerLeft = 0;
    int powerRight = 0;

    if (run) if (output >= 0) 
    {
      powerLeft = constrain(params.power + params.diff * output, -225, 255);
      powerRight = constrain(powerLeft - output, -255, 255);
      powerLeft = powerRight + output;
    }
    else 
    {
      powerRight = constrain(params.power - params.diff * output, -225, 255);
      powerLeft = constrain(powerRight + output, -255, 255);
      powerRight = powerRight - output;      
    }

    analogWrite(MotorLeftForward, powerLeft > 0 ? powerLeft : 0);
    analogWrite(MotorLeftBackward, powerLeft < 0 ? -powerLeft : 0);
    analogWrite(MotorRightForward, powerRight > 0 ? powerRight : 0);
    analogWrite(MotorRightBackward, powerRight < 0 ? -powerRight : 0);
  }

  unsigned long difference = micros() - current;
  if (difference > calculationTime) calculationTime = difference;
}

void onUnknownCommand(char *command)
{
  SerialPort.print("unknown command: \"");
  SerialPort.print(command);
  SerialPort.println("\"");
}

void onSet()
{
  char* param = sCmd.next();
  char* value = sCmd.next();  
  if (strcmp(param, "cycle") == 0)
  {
    long newCycleTime = atol(value);
    float ratio = ((float) newCycleTime) / ((float) params.cycleTime);

    params.ki *= ratio;
    params.kd /= ratio;

    params.cycleTime = newCycleTime;
  }
  else if (strcmp(param, "ki") == 0)
  {
    float cycleTimeInSec = ((float) params.cycleTime) / 1000000;
    params.ki = atof(value) * cycleTimeInSec;
  }
  else if (strcmp(param, "kd") == 0)
  {
    float cycleTimeInSec = ((float) params.cycleTime) / 1000000;
    params.kd = atof(value) / cycleTimeInSec;
  }
  else if (strcmp(param, "power") == 0) params.power = atol(value);
  else if (strcmp(param, "diff") == 0) params.diff = atof(value);
  else if (strcmp(param, "kp") == 0) params.kp = atof(value);

  /* parameters een nieuwe waarde geven via het set commando doe je hier ... */
  
  EEPROM_writeAnything(0, params);
}

void onDebug()
{
  SerialPort.print("cycle time: ");
  SerialPort.println(params.cycleTime);

  SerialPort.print("Black: ");
  for (int i = 0; i < 6; i++) {
    SerialPort.print(params.black[i]);
    SerialPort.print(" ");
  }
  SerialPort.println(" ");
  
  SerialPort.print("White: ");
  for (int i = 0; i < 6; i++) {
    SerialPort.print(params.white[i]);
    SerialPort.print(" ");
  }
  SerialPort.println(" ");

  SerialPort.print("Sensoren: ");
  for (int i = 0; i < 6; i++) {
    SerialPort.print(analogRead(sensor[i]));
    SerialPort.print(" ");
  }
  SerialPort.println(" ");

  SerialPort.print ("Normalised Values: ");
  for (int i = 0; i < 6; i++){
        SerialPort.print(normalised[i]);
      SerialPort.print (" ");
  }
  SerialPort.println (" ");

  SerialPort.print("Position: ");
  SerialPort.println (debugPosition);

  SerialPort.print("Power: ");
  SerialPort.println (params.power);

  SerialPort.print("Diff: ");
  SerialPort.println (params.diff);

  SerialPort.print("Kp: ");
  SerialPort.println (params.kp);

  float cycleTimeInSec = ((float) params.cycleTime) / 1000000;
  float ki = params.ki / cycleTimeInSec;
  SerialPort.print("Ki: ");
  SerialPort.println(ki);

  float kd = params.kd * cycleTimeInSec;
  SerialPort.print("Kd: ");
  SerialPort.println(kd);

  SerialPort.print("calculation time: ");
  SerialPort.println(calculationTime);

  SerialPort.println("-----------------------------------------");

  calculationTime = 0;
}

void onCalibrate()
{
  char* param = sCmd.next();

  if (strcmp(param, "black") == 0)
  {
    SerialPort.print("start calibrating black... ");
    for (int i = 0; i < 6; i++) params.black[i]=analogRead(sensor[i]);
    SerialPort.println("done");
  }
  else if (strcmp(param, "white") == 0)
  {
    SerialPort.print("start calibrating white... ");    
    for (int i = 0; i < 6; i++) params.white[i]=analogRead(sensor[i]);  
    SerialPort.println("done");      
  }

  EEPROM_writeAnything(0, params);
}

void onRun()
{
  SerialPort.println("running");
  run = true;
  z = 1;
}

void onStop()
{
  SerialPort.println("stopped");
  run = false;
  z = 0;
}

void ISR_test(void)
{
  z++;
  SerialPort.println(z);
  if(z == 1){
    run = true;
    SerialPort.println("z = 1");
  }
  else if (z == 2){
   run = false;
  SerialPort.println("z = 2");
  } 
}
