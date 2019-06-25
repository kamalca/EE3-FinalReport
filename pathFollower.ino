#define LED RED_LED
  const int left_nslp_pin = 31; //not sleep, digital
  const int left_dir_pin = 29; //direction, digital
  const int left_pwn_pin = 40; //duty cycle, analoge, 0-255
  const int right_nslp_pin = 11; //not sleep, digital
  const int right_dir_pin = 30; //direction, digital
  const int right_pwn_pin = 39; //duty cycle, analoge, 0-255
  const int l_sleep = 31; //not sleep, digital
  const int l_dir = 29; //direction, digital
  const int l_pwr = 40; //duty cycle, analoge, 0-255
  const int r_sleep = 11; //not sleep, digital
  const int r_dir = 30; //direction, digital
  const int r_pwr = 39; //duty cycle, analoge, 0-255
  const int sensors[8] = {65, 48, 64, 47, 52, 68, 53, 69}; //Right to left
  int readings;
  int sum;
  const int buffSize = 6;
  int buffLoc = 0;
  int pastReadings[buffSize];
  bool secondHalf = false;

  int c = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(left_nslp_pin, OUTPUT);
  pinMode(left_dir_pin, OUTPUT);
  digitalWrite(left_nslp_pin, HIGH);
  digitalWrite(left_dir_pin, LOW);
  pinMode(right_nslp_pin, OUTPUT);
  pinMode(right_dir_pin, OUTPUT);
  digitalWrite(right_nslp_pin, HIGH);
  digitalWrite(right_dir_pin, LOW);

  pinMode(45, OUTPUT);
  pinMode(61, OUTPUT);
  digitalWrite(45, HIGH);
  digitalWrite(61, HIGH);
  
  pinMode(left_pwn_pin, OUTPUT);
  pinMode(right_pwn_pin, OUTPUT);
  pinMode(LED, OUTPUT);

  for(int i = 0; i < buffSize; i++)
    pastReadings[i] = 4;

  //Serial.begin(9600);
    

  delay(1000);
}

void loop() {
  readings = 0;
  sum = 0;
  for(int i = 0; i < 8; i++)
  {
    pinMode(sensors[i], OUTPUT);
    digitalWrite(sensors[i], HIGH);
    delay(10);
    pinMode(sensors[i], INPUT);
    delay(1);
    if(digitalRead(sensors[i])){
      sum++;
      if(readings == 0)
        readings = i;
    }
  }

  if(sum > 3){
    if(!secondHalf){
      digitalWrite(right_dir_pin, HIGH);
      analogWrite(r_pwr, 80);
      analogWrite(l_pwr, 80);
      delay(710);
      digitalWrite(right_dir_pin, LOW);
      analogWrite(r_pwr, 0);
      analogWrite(l_pwr, 0);
      secondHalf = true;
      for(int i = 0; i < buffSize; i++)
        pastReadings[i] = 4;
      delay(100);
    }
    else{
      analogWrite(r_pwr, 0);
      analogWrite(l_pwr, 0);
      delay(1000000);
    }
  }

  if(pastReadings[buffLoc % buffSize] - readings > 6){
    readings = 7;
  }

  int error = readings - 4;
  
  analogWrite(r_pwr, (60 + error * 4) - 3*(pastReadings[(buffLoc + buffSize - 3) % buffSize] - readings));
  analogWrite(l_pwr, (60 - error * 4) + 3*(pastReadings[(buffLoc + buffSize - 3) % buffSize] - readings));
  
  buffLoc++;
  buffLoc = buffLoc % buffSize;
  pastReadings[buffLoc % buffSize] = readings;
}
