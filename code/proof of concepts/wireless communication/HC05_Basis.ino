#include<SoftwareSerial.h>

/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(10,11); /* (Rx,Tx) opletten: Rx van module wordt Tx op arduino en omgekeerd! */	

void setup() {
  bt.begin(9600);	/* Define baud rate for software serial communication */
  Serial.begin(9600);	/* Define baud rate for serial communication */
}

void loop() {
  
    if (bt.available())	/* If data is available on serial port */
    {
     Serial.write(bt.read());	/* Print character received on to the serial monitor */
    }

    if (Serial.available()) /* If any data is sent via the Serial Monitor (Arduino) */
    {
    bt.write(Serial.read()); /* Send this data via the Bluetooth Serial Port */
    }
}