
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
        if (glyph != kmpf::consts::Controller::U8g2::k_NoGlyph) {
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

    void drawSelectReceiver(const std::vector<kmpf::KnownReceiver> &receivers, int selected_index, int scroll) {
        m_u8g2.clearBuffer();
        m_u8g2.setFont(u8g2_font_ncenB08_tr);
        m_u8g2.drawStr(20, 15, "List of Receivers:");
        // Show the found receivers
        for (int i = 0; i < kmpf::consts::Controller::k_MACsDrawnPerScreen; i++) {
            int mod_i = i + scroll;
            if (mod_i < receivers.size()) { // Check if index is within bounds
                m_u8g2.drawButtonUTF8((128-m_u8g2.getUTF8Width(receivers[mod_i].name.c_str()))/2, i*20+30, mod_i == selected_index ? 0x02 : 0x20, 0,  2,  2, receivers[mod_i].name.c_str());
            }
        }
        m_u8g2.sendBuffer();
    };


    static const unsigned char* getImageFromBattery(uint8_t battery) {
        switch(battery){
            case kmpf::consts::Controller::U8g2::k_Battary_0_25:
                return kU8g2Image_Battery_0_25;
            case kmpf::consts::Controller::U8g2::k_Battary_25_50:
                return kU8g2Image_Battery_25_50;
            case kmpf::consts::Controller::U8g2::k_Battary_50_75:
                return kU8g2Image_Battery_50_75;
            case kmpf::consts::Controller::U8g2::k_Battary_75_100:
                return kU8g2Image_Battery_75_100;
            default:
                return kU8g2Image_Battery_0_25;
        }
    };
    static const unsigned char* getImageFromDirection(uint8_t direction) {
        switch (direction) {
            case kmpf::consts::Controller::U8g2::k_DirectionCenter:
                return kU8g2Image_JoystickCenter;
            case kmpf::consts::Controller::U8g2::k_DirectionUp:
                return kU8g2Image_JoystickUp;
            case kmpf::consts::Controller::U8g2::k_DirectionDown:
                return kU8g2Image_JoystickDown;
            case kmpf::consts::Controller::U8g2::k_DirectionLeft:
                return kU8g2Image_JoystickLeft;
            case kmpf::consts::Controller::U8g2::k_DirectionRight:
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
            case kmpf::consts::Controller::U8g2::k_DirectionCenter:
                return kmpf::consts::Controller::U8g2::k_NoGlyph;
            case kmpf::consts::Controller::U8g2::k_DirectionUp:
                return kmpf::consts::Controller::U8g2::k_GlyphUp;
            case kmpf::consts::Controller::U8g2::k_DirectionDown:
                return kmpf::consts::Controller::U8g2::k_GlyphDown;
            case kmpf::consts::Controller::U8g2::k_DirectionLeft:
                return kmpf::consts::Controller::U8g2::k_GlyphLeft;
            case kmpf::consts::Controller::U8g2::k_DirectionRight:
                return kmpf::consts::Controller::U8g2::k_GlyphRight;
            default:
                return kmpf::consts::Controller::U8g2::k_NoGlyph;
        }
    };

};