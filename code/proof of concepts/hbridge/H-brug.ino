#include "SerialCommand.h"

#include <EEPROM.h>
#include "EEPROMAnything.h"

#define SerialPort Serial

#define Baudrate 9600

int MA1 = 3;
int MA2 = 5;
int MB1 = 6;
int MB2 = 9;

SerialCommand sCmd(SerialPort);
bool debug;
unsigned long previous, calculationTime;
struct param_t
{
  bool start;
  unsigned long cycleTime;
  int power;
  bool links;
  bool reverse;
  bool rechts;
  
} params;

void setup()
{
  SerialPort.begin(Baudrate);

  pinMode(3, OUTPUT);  //A1
  pinMode(5, OUTPUT);  //A2
  pinMode(6, OUTPUT);  //B2
  pinMode(9, OUTPUT); //B1

  sCmd.addCommand("set", onSet);
  sCmd.addCommand("start", onStart);
  sCmd.addCommand("stop", onStop);
  sCmd.addCommand("links", onLinks);
  sCmd.addCommand("rechts", onRechts);
  sCmd.addCommand("reverse", onReverse);
  sCmd.addCommand("debug", onDebug);
  sCmd.setDefaultHandler(onUnknownCommand);

  EEPROM_readAnything(0, params);
  params.start = false;
  SerialPort.println("ready");


}

void loop()
{
 
  sCmd.readSerial();
 
  unsigned long current = micros();
  if (current - previous >= params.cycleTime)
  {
    previous = current;
  }
 int snelheid = params.power;
    if(params.start){
      if(params.links){
          analogWrite(MA2, abs(snelheid));
          digitalWrite(MA1, LOW);
          digitalWrite(MB2, LOW);
          digitalWrite(MB1, LOW);
      }
      else if(params.rechts){
          digitalWrite(MA1, LOW);
          digitalWrite(MA2, LOW);
          analogWrite(MB2, abs(snelheid));
          digitalWrite(MB1, LOW);
      }
      else if(params.reverse){
          analogWrite(MA1, abs(snelheid));
          digitalWrite(MA2, LOW);
          analogWrite(MB1, abs(snelheid));
          digitalWrite(MB2, LOW);
      }else{
          analogWrite(MA2, abs(snelheid));
          digitalWrite(MA1, LOW);
          analogWrite(MB2, abs(snelheid));
          digitalWrite(MB1, LOW);
      }
    }else{
      digitalWrite(MA1, LOW);
      digitalWrite(MA2, LOW);
      digitalWrite(MB1, LOW);
      digitalWrite(MB2, LOW);
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
  
  if (strcmp(param, "cycle") == 0) params.cycleTime = atol(value);
  if (strcmp(param, "power") == 0) params.power = atoi(value);

  EEPROM_writeAnything(0, params);
}

void onDebug()
{
  SerialPort.print("cycle time: ");
  SerialPort.println(params.cycleTime);
  SerialPort.print("Aan : ");
  SerialPort.println(params.start);
  SerialPort.print("Power : ");
  SerialPort.println(params.power); 
  SerialPort.print("calculation time: ");
  SerialPort.print(calculationTime);
  calculationTime = 0;
}

void onStart()

{
    params.start = true;
  
    
}

void onStop()

{
    params.start = false;
    params.links = false;
    params.rechts = false;
    params.reverse =false;
}
void onLinks()
{
  params.links = true;
  params.reverse = false;
  params.rechts = false;
  
}
void onRechts()
{
  params.rechts = true;
  params.links = false;
  params.reverse = false;
}
void onReverse()
{
  params.reverse = true;
  params.links = false;
  params.rechts = false;
}


   
