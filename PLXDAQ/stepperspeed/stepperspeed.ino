const long f = 1000000; //frequency of the counter;
int Km = 64, reduktor = 64, K = Km*reduktor,kasni=66;
// dspeed [rad/s]-desired speed, acce [rad/s^2]-acceleration
// dece[rad/s^2]-deceleration, ugao[deg]-angle
float dspeed = 3, acce = 0.5, dece = 1.5, ugao = 0;
double alfa = TWO_PI/K, Co, Cm, Ci,Ra,Rd;
long imaK = 0,N = 0,nad = 0,na = 0, nd = 0, np = 0, broj = 0;
boolean smjer = true, acc = true, stoj = true;
//uni-polar motor – we use microstepping manner of stepping
byte cw[] = {0x01,0x03,0x02,0x06,0x04,0x0C,0x08,0x09};
byte duzcw = sizeof(cw), kk = 0, maska = 0xF0; //
char chh;
double q;
//
void setup(){
 Serial.begin(9600);
 Serial.println("Enter some of the following commands:");
 Serial.print("Uxxxx, - ");
 Serial.println("desired angle[deg]x10");
 Serial.print("Bxx, - ");
 Serial.println("desired speed [rad/s]x10");
 Serial.print("Axx, -");
 Serial.println("acceleration[rad/s^2]x10");
 Serial.print("Dxx, -");
 Serial.println("deceleration[rad/s^2]x10");
 Serial.print("S, - ");Serial.println("STOP");
 Serial.print("M,- ");Serial.println("MOVE");
 DDRB = 0x0F;//pins 8,9,10,11 of the Arduino are outputs
 PORTB &= 0xF0;//four low bits of PORTB are zero
}
//
void loop(){
 if (!stoj){ oneStep(smjer);
 delayMicroseconds(Ci - ((Ci == Cm) ? 4 : kasni) );
 Ci = solveC();
 if (++np >= N) { np = 0; kk = 0; Ci = Co; stoj = true;
 Serial.print("Steps = ") ;Serial.print(imaK);
 Serial.print(", angle = ");Serial.println(imaK*360/K);
 }
 }
}
//one step in the desired direction, where ‘desno’ is direction
void oneStep(boolean desno){
 if (desno) {PORTB=(PORTB& maska) | cw[kk++]; imaK++;}
 else {PORTB=(PORTB & maska) | cw[duzcw-1-kk++];imaK--;} if ( kk == duzcw ) kk = 0;

}
//solve the time delay
double solveC()
{ 
  if (na == 0) return (Cm);
 if ( (np<=na)||(np>=nd) )//acceleration and deceleration phase
 double q = 1+( (np<=na)?Ra:Rd )*Ci*Ci; Ci = Ci/q;kasni=66;
 if ( ( (np>= 1 && (np<= 5)) || ((N-np <= 5) && ( N-np >= 1))))
 { 
  Ci = Ci*(1+0.08/np) ; 
 
 kasni=120;}//correction
 
 if (Ci < Cm)
 {
 Ci = Cm; //using variable ‘kasni’ we take into
 } else 
 Ci = Cm; 
 return Ci; //account all delays occurred during
} //the call and execute of program
//this procedure calculate the parameters of the motion'
void init(float degU){
 Ra=acce/(alfa*f*f); Rd=-dece/(alfa*f*f); Cm=alfa*f/dspeed;
 N = (long) degU*K/360.0 - imaK; stoj = false;
 if (N == 0) {stoj = true; return; }
 if (N > 0) smjer = true;
 if (N < 0) {smjer = false; N = -N;}
 if (N == 1) oneStep(smjer);
 // trajectory planning
 if (acce != 0){// acceleration exists
 nad = (long)(N*dece)/(acce+dece);
 na = (long)(dspeed*dspeed)/(2*alfa*acce);
 if (nad > na) { nd = N - na * acce/dece; }//case (i)
 else { na = nad; nd = na; } //case (ii)
 Co = f * sqrt(2*alfa/acce); Ci = Co;//Co is initial time delay
 } else {//without acceleration
 na = 0; nd = N; Ci = Cm;
 }
 if (nd < na) { // this is might be due to rounding
 long np=na; na=nd;nd=np;//exchange the values of 'na' and 'nd'
 } np = 0;
}
//this function is called for every cycle in the loop procedure
void serialEvent(){ //command of the stepper motor
 if (Serial.available() > 0 ){
 char ch = toupper(Serial.read());
 if ((ch == 'S') || (ch == 'M')) chh = ch;
 if ((ch == 'U') || (ch == 'B') || (ch == 'A') || (ch == 'D')){
 chh = ch; broj = 0;
 }
//if ch is alphanumeric than calculate of the parameter value
 if (ch >= '0' && ch <= '9') broj = broj * 10 + (int)ch-'0';
 if (ch == ','){//comma is denoted end of command
 if (chh == 'U') {ugao = broj/10.0; init(ugao);}
 if (chh == 'B') dspeed = broj/10.0;
 if (chh == 'A') acce = broj/10.0;
 if (chh == 'D') dece = broj/10.0;
 if (chh == 'S') stoj = true; //STOP moving
 if (chh == 'M') stoj = false; //continuoe the moving
 broj = 0;
 }
}
}

