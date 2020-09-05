
#include "LedControl.h"

// --------------------------------------------------------------------------------- //
// Parametres Boutons                                                                //
// --------------------------------------------------------------------------------- //

#define BTN1 A5  // Start / Stop
#define BTN2 5   // Tap Tempo
#define ROTB 4   // Rotary Button

#define ROT1 2
#define ROT2 3

// --------------------------------------------------------------------------------- //
// Parametres Affichage                                                              //
// --------------------------------------------------------------------------------- //

#define DGT8_DIN 12
#define DGT8_CS  10
#define DGT8_CLK 9

LedControl lc=LedControl(DGT8_DIN,DGT8_CLK,DGT8_CS,1);

#define LED1 8  // tempo
#define LED2 6  // Running

// --------------------------------------------------------------------------------- //
//  Controles pour generateur de sons                                                //
// --------------------------------------------------------------------------------- //

#define Sound1 15 // A1  // Kick
#define Sound2 16 // A2  // HiHat
#define Sound3 17 // A3  // Snare
#define Sound4 18 // A4  // Ride

// --------------------------------------------------------------------------------- //
// Procedures d'Affichage                                                            //
// --------------------------------------------------------------------------------- //

void DisplayInt(int xi) {
  lc.setDigit(0,0,xi % 10,false);
  xi=xi / 10;
  lc.setDigit(0,1,xi % 10,false);
  xi=xi / 10;
  lc.setDigit(0,2,xi % 10,false);
}

void DisplayInt2(int xi) {
  lc.setDigit(0,4,xi % 10,false);
  xi=xi / 10;
  lc.setDigit(0,5,xi % 10,false);
  xi=xi / 10;
  lc.setDigit(0,6,xi % 10,false);
}

void DisplayInt8(long int xi) {
  lc.setDigit(0,0,xi % 10,false);
  xi=xi / 10;
  lc.setDigit(0,1,xi % 10,false);
  xi=xi / 10;
  lc.setDigit(0,2,xi % 10,false);
  xi=xi / 10;
  lc.setDigit(0,3,xi % 10,false);
  xi=xi / 10;
  lc.setDigit(0,4,xi % 10,false);
  xi=xi / 10;
  lc.setDigit(0,5,xi % 10,false);
  xi=xi / 10;
  lc.setDigit(0,6,xi % 10,false);
  xi=xi / 10;
  lc.setDigit(0,7,xi % 10,false);
}

// --------------------------------------------------------------------------------- //
//                                      Paterns                                      //
// --------------------------------------------------------------------------------- //

#define timecte 234375

boolean BmpChange = false;
int Bmp     =  80;
int BmpO    =   0;     // Old value
int Divider =   2;     // 1 noire, 2 croche, 4 double croche 
int Dly     = timecte / Bmp / Divider;  

// 1 - Kick
// 2 - HiHat
// 3 - Snare
// 4 - Ride

#define MAXNOTES  48
#define NBPatern  32
byte    Ntemps; 

byte Tempo[MAXNOTES];
//const byte PROGMEM Temp00[] = { 1,0,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0 , 1,0,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0 , 1,0,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0 }; const byte NT00 = 48;  const byte DV00 = 4; // this 3 paterns 
//const byte PROGMEM Temp01[] = { 1,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0 , 1,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0 , 1,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0 }; const byte NT01 = 48;  const byte DV01 = 2; //       are 
//const byte PROGMEM Temp02[] = { 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1 , 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1 , 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1 }; const byte NT02 = 48;  const byte DV02 = 1; //   equivalent

                            //  1         2         3         4         5         6         7         8         9         10        11        12                    Nb Notes               Space Divider    
const byte PROGMEM Temp00[] = { 1,0,1,0 , 1,0,1,0 , 1,0,1,0 , 1,0,1,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 };       const byte NT00 = 16;  const byte DV00 = 2; // Rythme  
const byte PROGMEM Temp01[] = { 1,0,1,1 , 1,0,1,1 , 1,0,1,1 , 1,0,2,2 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 };       const byte NT01 = 16;  const byte DV01 = 2; // Rythme 
const byte PROGMEM Temp02[] = { 1,0,1,0 , 1,1,1,0 , 1,0,1,0 , 1,1,2,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 };       const byte NT02 = 16;  const byte DV02 = 2; // Rythme 
const byte PROGMEM Temp03[] = { 1,1,2,2 , 1,1,2,2 , 1,1,2,2 , 1,1,2,2 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 };       const byte NT03 = 16;  const byte DV03 = 2; // Rythme 
const byte PROGMEM Temp04[] = { 1,0,1,0 , 1,0,1,0 , 1,0,1,0 , 1,0,1,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 };       const byte NT04 = 16;  const byte DV04 = 2; // Rythme  
const byte PROGMEM Temp05[] = { 1,0,1,0 , 1,0,1,0 , 1,0,1,0 , 1,0,1,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 };       const byte NT05 = 16;  const byte DV05 = 2; // Rythme  
const byte PROGMEM Temp06[] = { 1,0,1,0 , 1,0,1,0 , 1,0,1,0 , 1,0,1,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 };       const byte NT06 = 16;  const byte DV06 = 2; // Rythme  
const byte PROGMEM Temp07[] = { 1,0,1,0 , 1,0,1,0 , 1,0,1,0 , 1,0,1,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 };       const byte NT07 = 16;  const byte DV07 = 2; // Rythme  

const byte PROGMEM Temp08[] = { 2,1,1,1 , 1,1,1,1 , 1,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 3,1,1,1 , 3,1,1,1 , 2,1,1,1 , 1,1,1,1 };       const byte NT08 = 48;  const byte DV08 = 1; // Blues 
const byte PROGMEM Temp09[] = { 2,1,1,1 , 1,1,1,1 , 1,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 3,1,1,1 , 3,1,1,1 , 2,1,1,1 , 1,1,1,1 };       const byte NT09 = 48;  const byte DV09 = 1; // Blues 
const byte PROGMEM Temp10[] = { 2,1,1,1 , 1,1,1,1 , 1,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 3,1,1,1 , 3,1,1,1 , 2,1,1,1 , 1,1,1,1 };       const byte NT10 = 48;  const byte DV10 = 1; // Blues 
const byte PROGMEM Temp11[] = { 2,1,1,1 , 1,1,1,1 , 1,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 3,1,1,1 , 3,1,1,1 , 2,1,1,1 , 1,1,1,1 };       const byte NT11 = 48;  const byte DV11 = 1; // Blues 
const byte PROGMEM Temp12[] = { 2,1,1,1 , 1,1,1,1 , 1,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 3,1,1,1 , 3,1,1,1 , 2,1,1,1 , 1,1,1,1 };       const byte NT12 = 48;  const byte DV12 = 1; // Blues 
const byte PROGMEM Temp13[] = { 2,1,1,1 , 1,1,1,1 , 1,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 3,1,1,1 , 3,1,1,1 , 2,1,1,1 , 1,1,1,1 };       const byte NT13 = 48;  const byte DV13 = 1; // Blues 
const byte PROGMEM Temp14[] = { 2,1,1,1 , 1,1,1,1 , 1,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 3,1,1,1 , 3,1,1,1 , 2,1,1,1 , 1,1,1,1 };       const byte NT14 = 48;  const byte DV14 = 1; // Blues 
const byte PROGMEM Temp15[] = { 2,1,1,1 , 1,1,1,1 , 1,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 2,1,1,1 , 1,1,1,1 , 3,1,1,1 , 3,1,1,1 , 2,1,1,1 , 1,1,1,1 };       const byte NT15 = 48;  const byte DV15 = 1; // Blues 

                             // 1                 2                 3                 4                 5                 6                 
const byte PROGMEM Temp16[] = { 1,0,0,0,1,0,0,0 , 1,0,0,0,1,0,0,0 , 1,0,0,0,3,0,0,0 , 0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0 };                   const byte NT16 = 24;  const byte DV16 = 8; //
const byte PROGMEM Temp17[] = { 1,0,0,0,1,0,0,0 , 1,0,0,0,1,0,0,0 , 1,0,0,0,1,0,0,0 , 1,0,0,0,1,0,0,0 , 1,0,0,0,3,0,0,0 , 0,0,0,0,0,0,0,0 };                   const byte NT17 = 40;  const byte DV17 = 8; //
const byte PROGMEM Temp18[] = { 1,0,0,0,1,0,0,0 , 1,0,0,0,1,0,0,0 , 1,0,0,0,1,0,0,0 , 1,0,0,0,1,0,0,0 , 0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0 };                   const byte NT18 = 24;  const byte DV18 = 8; //
const byte PROGMEM Temp19[] = { 1,0,0,0,0,0,0,0 , 1,0,0,0,0,0,0,0 , 1,0,0,0,0,0,0,0 , 1,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0 };                   const byte NT19 = 24;  const byte DV19 = 8; //

                             // 1       2       3       4       5       6       7      8       9      10      11      12      13      14      15      16     
const byte PROGMEM Temp20[] = { 1,0,1 , 1,0,1 , 1,0,1 , 1,0,1 , 1,0,1 , 1,0,1 , 1,0,1, 1,0,1 , 0,0,0, 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 }; const byte NT20 = 24;  const byte DV20 = 3; // Suffle 01
const byte PROGMEM Temp21[] = { 1,0,1 , 1,0,1 , 1,0,1 , 1,0,1 , 1,0,1 , 1,0,1 , 1,0,1, 1,0,1 , 0,0,0, 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 }; const byte NT21 = 24;  const byte DV21 = 3; // Suffle 01
const byte PROGMEM Temp22[] = { 1,0,2 , 2,0,2 , 3,0,2 , 2,0,2 , 1,0,2 , 2,0,2 , 3,0,2, 2,0,2 , 0,0,0, 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 }; const byte NT22 = 24;  const byte DV22 = 3; // Suffle 02
const byte PROGMEM Temp23[] = { 1,0,2 , 2,0,2 , 3,0,2 , 2,0,2 , 1,0,2 , 2,0,1 , 1,1,1, 1,0,2 , 0,0,0, 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 , 0,0,0 }; const byte NT23 = 24;  const byte DV23 = 3; // Suffle 03

                             // 1             2             3             4             5             6             7             8       
const byte PROGMEM Temp24[] = { 1,0,0,1,1,0 , 1,0,0,1,1,0 , 1,0,0,1,1,0 , 1,0,0,1,1,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 };               const byte NT24 = 24;  const byte DV24 = 6; //
const byte PROGMEM Temp25[] = { 1,0,1,1,0,0 , 1,0,1,1,0,0 , 1,0,1,1,0,0 , 1,0,1,1,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 };               const byte NT25 = 24;  const byte DV25 = 6; //
const byte PROGMEM Temp26[] = { 1,0,0,0,0,0 , 1,0,0,0,0,0 , 1,0,0,0,0,0 , 1,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 };               const byte NT26 = 24;  const byte DV26 = 6; //
const byte PROGMEM Temp27[] = { 1,0,0,0,0,0 , 1,0,0,0,0,0 , 1,0,0,0,0,0 , 1,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 };               const byte NT27 = 24;  const byte DV27 = 6; //

                            //  1         2         3         4         5         6         7         8         9         10        11        12
const byte PROGMEM Temp28[] = { 1,0,2,0 , 3,0,2,0 , 2,0,1,0 , 3,0,2,0 , 1,0,2,0 , 3,0,2,0 , 2,0,1,0 , 3,0,2,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 };       const byte NT28 = 32;  const byte DV28 = 4; // Rock 3
const byte PROGMEM Temp29[] = { 1,0,2,0 , 1,0,3,0 , 1,0,2,0 , 1,0,3,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 };       const byte NT29 = 16;  const byte DV29 = 2; // House 1
const byte PROGMEM Temp30[] = { 1,0,2,1 , 3,0,1,0 , 2,0,1,0 , 3,1,2,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 };       const byte NT30 = 16;  const byte DV30 = 2; // Hip-Hop
const byte PROGMEM Temp31[] = { 1,0,2,1 , 3,0,1,0 , 2,0,1,0 , 3,1,2,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 , 0,0,0,0 };       const byte NT31 = 16;  const byte DV31 = 2; // Hip-Hop


byte Patern  = 0;
byte PaternO = 0;

void cptab( byte Tx[] ) {
  for (int i=0;i<MAXNOTES;i++) {
    Tempo[i]=pgm_read_byte( &(Tx[i]) );   
  }
}

void SelectTemo(int n) {
  switch (n) {
    case  1 : Ntemps=NT01; cptab(Temp01); Divider=DV01; break;
    case  2 : Ntemps=NT02; cptab(Temp02); Divider=DV02; break;
    case  3 : Ntemps=NT03; cptab(Temp03); Divider=DV03; break;
    case  4 : Ntemps=NT04; cptab(Temp04); Divider=DV04; break;
    case  5 : Ntemps=NT05; cptab(Temp05); Divider=DV05; break;
    case  6 : Ntemps=NT06; cptab(Temp06); Divider=DV06; break;
    case  7 : Ntemps=NT07; cptab(Temp07); Divider=DV07; break;
    case  8 : Ntemps=NT08; cptab(Temp08); Divider=DV08; break;
    case  9 : Ntemps=NT09; cptab(Temp09); Divider=DV09; break;
    case 10 : Ntemps=NT10; cptab(Temp10); Divider=DV10; break;
    case 11 : Ntemps=NT11; cptab(Temp11); Divider=DV11; break;
    case 12 : Ntemps=NT12; cptab(Temp12); Divider=DV12; break;
    case 13 : Ntemps=NT13; cptab(Temp13); Divider=DV13; break;
    case 14 : Ntemps=NT14; cptab(Temp14); Divider=DV14; break;
    case 15 : Ntemps=NT15; cptab(Temp15); Divider=DV15; break;
    
    case 16 : Ntemps=NT16; cptab(Temp16); Divider=DV16; break;
    case 17 : Ntemps=NT17; cptab(Temp17); Divider=DV17; break;
    case 18 : Ntemps=NT18; cptab(Temp18); Divider=DV18; break;
    case 19 : Ntemps=NT19; cptab(Temp19); Divider=DV19; break;
    case 20 : Ntemps=NT20; cptab(Temp20); Divider=DV20; break;
    case 21 : Ntemps=NT21; cptab(Temp21); Divider=DV21; break;
    case 22 : Ntemps=NT22; cptab(Temp22); Divider=DV22; break;
    case 23 : Ntemps=NT23; cptab(Temp23); Divider=DV23; break;
    case 24 : Ntemps=NT24; cptab(Temp24); Divider=DV24; break;
    case 25 : Ntemps=NT25; cptab(Temp25); Divider=DV25; break;
    case 26 : Ntemps=NT26; cptab(Temp26); Divider=DV26; break;
    case 27 : Ntemps=NT27; cptab(Temp27); Divider=DV27; break;
    case 28 : Ntemps=NT28; cptab(Temp28); Divider=DV28; break;
    case 29 : Ntemps=NT29; cptab(Temp29); Divider=DV29; break;
    case 30 : Ntemps=NT30; cptab(Temp30); Divider=DV30; break;
    case 31 : Ntemps=NT31; cptab(Temp31); Divider=DV31; break;
        
    default: Ntemps=NT00; cptab(Temp00);  Divider=DV00;  
  }
  Dly=timecte / Bmp / Divider;  
}

// --------------------------------------------------------------------------------- //
//                         Interruptions et BMP                                      //
// --------------------------------------------------------------------------------- //

unsigned int Compteur = Dly;  //Compteur pour interruption

ISR (TIMER2_OVF_vect) {   
  if (!Compteur--) {
    Compteur=Dly;  
    InterruptTimer2();
  }  
} 

int cled=0;
boolean state = true;
boolean state2= false;
int ctemp=0;
int instrum=0;

void InterruptTimer2() {
  if ( cled==0 ) { 
    state= not(state);
  }
  cled++;
  if ( cled > 1 ) {
    cled=0;
  }
  
  digitalWrite(LED1, state);
  state2= not(state2);

  if (state2 ) {
    if (ctemp>=Ntemps) {
      ctemp=0;
    }
    instrum=Tempo[ctemp];
    ctemp++;
    if (instrum > 0 ) {
      digitalWrite(Sound1 -1 + instrum,true);
    }    
  } else {
    if (instrum > 0 ) {
      digitalWrite(Sound1 -1 + instrum,false);
    }    
  }
}

// --------------------------------------------------------------------------------- //
//                                 Boutons                                           //
// --------------------------------------------------------------------------------- //

boolean Btn1Down =false;
boolean Btn1Press=false;

boolean Btn2Down =false;
boolean Btn2Press=false;
long int Btn2time=0; 
long int Btn2Delay; 

boolean ROTBDown =false;
boolean ROTBPress=false;

void CheckButtons () {  
  // ------------------  test bouton 1 ------------------
  if ( Btn1Down ) {
    if (digitalRead(BTN1)==true) { // bouton plus enfoncé
      Btn1Down=false;
      delay(10);
    }
  } else {
    if (digitalRead(BTN1)==false) { // bouton enfoncé
      Btn1Down=true;
      Btn1Press=true;
    }    
  }
  // ---------------  test bouton 2 ( TAP ) -------------
  long int t0=millis();
  if ( Btn1Down ) {
    if (digitalRead(BTN2)==true) { // bouton plus enfoncé
      Btn2Down=false;
      delay(10);
    }
  } else {
    if (digitalRead(BTN2)==false) { // bouton enfoncé
      Btn2Down=true;
      if (Btn2time>0) {
        Btn2Delay=t0-Btn2time;
        if ((Btn2Delay>100) && (Btn2Delay<1000)) {
          Bmp=30000/Btn2Delay*(Divider/2);
          Dly=timecte/Bmp/Divider;
          BmpChange=true;
          DisplayInt(Bmp);
        }
        delay(5);
      }
      Btn2time =t0;
    } else {
      if (t0-Btn2time>1000) {
        Btn2time=0;
      }
    }
  }  

  // -------------  test bouton 3 ( Rotary ) ------------
  if ( ROTBDown ) {
    if (digitalRead(ROTB)==true) { // bouton plus enfoncé
      ROTBDown=false;
      delay(10);
    }
  } else {
    if (digitalRead(ROTB)==false) { // bouton enfoncé
      ROTBDown=true;
      ROTBPress=true;
    }    
  }
}

boolean keyPress1() {
  boolean tmp;
  tmp=Btn1Press;
  Btn1Press=false;
  return tmp; 
}

boolean keyPress3() {
  boolean tmp;
  tmp=ROTBPress;
  ROTBPress=false;
  return tmp; 
}

// --------------------------------------------------------------------------------- //
//  Rotary Encoder                                                                   //
// --------------------------------------------------------------------------------- //

unsigned long ltime;
short int mode=0;

void RotaryChange() {
  unsigned long ntime;
  int increment=0;
  
  ntime=millis();
  if ((ntime-ltime) < 100 ) {
    if (digitalRead(ROT1) == digitalRead(ROT2)) {
      increment= -1;   
     } else {
      increment= +1;   
     }
  }

  if (mode==0) {
    Bmp   = Bmp   + increment;      
  } else if (mode==1) {
    Patern = Patern + increment;       
  }

  ltime=ntime;
}

// --------------------------------------------------------------------------------- //
// set dot point side of selected ( Patern / Bmp )
 
void Active() {
  if (mode==0) {
    lc.setLed(0, 3, 0, true);
    lc.setLed(0, 7, 0, false);
  } else {
    lc.setLed(0, 3, 0, false);
    lc.setLed(0, 7, 0, true);
  }
}

// --------------------------------------------------------------------------------- //
//                                  S E T U P                                        //
// --------------------------------------------------------------------------------- //
boolean StartRun = false;

void setup() {
  SelectTemo(0);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  pinMode(Sound1,OUTPUT);
  pinMode(Sound2,OUTPUT);
  pinMode(Sound3,OUTPUT);
  pinMode(Sound4,OUTPUT);
  digitalWrite(Sound1,false);
  digitalWrite(Sound2,false);
  digitalWrite(Sound3,false);
  digitalWrite(Sound4,false); 
       
  pinMode(BTN1,INPUT_PULLUP);
  pinMode(BTN2,INPUT_PULLUP);

  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);

  pinMode(ROT1,INPUT_PULLUP);
  pinMode(ROT2,INPUT_PULLUP);
  pinMode(ROTB,INPUT_PULLUP);
  attachInterrupt(0, RotaryChange, CHANGE);
  
  // initialisation interruption Timer 2
  //MsTimer2::set(Dly, InterruptTimer2);
  //MsTimer2::start(); // active Timer2 
  
  // Initialise le Timer 2 pour déclencher les interruptions à intervalle régulier
  TCCR2A = 0; //default 
  TCCR2B = 0b00000010; // clk / 8
//  TIMSK2 = 0b00000001; //  
  
  sei();               // autorise les interruptions
  
  DisplayInt(Bmp);
  DisplayInt2(Patern);
  Active();
}

// --------------------------------------------------------------------------------- //
//                                  L O O P                                          //
// --------------------------------------------------------------------------------- //

void loop() { 
  CheckButtons();
  
  if (keyPress3()) {
    mode++;
    if (mode >1) {
      mode=0;   
    }
    Active();
  }
  
  if (keyPress1()) {
    StartRun=not(StartRun);
    if (StartRun ) {
      cli();
      TIMSK2 = 0b00000001;
      digitalWrite(LED2,true);  
      sei();
    } else {
      cli();
      TIMSK2 = 0b00000000;  
      digitalWrite(LED2,false);  
      sei();
    }
  }

  if ( Bmp != BmpO ) {
    Dly=timecte / Bmp / Divider;  // calculate Delay
    BmpO=Bmp;
    BmpChange=true;
    DisplayInt(Bmp);
  }

  if ( Patern != PaternO ) {
    if (Patern <  0 )       { Patern = NBPatern; }
    if (Patern >= NBPatern) { Patern = 0; }
    PaternO=Patern;
    DisplayInt2(Patern);
    SelectTemo(Patern);
  }
}
