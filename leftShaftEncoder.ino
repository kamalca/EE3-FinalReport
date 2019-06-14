#define ELA P10_5

int ELAticks = 0;

int ELA_maxticks = 12;

int ELA_start_time = 0;
bool ELA_last_state = 0;
bool ELA_current_state = 0;


void setup2 ()
{
  pinMode(ELA, INPUT);
  
  ELAticks = ELA_maxticks;

  ELA_start_time = millis();
  ELA_last_state = 0;
  ELA_current_state = 0;
}

void loop2()
{
  if (ELAticks < ELA_maxticks)  {
    ELA_current_state = digitalRead(ELA);
    
    if (ELA_current_state && !ELA_last_state) //rising edge
    {
      ELAticks++;
      totalLA++;
    }
    
    ELA_last_state = ELA_current_state;
  }
  else
  {
    diffLA = millis() - ELA_start_time;
    ELAticks = 0;
    
    ELA_start_time = millis();
    ELA_last_state = 0;
    ELA_current_state = 0;
  }
}
