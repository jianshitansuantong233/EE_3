const int ELA=72;

int ELAticks = 0;



int ELA_start_time = 0;
bool ELA_last_state = 0;
bool ELA_current_state = 0;


void setup3 ()
{
  pinMode(ELA, INPUT);
  
  ELAticks = ELA_maxticks;
}

void loop3()
{
  ELA_start_time = millis();
  ELA_last_state = 0;
  ELA_current_state = 0;
  
  while (ELAticks < ELA_maxticks)
  {
    ELA_current_state = digitalRead(ELA);
    
    if (ELA_current_state && !ELA_last_state) //rising edge
    {
      ELAticks++;
    }
    
    ELA_last_state = ELA_current_state;
  }
  
  diff2 = millis() - ELA_start_time;
  ELAticks = 0;
}
