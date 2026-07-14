
#include "U8g2_utils.h"

namespace u8g2 {

    U8G2_SSD1306_128X64_NONAME_F_HW_I2C m_u8g2(U8G2_R0, U8X8_PIN_NONE, /* clock=*/ 9, /* data=*/ 8);

    void drawRIOTLogo() {
        m_u8g2.clearBuffer();
        m_u8g2.drawXBMP(0, 0, 128, 64, kU8g2Image_RIOTLogo);
        m_u8g2.sendBuffer();
    };

    void initializeU8G2() {
        m_u8g2.begin();
        m_u8g2.setFont(u8g2_font_t0_12b_mf);
        m_u8g2.setColorIndex(1);
        // drawLogo();
        // Serial.println("Printing logo:");
    };

    void drawText(const char *str, int d, int x, int y, bool setScreen) {
        m_u8g2.setFont(u8g2_font_ncenB08_tr); // Set any readable font
        m_u8g2.drawStr(x, y, str);
        if (setScreen) {
            m_u8g2.sendBuffer();
            delay(d);
        }
    };

    constexpr double k_JoystickDisplayDeadband = 0.2;
    static int getDirectionFromXY(double x, double y, double range_low, double range_high) {
        double x_percent = ((x - range_low) / (range_high - range_low)) * 2 - 1; // -1 to 1
        double y_percent = ((y - range_low) / (range_high - range_low)) * 2 - 1; // -1 to 1 

        if (std::abs(x_percent) > std::abs(y_percent)) {
            if (x_percent > k_JoystickDisplayDeadband) {
                return 4; // Right
            }else if (x_percent < -k_JoystickDisplayDeadband) {
                return 3; // Left
            }else {
                return 0; // Center
            }
        }else {
            if (y_percent > k_JoystickDisplayDeadband) {
                return 1; // Up
            }else if (y_percent < -k_JoystickDisplayDeadband) {
                return 2; // Down
            }else {
                return 0; // Center
            }
        }
    }; 

    // void printMainMenu(uint16_t analogPins[], bool digitalPins[], uint8_t dir[], bool connected, int battery) {
    void printMainMenu(const atmt::JoystickState &state, bool connected, int battery) {
        m_u8g2.clearBuffer();
        m_u8g2.setFont(u8g2_font_5x8_tf);
        
        // m_u8g2.drawXBMP(5, 1, 28, 15, getImageFromBattery(battery));
        if (connected) {
            m_u8g2.drawXBMP(5, 1, 28, 15, kU8g2Image_Connected);
        }else {
            m_u8g2.drawXBMP(5, 1, 28, 15, kU8g2Image_No);
        }

        // m_u8g2.drawXBMP(65, 20, kU8g2Image_JoystickImageWidth, kU8g2Image_JoystickImageHeight, getImageFromDirection(dir[0]));
        // m_u8g2.drawXBMP(85, 20, kU8g2Image_JoystickImageWidth, kU8g2Image_JoystickImageHeight, getImageFromDirection(dir[1]));
        m_u8g2.drawXBMP(65, 20, kU8g2Image_JoystickImageWidth, kU8g2Image_JoystickImageHeight, getImageFromDirection(getDirectionFromXY(state.axes[atmt::LXAxis], state.axes[atmt::LYAxis], state.axis_range[0], state.axis_range[1])));
        m_u8g2.drawXBMP(85, 20, kU8g2Image_JoystickImageWidth, kU8g2Image_JoystickImageHeight, getImageFromDirection(getDirectionFromXY(state.axes[atmt::RXAxis], state.axes[atmt::RYAxis], state.axis_range[0], state.axis_range[1])));
        
        // m_u8g2.drawXBMP(65, 5, kU8g2Image_ButtonImageWidth, kU8g2Image_ButtonImageHeight, getImageFromButton(digitalPins[0]));
        // m_u8g2.drawXBMP(85, 5, kU8g2Image_ButtonImageWidth, kU8g2Image_ButtonImageHeight, getImageFromButton(digitalPins[1]));
        // m_u8g2.drawXBMP(90, 35, kU8g2Image_ButtonImageWidth, kU8g2Image_ButtonImageHeight, getImageFromButton(digitalPins[3]));
        // m_u8g2.drawXBMP(105, 21, kU8g2Image_ButtonImageWidth, kU8g2Image_ButtonImageHeight, getImageFromButton(digitalPins[2]));
        m_u8g2.drawXBMP(65, 5, kU8g2Image_ButtonImageWidth, kU8g2Image_ButtonImageHeight, getImageFromButton(atmt::getJoystickStateButton(state, atmt::AButton)));
        m_u8g2.drawXBMP(85, 5, kU8g2Image_ButtonImageWidth, kU8g2Image_ButtonImageHeight, getImageFromButton(atmt::getJoystickStateButton(state, atmt::BButton)));
        m_u8g2.drawXBMP(90, 35, kU8g2Image_ButtonImageWidth, kU8g2Image_ButtonImageHeight, getImageFromButton(atmt::getJoystickStateButton(state, atmt::R1Button)));
        m_u8g2.drawXBMP(105, 21, kU8g2Image_ButtonImageWidth, kU8g2Image_ButtonImageHeight, getImageFromButton(atmt::getJoystickStateButton(state, atmt::L1Button)));


        m_u8g2.drawXBMP(5, 20, 48, 35, kU8g2Image_Robot);

        m_u8g2.setFont(u8g2_font_open_iconic_all_1x_t);

        int glyph = getGlyphFromDirection(getDirectionFromXY(state.axes[atmt::LXAxis], state.axes[atmt::LYAxis], state.axis_range[0], state.axis_range[1]));
        if (glyph != 0) {
            m_u8g2.drawGlyph(24, 42, glyph);
        }

        // glyph = getGlyphFromDirection(dir[1]);
        // if (glyph != 0) {
        //     m_u8g2.drawGlyph(24, 42, glyph);
        // }
        
        m_u8g2.sendBuffer();
    };

    void drawConfirmReceiver(const uint8_t selected_mac_addr[]) {
        m_u8g2.clearBuffer();
        m_u8g2.drawStr(0, 10, "Selecting Radio:" );

        char bufMac[25];
        snprintf(
            bufMac,
            sizeof(bufMac),
            "%02X:%02X:%02X:%02X:%02X:%02X",
            selected_mac_addr[0],
            selected_mac_addr[1],
            selected_mac_addr[2],
            selected_mac_addr[3],
            selected_mac_addr[4],
            selected_mac_addr[5]
        );
        m_u8g2.drawStr(0,30, bufMac);

        m_u8g2.sendBuffer();
    };


    static const unsigned char* getImageFromBattery(uint8_t battery) {
        switch(battery){
            case 0:
                return kU8g2Image_Battery_0_25;
            case 1:
                return kU8g2Image_Battery_25_50;
            case 2:
                return kU8g2Image_Battery_50_75;
            case 3:
                return kU8g2Image_Battery_75_100;
            default:
                return kU8g2Image_Battery_0_25;
        }
    };
    static const unsigned char* getImageFromDirection(uint8_t direction) {
        switch (direction) {
            case 0:
                return kU8g2Image_JoystickCenter;
            case 1:
                return kU8g2Image_JoystickUp;
            case 2:
                return kU8g2Image_JoystickDown;
            case 3:
                return kU8g2Image_JoystickLeft;
            case 4:
                return kU8g2Image_JoystickRight;
            default:
                return kU8g2Image_JoystickCenter;
        }
    };
    static const unsigned char* getImageFromButton(bool button) {
        return button ? kU8g2Image_ButtonPressed : kU8g2Image_ButtonUnpressed;
    };
    static int getGlyphFromDirection(uint8_t direction) {
        switch (direction) {
            case 0:
                return 0;
            case 1:
                return 76;
            case 2:
                return 73;
            case 3:
                return 75;
            case 4:
                return 74;
            default:
                return 0;
        }
    };

};