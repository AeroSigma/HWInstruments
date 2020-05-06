
/*****************************************************************************
   midi.h
   Lab 6: Final Project
   ECE 476: Digital Systems Design Using Microcontrollers
   Cornell University
   April 2007
   Andrew Godbehere (abg34) and Nathan Ward (njw23)
 ****************************************************************************/


/****************************************************************************/
#include <stdio.h>  //putchar

//MIDI op codes
#define NOTE_OFF 0b1000
#define NOTE_ON 0b1001
#define CONTROL_CHANGE 0b1011
#define CHANNEL_MODE 0b1011

//Note numbers
//Octave   Note Numbers
//         C  C#   D  D#   E   F  F#   G  G#   A  A#   B
//-1       0   1   2   3   4   5   6   7   8   9  10  11
//0       12  13  14  15  16  17  18  19  20  21  22  23
//1       24  25  26  27  28  29  30  31  32  33  34  35
//2       36  37  38  39  40  41  42  43  44  45  46  47
//3       48  49  50  51  52  53  54  55  56  57  58  59
//4       60  61  62  63  64  65  66  67  68  69  70  71
//5       72  73  74  75  76  77  78  79  80  81  82  83
//6       84  85  86  87  88  89  90  91  92  93  94  95
//7       96  97  98  99 100 101 102 103 104 105 106 107
//8      108 109 110 111 112 113 114 115 116 117 118 119
//9      120 121 122 123 124 125 126 127

//MIDI channels
//
//20-31 undefined
//

#define NOTE_Cn1  0
#define NOTE_Csn1 1
#define NOTE_Dn1  2
#define NOTE_Dsn1 3
#define NOTE_En1  4
#define NOTE_Fn1  5
#define NOTE_Fsn1 6
#define NOTE_Gn1  7
#define NOTE_Gsn1 8
#define NOTE_An1  9
#define NOTE_Asn1 10
#define NOTE_Bn1  11
#define NOTE_C0   12
#define NOTE_Cs0  13
#define NOTE_D0   14
#define NOTE_Ds0  15
#define NOTE_E0   16
#define NOTE_F0   17
#define NOTE_Fs0  18
#define NOTE_G0   19
#define NOTE_Gs0  20
#define NOTE_A0   21
#define NOTE_As0  22
#define NOTE_B0   23
#define NOTE_C1   24
#define NOTE_Cs1  25
#define NOTE_D1   26
#define NOTE_Ds1  27
#define NOTE_E1   28
#define NOTE_F1   29
#define NOTE_Fs1  30
#define NOTE_G1   31
#define NOTE_Gs1  32
#define NOTE_A1   33
#define NOTE_As1  34
#define NOTE_B1   35
#define NOTE_C2   36
#define NOTE_Cs2  37
#define NOTE_D2   38
#define NOTE_Ds2  39
#define NOTE_E2   40
#define NOTE_F2   41
#define NOTE_Fs2  42
#define NOTE_G2   43
#define NOTE_Gs2  44
#define NOTE_A2   45
#define NOTE_As2  46
#define NOTE_B2   47
#define NOTE_C3   48
#define NOTE_Cs3  49
#define NOTE_D3   50
#define NOTE_Ds3  51
#define NOTE_E3   52
#define NOTE_F3   53
#define NOTE_Fs3  54
#define NOTE_G3   55
#define NOTE_Gs3  56
#define NOTE_A3   57
#define NOTE_As3  58
#define NOTE_B3   59
#define NOTE_C4   60  //Middle C
#define NOTE_Cs4  61
#define NOTE_D4   62
#define NOTE_Ds4  63
#define NOTE_E4   64
#define NOTE_F4   65
#define NOTE_Fs4  66
#define NOTE_G4   67
#define NOTE_Gs4  68
#define NOTE_A4   69
#define NOTE_As4  70
#define NOTE_B4   71
#define NOTE_C5   72
#define NOTE_Cs5  73
#define NOTE_D5   74
#define NOTE_Ds5  75
#define NOTE_E5   76
#define NOTE_F5   77
#define NOTE_Fs5  78
#define NOTE_G5   79
#define NOTE_Gs5  80
#define NOTE_A5   81
#define NOTE_As5  82
#define NOTE_B5   83
#define NOTE_C6   84
#define NOTE_Cs6  85
#define NOTE_D6   86
#define NOTE_Ds6  87
#define NOTE_E6   88
#define NOTE_F6   89
#define NOTE_Fs6  90
#define NOTE_G6   91
#define NOTE_Gs6  92
#define NOTE_A6   93
#define NOTE_As6  94
#define NOTE_B6   95
#define NOTE_C7   96
#define NOTE_Cs7  97
#define NOTE_D7   98
#define NOTE_Ds7  99
#define NOTE_E7  100
#define NOTE_F7  101
#define NOTE_Fs7 102
#define NOTE_G7  103
#define NOTE_Gs7 104
#define NOTE_A7  105
#define NOTE_As7 106
#define NOTE_B7  107
#define NOTE_C8  108
#define NOTE_Cs8 109
#define NOTE_D8  110
#define NOTE_Ds8 111
#define NOTE_E8  112
#define NOTE_F8  113
#define NOTE_Fs8 114
#define NOTE_G8  115
#define NOTE_Gs8 116
#define NOTE_A8  117
#define NOTE_As8 118
#define NOTE_B8  119
#define NOTE_C9  120
#define NOTE_Cs9 121
#define NOTE_D9  122
#define NOTE_Ds9 123
#define NOTE_E9  124
#define NOTE_F9  125
#define NOTE_Fs9 126
#define NOTE_G9  127

/****************************************************************************/
void init_midi(void) {
  //SET UP UART
  //Set USART Control and Status Register A (UCSRA)
  UCSR0A = 0b00000000;  //U2X=0
  //Set USART Control and Status Register B (UCSRB)
  UCSR0B = 0b00001000;  //Enable USART transmitter
  //Set USART Control and Status Register C (UCSRC)
  UCSR0C = 0b00000110;  //Asynchronous operation with 8-bit frames
  //Set USART Baud Rate Register (UBRR)
  //UBRR = fosc/(16*BAUD) - 1 = 8MHz/(16*31.25kBaud) - 1 = 15
  UBRR0H = 0;
  UBRR0L = 15;  //MIDI is 31.25 kBaud
}

/****************************************************************************/
unsigned char status_byte(unsigned char opcode, unsigned char channel) {
  //Upper 4 bits: opcode to designate the type of message
  //Lower 4 bits: MIDI channel number
  if (channel >= 1 && channel <= 16) return ((opcode << 4) | (channel - 1));
  else return 0xBF;
}

/****************************************************************************/
//Send a MIDI Control Change message containing one sensor value
void send_midi(unsigned char controller_number,
               unsigned char controller_value) {
  //MIDI spec for "Control Change" messages sends three bytes:
  // 1) status byte: opcode/channel number
  // 2) first data byte: controller number
  // 3) second data byte: controller value
  Serial.write(status_byte(CONTROL_CHANGE, 1));  //Channel 1
  Serial.write(controller_number & 0x7F);        //Controller number
  Serial.write(controller_value & 0x7F);         //7 bits (0-127)
}

/****************************************************************************/
void send_allnotesoff(void) {
  //"All Notes Off" Channel Mode Message
  //Same as the Control Change, but implements Mode control and special
  //message by using reserved controller numbers 120-127
  Serial.write(status_byte(CHANNEL_MODE, 1));    //Channel 1
  Serial.write(123);
  Serial.write(0);
  Serial.write(status_byte(CHANNEL_MODE, 2));    //Channel 2
  Serial.write(123);
  Serial.write(0);
  Serial.write(status_byte(CHANNEL_MODE, 3));    //Channel 3
  Serial.write(123);
  Serial.write(0);
}

/****************************************************************************/
void send_noteon(unsigned char note, unsigned char velocity,
                 unsigned char midi_chan) {
  //MIDI spec for "Note On" event sent when a note is depressed (start)
  //sends three bytes:
  // 1) status byte: opcode/channel number
  // 2) first data byte: the key (note) number
  // 3) second data byte: the velocity
  //midi_chan must be between 1 and 3
  Serial.write(status_byte(NOTE_ON, midi_chan)); //Channel midi_chan
  Serial.write(note & 0x7F);                     //7 bits (0-127)
  Serial.write(velocity & 0x7F);                 //7 bits (0-127)
}

/****************************************************************************/
void send_noteoff(unsigned char note, unsigned char velocity,
                  unsigned char midi_chan) {
  //MIDI spec for "Note Off" event sent when a note is released (ended)
  //sends three bytes:
  // 1) status byte: opcode/channel number
  // 2) first data byte: the key (note) number
  // 3) second data byte: the velocity
  Serial.write(status_byte(NOTE_OFF, midi_chan)); //Channel midi_chan
  Serial.write(note & 0x7F);                     //7 bits (0-127)
  Serial.write(velocity & 0x7F);                 //7 bits (0-127)
}

/****************************************************************************/
