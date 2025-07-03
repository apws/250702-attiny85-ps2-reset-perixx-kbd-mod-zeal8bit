#include <avr/sleep.h>
#include <avr/io.h>
#include <util/delay.h>

// PS/2 pin definitions (Digispark default board) 
#define PS2_CLK  0  // PB0
#define PS2_DATA 2  // PB2
#define LED      1  // LED internal

// Pull line LOW (emulated open-drain)
void driveLow(uint8_t pin) {
  digitalWrite(pin, LOW);
  pinMode(pin, OUTPUT);
}

// Release line (float HIGH via external pull-up)
void release(uint8_t pin) {
  pinMode(pin, INPUT); // no pullup!
}

// Wait for clock falling edge (from keyboard)
void waitClkFall() {
  while (digitalRead(PS2_CLK) == LOW);  // wait for HIGH
  while (digitalRead(PS2_CLK) == HIGH); // wait for LOW
}

// Send 1 bit, synced to clock
void sendBit(bool bit) {
  if (bit) release(PS2_DATA); else driveLow(PS2_DATA);
  waitClkFall();                                                                   
}

// Send full byte with start, parity, stop
void sendByte(uint8_t b) {
  uint8_t parity = 1;

  // Start bit (0)
  driveLow(PS2_DATA);
  waitClkFall();

  // 8 data bits, LSB first
  for (uint8_t i = 0; i < 8; i++) {
    bool bit = b & (1 << i);
    sendBit(bit);
    parity ^= bit;
  }

  // Parity bit (odd)
  sendBit(parity);

  // Stop bit (1)
  release(PS2_DATA);
  waitClkFall();

  // Idle
  release(PS2_DATA);
}

void setup() {
  // Set both lines released initially
  release(PS2_CLK);
  release(PS2_DATA);

  // Delay for keyboard power-up
  _delay_ms(100);

  // Inhibit: pull CLK low for >100µs
  driveLow(PS2_CLK);
  _delay_us(150);

  // Prepare: pull DATA low
  driveLow(PS2_DATA);
  _delay_us(10);

  // Release CLK to allow keyboard to clock
  release(PS2_CLK);

  // Send 0xFF (Reset)
  sendByte(0xFF);

  _delay_ms(100);

  // !! not necessary
  // Send 0xFA (Fake ACK — required by Perixx workaround) 
  //sendByte(0xFA);

  // SET shortest delay, fastest rate
  sendByte(0xF3);     // Set Typematic Rate/Delay
  _delay_ms(10);      // Wait for ACK (ideally: read and confirm 0xFA)
  sendByte(0x00);     // Fastest rate (30Hz), 250ms delay
  _delay_ms(10);      // Wait for ACK (again ideally read 0xFA)

  // Release lines
  release(PS2_CLK);
  release(PS2_DATA);

  // Power-down sleep forever
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
}

void loop() {
  // never reached
}
