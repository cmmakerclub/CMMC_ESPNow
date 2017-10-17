#ifndef CMMC_ESPNow_H
#define CMMC_ESPNow_H

#include "ESP8266WiFi.h"
#include <functional>

#ifdef ESP8266
extern "C" {
  #include "user_interface.h"
  #include "espnow.h"
}
#endif

#define NOW_MODE_SLAVE 1
#define NOW_MODE_CONTROLLER 2

class CMMC_ESPNow
{
  public:
      // constructor
      CMMC_ESPNow() {
        esp_now_recv_cb_t dummy_recv;
        esp_now_send_cb_t dummy_sent;
        this->_user_on_message_recv = dummy_recv;
        this->_user_on_message_sent = dummy_sent;
      }
      ~CMMC_ESPNow() {}
      void init(int mode);
      void send(uint8_t *mac, u8* data, int len) {
        esp_now_send(mac, (u8*) &data, len);
      }

      void on_message_recv(esp_now_recv_cb_t cb) {
        if (cb != NULL) {
          this->_user_on_message_recv = cb;
        }
      }

      void on_message_sent(esp_now_send_cb_t cb) {
        if (cb != NULL) {
          this->_user_on_message_sent = cb;
        }
      }
  private:
    esp_now_recv_cb_t _user_on_message_recv;
    esp_now_send_cb_t _user_on_message_sent;
};

#endif //CMMC_ESPNow_H
