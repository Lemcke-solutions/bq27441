#include "bq27441.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <SparkFunBQ27441.h>

namespace esphome {
namespace bq27441 {

static const char *const TAG = "bq27441";
const unsigned int BATTERY_CAPACITY = 2000; // e.g. 850mAh battery


// based on
//  - https://cdn.sparkfun.com/datasheets/BreakoutBoards/CCS811_Programming_Guide.pdf

//#define CHECK_TRUE(f, error_code) \
//  if (!(f)) { \
//    this->mark_failed(); \
//    this->error_code_ = (error_code); \
//    return; \
//  }
//
//#define CHECKED_IO(f) CHECK_TRUE(f, COMMUNICATION_FAILED)


void setupBQ27441(void)
{
  // Use lipo.begin() to initialize the BQ27441-G1A and confirm that it's
  // connected and communicating.
  if (!lipo.begin()) // begin() will return true if communication is successful
  {
	// If communication fails, print an error message and loop forever.
    Serial.println("Error: Unable to communicate with BQ27441.");
    Serial.println("  Check wiring and try again.");
    Serial.println("  (Battery must be plugged into Battery Babysitter!)");
    while (1) ;
  }
  Serial.println("Connected to BQ27441!");

  // Uset lipo.setCapacity(BATTERY_CAPACITY) to set the design capacity
  // of your battery.
  lipo.setCapacity(BATTERY_CAPACITY);
}


void BQ27441Component::setup() {
  setupBQ27441();
}

void BQ27441Component::update() {

    unsigned int soc = lipo.soc();

    this->battery_level->publish_state(soc);

//  this->status_clear_warning();

//  this->send_env_data_();
}

void BQ27441Component::dump_config() {
//  ESP_LOGCONFIG(TAG, "CCS811");
//  LOG_I2C_DEVICE(this)
//  LOG_UPDATE_INTERVAL(this)
//  LOG_SENSOR("  ", "CO2 Sensor", this->co2_)
//  LOG_SENSOR("  ", "TVOC Sensor", this->tvoc_)
//  LOG_TEXT_SENSOR("  ", "Firmware Version Sensor", this->version_)
//  if (this->baseline_) {
//    ESP_LOGCONFIG(TAG, "  Baseline: %04X", *this->baseline_);
//  } else {
//    ESP_LOGCONFIG(TAG, "  Baseline: NOT SET");
//  }
//  if (this->is_failed()) {
//    switch (this->error_code_) {
//      case COMMUNICATION_FAILED:
//        ESP_LOGW(TAG, "Communication failed! Is the sensor connected?");
//        break;
//      case INVALID_ID:
//        ESP_LOGW(TAG, "Sensor reported an invalid ID. Is this a CCS811?");
//        break;
//      case SENSOR_REPORTED_ERROR:
//        ESP_LOGW(TAG, "Sensor reported internal error");
//        break;
//      case APP_INVALID:
//        ESP_LOGW(TAG, "Sensor reported invalid APP installed.");
//        break;
//      case APP_START_FAILED:
//        ESP_LOGW(TAG, "Sensor reported APP start failed.");
//        break;
//      case UNKNOWN:
//      default:
//        ESP_LOGW(TAG, "Unknown setup error!");
//        break;
//    }
//  }
}

}  // namespace ccs811
}  // namespace esphome
