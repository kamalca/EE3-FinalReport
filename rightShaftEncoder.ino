#define ERA P10_4

int ERAticks = 0;

int ERA_maxticks = 12;

int ERA_start_time = 0;
bool ERA_last_state = 0;
bool ERA_current_state = 0;


void setup3 ()
{
  pinMode(ERA, INPUT);
  
  ERAticks = ERA_maxticks;

  ERA_start_time = millis();
  ERA_last_state = 0;
  ERA_current_state = 0;
  
}

void loop3()
{
  if (ERAticks < ERA_maxticks)

//    ELA_start_time = millis();
//    ELA_last_state = 0;
//    ELA_current_state = 0;
//  while (ELAticks < ELA_maxticks)
  {
    ERA_current_state = digitalRead(ELA);
    
    if (ERA_current_state && !ERA_last_state) //rising edge
    {
      ERAticks++;
      totalRA++;
    }
    
    ERA_last_state = ERA_current_state;
  }
  else
  {
    diffRA = millis() - ERA_start_time;
    ERAticks = 0;
    
    ERA_start_time = millis();
    ERA_last_state = 0;
    ERA_current_state = 0;
  }
}
