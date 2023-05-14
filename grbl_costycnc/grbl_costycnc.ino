char c;
int x=0;
int y=0;
int g=0;
int absolute=0;
int x0=0;
int x1=0;
int y0=0;
int y1=0;
int t=0;
int dx=0;
int dy=0;
int error=0;
int sx=0;
int sy=0;
int e2=0;
int a=0;
int b=0;
int d=0;
int egal=0;


String instrx = ""; 
String instry = ""; 
String instrg = ""; 

int xx[]={1,3,2,6,4,12,8,9};

void movex(int pasx)
{
digitalWrite(2, (xx[pasx]>>0)&1);
digitalWrite(3, (xx[pasx]>>1)&1);
digitalWrite(4, (xx[pasx]>>2)&1);
digitalWrite(5, (xx[pasx]>>3)&1);    
}

void movey(int pasy)
{
digitalWrite(A0, (xx[pasy]>>0)&1);
digitalWrite(A1, (xx[pasy]>>1)&1);
digitalWrite(A2, (xx[pasy]>>2)&1);
digitalWrite(A3, (xx[pasy]>>3)&1); 
}


void muove_cnc()
{
  while(x0 != x1 || y0 != y1)
  {
  delay(1);
      e2 = 2 * error;
    if (e2 >= dy)
    {
      error = error + dy;
      x0 = x0 + sx;
      movex(x0&7);
    }  
    if (e2 <= dx)
    {
      error = error + dx;
      y0 = y0 + sy;
      movey(y0&7); 
    } 
  }


}


void gcode_exec(String string)
{Serial.println(string);
  if(g)
  {
    g=instrg.toInt();
    if(g=90){absolute=0;}
    if(g=91){absolute=1;}
  }

  if(x)
  { 
    t=int(instrx.toFloat()*100);
    if(absolute){x1=t;}
    else
    { x1=x0+t;}
  }

  if(y)
  { 
    t=int(instry.toFloat()*100);
    if(absolute){y1=t; }
    else
    {y1=y0+t;}
  }

  dx = abs(x1 - x0);
  if (x0<x1){sx=1;}
  else{sx=-1;}
  dy = -abs(y1 - y0);
  if (y0<y1){sy=1;}
  else
  {sy=-1;}
  error = dx + dy;
  muove_cnc();
 Serial.println("ok");
  x=0;
  y=0;
  g=0;

}

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
   Serial.begin(115200);
   if (Serial){Serial.println("Grbl costycnc");}
}

void loop()
{

  {
    if (Serial.available() > 0)
    {
      c = Serial.read();

      if (c != '\r')
      {
        if(x){ instrx +=char(c);}
        if(y){ instry +=char(c);}
        if(g){ instrg +=char(c);}
        if(c=='X'){x=1;instrx="";}
        if(c=='Y'){y=1;instry="";}
        if(c=='G'){g=1;instrg="";}
      }
      else
      {
        gcode_exec(instrg);
        //Serial.println("ok");
        a=1;

      }
    } 
  }
}

