#include <yasm.h>
YASM Machine; 

void setup() {
    Serial.begin(9600); 
    Machine.next(S3); //definition etat initial
    Serial.println("YASM test");
}

void loop() {
    static int j = 0;
    if (j>20) return;  

    Serial.print("loop "); Serial.print(j++); Serial.print(" ");
    Machine.run(); //execution de la machine
    
    if (j==2) Machine.stop();    //arret depuis l'exterieur
    if (j==3) Machine.resume();
    if (j==4) Machine.stop();
    if (j==6) Machine.next(S3);
    if (j==8) Machine.next(S3,true);
    if (j==12) Machine.resume();
    if (j==18) {Machine.next(S3,true);Machine.stop();}
    if (j==19) Machine.resume();
    
    Serial.println(" ");
}

//////////////// state machine states //////////////////
void S3() {
    static int i =0;
    if (Machine.isFirstRun()) Serial.print("fisrtRun");
    else Serial.print("        ");
    Serial.print(" state3 "); Serial.print(i++); Serial.print(" ");
    Serial.print(Machine.runCount());
    
    if(i==8) Machine.stop();
    if(Machine.runCount() == 5) Machine.next(S3);
    if(Machine.runCount() == 6) Machine.next(S3,true);
}
