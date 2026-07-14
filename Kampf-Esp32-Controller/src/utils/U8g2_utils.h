#ifndef U8G2EZ_H
#define U8G2EZ_H

#include <Arduino.h>
#include <U8g2lib.h>
#include "Automat/automat.h"
#include "U8g2_images.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

namespace u8g2 {

    extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C m_u8g2;

    void drawRIOTLogo();

    void initializeU8G2();

    void drawText(const char *str, int d, int x, int y, bool setScreen);

    void printMainMenu(const atmt::JoystickState &state, bool connected, int battery = 0);

    void drawConfirmReceiver(const uint8_t selected_mac_addr[]);

};

#endif