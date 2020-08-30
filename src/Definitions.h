#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

namespace Internals
{
    const uint16_t MAX_JSON_CONFIG_FILE_SIZE = 1000;
    const uint8_t MAX_CONFIG_SETTING_SIZE = 10;
    const uint16_t MAX_JSON_CONFIG_ARDUINOJSON_BUFFER_SIZE = JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(9) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(MAX_CONFIG_SETTING_SIZE);


    const uint8_t MAX_MAC_LENGTH = 6 + 1;
    const uint8_t MAX_MAC_STRING_LENGTH = (MAX_MAC_LENGTH * 2) + 1;

    const uint8_t MAX_WIFI_SSID_LENGTH = 32 + 1;
    const uint8_t MAX_WIFI_PASSWORD_LENGTH = 64 + 1;
    const uint16_t MAX_HOSTNAME_LENGTH = 255 + 1;

    const uint8_t MAX_MQTT_CREDS_LENGTH = 32 + 1;
    const uint8_t MAX_MQTT_BASE_TOPIC_LENGTH = 48 + 1;
    const uint8_t MAX_MQTT_TOPIC_LENGTH = 128 + 1;    

    const uint8_t MAX_FRIENDLY_NAME_LENGTH = 64 + 1;
    const uint8_t MAX_DEVICE_ID_LENGTH = 32 + 1;

    const uint8_t MAX_IP_STRING_LENGTH = 16 + 1;

    const char CONFIG_NEXT_BOOT_MODE_FILE_PATH[] = "/BootMode";
    const char CONFIG_FILE_PATH[] = "/config.json";

    const uint32_t STATS_SEND_INTERVAL_SEC = 1 * 60;

    const uint16_t DEFAULT_MQTT_PORT = 1883;
    const char DEFAULT_MQTT_BASE_TOPIC[] = "esphomer/";

    const uint16_t CONFIG_LED_TIME = 200; //ms
    const uint16_t WIFI_LED_TIME = 400; //ms
    const uint16_t MQTT_LED_TIME = 800; //ms
}