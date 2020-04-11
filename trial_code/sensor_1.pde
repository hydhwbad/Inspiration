// sensor test
PImage photo;

int bottom_x, bottom_y, top_x,top_y;

//bottom: center of blue start above bottom red block
int bottom_red_left_x, bottom_red_left_y;
int bottom_red_upper_left_x, bottom_red_upper_left_y;
int bottom_blue_left_x, bottom_blue_left_y;
int bottom_blue_right_x, bottom_blue_right_y;

int top_red_left_x, top_red_left_y;
int top_red_lower_left_x, top_red_lower_left_y;
int top_blue_left_x, top_blue_left_y;
int top_blue_right_x, top_blue_right_y;

int level_x,level_y;
float level_pct;

boolean debug = false;

long lim_millis;
long t0, t1;

void debugMark(int x, int y)
{
  if(!debug)
    return;
  
  debugMark(x,y,0);
}

void debugMark(int x, int y, int c)
{
          fill(c);
          noStroke();
          rect(x, y, 5,5);

}

boolean isInRed(int x, int y)
{
    color c;
    c = pixels[y*width+x];
    return (red(c)>64 && blue(c)<128);
}

boolean isInBlue(int x, int y)
{
    color c;
    c = pixels[y*width+x];
    return (red(c)<64 && blue(c)>128);
}

void findBottom()
{
    int x,y;
    color c;
    boolean found = false;

  for( y=height-1; y>=0 && !found; y--)
      for(x=0;x<width && !found; x++)
      {
        
        if(isInRed(x,y))
        {
          bottom_red_left_x = x;
          bottom_red_left_y = y;
          found = true;
          debugMark(x,y);
        }
      }
      x=bottom_red_left_x;
      y=bottom_red_left_y;
      found = false;
      
      while(!found)
      {
        if(isInRed(x,y-1))
          y--;
        else if(isInRed(x+1,y-1))
        {
          x++;
          y--;
        }
        else 
        {
          found=true;
          bottom_red_upper_left_x = x;
          bottom_red_upper_left_y = y;
          debugMark(x,y);
        }
        
      }
      
      x = bottom_red_upper_left_x;
      y = bottom_red_upper_left_y;
      found = false;
      
      //Reach blue while being on red border
      while(!found && millis()<lim_millis)
      {
        if(isInRed(x,y-1))
          y--;
        else if(isInRed(x+1,y-1))
        {
          x++;
          y--;
        }
        else if(isInRed(x+1,y))
          x++;
        else if(isInBlue(x+1,y))
        {
          x++;
          found=true;
          bottom_blue_left_x = x;
          bottom_blue_left_y = y;
          debugMark(x,y);
        }
        else if(isInBlue(x,y-1))
        {
          y--;
          found=true;
          bottom_blue_left_x = x;
          bottom_blue_left_y = y;
          debugMark(x,y);
        }
        
        else if(isInRed(x+1,y+1))
        {
          x++;
          y++;
        }
        
      }
      
      found = false;
      x = bottom_blue_left_x;
      y = bottom_blue_left_y;
      
      //move along blue border with red
      while(!found && millis()<lim_millis)
      {
        if(isInBlue(x+1,y))
        {
          x++;
        }
        else if(isInBlue(x+1,y+1))
        {
          x++;
          y++;
        }
        else 
        {
          found=true;
          bottom_blue_right_x = x;
          bottom_blue_right_y = y;
          debugMark(x,y);
        }        
      }
      
      bottom_x = (bottom_blue_left_x+bottom_blue_right_x)/2;
      bottom_y = (bottom_blue_left_y+bottom_blue_right_y)/2;
      debugMark(bottom_x, bottom_y);
     
}

void findTop()
{
    int x,y;
    color c;
    boolean found = false;

  for( y=0; y<height && !found; y++)
      for(x=0;x<width && !found; x++)
      {
        
        if(isInRed(x,y))
        {
          top_red_left_x = x;
          top_red_left_y = y;
          found = true;
          debugMark(x,y);
        }
      }
      x=top_red_left_x;
      y=top_red_left_y;
      found = false;
      
      while(!found)
      {
        if(isInRed(x,y+1))
          y++;
        else if(isInRed(x+1,y+1))
        {
          x++;
          y++;
        }
        else 
        {
          found=true;
          top_red_lower_left_x = x;
          top_red_lower_left_y = y;
          debugMark(x,y);
        }
        
      }
      
      x = top_red_lower_left_x;
      y = top_red_lower_left_y;
      found = false;
      
      /*
      //Reach blue while being on red border
      while(!found && millis()<lim_millis)
      {
        if(isInRed(x,y+1))
          y++;
        else if(isInRed(x+1,y+1))
        {
          x++;
          y++;
        }
        else if(isInRed(x+1,y))
          x++;
        else if(isInBlue(x+1,y))
        {
          x++;
          found=true;
          top_blue_left_x = x;
          top_blue_left_y = y;
          debugMark(x,y);
        }
        else if(isInBlue(x,y+1))
        {
          y++;
          found=true;
          top_blue_left_x = x;
          top_blue_left_y = y;
          debugMark(x,y);
        }
        
        else if(isInRed(x+1,y-1))
        {
          x++;
          y--;
        }
        
      }
      
      found = false;
      x = top_blue_left_x;
      y = top_blue_left_y;
      
      //move along blue border with red
      while(!found && millis()<lim_millis)
      {
        if(isInBlue(x+1,y))
        {
          x++;
        }
        else if(isInBlue(x+1,y-1))
        {
          x++;
          y++;
        }
        else 
        {
          found=true;
          top_blue_right_x = x;
          top_blue_right_y = y;
          debugMark(x,y);
        }        
      }
      */
      top_x = bottom_x;
      top_y = top_red_lower_left_y;
      debugMark(top_x, top_y);
     
}


void findHome()
{
  loadPixels();
  //println(pixels.length);
  lim_millis = millis() + 5000;
  findBottom();
  findTop();
  debugMark(bottom_x, bottom_y,color(0,255,0));
  debugMark(top_x, top_y,color(0,255,0));
  if(millis()>=lim_millis)
    println("Please help");
}


void findLevel()
{
  int x,y, color_sum, last_color;
  boolean found;
  x = bottom_x;
  y = bottom_y;
  /*
  color_sum =get(x,y)*5;
  last_color = get(x,y);
  color_avg = color_sum/5;
  */
  found = false;
  while(!found)
  {
    if(isInBlue(x,y-1))
      y--;
    else if(isInBlue(x+1,y-1) || isInBlue(x-1,y-1))
    {
      if(isInBlue(x+1,y-1))
        x++;
      else
        x--;
    }
    else
      found = true;
      
    if(y<=top_y)
      found=true;
     
      
  }
  level_y = y;
  level_x = x;
  debugMark(level_x,level_y, color(255,255,0));
  level_pct = dist(level_x,level_y, bottom_x, bottom_y)/dist(top_x,top_y, bottom_x, bottom_y);
}

void setup()
{
  
  size(600,600);
  //scale(0.5);
  //rotate(PI/6.0);

  photo = loadImage("test.png");
  image(photo,0,0);
  findHome();
  t0 = millis();
   findLevel();
  t1 = millis();
  println(t1-t0);
   fill(0);
   text(level_pct, level_x-100, level_y); 
  
}


void draw()
{
/*
    if(get(bottom_red_left_x, bottom_red_left_y)!=color(0,0,0))
      set(bottom_red_left_x, bottom_red_left_y, color(0,0,0)); 
   else
      set(bottom_red_left_x, bottom_red_left_y, color(255,0,0));
*/
   delay(500);
  
}
