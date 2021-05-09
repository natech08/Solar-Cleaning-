/*********************************************
 * This is code for solar Cleaning System    * 
 * prepared by Vector Circuit                *
 * info@vectorcircuit.in                     *
 *********************************************
 */ 



//Relay Pin
#define Right_relayCW 10
#define Right_relayCCW 11


#define Left_relayCW 12
#define Left_relayCCW 13



#define WaterPin 9

//Limiting Switch
#define LeftSwitch1 2
#define LeftSwitch2 3
#define RightSwitch1 4
#define RightSwitch2 5

void setup() {
  Serial.begin(9600);
  pinMode(Right_relayCW, OUTPUT);
  pinMode(Right_relayCCW, OUTPUT);

  pinMode(Left_relayCW, OUTPUT);
  pinMode(Left_relayCCW, OUTPUT);


  pinMode(WaterPin, OUTPUT);


  pinMode(LeftSwitch1, INPUT_PULLUP);
  pinMode(LeftSwitch2, INPUT_PULLUP);
  pinMode(RightSwitch1, INPUT_PULLUP);
  pinMode(RightSwitch2, INPUT_PULLUP);

  digitalWrite(LeftSwitch1, 1);
  digitalWrite(LeftSwitch2, 1);
  digitalWrite(RightSwitch1, 1);
  digitalWrite(RightSwitch2, 1);

  pinMode(WaterPin, OUTPUT);

}
String text = "";
bool x = 0;
bool y = 0;

void loop() {

  bool L1 = digitalRead(LeftSwitch1);
  bool L2 = digitalRead(LeftSwitch2);
  bool R1 = digitalRead(RightSwitch1);
  bool R2 = digitalRead(RightSwitch2);
  bool R = 0;
  bool L = 0;
  while (Serial.available())
  { delay(100);
    char c = Serial.read();
    text = text + c;
  }
  if (text == "left" || text == "left\n")
  { Left();
    x = 0;
    y = 0;
    text = "";
  }

  if (text == "right" || text == "right\n")
  { Right();
    x = 0;
    y = 0;
    text = "";
  }

  if (text == "stop" || text == "stop\n")
  { Stop();
    x = 0;
    y = 0;
    text = "";
  }


  if (text == "Won" || text == "Won\n")
  { digitalWrite(WaterPin, 1);
    Serial.print("WaterSpread ON");
    text = "";
  }

  if (text == "Woff" || text == "Woff\n")
  { digitalWrite(WaterPin, 0);
    Serial.print("WaterSpread OFF");
    text = "";
  }

  if (text == "mode1" || text == "mode1\n")
  { x = 1;
    y = 0;
    Left();
    text = "";
  }

  if (text == "mode2" || text == "mode2\n")
  { x = 0;
    y = 1;
    Left();
    text = "";
  }
  if ((L1 == 0 && L2 == 0))
  {
    L = 1;
  }
  if ((R1 == 0 && R2 == 0))
  {
    R = 1;
  }
  //Serial.println(L);
  if (x == 1 && L == 1)
  { Right();
    L = 0;
    R = 0;
  }
  if (x == 1 && R == 1)
  { Left();
    L = 0;
    R = 0;
  }
  if (y == 1 && L == 1)
  { Right();
    L = 0;
    R = 0;
  }
  if (y == 1 && R == 1)
  { Stop();
    x = 0;
    y = 0;
    L = 0;
    R = 0;
  }




}





void Left()
{ digitalWrite(Right_relayCW, 1);
  digitalWrite(Right_relayCCW, 0);
  digitalWrite(Left_relayCW, 1);
  digitalWrite(Left_relayCCW, 0);
  Serial.print("Left");
}

void Right()
{ digitalWrite(Right_relayCW, 0);
  digitalWrite(Right_relayCCW, 1);
  digitalWrite(Left_relayCW, 0);
  digitalWrite(Left_relayCCW, 1);
  Serial.print("Right");
}

void Stop()
{ digitalWrite(Right_relayCW, 0);
  digitalWrite(Right_relayCCW, 0);
  digitalWrite(Left_relayCW, 0);
  digitalWrite(Left_relayCCW, 0);
  Serial.print("Stop");
}
