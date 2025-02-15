/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.
  Copyright (c) 2016 Sandeep Mistry All right reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

#include <nrf.h>

#include "HardwareSerial.h"
#include "RingBuffer.h"
#include "rtos.h"

#include <cstddef>

class Uart : public HardwareSerial
{
  public:
    Uart(NRF_UARTE_Type *_nrfUart, IRQn_Type _IRQn, uint8_t _pinRX, uint8_t _pinTX);
    Uart(NRF_UARTE_Type *_nrfUart, IRQn_Type _IRQn, uint8_t _pinRX, uint8_t _pinTX, uint8_t _pinCTS, uint8_t _pinRTS);

    void setPins(uint8_t pin_rx, uint8_t pin_tx);
    void setPins(uint8_t pin_rx, uint8_t pin_tx, uint8_t _pinCTS, uint8_t _pinRTS);
    void getPins();

    void begin(unsigned long baudRate);
    void begin(unsigned long baudrate, uint16_t config);
    void end();
    int available();
    int peek();
    int read();
    void flush();
    size_t write(uint8_t data);
    size_t write(const uint8_t *buffer, size_t size);
    using Print::write; // pull in write(str) from Print

    void IrqHandler();

    operator bool ()
    {
      return _begun;
    }

  private:
    NRF_UARTE_Type *nrfUart;
    RingBuffer rxBuffer;
    uint8_t rxRcv;
    uint8_t txBuffer[SERIAL_BUFFER_SIZE];

    IRQn_Type IRQn;

    uint8_t uc_pinRX;
    uint8_t uc_pinTX;
    uint8_t uc_pinCTS;
    uint8_t uc_pinRTS;
    uint8_t uc_hwFlow;

    bool _begun;

    // Adafruit
    SemaphoreHandle_t _mutex;
};


// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#ifdef NRF52832_XXAA
  #define SERIAL_PORT_MONITOR         Serial
  #define SERIAL_PORT_HARDWARE        Serial

#else // ARDUINO_NECTIS
  #define SERIAL_PORT_MONITOR         Serial
  #define SERIAL_PORT_USBVIRTUAL      Serial

  #define SERIAL_PORT_HARDWARE        Serial1
  #define SERIAL_PORT_HARDWARE_OPEN   Serial1

#endif

extern Uart SERIAL_PORT_HARDWARE;

#if defined(PIN_SERIAL2_RX) && defined(PIN_SERIAL2_TX)
extern Uart Serial2;
#endif
