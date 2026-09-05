//PERFORM MULTIPLICATION AND DISPLAY ANSWER AND IF EXCEEDS 9999 THEN DISPLAY EEEE
//press * for multiplication and # for getting answer
//GLOBAL VARIABLE DECLARATION
volatile char *row,*col,*disp,*sel;
volatile short mem[10]={0};
volatile long k,z,x=0,y=0;
volatile short arr[11]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,0x06},arr2[4]={0};
volatile int i,j=0,power=1,cut=0;

void setup(){
volatile char *dir;
dir=0x21;*dir=0xff;//port a
dir=0x27;*dir=0xFF;//port c
dir=0x107;*dir=0x00;//port k
dir=0x30;*dir=0xff;//port f
}

void loop(){
row=0x31;col=0x106;disp=0x22;sel=0x28;
while(1){
  for(i=0;i<4;i++){
    row_write();
    col_scan();
  }
 if(cut==1) break;
}
 addition();
 if(cut!=2){
 while(1){
 display();
}
}
else{
  while(1){
    display_error();
  }
}
}

void row_write(){
*row=(1<<i);
}


void col_scan(){
if(*col!=0){
      if(i==0 && *col==0x01) mem[j]=0x01;
      if(i==0 && *col==0x02) mem[j]=0x02;
      if(i==0 && *col==0x04) mem[j]=0x03;
      if(i==1 && *col==0x01) mem[j]=0x04;
      if(i==1 && *col==0x02) mem[j]=0x05;
      if(i==1 && *col==0x04) mem[j]=0x06; 
      if(i==2 && *col==0x01) mem[j]=0x07;
      if(i==2 && *col==0x02) mem[j]=0x08;
      if(i==2 && *col==0x04) mem[j]=0x09; 
      if(i==3 && *col==0x02) mem[j]=0x00;
      if(i==3 && *col==0x01) mem[j]=0x0a;// * press
      if(i==3 && *col==0x04) {mem[j]=0x0b;// # press
      cut=1;
      }
      for(k=0;k<100000;k++);
      j++;
    }
}


void addition(){
for(i=j-2;mem[i]!=0x0a;i--){ //second number
  x=x+(mem[i]*power); 
  power=power*10;
}
power=1;
for(k=i-1;k>=0;k--){ //first number
  y=y+(mem[k]*power);
  power=power*10;
}
z= y*x;
if(z>9999){
  cut=2;
}
else{
  for(i=3;i>=0;i--){
    arr2[i]=z%10;
    z=z/10;
  }
}
}

void display(){
 for(i=0;i<=3;i++){
  *sel=(1<<i);
  *disp=arr[arr2[i]];
  for(k=0;k<100;k++);
  *disp=0xff;
  for(k=0;k<100;k++);
 }
 }

 void display_error(){
 for(i=0;i<=3;i++){
  *sel=(1<<i);
  *disp=arr[10];
  for(k=0;k<100;k++);
  *disp=0xff;
  for(k=0;k<100;k++);
 }
 }
