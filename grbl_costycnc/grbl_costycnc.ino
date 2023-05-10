char c;
int x=0;
int y=0;
int g=0;
int absolute=0;
float x0=0;
float x1=0;
float y0=0;
float y1=0;
float t=0;
float dx=0;
float dy=0;
float error=0;
int sx=0;
int sy=0;
float e2=0;
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
  

    //Serial.print((xx[pasy] >> 0) & 1);
    //Serial.print(xx[pasy] >> 1) & 1);
    //Serial.print(xx[pasy] >> 2) & 1);
    //Serial.print(xx[pasy] >> 3) & 1);
    //led4.value((x[pasy] >> 0) & 1)
    //led5.value((x[pasy] >> 1) & 1)
    //led6.value((x[pasy] >> 2) & 1)
    //led7.value((x[pasy] >> 3) & 1)
}





void gcode_exec(String string)
{

  if(g)
  {
    g=instrg.toInt();
    if(g=90){absolute=1;}
    if(g=91){absolute=0;}
  }

  if(x)
  {
    t=instrx.toFloat();
    if(absolute){x1=t;}
    else
    { x1=x0+t;}
  }

  if(y)
  { 
    t=instry.toFloat();
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
  x=0;
  y=0;
  g=0;

}

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
   Serial.begin(115200);
   if (Serial){Serial.println("Grbl costycnc");}

 
  TCCR1A = 0;                //Registro de control A a 0
  TCCR1B = 0;                //Limpiar registro
  TCNT1  = 0;                //Inicializar el temporizador
  OCR1A = 1999;            //Carga el valor del registro de comparación: 16MHz/1024/1Hz -1 = 15624 = 0X3D08
  TCCR1B |= (1 << WGM12)|(1 << CS11);   //Modo CTC, prescaler de 1024: CS12 = 1 y CS10 = 1  
  TIMSK1 |= (1 << OCIE1A);  //Habilita interrupción por igualdad de comparación



}

void loop()
{
  if(a==0)
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
        Serial.println("ok");
        a=1;
      }
    } 
  }
}

ISR(TIMER1_COMPA_vect)          //Interrupción por igualdad de comparación en TIMER1
{
  
if(a)
  {
      e2 = 2 * error;
    if (e2 >= dy)
    {
      error = error + dy;
      x0 = x0 + sx;
      b +=sx;
      movex(b&7);
    }  
    if (e2 <= dx)
    {
      error = error + dx;
      y0 = y0 + sy;
      d +=sy;
      movey(d&7); 
    } 

if(x0 == x1 and y0 == y1){a=0;}

  }


}






















/*
void loop() {
    if (x0 == x1 and y0 == y1){//arrivatto in punto di destinazione
        if (len(buffer)>0){// # daca buffer e gol atunci sare peste asta
            //print(len(buffer)," buffer prima=",buffer)
            //gcode_exec(buffer.pop(0)) 
            //print(len(buffer)," buffer dopo=",buffer)
            //conn.send("ok\n")
            
                       }}
    else{
            //do_step() # executa pana ajunge la destinazione
    }

}

from machine import Pin
import socket
import time

led = Pin(Pin.PB_14, Pin.OUT, Pin.PULL_FLOATING)
led1 = Pin(Pin.PB_15, Pin.OUT, Pin.PULL_FLOATING)
led2 = Pin(Pin.PB_16, Pin.OUT, Pin.PULL_FLOATING)
led3 = Pin(Pin.PB_17, Pin.OUT, Pin.PULL_FLOATING)
led4 = Pin(Pin.PB_18, Pin.OUT, Pin.PULL_FLOATING)
led5 = Pin(Pin.PB_06, Pin.OUT, Pin.PULL_FLOATING)
led6 = Pin(Pin.PB_07, Pin.OUT, Pin.PULL_FLOATING)
led7 = Pin(Pin.PB_08, Pin.OUT, Pin.PULL_FLOATING)

s = socket.socket()
s.bind(('', 80))
s.listen(5)
conn, addr = s.accept()
conn.setblocking(False)
x0=0
y0=0
x1=0
y1=0
dx=0
dy=0
sx=0
sy=0
error=0
buffer=[]
currentx=0
absolute=0
k=0
nn=[]
este=0
x=[1,3,2,6,4,12,8,9]
dorme=1


def movey(pasy):
    global x
    #print((x[a] >> 0) & 1,(x[a] >> 1) & 1,(x[a] >> 2) & 1,(x[a] >> 3) & 1)
    led4.value((x[pasy] >> 0) & 1)
    led5.value((x[pasy] >> 1) & 1)
    led6.value((x[pasy] >> 2) & 1)
    led7.value((x[pasy] >> 3) & 1)

def movex(pasx):
    led.value((x[pasx] >> 0) & 1)
    led1.value((x[pasx] >> 1) & 1)
    led2.value((x[pasx] >> 2) & 1)
    led3.value((x[pasx] >> 3) & 1)


def extract(a4):
    vrt=""
    for a5 in a4:    
        if  a5 in('.','0','1','2','3','4','5','6','7','8','9',"-"):
            vrt +=a5
        else:
            break
    return vrt    

def gcode_exec(strg):
    global x0,y0,x1,y1,dx,dy,sx,sy,error,absolute,este
    if "G90" in strg:
        absolute=1
        
    if "G91" in strg:
        absolute=0       
    
      
    if ("X") in strg:
        nn=strg.split("X")
        k=int(float(extract(nn[1]))*160)
        if absolute:
            x1=k             
        else:
            x1=x0+k
   
  
    if ("Y") in strg:
        targhety=0
        nn=strg.split("Y")
        k=int(float(extract(nn[1]))*160)
        if absolute:
            y1=k
        else:
            y1=y0+k 
    #print(x0," ",y0," ",x1," ",y1)
    dx = abs(x1 - x0)
    if x0<x1:
        sx=1
    else:
        sx=-1
    dy = -abs(y1 - y0)
    if y0<y1:
        sy=1
    else:
        sy=-1
    error = dx + dy           
        
       
           
    
def do_step(): 
    global currentx,x0,y0,x1,y1,sx,sy,dx,dy,error
    #print("x0=",x0," x1=",x1," y0=",y0," y1=",y1)
    e2 = 2 * error
    if e2 >= dy:
        error = error + dy
        x0 = x0 + sx
        #print("sx=",sx)
        movex(x0&7)
    if e2 <= dx:
        error = error + dx
        y0 = y0 + sy
        #print("sy=",sy)
        movey(y0&7)        
    time.sleep_us(300)
    
    

while True:

    if x0 == x1 and y0 == y1: # arrivatto in punto di destinazione
        if len(buffer)>0: # daca buffer e gol atunci sare peste asta
            #print(len(buffer)," buffer prima=",buffer)
            gcode_exec(buffer.pop(0)) 
            #print(len(buffer)," buffer dopo=",buffer)
            conn.send("ok\n")
            currentx=0            
    else:
            do_step() # executa pana ajunge la destinazione

    try:       
        request = conn.recv(200).decode()         
        if "?" in request:   
            conn.send("<Idle|MPos:"+str(x0/160)+","+str(y0/160)+",0.000|FS:0,0>\r")
            if(x0==0)and(y0==0): #se cursore e arivatto in 0,0 e buffer ancora ha data
                if len(buffer)>0: # significa che qualche ok e scapato o almeno non mi spiego 
                    conn.send("ok\n") #perche 3-4 istruzioni a fine risulta non lette
                    
                 
        elif "$$" in request:
            conn.send("ok\n")
        elif "costycnc" in request:
            conn.send("HTTP/1.1 200 ok\n")
            conn.send("Content-type: text /html\n")		
            conn.send("Connection: close\n\n")    
            conn.sendall('<html><head><meta name="viewport" content="width=device-width, initial-scale=1"></head><body><a href="192.168.43.1/b=0"><button>left</button></a><a href="192.168.43.1/b=1"><button>right</button></a><a href="192.168.43.1/b=2"><button>stop</button></a></body></html>')	
            conn.close()         
        else: 
            if len(buffer)<10:
                b=request.split("\n")
                for a in b: 
                    if a=="": 
                        pass
                    else:                        
                        buffer.append(a)

                
    except OSError as e:
        pass                 
      
# Clean up the connection.
conn.close()
print("closed. ") 
*/

