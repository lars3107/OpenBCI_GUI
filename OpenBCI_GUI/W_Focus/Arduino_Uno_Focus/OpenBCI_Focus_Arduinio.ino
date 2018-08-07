#include <ShiftRegister74HC595.h>

ShiftRegister74HC595 sr1 (1, 13, 11, 12);
ShiftRegister74HC595 sr2 (1, 10, 8, 9);
ShiftRegister74HC595 sr3 (1, 7, 5, 6);
ShiftRegister74HC595 sr4 (1, 4, 2, 3);      //Initialisierung der Classes für die Schieberegister.
                                            //Erste Zahl = Anzahl der Schieberegister in Reihe
                                            //Die drei nachfolgenden Zahlen geben die Ports an, an denen der Schieberegister vom Arduino angesteuert wird.

String inStringA = "";                      //in inStringA wird der ankommende Wert der Alpha-Wellen gespeichert
String inStringB = "";                      //in inStringB wird der ankommende Wert der Beta-Wellen gespeichert
int n=0;                                    //n ist eine Hilfsvariable zum differenzieren zwischen Alpha- und Beta-Wellen




void setup() {
  // initialize serial:
  Serial.begin(9600);                       //Initialisierung der seriellen Schnittstelle mit einer Baudrate von 9600
  
 sr1.setAllLow();                           //Setzt alle Pins des ersten Schieberegisters auf 0 und schaltet somit die damit verbundenen LED's aus.
 sr2.setAllLow();                           //Setzt alle Pins des zweiten Schieberegisters auf 0 und schaltet somit die damit verbundenen LED's aus.
 sr3.setAllLow();                           //Setzt alle Pins des dritten Schieberegisters auf 0 und schaltet somit die damit verbundenen LED's aus.
 sr4.setAllLow();                           //Setzt alle Pins des vierten Schieberegisters auf 0 und schaltet somit die damit verbundenen LED's aus.

  


}
void loop() {
uint8_t led0[] = {B00000000}; 
uint8_t led1[] = {B01000000};
uint8_t led2[] = {B01100000}; 
uint8_t led3[] = {B01110000}; 
uint8_t led4[] = {B01111000}; 
uint8_t led5[] = {B01111100}; 
uint8_t led6[] = {B01111110};               //Dies ist die Zuweisung eines Bitmusters zu dem Array led6[]. 
                                            //Das Bitmuster entspricht der Schaltung der Pins am Schieberegister, wobei die erste Stelle von links dem ersten Port des Schieberegisters entspricht.
                                            //z.B. wird beim Muster led1 die LED am zweiten port angeschaltet.
                                            //Da bei jedem Schieberegister erst ab dem zweiten Ausgang gearbeitet wird, ist es im Endeffekt die erste LED, die angeschaltet wird. 

 while (Serial.available() > 0) {           //Alles Nachfolgende wird nur dann ausgeführt und auch nur solange ausgeführt,wie Daten über den seriellen Port ankommen und ausgelesen werden können.
   
   
char inCharA;                             
char inCharB;                               //Initialisierng von zwei Char-Variablen, um den String wieder zusammen zu setzten.
                                            //der Wert der Wellen, der in einem String gesendet wird, kommt hintereinander als einzelne Zeichen an. 
                                            //die Zeichen werden jeweils in der entsprechenden Char-Variablen gespeichert und später wieder zu einem gesamten String zusammen gesetzt.
    
    if(n == 0)                              //Entscheidung, ob Alpha-Werte, oder Beta-Werte ankommen.
                                            //Zu Anfang ist der Wert = 0 also werden alle Zeichen bis zum ersten 'e' als Alphawellen abgespeichert.
    {
    inCharA = (char)Serial.read();          //Serial.read() liest das ankommende Zeichen und speichert es in der Variablen inCharA
    if(inCharA!='e')                        //da die Werte nahtlos hintereinander ankommen, muss identifizert werden, wann ein Wert vollständig ist.
                                            //Zu diesem Zweck wurde hinter jeden Wert ein 'e' gehängt.
                                            //wenn der ankommende Wert kein 'e' ist, ist es ein signifikantes Zeichen und wird somit an den String angehängt.
      {
      inStringA += inCharA;                 //entspricht a=a+b; Speichert das jeweilige Char-Zeichen in der String-Variablen inStringA.
                                            //durch die Void Loop wird bei jedem Durchgang das neu ankommende Zeichen gelesen und an den String angehängt,
                                            //solange, bis ein 'e' kommt, der Vorgang abbricht und der Wert vollständig übermittelt wurde.
      }
    }
    else                                    //Falls n nicht 0 ist erfolgt der selbe Vorgang wie oben nur, dass die ankommenden Zeichen als Werte für Beta-Wellen abgespeichert werden.
    {
      // get the new byte:
    inCharB = (char)Serial.read();
    // add it to the inputString:
    if(inCharB!='e')
      {
      inStringB += inCharB;
      }
    }
    
 
    if (inCharA== 'e')                      //Wenn die jweilige Charvariale für die Alpha-Wellen ein 'e' identifiziert hat, folgt die Auswertung.
    {
      if (inStringA.toInt() > 0)
        {
        sr3.setAll(led0);
        sr4.setAll(led1);
        }
       if (inStringA.toInt() >= 2000)       //Je nachdem, wie groß die Werte sind, werden entsprechende LEDs, über die Bitmuster angesteuert.
                                            //es entsteht somit eine Lichtleiste die ansteigt, je höher die Werte sind, 
          {
            sr3.setAll(led0);
            sr4.setAll(led2);
           }
       if (inStringA.toInt() >= 4000) 
          {
             sr3.setAll(led0);
             sr4.setAll(led3);
          }
       if (inStringA.toInt() >= 6000)
          {
              sr3.setAll(led0);
              sr4.setAll(led4);
           }
       if (inStringA.toInt() >= 8000)
          {
            sr3.setAll(led0);
            sr4.setAll(led5);
          }
        if (inStringA.toInt() >= 10000)
          {
            sr3.setAll(led0);
            sr4.setAll(led6);
          }
         if (inStringA.toInt() >= 12000)
          {                                  
            sr3.setAll(led1);
            sr4.setAll(led6);
          }
         if (inStringA.toInt() >= 14000)
          {
            sr3.setAll(led2);
            sr4.setAll(led6);
          }
         if (inStringA.toInt() >= 16000)
          {
            sr3.setAll(led3);
            sr4.setAll(led6);
          }
         if (inStringA.toInt() >= 18000)
          {
            sr3.setAll(led4);
            sr4.setAll(led6);
          }
         if (inStringA.toInt() >= 20000)
          {
            sr3.setAll(led5);
            sr4.setAll(led6);
          }
         if (inStringA.toInt() >= 22000)
          {
            sr3.setAll(led6);
            sr4.setAll(led6);
          }
        
       
           
         inStringA="";                      //Wenn die Auswertung erfolgt ist, wird der Wert aus der String Variabeln gelöscht, damit er wieder neu beschieben werden kann.
    n=1;                                    // n wird auf 1 gesetzt, um somit den nächsten ankommenden Wert als Beta-Wert zu speichern.
    }
 
    if (inCharB== 'e') {                    //Hier folgt der gleiche Prozess, wie bei den Alpha-Wellen, nur für die Beta-Wellen.
      if (inStringB.toInt() > 0)
        {
        sr1.setAll(led0);
        sr2.setAll(led1);
        }
       if (inStringB.toInt() >= 2000)
          {
            sr1.setAll(led0);
            sr2.setAll(led2);
           }
       if (inStringB.toInt() >= 4000) 
          {
             sr1.setAll(led0);
             sr2.setAll(led3);
          }
       if (inStringB.toInt() >= 6000)
          {
              sr1.setAll(led0);
              sr2.setAll(led4);
           }
       if (inStringB.toInt() >= 8000)
          {
            sr1.setAll(led0);
            sr2.setAll(led5);
          }
        if (inStringB.toInt() >= 10000)
          {
            sr1.setAll(led0);
            sr2.setAll(led6);
          }
         if (inStringB.toInt() >= 12000)      
          {
            sr1.setAll(led1);
            sr2.setAll(led6);
          }
         if (inStringB.toInt() >= 14000)
          {
            sr1.setAll(led2);
            sr2.setAll(led6);
          }
         if (inStringB.toInt() >= 16000)
          {
            sr1.setAll(led3);
            sr2.setAll(led6);
          }
         if (inStringB.toInt() >= 18000)
          {
            sr1.setAll(led4);
            sr2.setAll(led6);
          }
         if (inStringB.toInt() >= 20000)
          {
            sr1.setAll(led5);
            sr2.setAll(led6);
          }
         if (inStringB.toInt() >= 22000)
          {
            sr1.setAll(led6);
            sr2.setAll(led6);
          }
        
       

        inStringB="";                         //Auch hier wird der Wert der Beta-Wellen wieder zurückgesetzt, um wieder neu beschrieben zu werden.
    n=0;                                      //Hier wird n wieder auf 0 gesetzt, um den nächsten Wert wieder als Alpha-Wert zu Speichern.
                                              //Werte für Alpha-Wellen und Beta-Wellen kommen immer abwechsend an.
    }
    } 
   }
   
  
