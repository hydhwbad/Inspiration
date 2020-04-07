// Calibrate


#define CVAL_M_ML_PER_MM 9
#define CVAL_C_ML -53


#define CVAL_COARSE_STEPS_PER_MM 25
#define CVAL_COARSE_STEPS_FOR_HOME 200

/*
#define CVAL_COARSE_STEPS_PER_MM 1.5
#define CVAL_COARSE_STEPS_FOR_HOME 15
*/

int acceptablyEqual(float i, float j)
{
  if(i>0)
  {
    return (i>j)? ((i-j)/i <0.05): ((j-i)/i <0.05);
  }
  return false;
}

int getStepsForTidalVolume_Steps(int vol, float steps_per_mm)
{
		float m_ml_per_mm, c_ml, y_ml, x_mm;
		float s;
    m_ml_per_mm = CVAL_M_ML_PER_MM;
    c_ml = CVAL_C_ML;
		// y = mx+c :: y= volume, x = number of steps, c is a constant.
		y_ml = vol;
		x_mm = (y_ml-c_ml)/m_ml_per_mm;
		s = steps_per_mm*x_mm;
		return s;
}

int getStepsForTidalVolume(int vol)
{
  return getStepsForTidalVolume_Steps(vol, CVAL_COARSE_STEPS_PER_MM);
}

int getStepsHomeFromStart(void)
{
  return CVAL_COARSE_STEPS_FOR_HOME;
}
