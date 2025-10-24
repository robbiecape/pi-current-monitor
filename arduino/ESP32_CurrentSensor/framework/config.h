/**
 * ESP32 Sensor Framework - Configuration
 *
 * Common configuration settings for all sensor types
 */

#ifndef ESP_SENSOR_CONFIG_H
#define ESP_SENSOR_CONFIG_H

// Firmware Version
#define FRAMEWORK_VERSION "1.0"
#define BUILD_DATE __DATE__
#define BUILD_TIME __TIME__

// LED Configuration
#define LED_PIN 2
#define LED_BLINK_NORMAL 10000      // Normal blink every 10 seconds
#define LED_BLINK_MQTT_RETRY 500    // Fast blink during MQTT retry

// MQTT Configuration
#define MQTT_PORT 1883
#define MQTT_RETRY_FAST 10000       // Fast retry: 10 seconds
#define MQTT_RETRY_SLOW 600000      // Slow retry: 10 minutes
#define MQTT_RETRY_THRESHOLD 3      // Switch to slow retry after this many failures

// WiFi Configuration
#define WIFI_CONNECT_TIMEOUT 30000  // 30 seconds to connect
#define CONFIG_PORTAL_TIMEOUT 0     // 0 = blocking portal (wait forever)

// Data Publishing
#define PUBLISH_INTERVAL_CONNECTED 5000    // Publish every 5 seconds when connected
#define PUBLISH_INTERVAL_BUFFERING 30000   // Store every 30 seconds when disconnected
#define STATUS_PUBLISH_INTERVAL 10000      // Publish WiFi signal status every 10 seconds

// Local Buffering
#define BUFFER_MAX_SIZE 512000      // 500KB max buffer size
#define BUFFER_UPLOAD_DELAY 20      // 20ms delay between buffered uploads (50/sec)
#define BUFFER_PATH "/buffer"       // Directory for buffer files

// NTP Configuration
#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET_SEC 0
#define DAYLIGHT_OFFSET_SEC 0

// AWS Heartbeat for failure notifications
#define AWS_HEARTBEAT_URL "https://heartbeat.gooddecisionsmi.com/hb/32370e9e9064af59482f57365150b93c4207437f007c5dd16167a48d3905c049/"

// Web Server
#define WEB_SERVER_PORT 80

#endif // ESP_SENSOR_CONFIG_H
