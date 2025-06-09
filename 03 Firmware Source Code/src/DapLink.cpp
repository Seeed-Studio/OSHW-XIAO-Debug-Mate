#include "DapLink.h"
#include "Global.h"

#include <stdint.h>

#define USBDevice TinyUSBDevice

uint8_t const desc_hid_report[] =
{
    0x06, 0x00, 0xFF,                       /*  Usage Page (vendor defined) ($FF00) global */
    0x09, 0x01,                             /*  Usage (vendor defined) ($01) local */
    0xA1, 0x01,                             /*  Collection (Application) */
    0x15, 0,                                /*  LOGICAL_MINIMUM (0) */
    0x26, (0xFF&0xFF), ((0xFF>>8)&0xFF),    /* logical maximum = 255 */
    0x75, 8,                                /*  REPORT_SIZE (8bit) */
    // Input Report
    0x95, 64,                               /*  Report Length (64 REPORT_SIZE) */
    0x09, 0x01,                             /*  USAGE (Vendor Usage 1) */
    0x81, (0<<0 | 1<<1 | 0<<2),             /*  Input(data,var,absolute) */
    // Output Report
    0x95, 64,                               /*  Report Length (64 REPORT_SIZE) */
    0x09, 0x01,                             /*  USAGE (Vendor Usage 1) */
    0x91, (0<<0 | 1<<1 | 0<<2),             /*  Output(data,var,absolute) */
    // Feature Report
    0x95, 1,                                /*  Report Length (1 REPORT_SIZE) */
    0x09, 0x01,                             /*  USAGE (Vendor Usage 1) */
    0xB1, (0<<0 | 1<<1 | 0<<2),             /*  Feature(data,var,absolute) */
    0xC0                                    /*  END_COLLECTION	 */
};

static uint32_t free_count;
static uint32_t send_count;

static uint32_t recv_idx;
static uint32_t send_idx;
static volatile uint8_t  USB_ResponseIdle;

// define usb_hid
Adafruit_USBD_HID usb_hid;

static uint8_t USB_Request[DAP_PACKET_COUNT][DAP_PACKET_SIZE];  // Request  Buffer
uint8_t rawhidResponse[DAP_PACKET_SIZE];
bool daplinkStatus = true;

#define FREE_COUNT_INIT          (DAP_PACKET_COUNT)
#define SEND_COUNT_INIT          0

void initDapLink(bool blocked) {
    USBDevice.setProductDescriptor("CMSIS-DAP");
    USBDevice.setID(0x0D28,0x0204);

    if (!USBDevice.isInitialized()) {
        USBDevice.begin(0);
    }

    usb_hid.enableOutEndpoint(true);
    usb_hid.setPollInterval(2);
    usb_hid.setBootProtocol(0);
    usb_hid.setStringDescriptor("CMSIS-DAP");
    usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
    usb_hid.setReportCallback(get_report_callback, set_report_callback);

    int ret = usb_hid.begin();
    if (!ret) {
        ShowSerial.println("usb hid begin failed");
    }

    if (USBDevice.mounted()) {
        ShowSerial.println("DAPLink reattach");
        USBDevice.detach();
        delay(10);
        USBDevice.attach();
    }

    if (blocked) {
        // wait until device mounted
        int cnt = 0;
        while( !USBDevice.mounted() ) {
            delay(10);
            if (++cnt >= 300) {
                daplinkStatus = false;
                break;
            }
        }
    }

    DAP_Setup();

    recv_idx = 0;
    send_idx = 0;
    USB_ResponseIdle = 1;
    free_count = FREE_COUNT_INIT;
    send_count = SEND_COUNT_INIT;
}

void hid_send_packet()
{
    if (send_count) {
        send_count--;
        usb_hid.sendReport(0, USB_Request[0], DAP_PACKET_SIZE);
        send_idx = (send_idx + 1) % DAP_PACKET_COUNT;
        free_count++;
    }
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t get_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
    return (0);
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void set_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
    int i;
    // main_led_state_t led_next_state = MAIN_LED_FLASH;
    switch (report_type) {
        case 0:
        case 2:
            if (bufsize == 0) {
                break;
            }

            if (buffer[0] == ID_DAP_TransferAbort) {
                DAP_TransferAbort = 1;
                break;
            }

            // Store data into request packet buffer
            // If there are no free buffers discard the data
            if (free_count > 0) {
                free_count--;
                memcpy(USB_Request[recv_idx], buffer, bufsize);
                DAP_ExecuteCommand(buffer, USB_Request[recv_idx]);
                recv_idx = (recv_idx + 1) % DAP_PACKET_COUNT;
                send_count++;
                if (USB_ResponseIdle) {
                    hid_send_packet();
                }
            }
            break;

        case HID_REPORT_FEATURE:
            break;
    }
}
