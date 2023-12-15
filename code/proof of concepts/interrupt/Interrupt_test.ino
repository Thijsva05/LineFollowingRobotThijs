int led = 12;
bool start = false;
bool stop = false;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(7, INPUT);
  attachInterrupt(4, ISR_test, RISING);
}

void loop() {
  // put yo ur main code here, to run repeatedly:
  if(start == true){
    digitalWrite(led, HIGH);
  }
  else if (stop = true){
    digitalWrite(led, LOW);
  }
  else {}
}

void ISR_test(void){
  i++;
  if(i == 1){
    start = true;
    stop = false;
    Serial.println("Programma start");
  }
  else if(i == 2){
    start = false;
    stop = true;
    i = 0;
    Serial.println("Programma stop");
  }
  else {}
}