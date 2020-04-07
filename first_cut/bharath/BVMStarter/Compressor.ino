
#define ACTIVE_REQUEST_RESET 3
#define ACTIVE_REQUEST_EXPAND 2
#define ACTIVE_REQUEST_COMPRESS 1
#define NO_REQUEST 0

char compressionRequest=NO_REQUEST; 
unsigned short home_steps = 15;
unsigned short stroke_steps = 150;
unsigned short stroke_fwd_time = 2000;
unsigned short stroke_rev_time = 2000;
unsigned short current_steps = 0;
unsigned char last_c_request  = NO_REQUEST;
unsigned char last_steps_done = 0;

void initStrokeParams(unsigned short iHome, unsigned short iSteps, unsigned short iFwd, unsigned short iRev) 
{
   home_steps = iHome;
   stroke_steps = iSteps;
   stroke_fwd_time = iFwd;
   stroke_rev_time = iRev;
}
int getStrokeSteps()
{
  return stroke_steps;
}

void reset()
{
	// Called ONLY after stop
	int sd, sn, dn;
	
	sd = 	last_steps_done;
	dn = LOW; // backwards;
	
	if(last_c_request == ACTIVE_REQUEST_RESET || compressionRequest!=NO_REQUEST)
			return;
		
	if(last_c_request == ACTIVE_REQUEST_EXPAND)
		sn = stroke_steps - sd;
	else if( last_c_request == ACTIVE_REQUEST_COMPRESS)
		sn = sd;
	if(last_c_request !=ACTIVE_REQUEST_RESET)
	{
		compressionRequest=ACTIVE_REQUEST_RESET;
		travelRequest(HIGH, stroke_steps, stroke_fwd_time);	  
	}
}

void compress(void)
{
	if(compressionRequest==NO_REQUEST)
	{
	 compressionRequest=ACTIVE_REQUEST_COMPRESS;	
      travelRequest(HIGH, stroke_steps, stroke_fwd_time);	  
	}
}

void expand(void)
{

		if(compressionRequest==NO_REQUEST)
		{
			travelRequest(LOW, stroke_steps, stroke_rev_time);
			compressionRequest=ACTIVE_REQUEST_EXPAND;	
		}
}	

void stopCompressor()
{
  
	stopMotor();
  last_c_request=compressionRequest;
  last_steps_done = getStepsMoved();
  //compressionRequest = ACTIVE_REQUEST_RESET;
  
}
//=========================================================
void compressionRefresh(void)
{
	if(compressionRequest!=NO_REQUEST)
	{
    if(getAlarmState() == SYS_SAFETY_SAFE)
    {
		  refresh();
    
  		if(getStepperMode() == NO_REQUEST)
  		{
  			last_c_request = compressionRequest;
  			last_steps_done = getStepsMoved();
  			compressionRequest = NO_REQUEST;
  		}
      
    }
    else
    {
      compressionRequest = NO_REQUEST;
    }
	}
}
