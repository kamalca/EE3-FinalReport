  #define LED BLUE_LED
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
  bool secondHalf = false;
  const int buffSize = 6;
  int buffLoc = 0;
  int pastReadings[buffSize];

int diffLA = 10000;
int diffRA = 10000;
long long totalLA = 0;
long long totalRA = 0;

int i;
int bp = 20;
const int acceleration = 2;
const float fast = 4;
const float slow = 1;
float targetSpeed = fast;
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
  digitalWrite(LED, LOW);
  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
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

  if(sum > 4){
    if(!secondHalf){
      targetSpeed = slow;
      digitalWrite(LED, HIGH);
      secondHalf = true;
      delay(200);
    }
    else{
      targetSpeed = fast;
      digitalWrite(LED, LOW);
      delay(200);
    }
  }

  float speedL = (12*7.5*1000) / (12 * 120 * diffLA);
  float speedR = (12*7.5*1000) / (12 * 120 * diffRA);
  float speed = (speedL + speedR) / 2;

  
  if(speed < targetSpeed){
    bp += acceleration;
  }
  else if(bp > 20){
    bp -= acceleration;
  }


//  if(totalLA > totalRA){
//    pL--;
//  }
//  else if(totalRA > totalLA){
//    pR--;
//  }
//  else{
//    totalLA = 0;
//    totalRA = 0;
//  }
  
  analogWrite(r_pwr, bp + 2*(readings - 4) - 3*(pastReadings[(buffLoc + buffSize - 2) % buffSize] - readings));
  analogWrite(l_pwr, bp - 2*(readings - 4) + 3*(pastReadings[(buffLoc + buffSize - 2) % buffSize] - readings));

  buffLoc++;
  buffLoc = buffLoc % buffSize;
  pastReadings[buffLoc % buffSize] = readings;
  
//  i++;
//if(i%10000 == 0) {
//  Serial.print("Left: ");
//  Serial.print(diffLA);
//  Serial.print("\n");
//  Serial.print("Right: ");
//  Serial.print(diffRA);
//  Serial.print("\n");
//}
}
