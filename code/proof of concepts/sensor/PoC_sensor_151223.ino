const int sensor[] = {A0, A1, A2, A3, A4, A5};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    for (int i = 0; i < 6; i++)
    {
      long value = analogRead(sensor[i]);
      Serial.print(value);
      Serial.print(" ");
    }
    Serial.println(" ");
    delay (1000);
}
