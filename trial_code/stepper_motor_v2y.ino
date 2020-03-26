    /*     RT Stepper
     *      
     *     DVS Bharath based on tutorial on non-RT steppers
     *  by Dejan Nedelkovski, www.HowToMechatronics.com
     *  
     */
    #define T_STEPPER_HIGH 5
    #define T_STEPPER_LOW 5

    #define ACTIVE_REQUEST 1
    #define NO_REQUEST 0
    // defines pins numbers
    const int stepPin = 4; 
    const int dirPin = 5; 

    int pDir, pSteps_asked, pSteps_done, pRequestTicks, pTickInterval, pCurrentTicks ;
    long time_of_request, time_limit_of_request; 
    int my_leastcount_millis = 1;
    char pMode = 0;
    
    /*
     * dir = HIGH: Clockwise
     * dir = LOW: CounterClockwise
     */
    void travelRequest(int dir, int steps, long time_limit_millis)
    {
  
      if(steps > time_limit_millis/my_leastcount_millis)
        return;
      pMode    = ACTIVE_REQUEST;
      
      pRequestTicks =    time_limit_millis/my_leastcount_millis;
      pTickInterval = pRequestTicks/steps;
      pCurrentTicks = 0;
      pDir = dir;
      pSteps_asked = steps;
      pSteps_done = 0;
      time_of_request = millis();
      time_limit_of_request = time_limit_millis;
    }

    void move_a_step(void)
    {
        digitalWrite(dirPin,pDir); // Enables the motor to move in a particular direction
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(T_STEPPER_HIGH); // spec says 1uS, we need 2uS, but least count is 4uS :)
        digitalWrite(stepPin,LOW); 
        delayMicroseconds(T_STEPPER_LOW); 

    }

    void move_a_step_rt(int d)
    {
      pDir = d;
      move_a_step();
      delay(1);
    }

    void appError (String s)
    {
      Serial.println(s);      
    }
    
    void refresh() // will be called every millisecond
    {
      long currentT;
      int remainingSteps;
      
      //TODO
      //Case of little time left
      if(pMode !=ACTIVE_REQUEST)
        return;
      pCurrentTicks++;
      if(pCurrentTicks == pTickInterval)
      {
        move_a_step();
        pSteps_done++;
        pCurrentTicks = 0;
      }
      if(pSteps_asked == pSteps_done)
      {
        pMode = NO_REQUEST;    
      }


      /*
      if(pMode !=NO_REQUEST)
      {
          //check if we are short of time;
          currentT = millis();
          remainingSteps = pSteps_asked -pSteps_done;
          if(time_of_request+time_limit_of_request < currentT)
          {
            appError("Motor too late"); 
              pMode =NO_REQUEST;
            
          }
          
          
          if(remainingSteps >  ((time_of_request+time_limit_of_request -currentT)/my_leastcount_millis)) 
          {
              appError("Motor too late");
              pMode =NO_REQUEST;
              // TODO
              // Actually, we should further check if the time is less we will take up slack in completing
              //travelRequest(pDir, remainingSteps, time_limit_millis);    
                   
          }
      }

      */
    }

    void setLeastCountMillis(int lc)
    {
      my_leastcount_millis = lc;
    }

    void stop()
    {
      
    }
    
    int getStepsMoved()
    {
      return pSteps_done;
    }
    
    void setup() {
      // Sets the two pins as Outputs
      pinMode(stepPin,OUTPUT); 
      pinMode(dirPin,OUTPUT);
    }
    void loopx() {
      digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
      // Makes 200 pulses for making one full cycle rotation
      for(int x = 0; x < 200; x++) {
        digitalWrite(stepPin,HIGH); 
        delayMicroseconds(4); 
        digitalWrite(stepPin,LOW); 
        delayMicroseconds(4); 
        delay(50);
      }
      delay(1000); // One second delay
      
    }

    void loop()
    {
      int i;
      int steps = (analogRead(A0)/100)*20;
      if(steps >200)
          steps = 200;
      int spd = (analogRead(A1)*3);
      if(spd<steps) 
          spd = steps;
          
      travelRequest(HIGH, steps, spd);
      for(i=0; i<2001; i++)
      {
        refresh();
        delay(1);
      }
      delay(5000);
      
      
    }
