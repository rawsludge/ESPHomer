#include "DeviceConfig.hpp"

using namespace Internals;

DeviceConfig::DeviceConfig() :
    _configStruct(),
    _fileSystem(false),
    _configValid(false)
{
}

bool DeviceConfig::initFileSystem()
{
    if( _fileSystem ) return _fileSystem;

    _fileSystem = LittleFS.begin();

    if( !_fileSystem ) 
        Log.error("File system can't initialized" CR);
    return _fileSystem;
}

bool DeviceConfig::load()
{
    if( !initFileSystem() ) return false;

    //LittleFS.remove(CONFIG_FILE_PATH);

    _configValid = false;
    if (!LittleFS.exists(CONFIG_FILE_PATH)) {
        Log.error( " %s doesn't exist" CR, CONFIG_FILE_PATH);
        return false;
    }    

    File configFile = LittleFS.open(CONFIG_FILE_PATH, "r");
    if (!configFile) {
        Log.error( "Cannot open config file" CR);
        return false;
    }    
    size_t configSize = configFile.size();
    if (configSize >= MAX_JSON_CONFIG_FILE_SIZE) {
        Log.error( "Config file too big" CR);
        return false;
    }    
    char buf[MAX_JSON_CONFIG_FILE_SIZE];
    configFile.readBytes(buf, configSize);
    configFile.close();
    buf[configSize] = '\0';   

    return load(buf);
}

bool DeviceConfig::load(const char *configBuf)
{
    StaticJsonDocument<MAX_JSON_CONFIG_ARDUINOJSON_BUFFER_SIZE> jsonDoc;
    if (deserializeJson(jsonDoc, configBuf) != DeserializationError::Ok || !jsonDoc.is<JsonObject>()) {
        Log.error("Invalid JSON in the config file" CR);
        return false;
    }     

    JsonObject parsedJson = jsonDoc.as<JsonObject>();
    JsonObject reqWifi = parsedJson["wifi"];
    JsonObject reqMqtt = parsedJson["mqtt"];    

    const char* reqName = parsedJson["name"];
    const char* reqWifiSsid = reqWifi["ssid"];
    const char* reqMqttHost = reqMqtt["host"];    

    /* Optional config items */
    const char* reqDeviceId = parsedJson["device_id"] | Helpers::getID();
    uint16_t regDeviceStatsInterval = parsedJson["device_stats_interval"] | STATS_SEND_INTERVAL_SEC;
    bool reqOtaEnabled = parsedJson["ota"]["enabled"] | false;    


    //uint16_t reqWifiChannel = reqWifi["channel"] | 0;
    //const char* reqWifiBssid = reqWifi["bssid"] | "";
    const char* reqWifiPassword = reqWifi["password"]; // implicit | nullptr;
    //const char* reqWifiIp = reqWifi["ip"] | "";
    //const char* reqWifiMask = reqWifi["mask"] | "";
    //const char* reqWifiGw = reqWifi["gw"] | "";
    //const char* reqWifiDns1 = reqWifi["dns1"] | "";
    //const char* reqWifiDns2 = reqWifi["dns2"] | "";

    uint16_t reqMqttPort = reqMqtt["port"] | DEFAULT_MQTT_PORT;
    //bool reqMqttSsl = reqMqtt["ssl"] | false;
    bool reqMqttAuth = reqMqtt["auth"] | false;
    const char* reqMqttUsername = reqMqtt["username"] | "";
    const char* reqMqttPassword = reqMqtt["password"] | "";
    //const char* reqMqttFingerprint = reqMqtt["ssl_fingerprint"] | "";
    const char* reqMqttBaseTopic = reqMqtt["base_topic"] | DEFAULT_MQTT_BASE_TOPIC;

    strlcpy(_configStruct.name, reqName, MAX_FRIENDLY_NAME_LENGTH);
    strlcpy(_configStruct.deviceId, reqDeviceId, MAX_DEVICE_ID_LENGTH);
    _configStruct.deviceStatsInterval = regDeviceStatsInterval;
    strlcpy(_configStruct.wifi.ssid, reqWifiSsid, MAX_WIFI_SSID_LENGTH);
    if (reqWifiPassword) strlcpy(_configStruct.wifi.password, reqWifiPassword, MAX_WIFI_PASSWORD_LENGTH);
    /*
    strlcpy(_configStruct.wifi.bssid, reqWifiBssid, MAX_MAC_STRING_LENGTH + 6);
    _configStruct.wifi.channel = reqWifiChannel;
    strlcpy(_configStruct.wifi.ip, reqWifiIp, MAX_IP_STRING_LENGTH);
    strlcpy(_configStruct.wifi.gw, reqWifiGw, MAX_IP_STRING_LENGTH);
    strlcpy(_configStruct.wifi.mask, reqWifiMask, MAX_IP_STRING_LENGTH);
    strlcpy(_configStruct.wifi.dns1, reqWifiDns1, MAX_IP_STRING_LENGTH);
    strlcpy(_configStruct.wifi.dns2, reqWifiDns2, MAX_IP_STRING_LENGTH);
    */
    strlcpy(_configStruct.mqtt.server.host, reqMqttHost, MAX_HOSTNAME_LENGTH);
    /*
    #if ASYNC_TCP_SSL_ENABLED
    _configStruct.mqtt.server.ssl.enabled = reqMqttSsl;
    if (strcmp_P(reqMqttFingerprint, PSTR("")) != 0) {
        _configStruct.mqtt.server.ssl.hasFingerprint = true;
        Helpers::hexStringToByteArray(reqMqttFingerprint, _configStruct.mqtt.server.ssl.fingerprint, MAX_FINGERPRINT_SIZE);
    }
    #endif
    */
    _configStruct.mqtt.server.port = reqMqttPort;
    strlcpy(_configStruct.mqtt.baseTopic, reqMqttBaseTopic, MAX_MQTT_BASE_TOPIC_LENGTH);
    _configStruct.mqtt.auth = reqMqttAuth;
    strlcpy(_configStruct.mqtt.username, reqMqttUsername, MAX_MQTT_CREDS_LENGTH);
    strlcpy(_configStruct.mqtt.password, reqMqttPassword, MAX_MQTT_CREDS_LENGTH);
    _configStruct.ota.enabled = reqOtaEnabled;

    /* Parse the settings */

    //JsonObject settingsObject = parsedJson["settings"].as<JsonObject>();    
    _configValid = true;
    return true;    
}

bool DeviceConfig::save()
{
    return false;
}

bool DeviceConfig::save(const char *buffer)
{
    if (!initFileSystem()) { return false; }
    LittleFS.remove(CONFIG_FILE_PATH);
    File configFile = LittleFS.open(CONFIG_FILE_PATH, "w");
    if (!configFile) {
        Log.error("Cannot open config file");
        return false;
    }

    DynamicJsonDocument parseJsonDoc(MAX_JSON_CONFIG_ARDUINOJSON_BUFFER_SIZE);
    if (deserializeJson(parseJsonDoc, buffer) != DeserializationError::Ok || !parseJsonDoc.is<JsonObject>()) {
        strncpy(Helpers::_lastError, "Invalid or too big JSON", 80);
        return false;
    }
    JsonObject parsedJson = parseJsonDoc.as<JsonObject>();
    serializeJson(parsedJson, configFile);
    configFile.close();

    return true;
}

struct ConfigStruct DeviceConfig::Details()
{
    return _configStruct;
}

DeviceConfig::~DeviceConfig()
{
}
