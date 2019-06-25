int pin = 7;                                        // 미세먼지 측정

unsigned long duration;

unsigned long starttime;

unsigned long sampletime_ms = 30000;                //sampel time 30초 정의

unsigned long lowpulseoccupancy = 0;

 

float pcsPerCF = 0;

float ugm3 = 0;

float ratio = 0;

float concentration = 0;                            // 미세먼지 측정

int whole=0;

int LED = 13;                                     // 온도에 따른 LED 변화 

 

int ad_conv(byte channel, byte num);              // 습도 측정

int calc_RH10(int adval);                        // 습도 측정

 

int cds = A1;                                   //조도에 따른 LEDS 변화

int LEDS = 8;                                   //조도에 따른 LEDS 변화

 

void setup() {

 

  

  Serial.begin(9600);

 

  pinMode(cds,INPUT);                    //조도에 따른 LEDS 변화

  pinMode(LEDS,OUTPUT);                  //조도에 따른 LEDS 변화

  

  pinMode(7, INPUT);                              // 미세먼지 측정

 

  pinMode(LED,OUTPUT);                   // 온도에 따른 LED 변화

 

  starttime = millis();               //현재시간 가져오기

}

 

void loop() {

  {

    ////////////////////////////////////////

    unsigned int val;                                        // 온도에 따른 LED 변화

    unsigned int dat;

    int ondo=0;

    val=analogRead(0);

    dat=(500 * val) /1024;;

    ondo = dat;

    //Serial.print("온도 : ");

    //Serial.print(ondo);   // 온도 측정

//    Serial.print("C");

   

    if(dat>25)

    {

      digitalWrite(LED,HIGH);

    }

    else

    {

      digitalWrite(LED,LOW);

    }

    //delay(500);                                                // 온도에 따른 LED 변화

      

 

 

 

      int vals = analogRead(cds);          //조도에 따른 LEDS 변화

      //Serial.print("조도 : ");

 

      if(vals>500){

      digitalWrite(LEDS,HIGH);

      //Serial.println(" -> LED ON");

      }

      else{

      digitalWrite(LEDS,LOW);

      //Serial.println(" -> LED OFF");

      }

      //delay(200);                          //조도에 따른 LEDS 변화

      

    

    ////////////////////////////////////////

    int mise=0;

    duration = pulseIn(pin, LOW);                                                             // 미세먼지 측정

    lowpulseoccupancy = lowpulseoccupancy + duration;

 

    if ((millis() - starttime) > sampletime_ms)                                               // 미세먼지 / 습도 30초마다 측정

    {

      ratio = lowpulseoccupancy / (sampletime_ms * 10.0);                                     // Integer percentage 0=>100

      concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62;         // using spec sheet curve

      pcsPerCF = concentration * 100;

      ugm3 = pcsPerCF / 13000;

      mise = ugm3;

      //Serial.print("미세먼지 : ");

      //Serial.print(mise);  // 미세먼지 측정

      

      lowpulseoccupancy = 0;                                                                  // 미세먼지 측정     

 

      int adval, RH10;                                                                       // 습도 측정

      adval = ad_conv(0, 32);                                                                // 32 samples on Channel 0

      RH10 = calc_RH10(adval);

      //display(RH10);   // 습도 측정

      starttime = millis();                                                                  // 습도 측정

      //Serial.println();

      //delay(1000);

      //////////////////////////////////////////////

      char data[9] = {0,};

      //Serial.print(mise);  // 미세먼지 측정

      display(RH10);   // 습도 측정

      //Serial.print(ondo);   // 온도 측정

      //Serial.print(vals);  // 조도 측정

      sprintf(data, "%03d%02d%02d%02d",vals,mise,whole,ondo);

      Serial.print(data);

      

      //Serial.print();

////////////////////////////////////////////// 

    }    

     /*                                                                                                                                                                         

    unsigned int val;                                        // 온도에 따른 LED 변화

    unsigned int dat;

    int ondo=0;

    val=analogRead(0);

    dat=(500 * val) /1024;;

    ondo = dat;

    //Serial.print("온도 : ");

    //Serial.print(ondo);   // 온도 측정

//    Serial.print("C");

   

    if(dat>25)

    {

      digitalWrite(LED,HIGH);

    }

    else

    {

      digitalWrite(LED,LOW);

    }

    //delay(500);                                                // 온도에 따른 LED 변화

      

 

 

 

      int vals = analogRead(cds);          //조도에 따른 LEDS 변화

      //Serial.print("조도 : ");

 

      if(vals>500){

      digitalWrite(LEDS,HIGH);

      //Serial.println(" -> LED ON");

      }

      else{

      digitalWrite(LEDS,LOW);

      //Serial.println(" -> LED OFF");

      }

      //delay(200);                          //조도에 따른 LEDS 변화

      

    */

  }

}

 

int ad_conv(byte channel, byte num)              // 습도 측정

{

  long sum = 0;

  byte n;

 

  for (n = 0; n < num; n++)

  {

    sum = sum + analogRead(channel);

  }

  return (sum / num);

}

 

int calc_RH10(int adval)

{

  int RH10;

  RH10 = adval + 6 * adval / 10 + 3 * adval / 100; // 1.63 * adval

  return (RH10);

}

 

 

void display(int x)

{

  int fract;

  float sum = 0.0;

 

  whole = x / 10;

  fract = x % 10;

  sum = whole + fract;

  

  //Serial.print("습도 : ");

  //Serial.print(whole, DEC);

  //Serial.print(".");

  //Serial.println(fract, DEC);

  //Serial.print(whole);

}                                                     // 습도 측정
