/*  EXL 100 PS2 adapter by Andrea Ottaviani
 *   
 *   based on:
 *   PS2Keyboard library 
  
  PS2Keyboard now requries both pins specified for begin()

  keyboard.begin(data_pin, irq_pin);
 
 for more information you can read the original wiki in arduino.cc
  at http://www.arduino.cc/playground/Main/PS2Keyboard
  or http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
  
*/
   
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>


#include <PS2Keyboard.h>

const int DataPin = 2;
const int IRQpin =  3;


PS2Keyboard keyboard;
// 1155=A 590=B 540=C 1100=D
uint16_t irSignal[20]; 
const char irCh00[] = "ACBCBCBCBCBCA"; // A2-aE7 n.c.
const char irCh01[] = "AABCBCBCBCBC";// A2-aE6 n.c.
const char irCh02[] ="BBAABCBCBCB";  // A2-aE5 %
const char irCh03[] = "ABCABCBCBCB"; // A2-aE4 5
const char irCh04[] = "BCBCADBCBCB";  // A2-aE3 Enter 
const char irCh05[] = "AAAABCBCB";   // A2-aE2 L
const char irCh06[] ="BBABCABCBCB";  // A2-aE1 I
const char irCh07[] = "ABCBCABCBCB"; // A2-aE8 Q
const char irCh08[] ="BBBCBCAABCB";  // A3-aE7 F 
const char irCh09[] = "AABCAABCB";   // A3-aE6 *
const char irCh10[] ="BBAAAABCB";    // A3-aE5 7
const char irCh11[] = "ABCAAABCB";   // A3-aE4 4
const char irCh12[] ="BCBCABCABCB";  // A3-aE3  ~ 126
const char irCh13[] = "AAABCABCB";   // A3-aE2 J
const char irCh14[] ="CBABCBCABCB";  // A3-aE1 P
const char irCh15[] ="ACBCBCBDBC";  // A3-aE8 W
const char irCh16[] ="BBBCBCBCAAB";  // A1-aE7 D
const char irCh17[] = "AABCBCAAB";   // A1-aE6 B
const char irCh18[] ="BBAABCAAB";    // A1-aE5 n.c.
const char irCh19[] = "ACBDBCAD";    // A1-aE4 Y
const char irCh20[] ="BBBCAAAAB";    // A1-aE3 ]
const char irCh21[] = "AAAAAAB";     // A1-aE2 K 
const char irCh22[] ="BBABCAAAB";    // A1-aE1 U
const char irCh23[] = "ABCBCAAAB";   // A1-aE8 S
const char irCh24[] ="BCBCBCABCAB";  // A4-aE7 G
const char irCh25[] = "AABCDBBAB";   // A4-aE6 N 
const char irCh26[] = "BCADACBD";    // A4-aE5 M
const char irCh27[] = "ABCAABCAB";   // A4-aE4 T
const char irCh28[] ="BBBCABCBCAB";  // A4-aE3 [
const char irCh29[] ="ADACBCBD";     // A4-aE2 H
const char irCh30[] ="BCACBCBCBDC";  // A4-aE1 O 
const char irCh31[] ="ACBCBCBCBDC";  // A4-aE8 Shift
const char irCh32[] ="BBBCBCBCBCAB"; // A2-E7 #
const char irCh33[] = "AABCBCBCAB";  // A2-E6 9
const char irCh34[] ="BBAABCBCAB";   // A2-E5 3
const char irCh35[] = "ABCABCBCAB";  // A2-E4 Z
const char irCh36[] ="BBBCAABCAB";   // A2-E3 ;
const char irCh37[] = "ADADBBAB";    // A2-E2 C
const char irCh38[] = "BBABCABCAB";  // A2-E1 Delete
const char irCh39[] = "ABCBCABCAB";  // A2-E8 A
const char irCh40[] = "BBBCBCAAAC";  // A3-E7 0 (zero)
const char irCh41[] = "AABCAAAC";    // A3-E6 8 
const char irCh42[] = "BBAAAAAB";    // A3-E5 6
const char irCh43[] = "ABCADDDB";    // A3-E4 1
const char irCh44[] = "BBBCABCAAB";  // A3-E3 =
const char irCh45[] = "AAABCAAB";    // A3-E2 V
const char irCh46[] = "BCACBCBDAC";  // A3-E1 Home
const char irCh47[] = "ABCBCBCAAB";  // A3-E8 Tab
const char irCh48[] = "BBBCBCBCACBC";// A1-E7 F
const char irCh49[] = "AABCBCABCB";  // A1-E6 ?
const char irCh50[] ="BBADCBACBC";   // A1-E5 R
const char irCh51[] ="ABCABCABCB";   // A1-E4 Esc
const char irCh52[] ="BBBCAAABCB";   // A1-E3 /
const char irCh53[] ="ADADACBC";     // A1-E2 X
const char irCh54[] ="BBABCAABCB";   // A1-E1 Caps Lock
const char irCh55[] ="ACBCBDACBC";   // A1-E8 Ctrl
const char irCh56[] ="BBBCBCABBCBC"; // A4-E7 -
const char irCh57[] ="ADBCACBCBC";   // A4-E6 Space
const char irCh58[] ="BCADACBCBC";   // A4-E5 E
const char irCh59[] ="ACBDACBCBC";   // A4-E4 CrsLeft
const char irCh60[] ="BCBCACBCBCBC"; // A4-E3 CrsDown
const char irCh61[] ="ADACBCBCBC";   // A4-E2 CrsRight
const char irCh62[] ="BCACBCBCBCBC"; // A4-E1 CrsUp
const char irCh63[] ="ABCBCBCBCBCB"; // A4-E8 Z
 
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);

#if defined(IR_SEND_PIN)
    IrSender.begin(); // Start with IR_SEND_PIN as send pin and enable feedback LED at default feedback LED pin
#else
    IrSender.begin(8, ENABLE_LED_FEEDBACK); // Specify send pin and enable feedback LED at default feedback LED pin
#endif

    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
  
  
  keyboard.begin(DataPin, IRQpin);
  Serial.println("");
}

void sendIR(char* src, int len) {
    len=len+2;
    irSignal[0]=540;
    irSignal[1]=2840;
    irSignal[2]=540;
    
    for (int i = 0; i < (len-3); i++) {
      // 1155=A 590=B 540=C 1100=D
      switch (src[i]) {
        case 'A': 
        irSignal[i+3]=1155;
        break;
        case 'B': 
        irSignal[i+3]=590;
        break;
        case 'C': 
        irSignal[i+3]=540;
        break;
        case 'D': 
        irSignal[i+3]=1100;
        break;
      }
     }
     
    Serial.flush();
    for (int i=0;i<3;i++) {
      IrSender.sendRaw(irSignal, len, 28); // Note the approach used to automatically calculate the size of the array.
      delay(88); // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal 
    }
}

void loop() {
  
  
  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();
    //Serial.print(c);
    // check for some of the special keys
    if (c ==  'z' ) {
        sendIR(irCh00,sizeof(irCh00));
   } else if (c == '%' ) {
      sendIR(irCh02,sizeof(irCh02));
   } else if (c == '5' ) {
      sendIR(irCh03,sizeof(irCh03));
    } else if (c == PS2_ENTER ) {
      sendIR(irCh04,sizeof(irCh04));
    } else if (c == 'l' ) {
      sendIR(irCh05,sizeof(irCh05));
    } else if (c == 'i' ) {
      sendIR(irCh06,sizeof(irCh06));
    } else if (c == 'q' ) {
      sendIR(irCh07,sizeof(irCh07));
    } else if (c == 'f' ) {
      sendIR(irCh08,sizeof(irCh08));
    } else if (c == '*' ) {
      sendIR(irCh09,sizeof(irCh09));
    } else if (c == '7' ) {
      sendIR(irCh10,sizeof(irCh10));
    } else if (c == '4' ) {
      sendIR(irCh11,sizeof(irCh11));
    } else if (c == '~' ) {
      sendIR(irCh12,sizeof(irCh12));
    } else if (c == 'j' ) {
      sendIR(irCh13,sizeof(irCh13));
    } else if (c == 'p' ) {
      sendIR(irCh14,sizeof(irCh14));
     } else if (c == 'w' ) {
      sendIR(irCh15,sizeof(irCh15));
     } else if (c == 'd' ) {
      sendIR(irCh16,sizeof(irCh16));
     } else if (c == 'b' ) {
      sendIR(irCh17,sizeof(irCh17));
    // } else if (c == '@' ) {  // n.c.
    //  sendIR(irCh18,sizeof(irCh18));
     } else if (c == 'y' ) {
      sendIR(irCh19,sizeof(irCh19));
     } else if (c == ']' ) {
      sendIR(irCh20,sizeof(irCh20));
     }  else if (c == 'k' ) {
      sendIR(irCh21,sizeof(irCh21));
     } else if (c == 'u' ) {
      sendIR(irCh22,sizeof(irCh22));
     } else if (c == 's' ) {
      sendIR(irCh23,sizeof(irCh23));
     } else if (c == 'g' ) {
      sendIR(irCh24,sizeof(irCh24));
      } else if (c == 'n' ) {
      sendIR(irCh25,sizeof(irCh25));
      } else if (c == 'm' ) {
      sendIR(irCh26,sizeof(irCh26));
     } else if (c == 't' ) {
      sendIR(irCh27,sizeof(irCh27));
     } else if (c == '[' ) {
      sendIR(irCh28,sizeof(irCh28));
     } else if (c == 'h' ) {
      sendIR(irCh29,sizeof(irCh29));
     } else if (c == 'o' ) {
      sendIR(irCh30,sizeof(irCh30));
     } else if (c == '-' ) {   // SHIFT !!!  
      sendIR(irCh31,sizeof(irCh31));
     } else if (c == '#' ) {
      sendIR(irCh32,sizeof(irCh32));
     } else if (c == '9' ) {
      sendIR(irCh33,sizeof(irCh33));
     } else if (c == '3' ) {
      sendIR(irCh34,sizeof(irCh34));
     } else if (c == '2' ) {
       sendIR(irCh35,sizeof(irCh35));
     } else if (c == '.' ) {
       sendIR(irCh36,sizeof(irCh36));
     } else if (c == 'c' ) {
       sendIR(irCh37,sizeof(irCh37));
      } else if (c == PS2_DELETE ) {   // delete
       sendIR(irCh38,sizeof(irCh38));
     } else if (c == 'a' ) {
       sendIR(irCh39,sizeof(irCh39));
     } else if (c == '0' ) {
       sendIR(irCh40,sizeof(irCh40));
     } else if (c == '8' ) {
       sendIR(irCh41,sizeof(irCh41));
     } else if (c == '6' ) {     
       sendIR(irCh42,sizeof(irCh42));
      } else if (c == '1' ) {             
       sendIR(irCh43,sizeof(irCh43));
     } else if (c == '=' ) {
       sendIR(irCh44,sizeof(irCh44));
     } else if (c == 'v' ) {
       sendIR(irCh45,sizeof(irCh45));
     } else if (c == PS2_PAGEUP ) {               //home
       sendIR(irCh46,sizeof(irCh46));
     } else if (c == PS2_TAB ) {     
       sendIR(irCh47,sizeof(irCh47));
      } else if (c == '[' ) {   
       sendIR(irCh48,sizeof(irCh48));
     } else if (c == '?' ) {
       sendIR(irCh49,sizeof(irCh49));
     } else if (c == 'r' ) {  
       sendIR(irCh50,sizeof(irCh50));
       } else if (c == PS2_ESC ) {        
       sendIR(irCh51,sizeof(irCh51));
     } else if (c == '/' ) {             
       sendIR(irCh52,sizeof(irCh52));
     } else if (c == 'x' ) {
       sendIR(irCh53,sizeof(irCh53));
     } else if (c == PS2_PAGEDOWN) {   // caps lock
         sendIR(irCh54,sizeof(irCh54));
     } else if (c == 92 ) {    // control  |\ key     
       sendIR(irCh55,sizeof(irCh55));
      } else if (c == '_' ) {   
       sendIR(irCh56,sizeof(irCh56));
     } else if (c == ' ' ) {
       sendIR(irCh57,sizeof(irCh57));
     } else if (c == 'e' ) {  
       sendIR(irCh58,sizeof(irCh58));
     } else if (c == PS2_LEFTARROW ) {   
       sendIR(irCh59,sizeof(irCh59));
     } else if (c == PS2_DOWNARROW ) {   
       sendIR(irCh60,sizeof(irCh60));
    } else if (c == PS2_RIGHTARROW ) {   
       sendIR(irCh61,sizeof(irCh61));
    } else if (c == PS2_UPARROW ) {   
       sendIR(irCh62,sizeof(irCh62));
   } else if (c == 'z' ) {   
       sendIR(irCh63,sizeof(irCh63));
    } else {
      
      // otherwise, just print all normal characters
      Serial.print(c);
    }
  }
 //* Define macros for input and output pin etc.

   /*
     * Send hand crafted data from RAM
     * The values are NOT multiple of 50, but are taken from the NEC timing definitions
     */
     
}
