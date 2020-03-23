    /*     
     *      
     *    HYD BVM Ventilator
     *    Stepper Motor control
     *      
     *    v0.3: 2020-03-23 Provides a single constant parameter: RR: breaths per minute. 
     *    v0.4: Tidal volume 
     *    
     *    Single bipolar stepper motor is rotated 180 degrees and returned to zero, causing the Ambubag to ventilate.
     *    
     *    
     *    TODO:
     *    a. Tidal Volume: Stroke
     *    b. Pressure: (?) Speed /Speed curve?
     *    c. Control for TV and RR
     *    d. Pressure curve
     *    e. Volume measurements from flow
     *    f. Valve control
     *    g. PEEP
     *    h. Trigger
     *    i. IE ratio
     *    j. Interrupt Driven implementation
     *    k. Sending out data on default via RX/TX
     *    l. Display on 4x20
     *    m. Timing adjustments if not interrupt driven implementation
     *    n. Command processing 
     *    o. Timing adjustments for interrupt driven, for adjusting for 
     *    p. Control for doctors to ease into triggers
     *    q. Control for patients to manually trigger
     *    r. Alarms
     *    s. Calibration
     *    t. Detection of potential failure in bag
     *    u. FiO2 detection and reporting 
     *    
     *    DVS Bharath 2020-03-23, HYDHWBAD Project.
     *    
     *  Based on  Simple Stepper Motor Control Example Code  
     *  by Dejan Nedelkovski, www.HowToMechatronics.com
     *  
     */
     
    // defines pins numbers
    const int stepPin = 4; 
    const int dirPin = 5; 

   
    int breaths_per_min = 15;
    int t_delay_in_micros, t_delay_out_micros, t_pause_millis;
    
     
    void setup() {
      int t_in_millis, t_out_millis, t_pause_millis, t_tot_millis;
      // Sets the two pins as Outputs
      pinMode(stepPin,OUTPUT); 
      pinMode(dirPin,OUTPUT);

      //200 pulses = 1 full rotation.
      t_pause_millis = 100;
      t_tot_millis = 60000/breaths_per_min;
      t_in_millis = (t_tot_millis - t_pause_millis)/2; //t_in_millis
      t_out_millis = t_in_millis;   // t_in_millis

      t_delay_in_micros = t_in_millis*5; // From millis to micros, then divided by 100, then divided by 2 for equal delay. 
      t_delay_out_micros = t_out_millis*5;
            
    }
    int STEPS = 20;
    void loop() {
      digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction

      // Makes 100 pulses for making one half cycle rotation      
      for(int x = 0; x < STEPS; x++) {
        digitalWrite(stepPin,HIGH); 
        delayMicroseconds(t_delay_in_micros); 
        digitalWrite(stepPin,LOW); 
        delayMicroseconds(t_delay_in_micros); 
      }
      
      delay(t_pause_millis); // Pause
      
      digitalWrite(dirPin,LOW); //Changes the rotations direction
      // Makes 100 pulses for making reverse of the cycle rotation
      for(int x = 0; x < STEPS; x++) {
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(t_delay_out_micros);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(t_delay_out_micros);
      }
      
    }
