#include "Tool.h"
#include "Global.h"

#include <Arduino.h>
#include <Wire.h>
#include <I2C_eeprom.h>

typedef struct {
    double baseI;
    int segmentIndex;
} CompensationResult;

typedef struct {
    double umin, umax;
    double cmin_mA, cmax_mA;
} CLAMP_SEG_T;

static const CLAMP_SEG_T clamp_10[] = {
    {0.0,         9.86e-05,     -8.48112692237e-05,  -4.69616047198e-05},
    {9.86e-05,    0.002075875,  -8.61787944278e-04,  -8.48112692237e-05},
    {0.002075875, 0.00213061,   -9.52794616127e-03,  -8.61787944278e-04},
    {0.00213061,  0.005489525,  -9.52794616127e-03,  -5.97878307524e-04},
    {0.005489525, 0.00795575,   -5.97878307524e-04,   1.41867587583e-02},
    {0.00795575,  0.010019594,  -1.56392297064e-02,   1.41867587583e-02},
    {0.010019594, 0.021018875,  -1.56392297064e-02,   4.45660115955e-03},
    {0.021018875, 0.02638275,    4.45660115955e-03,   4.45660115955e-03},
};
static const size_t Num_10 = sizeof(clamp_10)/sizeof(clamp_10[0]);

static const CLAMP_SEG_T clamp_1L[] = {
    {0.005489525, 0.00795575,   -1.92964802838e-03,   2.35871423428e-02},
    {0.00795575,  0.010000000,  -3.32966809910e-02,   2.35871423428e-02},
};
static const size_t Num_1L = sizeof(clamp_1L)/sizeof(clamp_1L[0]);

static const CLAMP_SEG_T clamp_1H[] = {
    {0.010000000, 0.010019594,   1.99173356672e-02,   1.99174131238e-02},
    {0.010019594, 0.021018875,   1.99174131238e-02,   2.00495119225e-02},
    {0.021018875, 0.02638275,    1.96273396812e-02,   2.00495119225e-02},
    {0.02638275,  0.047608391,   1.92620376901e-02,   1.96273396812e-02},
    {0.047608391, 0.076459006,   1.92620376901e-02,   1.97879914415e-02},
    {0.076459006, 0.101737855,   1.95208084211e-02,   1.97879914415e-02},
    {0.101737855, 0.104738533,   1.95208084211e-02,   1.99486497893e-02},
    {0.104738533, 0.1075482,      1.87823399531e-02,   1.99486497893e-02},
};
static const size_t Num_1H = sizeof(clamp_1H)/sizeof(clamp_1H[0]);

static const CLAMP_SEG_T clamp_01[] = {
    {0.010019594, 0.021018875,  -3.26653169049e-01,  -3.22430462952e-02},
    {0.021018875, 0.02638275,   -3.26653169049e-01,   6.14246995043e-01},
    {0.02638275,  0.047608391,   6.14246995043e-01,   1.42839977400e+00},
    {0.047608391, 0.076459006,   2.56200556005e-01,   1.42839977400e+00},
    {0.076459006, 0.101737855,   2.56200556005e-01,   8.51674448332e-01},
    {0.101737855, 0.104738533,  -1.01860564654e-01,   8.51674448332e-01},
    {0.104738533, 0.1075482,     -1.01860564654e-01,   2.49750767675e+00},
};
static const size_t Num_01 = sizeof(clamp_01)/sizeof(clamp_01[0]);

struct EEPROM_VALUE_T {
    double value[37];
} g_value;

void initValueFromEEPROM() {
    Wire1.setPins(EEPROM_I2C_SDA, EEPROM_I2C_SCL);
    Wire1.setClock(EEPROM_I2C_FREQUENCY);
    Wire1.begin();

    I2C_eeprom ee(EEPROM_I2C_ADDR, 1024, &Wire1);

    if (!ee.begin()) {
        Serial.println("Failed to initialize EEPROM!");
        return;
    }

    ee.readBlock(0, (uint8_t*)&g_value, sizeof(EEPROM_VALUE_T));
}

// U: V
// return: mA
CompensationResult calCompensationByShuntVol(double U) {
    double I = 0.0;
    int seg_idx = -1;
    
    if      (U > 0           && U <= 1e-06)        { I = 0.0; seg_idx = -1; }
    else if (U > 1e-06       && U <= 9.86e-05)     { I = -4.96717885515552e-05 + U * (-1.15024973780837    ) + U * U * ( 7.50380233713587e+03); seg_idx = 0; }
    else if (U > 9.86e-05    && U <= 0.002075875)  { I = -1.17572123826341e-04 + U * (-3.76425950965523e-01) + U * U * (-2.64636863429469e+01); seg_idx = 1; }
    else if (U > 0.002075875 && U <= 0.00213061)   { I =  4.00173135933271e-01 + U * (-1.93091389761448e+02) + U * U * (-8.12502147858271e-01); seg_idx = 2; }
    else if (U > 0.00213061  && U <= 0.005489525)  { I =  2.80464450771294e+01 + U * (-1.06774687954604e+04) + U * U * ( 1.01433693037010e+06); seg_idx = 3; }
    else if (U > 0.005489525 && U <= 0.00795575)   { I =  4.15192674006609e-01 + U * (-1.37494120471743e+02) + U * U * ( 1.11074715236611e+04); seg_idx = 4; }
    else if (U > 0.00795575  && U <= 0.010019594)  { I =  4.73398883967983e+01 + U * (-9.45635027923620e+03) + U * U * ( 4.71917518500573e+05); seg_idx = 5; }
    else if (U > 0.010019594 && U <= 0.021018875)  { I = -4.94687661493529e+00 + U * ( 7.42737702877842e+02) + U * U * (-2.48740191915014e+04); seg_idx = 6; }
    else if (U > 0.021018875 && U <= 0.02638275)   { I = -7.42724335142089e+02 + U * ( 6.33783048995403e+04) + U * U * (-1.33432949251484e+06); seg_idx = 7; }
    else if (U > 0.02638275  && U <= 0.047608391)  { I =  5.94080582648901e+01 + U * (-2.80934246583276e+03) + U * U * ( 3.34248352232072e+04); seg_idx = 8; }
    else if (U > 0.047608391 && U <= 0.076459006)  { I = -2.69169784448099e+01 + U * ( 8.67709858761791e+02) + U * U * (-6.70079569468977e+03); seg_idx = 9; }
    else if (U > 0.076459006 && U <= 0.101737855)  { I =  9.49616304079839e+01 + U * (-2.16873837281881e+03) + U * U * ( 1.22241630543939e+04); seg_idx = 10; }
    else if (U > 0.101737855 && U <= 0.104738533)  { I =  2.25813965130917e+03 + U * (-4.64186589084307e+04) + U * U * ( 2.37333030351984e+05); seg_idx = 11; }
    else if (U > 0.104738533 && U <= 0.1075482)    { I =  2.25813965130917e+03 + U * (-4.64186589084307e+04) + U * U * ( 2.37333030351984e+05); seg_idx = 12; }

    return {I, seg_idx};
}

// return: V
double getShuntVoltage(Adafruit_INA228 *ina228) {
    double shuntVol_V = ina228->readShuntVoltage() / 1000;
    int mos1 = 0, mos2 = 0;

    mos1 = digitalRead(MOS1_PIN);
    mos2 = digitalRead(MOS2_PIN);

    if (mos1 == 0 && mos2 == 0) {
        shuntVol_V = (shuntVol_V > 0.020702038) ? 0.020702038 : shuntVol_V;
    } else if(mos1 == 1 && mos2 == 0) {
        shuntVol_V = (shuntVol_V < 0.004849256) ? 0.004849256 : shuntVol_V;
        shuntVol_V = (shuntVol_V > 0.130323311) ? 0.130323311 : shuntVol_V;
    }

    return shuntVol_V;
}

// return: A
double getCompensation(Adafruit_INA228 *ina228) {
  int mos1 = 0, mos2 = 0;
    double p0 = 0.945438167, p1 = -45.633764711;
    double dl = -0.001059181, gl = 1.011767876, dh = 0.019902946, gh = -0.000451617;
    double g01 = 1.006524039;
    double shuntVol_V = 0, compensation = 0;
    double cmax_mA = 0, cmin_mA = 0;
    int offset = 0;

    mos1 = digitalRead(MOS1_PIN);
    mos2 = digitalRead(MOS2_PIN);

    if (mos1 == 0 && mos2 == 0) {
        offset = 0;
    } else if (mos1 == 1 && mos2 == 0) {
        offset = 12;
    } else if (mos1 == 1 && mos2 == 1) {
        offset = 24;
    }

    shuntVol_V = getShuntVoltage(ina228);
    CompensationResult result = calCompensationByShuntVol(shuntVol_V);
    compensation = result.baseI;  // mA, without g_value
    int seg_idx = result.segmentIndex;

    if (mos1 == 0 && mos2 == 0) {
        compensation = (p0 + p1 * shuntVol_V) * compensation;

        // Get the maximum and minimum values of the current compensation interval
        for (int i = 0; i < Num_10; i++) {
            if (shuntVol_V >= clamp_10[i].umin && shuntVol_V < clamp_10[i].umax) {
                cmin_mA = clamp_10[i].cmin_mA;
                cmax_mA = clamp_10[i].cmax_mA;
                break;
            }
        }
    } else if(mos1 == 1 && mos2 == 0) {
        if (shuntVol_V < 0.01) {
            compensation = dl + gl * compensation;
        } else {
            compensation = dh + gh * compensation;
        }

        // Get the maximum and minimum values of the current compensation interval
        for (int i = 0; i < Num_1L; i++) {
            if (shuntVol_V >= clamp_1L[i].umin && shuntVol_V < clamp_1L[i].umax) {
                cmin_mA = clamp_1L[i].cmin_mA;
                cmax_mA = clamp_1L[i].cmax_mA;
                break;
            }
        }

        for (int i = 0; i < Num_1H; i++) {
            if (shuntVol_V >= clamp_1H[i].umin && shuntVol_V < clamp_1H[i].umax) {
                cmin_mA = clamp_1H[i].cmin_mA;
                cmax_mA = clamp_1H[i].cmax_mA;
                break;
            }
        }
    } else if(mos1 == 1 && mos2 == 1) {
        compensation = g01 * compensation;

        // Get the maximum and minimum values of the current compensation interval
        for (int i = 0; i < Num_01; i++) {
            if (shuntVol_V >= clamp_01[i].umin && shuntVol_V < clamp_01[i].umax) {
                cmin_mA = clamp_01[i].cmin_mA;
                cmax_mA = clamp_01[i].cmax_mA;
                break;
            }
        }
    }

    // Clamp the base compensation
    compensation = (compensation < cmin_mA) ? cmin_mA : compensation;
    compensation = (compensation > cmax_mA) ? cmax_mA : compensation;

    // Add g_value after clamping, if applicable
    if (seg_idx >= 0) {
        compensation += g_value.value[offset + seg_idx];
    }

    return compensation / 1000;
}