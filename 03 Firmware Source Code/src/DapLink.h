#ifndef __DAP_LINK_H__
#define __DAP_LINK_H__

#include "DAP_config.h"
#include "DAP.h"

void initDapLink();

void set_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize);

uint16_t get_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen);

#endif
