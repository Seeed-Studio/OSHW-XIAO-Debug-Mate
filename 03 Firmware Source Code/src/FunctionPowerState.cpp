#include "FunctionPowerState.h"

FunctionPowerState::FunctionPowerState()
    : FunctionState("FunctionPowerState"),
      m_powerStateUI(),
      m_startTime(0),
      m_currentIndex(0), 
      m_update(0), 
      m_voltage(0.0), 
      m_current(0.0), 
      m_minCurrent(999999), 
      m_maxCurrent(0.0), 
      m_totalCurrent(0.0), 
      m_power(0.0), 
      m_minPower(999999), 
      m_maxPower(0.0), 
      m_totalPower(0.0)
{
}

void FunctionPowerState::createPowerSimpleUI()
{
    m_powerStateUI.powerGroup[POWER_INTERFACE_SIMPLE] = lv_obj_create(m_powerStateUI.Screen);
    lv_obj_set_size(m_powerStateUI.powerGroup[POWER_INTERFACE_SIMPLE], 296, 240);
    lv_obj_set_pos(m_powerStateUI.powerGroup[POWER_INTERFACE_SIMPLE], 12, 0);
    lv_obj_add_style(m_powerStateUI.powerGroup[POWER_INTERFACE_SIMPLE], &style_screen, 0);

    lv_obj_t* label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_SIMPLE]);
    lv_label_set_text(label, "U");
    lv_obj_set_pos(label, 20, 25);
    lv_obj_set_style_text_color(label, lv_color_hex(0xDDE62F), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_48, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_SIMPLE]);
    lv_label_set_text(label, "I");
    lv_obj_set_pos(label, 20, 25 + 60);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_48, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_SIMPLE]);
    lv_label_set_text(label, "P");
    lv_obj_set_pos(label, 20, 25 + 60 + 60);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_48, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_SIMPLE]);
    lv_label_set_text(label, "V");
    lv_obj_set_pos(label, 247, 25 + 20);
    lv_obj_set_style_text_color(label, lv_color_hex(0xDDE62F), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_28, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_SIMPLE]);
    lv_label_set_text(label, "A");
    lv_obj_set_pos(label, 247, 25 + 60 + 20);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_28, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_SIMPLE]);
    lv_label_set_text(label, "W");
    lv_obj_set_pos(label, 247, 25 + 60 + 60 + 20);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_28, 0);

    m_powerStateUI.powerSimple.voltage = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_SIMPLE]);
    lv_label_set_text(m_powerStateUI.powerSimple.voltage, "0.0000");
    lv_obj_set_pos(m_powerStateUI.powerSimple.voltage, 62, 25);
    lv_obj_set_style_text_color(m_powerStateUI.powerSimple.voltage, lv_color_hex(0xDDE62F), LV_PART_MAIN);
    lv_obj_add_style(m_powerStateUI.powerSimple.voltage, &style_font_48, 0);

    m_powerStateUI.powerSimple.current = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_SIMPLE]);
    lv_label_set_text(m_powerStateUI.powerSimple.current, "0.0000");
    lv_obj_set_pos(m_powerStateUI.powerSimple.current, 62, 25 + 60);
    lv_obj_set_style_text_color(m_powerStateUI.powerSimple.current, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(m_powerStateUI.powerSimple.current, &style_font_48, 0);

    m_powerStateUI.powerSimple.power = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_SIMPLE]);
    lv_label_set_text(m_powerStateUI.powerSimple.power, "0.0000");
    lv_obj_set_pos(m_powerStateUI.powerSimple.power, 62, 25 + 60 + 60);
    lv_obj_set_style_text_color(m_powerStateUI.powerSimple.power, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_add_style(m_powerStateUI.powerSimple.power, &style_font_48, 0);
}

void FunctionPowerState::createPowerMediumUI()
{
    m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM] = lv_obj_create(m_powerStateUI.Screen);
    lv_obj_set_size(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM], 186, 223);
    lv_obj_center(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_obj_add_style(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM], &style_screen, 0);

    lv_obj_t* label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(label, "U");
    lv_obj_set_pos(label, 0, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xDDE62F), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_30, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(label, "I");
    lv_obj_set_pos(label, 0, 34);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_30, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(label, "P");
    lv_obj_set_pos(label, 0, 146);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_30, 0);

    m_powerStateUI.powerMedium.voltage = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(m_powerStateUI.powerMedium.voltage, "0.0000");
    lv_obj_set_pos(m_powerStateUI.powerMedium.voltage, 30, 0);
    lv_obj_set_style_text_color(m_powerStateUI.powerMedium.voltage, lv_color_hex(0xDDE62F), LV_PART_MAIN);
    lv_obj_set_style_width(m_powerStateUI.powerMedium.voltage, 108, 0);
    lv_obj_add_style(m_powerStateUI.powerMedium.voltage, &style_font_30, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(label, "V");
    lv_obj_set_pos(label, 148, 12);
    lv_obj_set_style_text_color(label, lv_color_hex(0xDDE62F), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    m_powerStateUI.powerMedium.current_A = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(m_powerStateUI.powerMedium.current_A, "0.0000");
    lv_obj_set_pos(m_powerStateUI.powerMedium.current_A, 30, 34);
    lv_obj_set_style_text_color(m_powerStateUI.powerMedium.current_A, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_set_style_width(m_powerStateUI.powerMedium.current_A, 108, 0);
    lv_obj_add_style(m_powerStateUI.powerMedium.current_A, &style_font_30, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(label, "A");
    lv_obj_set_pos(label, 148, 34 + 12);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    m_powerStateUI.powerMedium.current_mA = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(m_powerStateUI.powerMedium.current_mA, "00.000");
    lv_obj_set_pos(m_powerStateUI.powerMedium.current_mA, 30, 71);
    lv_obj_set_style_width(m_powerStateUI.powerMedium.current_mA, 108, 0);
    lv_obj_set_style_text_color(m_powerStateUI.powerMedium.current_mA, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_set_style_text_align(m_powerStateUI.powerMedium.current_mA, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_add_style(m_powerStateUI.powerMedium.current_mA, &style_font_30, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(label, "mA");
    lv_obj_set_pos(label, 148, 71 + 12);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    m_powerStateUI.powerMedium.current_uA = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(m_powerStateUI.powerMedium.current_uA, "00000");
    lv_obj_set_pos(m_powerStateUI.powerMedium.current_uA, 30, 109);
    lv_obj_set_style_width(m_powerStateUI.powerMedium.current_uA, 108, 0);
    lv_obj_set_style_text_color(m_powerStateUI.powerMedium.current_uA, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_set_style_text_align(m_powerStateUI.powerMedium.current_uA, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_add_style(m_powerStateUI.powerMedium.current_uA, &style_font_30, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(label, "uA");
    lv_obj_set_pos(label, 148, 109 + 12);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    m_powerStateUI.powerMedium.power_W = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(m_powerStateUI.powerMedium.power_W, "0.0000");
    lv_obj_set_pos(m_powerStateUI.powerMedium.power_W, 30, 146);
    lv_obj_set_style_text_color(m_powerStateUI.powerMedium.power_W, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_set_style_width(m_powerStateUI.powerMedium.power_W, 108, 0);
    lv_obj_add_style(m_powerStateUI.powerMedium.power_W, &style_font_30, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(label, "W");
    lv_obj_set_pos(label, 148, 146 + 12);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    m_powerStateUI.powerMedium.power_mW = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(m_powerStateUI.powerMedium.power_mW, "00.0");
    lv_obj_set_pos(m_powerStateUI.powerMedium.power_mW, 30, 183);
    lv_obj_set_style_width(m_powerStateUI.powerMedium.power_mW, 108, 0);
    lv_obj_set_style_text_color(m_powerStateUI.powerMedium.power_mW, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_set_style_text_align(m_powerStateUI.powerMedium.power_mW, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_add_style(m_powerStateUI.powerMedium.power_mW, &style_font_30, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM]);
    lv_label_set_text(label, "mW");
    lv_obj_set_pos(label, 148, 183 + 12);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);
}

void FunctionPowerState::createPowerComplexUI()
{
    lv_obj_t* label = nullptr;

    m_powerStateUI.powerGroup[POWER_INTERFACE_COMPLEX] = lv_obj_create(m_powerStateUI.Screen);
    lv_obj_set_size(m_powerStateUI.powerGroup[POWER_INTERFACE_COMPLEX], 296, 240);
    lv_obj_set_pos(m_powerStateUI.powerGroup[POWER_INTERFACE_COMPLEX], 12, 0);
    lv_obj_add_style(m_powerStateUI.powerGroup[POWER_INTERFACE_COMPLEX], &style_screen, 0);

    // Top bar
    m_powerStateUI.powerComplex.voltage = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_COMPLEX]);
    lv_label_set_text(m_powerStateUI.powerComplex.voltage, "5.00");
    lv_obj_set_pos(m_powerStateUI.powerComplex.voltage, 48, 10);
    lv_obj_set_style_text_color(m_powerStateUI.powerComplex.voltage, lv_color_hex(0xDDE62F), LV_PART_MAIN);
    lv_obj_add_style(m_powerStateUI.powerComplex.voltage, &style_font_14, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_COMPLEX]);
    lv_label_set_text(label, "V");
    lv_obj_set_pos(label, 85, 10);
    lv_obj_set_style_text_color(label, lv_color_hex(0xDDE62F), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_14, 0);

    m_powerStateUI.powerComplex.current = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_COMPLEX]);
    lv_label_set_text(m_powerStateUI.powerComplex.current, "0.00");
    lv_obj_set_pos(m_powerStateUI.powerComplex.current, 123, 10);
    lv_obj_set_style_text_color(m_powerStateUI.powerComplex.current, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(m_powerStateUI.powerComplex.current, &style_font_14, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_COMPLEX]);
    lv_label_set_text(label, "A");
    lv_obj_set_pos(label, 160, 10);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_14, 0);

    m_powerStateUI.powerComplex.power = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_COMPLEX]);
    lv_label_set_text(m_powerStateUI.powerComplex.power, "0.00");
    lv_obj_set_pos(m_powerStateUI.powerComplex.power, 198, 10);
    lv_obj_set_style_text_color(m_powerStateUI.powerComplex.power, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_add_style(m_powerStateUI.powerComplex.power, &style_font_14, 0);

    label = lv_label_create(m_powerStateUI.powerGroup[POWER_INTERFACE_COMPLEX]);
    lv_label_set_text(label, "W");
    lv_obj_set_pos(label, 235, 10);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2F8EE6), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_14, 0);

    // Group
    m_powerStateUI.powerComplex.viewGroup = lv_obj_create(m_powerStateUI.powerGroup[POWER_INTERFACE_COMPLEX]);
    lv_obj_set_size(m_powerStateUI.powerComplex.viewGroup, 273, 184);
    lv_obj_center(m_powerStateUI.powerComplex.viewGroup);
    lv_obj_add_style(m_powerStateUI.powerComplex.viewGroup, &style_screen, 0);

    // Min
    label = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(label, "Min");
    lv_obj_set_pos(label, 0, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    m_powerStateUI.powerComplex.minCurrent_A = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(m_powerStateUI.powerComplex.minCurrent_A, "0.0000");
    lv_obj_set_pos(m_powerStateUI.powerComplex.minCurrent_A, 0, 21);
    lv_obj_set_style_text_color(m_powerStateUI.powerComplex.minCurrent_A, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(m_powerStateUI.powerComplex.minCurrent_A, &style_font_26, 0);

    label = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(label, "A");
    lv_obj_set_pos(label, 98, 31);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    m_powerStateUI.powerComplex.minPower_W = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(m_powerStateUI.powerComplex.minPower_W, "0.0000");
    lv_obj_set_pos(m_powerStateUI.powerComplex.minPower_W, 0, 55);
    lv_obj_set_style_text_color(m_powerStateUI.powerComplex.minPower_W, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(m_powerStateUI.powerComplex.minPower_W, &style_font_26, 0);

    label = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(label, "W");
    lv_obj_set_pos(label, 98, 65);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    // Max
    label = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(label, "Max");
    lv_obj_set_pos(label, 142, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    m_powerStateUI.powerComplex.maxCurrent_A = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(m_powerStateUI.powerComplex.maxCurrent_A, "0.0000");
    lv_obj_set_pos(m_powerStateUI.powerComplex.maxCurrent_A, 142, 21);
    lv_obj_set_style_text_color(m_powerStateUI.powerComplex.maxCurrent_A, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(m_powerStateUI.powerComplex.maxCurrent_A, &style_font_26, 0);

    label = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(label, "A");
    lv_obj_set_pos(label, 240, 31);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    m_powerStateUI.powerComplex.maxPower_W = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(m_powerStateUI.powerComplex.maxPower_W, "0.0000");
    lv_obj_set_pos(m_powerStateUI.powerComplex.maxPower_W, 142, 55);
    lv_obj_set_style_text_color(m_powerStateUI.powerComplex.maxPower_W, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(m_powerStateUI.powerComplex.maxPower_W, &style_font_26, 0);

    label = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(label, "W");
    lv_obj_set_pos(label, 240, 65);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    // Total
    label = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(label, "Total");
    lv_obj_set_pos(label, 0, 95);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    m_powerStateUI.powerComplex.totalCurrent_Ah = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(m_powerStateUI.powerComplex.totalCurrent_Ah, "0.0000");
    lv_obj_set_pos(m_powerStateUI.powerComplex.totalCurrent_Ah, 0, 116);
    lv_obj_set_style_text_color(m_powerStateUI.powerComplex.totalCurrent_Ah, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(m_powerStateUI.powerComplex.totalCurrent_Ah, &style_font_26, 0);

    label = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(label, "Ah");
    lv_obj_set_pos(label, 98, 126);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    m_powerStateUI.powerComplex.totalPower_Wh = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(m_powerStateUI.powerComplex.totalPower_Wh, "0.0000");
    lv_obj_set_pos(m_powerStateUI.powerComplex.totalPower_Wh, 0, 150);
    lv_obj_set_style_text_color(m_powerStateUI.powerComplex.totalPower_Wh, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(m_powerStateUI.powerComplex.totalPower_Wh, &style_font_26, 0);

    label = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(label, "Wh");
    lv_obj_set_pos(label, 98, 160);
    lv_obj_set_style_text_color(label, lv_color_hex(0x2FE6AC), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    // Time
    label = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(label, "Time");
    lv_obj_set_pos(label, 142, 95);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(label, &style_font_16, 0);

    m_powerStateUI.powerComplex.time = lv_label_create(m_powerStateUI.powerComplex.viewGroup);
    lv_label_set_text(m_powerStateUI.powerComplex.time, "00:00:00");
    lv_obj_set_pos(m_powerStateUI.powerComplex.time, 142, 116);
    lv_obj_set_style_text_color(m_powerStateUI.powerComplex.time, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_style(m_powerStateUI.powerComplex.time, &style_font_26, 0);
}

void FunctionPowerState::onEnter()
{
    if (m_powerStateUI.Screen != nullptr) {
        if (lv_scr_act() != m_powerStateUI.Screen) {
            lv_scr_load(m_powerStateUI.Screen);
        }
        return;
    }

    m_powerStateUI.Screen = lv_obj_create(NULL);
    lv_obj_add_style(m_powerStateUI.Screen, &style_screen, 0);

    createPowerSimpleUI();
    createPowerMediumUI();
    createPowerComplexUI();

    lv_obj_add_flag(m_powerStateUI.powerGroup[POWER_INTERFACE_MEDIUM], LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(m_powerStateUI.powerGroup[POWER_INTERFACE_COMPLEX], LV_OBJ_FLAG_HIDDEN);

    lv_scr_load(m_powerStateUI.Screen);
}

void FunctionPowerState::onExit()
{
}

bool FunctionPowerState::handleEvent(StateMachine* machine, const Event* event)
{
    if (!machine || !event) {
        return false;
    }

    switch (event->getType()) {
        case EVENT_WHEEL_CLOCKWISE: {
            m_currentIndex = (m_currentIndex + 1) % 3;
            m_update = 1;
            break;
        }

        case EVENT_WHEEL_COUNTERCLOCKWISE: {
            m_currentIndex = (m_currentIndex - 1 + 3) % 3;
            m_update = 1;
            break;
        }

        case EVENT_BUTTON_PRESS:
        case EVENT_BUTTON_LONGPRESS: {
            const ButtonEvent* buttonEvent = static_cast<const ButtonEvent*>(event);
            if (buttonEvent->getButtonId() == BOOT_BTN) {
                int stateId = MainMenuState::ID;
                State* nextState = StateManager::getInstance()->getState(stateId);
                if (nextState) {
                    machine->changeState(nextState);
                    return true;
                }
            }
        }

        default:
            break;
    }

    return true;
}

void FunctionPowerState::updateDisplay(DisplayContext* display)
{
    if (!display) {
        return;
    }

    if (m_update) {
        for (int i = 0; i < 3; i++) {
            lv_obj_add_flag(m_powerStateUI.powerGroup[i], LV_OBJ_FLAG_HIDDEN);
            if (i == m_currentIndex) {
                lv_obj_remove_flag(m_powerStateUI.powerGroup[i], LV_OBJ_FLAG_HIDDEN);
                continue;
            }
        }

        m_update = 0;
    }

    Adafruit_INA228* ina228 = nullptr;
    char value[10];
    float vol = 0, cur = 0, power = 0;
    static unsigned long lastTime = 0;

    ina228 = display->getINA228();
    vol = (ina228->readBusVoltage() / 1000 - ina228->readShuntVoltage()) / 1000;
    cur = _max(0.0, ina228->readCurrent() / 1000);
    power = vol * cur;

    if (m_currentIndex == POWER_INTERFACE_COMPLEX && !m_startTime) {
        m_startTime = millis();
    } else if(m_currentIndex != POWER_INTERFACE_COMPLEX) {
        m_startTime = 0;
        m_minCurrent = m_maxCurrent = cur;
        m_minPower = m_maxPower = power;
        m_totalCurrent = m_totalPower = 0;
    }

    switch (m_currentIndex) {
        case POWER_INTERFACE_SIMPLE: {
            snprintf(value, sizeof(value), "%.4f", vol);
            lv_label_set_text(m_powerStateUI.powerSimple.voltage, value);

            snprintf(value, sizeof(value), "%.4f", cur);
            lv_label_set_text(m_powerStateUI.powerSimple.current, value);

            snprintf(value, sizeof(value), "%.4f", power);
            lv_label_set_text(m_powerStateUI.powerSimple.power, value);
            break;
        }

        case POWER_INTERFACE_MEDIUM: {
            snprintf(value, sizeof(value), "%.4f", vol);
            lv_label_set_text(m_powerStateUI.powerMedium.voltage, value);

            snprintf(value, sizeof(value), "%.4f", cur);
            lv_label_set_text(m_powerStateUI.powerMedium.current_A, value);
            snprintf(value, sizeof(value), "%.3f", cur * 1000);
            lv_label_set_text(m_powerStateUI.powerMedium.current_mA, value);
            snprintf(value, sizeof(value), "%.0f", cur * 1000 * 1000);
            lv_label_set_text(m_powerStateUI.powerMedium.current_uA, value);

            snprintf(value, sizeof(value), "%.4f", power);
            lv_label_set_text(m_powerStateUI.powerMedium.power_W, value);
            snprintf(value, sizeof(value), "%.1f", power * 1000);
            lv_label_set_text(m_powerStateUI.powerMedium.power_mW, value);
            break;
        }

        case POWER_INTERFACE_COMPLEX: {
            unsigned long currentTime = millis();

            if (lastTime != 0) {
                double timeInterval = (double)(currentTime - lastTime) / 1000 / 360;
                m_totalCurrent += cur * timeInterval;
                m_totalPower += power * timeInterval;
            }
            lastTime = currentTime;

            m_minCurrent = _min(m_minCurrent, cur);
            m_minPower = _min(m_minPower, power);
            m_maxCurrent = _max(m_maxCurrent, cur);
            m_maxPower = _max(m_maxPower, power);

            snprintf(value, sizeof(value), "%.2f", vol);
            lv_label_set_text(m_powerStateUI.powerComplex.voltage, value);
            snprintf(value, sizeof(value), "%.2f", cur);
            lv_label_set_text(m_powerStateUI.powerComplex.current, value);
            snprintf(value, sizeof(value), "%.2f", power);
            lv_label_set_text(m_powerStateUI.powerComplex.power, value);

            snprintf(value, sizeof(value), "%.4f", m_minCurrent);
            lv_label_set_text(m_powerStateUI.powerComplex.minCurrent_A, value);
            snprintf(value, sizeof(value), "%.4f", m_minPower);
            lv_label_set_text(m_powerStateUI.powerComplex.minPower_W, value);

            snprintf(value, sizeof(value), "%.4f", m_maxCurrent);
            lv_label_set_text(m_powerStateUI.powerComplex.maxCurrent_A, value);
            snprintf(value, sizeof(value), "%.4f", m_maxPower);
            lv_label_set_text(m_powerStateUI.powerComplex.maxPower_W, value);

            snprintf(value, sizeof(value), "%.4f", m_totalCurrent);
            lv_label_set_text(m_powerStateUI.powerComplex.totalCurrent_Ah, value);
            snprintf(value, sizeof(value), "%.4f", m_totalPower);
            lv_label_set_text(m_powerStateUI.powerComplex.totalPower_Wh, value);

            currentTime = (currentTime - m_startTime) / 1000;
            sprintf(value, "%02lu:%02lu:%02lu", currentTime / 60 / 60, currentTime / 60 % 60, currentTime % 60);
            lv_label_set_text(m_powerStateUI.powerComplex.time, value);
            break;
        }

        default:
            break;
    }
}

int FunctionPowerState::getID() const
{
    return ID;
}

const char* FunctionPowerState::getName() const
{
    return "FunctionPowerState";
}
