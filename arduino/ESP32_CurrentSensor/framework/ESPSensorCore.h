/**
 * ESP32 Sensor Framework - Core Module
 *
 * Provides reusable WiFi, MQTT, buffering, and status reporting for ESP32 sensors
 *
 * Usage:
 *   #include "framework/ESPSensorCore.h"
 *   ESPSensorCore framework;
 *
 *   void setup() {
 *     framework.begin();
 *   }
 *
 *   void loop() {
 *     framework.update();
 *     if (framework.shouldPublish()) {
 *       framework.publish("temperature_celsius", 22.5);
 *     }
 *   }
 */

#ifndef ESP_SENSOR_CORE_H
#define ESP_SENSOR_CORE_H

#include <WiFi.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <ESPmDNS.h>
#include <Preferences.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <time.h>
#include "config.h"

// =============================================================================
// HELPER FUNCTIONS
// =============================================================================

/**
 * Convert WiFi RSSI to human-readable quality string
 */
String getWiFiQuality(int rssi) {
  if (rssi >= -50) return "Excellent";
  if (rssi >= -60) return "Very Good";
  if (rssi >= -67) return "Good";
  if (rssi >= -70) return "Fair";
  if (rssi >= -80) return "Weak(!!)";
  return "Very Weak(!!!)";
}

/**
 * Sanitize device name for mDNS (lowercase, replace spaces with dashes)
 */
String sanitizeForMDNS(String name) {
  name.toLowerCase();
  name.replace(" ", "-");
  name.replace("_", "-");
  return name;
}

// =============================================================================
// DATA BUFFER CLASS
// =============================================================================

class DataBuffer {
private:
  String bufferPath;
  unsigned long currentHourFile;
  File hourlyFile;
  bool fileOpen;

  String getHourFileName(unsigned long timestamp) {
    struct tm timeinfo;
    time_t t = timestamp;
    gmtime_r(&t, &timeinfo);
    char filename[20];
    strftime(filename, sizeof(filename), "%Y%m%d%H", &timeinfo);
    return String(bufferPath) + "/" + String(filename) + ".csv";
  }

  String getHourFileNameFromMillis() {
    unsigned long seconds = millis() / 1000;
    return String(bufferPath) + "/BOOT" + String(seconds / 3600) + ".csv";
  }

public:
  DataBuffer() : currentHourFile(0), fileOpen(false) {}

  bool begin() {
    bufferPath = BUFFER_PATH;

    if (!SPIFFS.begin(true)) {
      Serial.println("Failed to mount SPIFFS");
      return false;
    }

    // Create buffer directory if it doesn't exist
    if (!SPIFFS.exists(bufferPath)) {
      // SPIFFS doesn't have mkdir, directory is implicit from file paths
      Serial.println("Buffer directory will be created on first write");
    }

    Serial.println("SPIFFS mounted successfully");
    return true;
  }

  void writeReading(String timestamp, String topic, String value) {
    String filename;

    // Use timestamp-based filename if time is synced, otherwise use boot time
    if (timestamp.startsWith("BOOT+")) {
      filename = getHourFileNameFromMillis();
    } else {
      // Parse timestamp to get hour
      // For simplicity, use current hour from system time
      time_t now;
      time(&now);
      filename = getHourFileName(now);
    }

    // Open file in append mode
    File file = SPIFFS.open(filename, FILE_APPEND);
    if (!file) {
      Serial.println("Failed to open buffer file: " + filename);
      return;
    }

    // Write CSV line: timestamp,topic,value
    file.print(timestamp);
    file.print(",");
    file.print(topic);
    file.print(",");
    file.println(value);
    file.close();

    Serial.println("Buffered to " + filename + ": " + topic + "=" + value);

    // Check if buffer size exceeded
    checkBufferSize();
  }

  void checkBufferSize() {
    unsigned long totalSize = 0;
    File root = SPIFFS.open(bufferPath);
    if (!root) return;

    File file = root.openNextFile();
    while (file) {
      if (!file.isDirectory()) {
        totalSize += file.size();
      }
      file = root.openNextFile();
    }

    // If over limit, delete oldest files
    if (totalSize > BUFFER_MAX_SIZE) {
      Serial.printf("Buffer size %lu exceeds limit, deleting oldest files\n", totalSize);
      deleteOldestFile();
    }
  }

  void deleteOldestFile() {
    String oldestFile = "";
    File root = SPIFFS.open(bufferPath);
    if (!root) return;

    File file = root.openNextFile();
    while (file) {
      if (!file.isDirectory()) {
        String filename = String(file.name());
        if (oldestFile == "" || filename < oldestFile) {
          oldestFile = filename;
        }
      }
      file = root.openNextFile();
    }

    if (oldestFile != "") {
      SPIFFS.remove(oldestFile);
      Serial.println("Deleted oldest buffer file: " + oldestFile);
    }
  }

  bool hasBufferedData() {
    File root = SPIFFS.open(bufferPath);
    if (!root) return false;

    File file = root.openNextFile();
    bool hasFiles = (file && !file.isDirectory());
    return hasFiles;
  }

  int getFileCount() {
    int count = 0;
    File root = SPIFFS.open(bufferPath);
    if (!root) return 0;

    File file = root.openNextFile();
    while (file) {
      if (!file.isDirectory()) {
        count++;
      }
      file = root.openNextFile();
    }
    return count;
  }

  unsigned long getTotalSize() {
    unsigned long totalSize = 0;
    File root = SPIFFS.open(bufferPath);
    if (!root) return 0;

    File file = root.openNextFile();
    while (file) {
      if (!file.isDirectory()) {
        totalSize += file.size();
      }
      file = root.openNextFile();
    }
    return totalSize;
  }

  // Iterator for uploading buffered files
  class BufferIterator {
  private:
    File currentFile;
    String currentLine;
    File rootDir;

  public:
    BufferIterator(String path) {
      rootDir = SPIFFS.open(path);
      nextFile();
    }

    bool nextFile() {
      if (currentFile) currentFile.close();

      currentFile = rootDir.openNextFile();
      while (currentFile && currentFile.isDirectory()) {
        currentFile = rootDir.openNextFile();
      }

      return currentFile;
    }

    bool nextLine() {
      if (!currentFile || !currentFile.available()) {
        return nextFile() && nextLine();
      }

      currentLine = currentFile.readStringUntil('\n');
      currentLine.trim();
      return currentLine.length() > 0;
    }

    String getLine() { return currentLine; }
    String getCurrentFileName() { return currentFile ? String(currentFile.name()) : ""; }

    void deleteCurrentFile() {
      String filename = getCurrentFileName();
      currentFile.close();
      if (filename.length() > 0) {
        SPIFFS.remove(filename);
        Serial.println("Deleted uploaded file: " + filename);
      }
    }

    ~BufferIterator() {
      if (currentFile) currentFile.close();
    }
  };

  BufferIterator* getIterator() {
    return new BufferIterator(bufferPath);
  }
};

// =============================================================================
// MAIN SENSOR CORE CLASS
// =============================================================================

class ESPSensorCore {
private:
  // Device configuration
  String deviceName;
  String deviceMAC;
  String mdnsName;

  // WiFi & MQTT
  WiFiClient espClient;
  PubSubClient mqttClient;
  WiFiManager wifiManager;
  WiFiManagerParameter* customDeviceName;
  WiFiManagerParameter* customMqttBroker;
  String mqttServer;
  bool everConnectedMQTT;

  // Preferences
  Preferences preferences;

  // Data buffering
  DataBuffer dataBuffer;
  bool isBuffering;
  unsigned long lastBufferWrite;

  // Timing
  unsigned long lastPublish;
  unsigned long publishInterval;

  // LED
  enum LedMode { LED_BOOT, LED_NORMAL, LED_MQTT_RETRY };
  LedMode currentLedMode;
  unsigned long lastLedToggle;
  bool ledState;

  // MQTT Retry
  int mqttFailedAttempts;
  unsigned long lastMqttAttempt;
  bool failureNotificationSent;

  // Time sync
  bool timeIsSynced;

  // Web server
  WebServer* webServer;

  // Buffer upload state
  bool isUploadingBuffer;
  DataBuffer::BufferIterator* uploadIterator;
  unsigned long lastBufferUpload;
  String currentUploadFile;

  // Status publishing
  unsigned long lastStatusPublish;

  // ==========================================================================
  // PRIVATE METHODS
  // ==========================================================================

  String getDefaultDeviceName() {
    uint8_t mac[6];
    WiFi.macAddress(mac);
    char macStr[5];
    sprintf(macStr, "%02X%02X", mac[4], mac[5]);
    return "sensor-" + String(macStr);
  }

  void setupLED() {
    pinMode(LED_PIN, OUTPUT);
    currentLedMode = LED_BOOT;
    digitalWrite(LED_PIN, HIGH);
  }

  void updateLED() {
    unsigned long now = millis();

    switch (currentLedMode) {
      case LED_BOOT:
        digitalWrite(LED_PIN, HIGH);
        break;

      case LED_NORMAL:
        if (now - lastLedToggle >= LED_BLINK_NORMAL) {
          digitalWrite(LED_PIN, HIGH);
          lastLedToggle = now;
        } else if (now - lastLedToggle >= 100) {
          digitalWrite(LED_PIN, LOW);
        }
        break;

      case LED_MQTT_RETRY:
        if (now - lastLedToggle >= LED_BLINK_MQTT_RETRY) {
          ledState = !ledState;
          digitalWrite(LED_PIN, ledState ? HIGH : LOW);
          lastLedToggle = now;
        }
        break;
    }
  }

  void setupWiFi() {
    // Reduce WiFi power to prevent brownout on weak power supplies
    WiFi.setTxPower(WIFI_POWER_8_5dBm);  // Lowest power setting

    // Load saved configuration
    preferences.begin("sensor", false);
    deviceName = preferences.getString("deviceName", getDefaultDeviceName());
    mqttServer = preferences.getString("mqttServer", "");
    preferences.end();

    Serial.println("Device Name: " + deviceName);
    Serial.println("MQTT Server: " + mqttServer);

    // Setup WiFiManager
    wifiManager.setTitle("ESP32 Sensor Configuration");
    wifiManager.setConfigPortalBlocking(true);
    wifiManager.setSaveConfigCallback([this]() { this->saveConfigCallback(); });

    // Add custom parameters
    customDeviceName = new WiFiManagerParameter("device", "Device Name", deviceName.c_str(), 40);
    customMqttBroker = new WiFiManagerParameter("mqtt", "MQTT Broker IP", mqttServer.c_str(), 40);

    wifiManager.addParameter(customDeviceName);

    // Discover MQTT brokers
    String brokerListHTML = discoverMQTTBrokers();
    if (brokerListHTML.length() > 0) {
      WiFiManagerParameter customHtml(brokerListHTML.c_str());
      wifiManager.addParameter(&customHtml);
    }

    wifiManager.addParameter(customMqttBroker);

    // Check for manual reset (BOOT button held)
    pinMode(0, INPUT_PULLUP);
    Serial.println("Hold BOOT button for 3 seconds to reset all settings...");

    int buttonPressCount = 0;
    for (int i = 0; i < 30; i++) {
      if (digitalRead(0) == LOW) {
        buttonPressCount++;
      }
      delay(100);
    }

    bool forceReset = (buttonPressCount > 20);

    if (forceReset) {
      Serial.println("\n!!! BOOT BUTTON DETECTED - RESETTING ALL SETTINGS !!!");
      preferences.begin("sensor", false);
      preferences.clear();
      preferences.end();
      wifiManager.resetSettings();
      Serial.println("Settings reset complete. Restarting...");
      delay(2000);
      ESP.restart();
    }

    // Connect to WiFi
    Serial.println("Connecting to WiFi...");
    if (!wifiManager.autoConnect(("ESP32-" + deviceName).c_str(), CONFIG_PORTAL_PASSWORD)) {
      Serial.println("Failed to connect to WiFi");
      ESP.restart();
    }

    Serial.println("Connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Setup mDNS
    mdnsName = sanitizeForMDNS(deviceName);
    if (MDNS.begin(mdnsName.c_str())) {
      Serial.println("mDNS started: " + mdnsName + ".local");
      MDNS.addService("http", "tcp", WEB_SERVER_PORT);
    } else {
      Serial.println("Error starting mDNS");
    }

    // Sync time
    setupTime();
  }

  void saveConfigCallback() {
    Serial.println("Configuration saved callback triggered");

    String newDeviceName = customDeviceName->getValue();
    String newMqttServer = customMqttBroker->getValue();

    bool changed = false;

    if (newDeviceName.length() > 0 && newDeviceName != deviceName) {
      deviceName = newDeviceName;
      changed = true;
    }

    if (newMqttServer.length() > 0 && newMqttServer != mqttServer) {
      mqttServer = newMqttServer;
      changed = true;
    }

    if (changed) {
      preferences.begin("sensor", false);
      preferences.putString("deviceName", deviceName);
      preferences.putString("mqttServer", mqttServer);
      preferences.end();

      Serial.println("Configuration saved. Restarting...");
      delay(2000);
      ESP.restart();
    }
  }

  String discoverMQTTBrokers() {
    Serial.println("\n========================================");
    Serial.println("Scanning for MQTT brokers via mDNS...");
    Serial.println("========================================");

    if (!MDNS.begin("esp32-temp-discovery")) {
      Serial.println("Error starting mDNS for discovery");
      return "";
    }

    int numBrokers = MDNS.queryService("mqtt", "tcp");
    Serial.printf("\nFound %d MQTT broker(s):\n\n", numBrokers);

    String htmlList = "<div style='background:#e0e0e0;padding:10px;margin:10px 0;border-radius:5px;'>";
    htmlList += "<h3>Discovered MQTT Brokers:</h3>";

    if (numBrokers == 0) {
      Serial.println("No MQTT brokers discovered.");
      htmlList += "<p>No brokers found. Please enter IP manually.</p>";
    } else {
      htmlList += "<ul style='list-style:none;padding:0;'>";

      for (int i = 0; i < numBrokers; i++) {
        String hostname = MDNS.hostname(i);
        IPAddress ipAddr = MDNS.address(i);
        String ip = ipAddr.toString();
        int port = MDNS.port(i);

        Serial.printf("  [%d] %s\n", i+1, hostname.c_str());
        Serial.printf("      IP: %s\n", ip.c_str());
        Serial.printf("      Port: %d\n\n", port);

        htmlList += "<li style='margin:10px 0;padding:10px;background:white;border-radius:3px;'>";
        htmlList += "<strong>" + hostname + "</strong><br>";
        htmlList += "IP: <code>" + ip + "</code><br>";
        htmlList += "Port: " + String(port);
        htmlList += "</li>";
      }

      htmlList += "</ul>";
    }

    htmlList += "</div>";
    Serial.println("========================================");

    return htmlList;
  }

  void setupTime() {
    Serial.println("Syncing time with NTP server...");
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);

    int syncAttempts = 0;
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo) && syncAttempts < 10) {
      delay(500);
      syncAttempts++;
    }

    if (getLocalTime(&timeinfo)) {
      timeIsSynced = true;
      char timeStr[25];
      strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &timeinfo);
      Serial.printf("Time synced: %s UTC\n", timeStr);
    } else {
      Serial.println("NTP sync failed - will use boot time fallback");
      timeIsSynced = false;
    }
  }

  String getCurrentTimestamp() {
    if (!timeIsSynced) {
      return "BOOT+" + String(millis() / 1000);
    }

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      timeIsSynced = false;
      return "BOOT+" + String(millis() / 1000);
    }

    char timestamp[25];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
    return String(timestamp);
  }

  void setupMQTT() {
    mqttClient.setClient(espClient);
    if (mqttServer.length() > 0) {
      mqttClient.setServer(mqttServer.c_str(), MQTT_PORT);
      Serial.println("MQTT configured for: " + mqttServer);
    } else {
      Serial.println("No MQTT server configured");
    }

    // Get MAC address
    uint8_t mac[6];
    WiFi.macAddress(mac);
    deviceMAC = "";
    for(int i = 0; i < 6; i++) {
      if(mac[i] < 16) deviceMAC += "0";
      deviceMAC += String(mac[i], HEX);
    }
    deviceMAC.toUpperCase();
    Serial.println("MAC Address: " + deviceMAC);
  }

  void reconnectMQTT() {
    unsigned long now = millis();

    // Determine retry interval based on failure count
    unsigned long retryInterval;
    if (everConnectedMQTT) {
      retryInterval = (mqttFailedAttempts < MQTT_RETRY_THRESHOLD) ? MQTT_RETRY_FAST : MQTT_RETRY_SLOW;
    } else {
      retryInterval = MQTT_RETRY_FAST;
    }

    // Check if enough time has passed since last attempt
    if (now - lastMqttAttempt < retryInterval) {
      return;
    }
    lastMqttAttempt = now;

    Serial.print("Attempting MQTT connection...");

    String clientId = "ESP32-" + deviceMAC;

    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("connected");
      mqttFailedAttempts = 0;
      everConnectedMQTT = true;
      failureNotificationSent = false;

      currentLedMode = LED_NORMAL;
      lastLedToggle = millis();

      // Stop buffering, start uploading
      isBuffering = false;
      if (dataBuffer.hasBufferedData()) {
        Serial.println("MQTT reconnected - starting buffer upload");
        startBufferUpload();
      }

      // Publish version and status
      publishVersion();
      publishStatus();

    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());

      mqttFailedAttempts++;

      if (mqttFailedAttempts == 1) {
        Serial.println(" will retry in 10 seconds");
        currentLedMode = LED_MQTT_RETRY;
        lastLedToggle = millis();
      } else if (mqttFailedAttempts == MQTT_RETRY_THRESHOLD) {
        Serial.println("\n!!! MQTT BROKER UNREACHABLE - SWITCHING TO SLOW RETRY !!!");
        Serial.println("Will retry every 10 minutes");
        sendFailureNotification();

        // Start buffering
        isBuffering = true;
        Serial.println("Started local buffering");
      } else {
        unsigned long nextRetry = retryInterval / 1000;
        Serial.printf(" will retry in %lu seconds\n", nextRetry);
      }
    }
  }

  void sendFailureNotification() {
    if (failureNotificationSent) return;

    HTTPClient http;
    String url = String(AWS_HEARTBEAT_URL) + "ESP32-" + deviceMAC + "-MQTT-FAILED";

    Serial.println("Sending failure notification: " + url);

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.printf("Notification sent. Status: %d\n", httpCode);
      failureNotificationSent = true;
    } else {
      Serial.printf("Notification failed. Error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  void startBufferUpload() {
    if (uploadIterator) {
      delete uploadIterator;
    }
    uploadIterator = dataBuffer.getIterator();
    isUploadingBuffer = true;
    currentUploadFile = "";
    Serial.println("Buffer upload started");
  }

  void uploadBufferedData() {
    if (!isUploadingBuffer || !uploadIterator) return;
    if (!mqttClient.connected()) {
      // Stop uploading if MQTT disconnected
      isUploadingBuffer = false;
      delete uploadIterator;
      uploadIterator = nullptr;
      return;
    }

    unsigned long now = millis();

    // Rate limit uploads
    if (now - lastBufferUpload < BUFFER_UPLOAD_DELAY) {
      return;
    }
    lastBufferUpload = now;

    // Read next line from buffer
    if (uploadIterator->nextLine()) {
      String line = uploadIterator->getLine();

      // Parse CSV: timestamp,topic,value
      int firstComma = line.indexOf(',');
      int secondComma = line.indexOf(',', firstComma + 1);

      if (firstComma > 0 && secondComma > 0) {
        String timestamp = line.substring(0, firstComma);
        String topic = line.substring(firstComma + 1, secondComma);
        String value = line.substring(secondComma + 1);

        // Publish buffered data
        String fullTopic = deviceName + "/" + topic;
        mqttClient.publish(fullTopic.c_str(), value.c_str());

        Serial.println("Uploaded buffered: " + fullTopic + " = " + value);
      }
    } else {
      // Finished with current file, delete it
      uploadIterator->deleteCurrentFile();

      // Check if more files
      if (!dataBuffer.hasBufferedData()) {
        // All done
        Serial.println("Buffer upload complete");
        isUploadingBuffer = false;
        delete uploadIterator;
        uploadIterator = nullptr;
      }
    }
  }

  void setupWebServer() {
    webServer = new WebServer(WEB_SERVER_PORT);

    // Main status page
    webServer->on("/", [this]() {
      String html = "<!DOCTYPE html><html><head>";
      html += "<meta charset='UTF-8'>";
      html += "<title>" + deviceName + "</title>";
      html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
      html += "<style>body{font-family:monospace;margin:20px;background:#f0f0f0;}";
      html += ".container{background:white;padding:20px;border-radius:5px;max-width:600px;}";
      html += "h1{border-bottom:2px solid #333;padding-bottom:10px;}";
      html += ".section{margin:20px 0;padding:10px;background:#f9f9f9;border-radius:3px;}";
      html += ".label{font-weight:bold;display:inline-block;width:150px;}";
      html += ".status-ok{color:green;} .status-err{color:red;}";
      html += ".btn{display:inline-block;padding:10px 20px;background:#007bff;color:white;text-decoration:none;border-radius:5px;margin:10px 5px;}";
      html += ".btn:hover{background:#0056b3;}";
      html += "</style></head><body>";

      html += "<div class='container'>";
      html += "<h1>ESP32 Sensor Framework</h1>";

      html += "<div class='section'>";
      html += "<h2>Device Information</h2>";
      html += "<div><span class='label'>Device Name:</span>" + deviceName + "</div>";
      html += "<div><span class='label'>MAC Address:</span>" + deviceMAC + "</div>";
      html += "<div><span class='label'>IP Address:</span>" + WiFi.localIP().toString() + "</div>";
      html += "<div><span class='label'>mDNS:</span>" + mdnsName + ".local</div>";
      html += "</div>";

      html += "<div class='section'>";
      html += "<h2>WiFi</h2>";
      html += "<div><span class='label'>SSID:</span>" + WiFi.SSID() + "</div>";
      html += "<div><span class='label'>Signal:</span>" + getWiFiQuality(WiFi.RSSI()) + "</div>";
      html += "</div>";

      html += "<div class='section'>";
      html += "<h2>MQTT</h2>";
      html += "<div><span class='label'>Broker:</span>" + mqttServer + ":" + String(MQTT_PORT) + "</div>";
      String mqttStatus = mqttClient.connected() ? "<span class='status-ok'>Connected ✓</span>" : "<span class='status-err'>Disconnected ✗</span>";
      html += "<div><span class='label'>Status:</span>" + mqttStatus + "</div>";
      html += "<div><span class='label'>Base Topic:</span>" + deviceName + "/</div>";
      html += "<a href='/config' class='btn'>Change MQTT Server</a>";
      html += "</div>";

      html += "<div class='section'>";
      html += "<h2>System</h2>";
      unsigned long uptime = millis() / 1000;
      unsigned long days = uptime / 86400;
      unsigned long hours = (uptime % 86400) / 3600;
      unsigned long minutes = (uptime % 3600) / 60;
      String uptimeStr = String(days) + "d " + String(hours) + "h " + String(minutes) + "m";
      html += "<div><span class='label'>Uptime:</span>" + uptimeStr + "</div>";
      html += "<div><span class='label'>Version:</span>v" + String(FRAMEWORK_VERSION) + " " + String(BUILD_DATE) + "</div>";

      int bufferFiles = dataBuffer.getFileCount();
      unsigned long bufferSize = dataBuffer.getTotalSize();
      html += "<div><span class='label'>Buffer:</span>" + String(bufferFiles) + " files (" + String(bufferSize / 1024) + " KB)</div>";
      html += "</div>";

      html += "<div class='section'>";
      html += "<h2>Quick Links</h2>";
      html += "<div>";
      html += "<a href='/' class='btn'>Home</a> ";
      html += "<a href='/config' class='btn'>MQTT Settings</a>";
      html += "</div>";
      html += "<div style='margin-top:10px;font-size:12px;color:#666;'>";
      html += "To reset all settings: Hold BOOT button for 3 seconds";
      html += "</div>";
      html += "</div>";

      html += "</div></body></html>";

      webServer->send(200, "text/html", html);
    });

    // Complete configuration page
    webServer->on("/config", [this]() {
      String html = "<!DOCTYPE html><html><head>";
      html += "<meta charset='UTF-8'>";
      html += "<title>Configuration - " + deviceName + "</title>";
      html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
      html += "<style>body{font-family:monospace;margin:20px;background:#f0f0f0;}";
      html += ".container{background:white;padding:20px;border-radius:5px;max-width:600px;}";
      html += "h1{border-bottom:2px solid #333;padding-bottom:10px;}";
      html += "form{margin-top:20px;}";
      html += "label{display:block;margin:15px 0 5px;font-weight:bold;}";
      html += "input{width:100%;padding:8px;box-sizing:border-box;font-size:16px;}";
      html += ".btn{display:inline-block;padding:10px 20px;background:#28a745;color:white;border:none;border-radius:5px;margin:10px 5px 0 0;cursor:pointer;font-size:16px;}";
      html += ".btn:hover{background:#218838;}";
      html += ".btn-back{background:#6c757d;}";
      html += ".btn-back:hover{background:#5a6268;}";
      html += ".warning{background:#fff3cd;border:1px solid #ffc107;padding:10px;border-radius:3px;margin:10px 0;}";
      html += ".info{background:#d1ecf1;border:1px solid #0c5460;padding:10px;border-radius:3px;margin:10px 0;font-size:14px;}";
      html += "h3{margin-top:25px;border-bottom:1px solid #ddd;padding-bottom:5px;}";
      html += "</style></head><body>";

      html += "<div class='container'>";
      html += "<h1>Device Configuration</h1>";

      html += "<div class='warning'>";
      html += "<strong>Note:</strong> Changing WiFi settings will disconnect and reconnect to new network. ";
      html += "Device will restart after saving.";
      html += "</div>";

      html += "<form action='/save' method='POST'>";

      html += "<h3>Device Identity</h3>";
      html += "<label for='name'>Device Name:</label>";
      html += "<input type='text' id='name' name='name' value='" + deviceName + "' placeholder='my-sensor' required>";
      html += "<div class='info'>This name will be used for MQTT topics and mDNS.</div>";

      html += "<h3>WiFi Settings</h3>";
      html += "<label for='ssid'>WiFi SSID:</label>";
      html += "<input type='text' id='ssid' name='ssid' value='" + WiFi.SSID() + "' placeholder='MyNetwork' required>";
      html += "<label for='pass'>WiFi Password:</label>";
      html += "<input type='password' id='pass' name='pass' placeholder='Leave blank to keep current' autocomplete='new-password'>";
      html += "<div class='info'>Leave password blank to keep existing password.</div>";

      html += "<h3>MQTT Settings</h3>";
      html += "<label for='mqtt'>MQTT Broker IP Address:</label>";
      html += "<input type='text' id='mqtt' name='mqtt' value='" + mqttServer + "' placeholder='10.0.0.142' required>";

      html += "<button type='submit' class='btn'>Save & Restart</button>";
      html += "<a href='/' class='btn btn-back'>Cancel</a>";
      html += "</form>";

      html += "</div></body></html>";

      webServer->send(200, "text/html", html);
    });

    // Save complete configuration
    webServer->on("/save", HTTP_POST, [this]() {
      if (!webServer->hasArg("mqtt") || !webServer->hasArg("name") || !webServer->hasArg("ssid")) {
        webServer->send(400, "text/plain", "Missing required parameters");
        return;
      }

      String newName = webServer->arg("name");
      String newSSID = webServer->arg("ssid");
      String newPass = webServer->arg("pass");
      String newMqttServer = webServer->arg("mqtt");

      // Save to preferences
      preferences.begin("sensor", false);
      preferences.putString("deviceName", newName);
      preferences.putString("mqttServer", newMqttServer);
      preferences.end();

      // Success page
      String html = "<!DOCTYPE html><html><head>";
      html += "<meta charset='UTF-8'>";
      html += "<title>Saving Configuration...</title>";
      html += "<style>body{font-family:monospace;margin:20px;background:#f0f0f0;text-align:center;}";
      html += ".container{background:white;padding:40px;border-radius:5px;max-width:500px;margin:50px auto;}";
      html += ".success{color:#28a745;font-size:24px;margin:20px 0;}";
      html += ".info{margin:15px 0;padding:10px;background:#f9f9f9;border-radius:3px;}";
      html += "</style></head><body>";
      html += "<div class='container'>";
      html += "<div class='success'>✓ Configuration Saved!</div>";
      html += "<div class='info'><strong>Device Name:</strong> " + newName + "</div>";
      html += "<div class='info'><strong>WiFi SSID:</strong> " + newSSID + "</div>";
      html += "<div class='info'><strong>MQTT Broker:</strong> " + newMqttServer + "</div>";
      html += "<p style='margin-top:30px;'>Device is restarting...</p>";
      html += "<p>After restart, connect to new WiFi if changed.</p>";
      html += "<p style='font-size:12px;color:#666;'>New IP will be: http://" + newName + ".local</p>";
      html += "</div></body></html>";

      webServer->send(200, "text/html", html);

      Serial.println("Configuration updated:");
      Serial.println("  Device Name: " + newName);
      Serial.println("  WiFi SSID: " + newSSID);
      Serial.println("  MQTT Server: " + newMqttServer);

      // Save WiFi credentials via WiFiManager
      // Only update password if provided
      if (newPass.length() > 0) {
        Serial.println("  WiFi Password: Updated");
        WiFi.begin(newSSID.c_str(), newPass.c_str());
      } else {
        Serial.println("  WiFi Password: Unchanged");
        // Try to connect with existing credentials
        WiFi.begin(newSSID.c_str());
      }

      delay(2000);  // Give time for response to send
      Serial.println("Restarting device...");
      ESP.restart();
    });

    webServer->begin();
    Serial.println("Web server started on port " + String(WEB_SERVER_PORT));
  }

  void publishVersion() {
    String versionString = "v" + String(FRAMEWORK_VERSION) + " " + String(BUILD_DATE) + " " + String(BUILD_TIME);
    String topic = deviceName + "/version";
    mqttClient.publish(topic.c_str(), versionString.c_str(), true);
    Serial.println("Published version: " + versionString);
  }

  void publishStatus() {
    // Publish device status
    mqttClient.publish((deviceName + "/status/ip").c_str(), WiFi.localIP().toString().c_str(), true);
    mqttClient.publish((deviceName + "/status/mqtt_broker").c_str(), mqttServer.c_str(), true);
    mqttClient.publish((deviceName + "/status/wifi_ssid").c_str(), WiFi.SSID().c_str(), true);
    mqttClient.publish((deviceName + "/status/wifi_signal").c_str(), getWiFiQuality(WiFi.RSSI()).c_str(), false);

    Serial.println("Published status information");
  }

  void publishWiFiSignal() {
    // Publish only WiFi signal quality
    mqttClient.publish((deviceName + "/status/wifi_signal").c_str(), getWiFiQuality(WiFi.RSSI()).c_str(), false);
  }

  void checkBootButton() {
    // Check if BOOT button (GPIO0) is being held
    // If held for 3 seconds continuously, reset all settings
    static unsigned long buttonPressStart = 0;
    static bool buttonWasPressed = false;

    bool buttonPressed = (digitalRead(0) == LOW);

    if (buttonPressed && !buttonWasPressed) {
      // Button just pressed
      buttonPressStart = millis();
      buttonWasPressed = true;
      Serial.println("BOOT button pressed - hold for 3 seconds to reset...");
    }
    else if (buttonPressed && buttonWasPressed) {
      // Button still held - check duration
      unsigned long holdDuration = millis() - buttonPressStart;

      if (holdDuration >= 3000) {
        // Held for 3+ seconds - RESET!
        Serial.println("\n!!! BOOT BUTTON HELD 3 SECONDS - RESETTING ALL SETTINGS !!!");
        Serial.println("Clearing WiFi and MQTT settings...");

        preferences.begin("sensor", false);
        preferences.clear();
        preferences.end();

        wifiManager.resetSettings();

        Serial.println("Settings cleared. Restarting in 2 seconds...");
        Serial.println("After restart, device will create WiFi AP for configuration.");
        delay(2000);
        ESP.restart();
      }
    }
    else if (!buttonPressed && buttonWasPressed) {
      // Button released before 3 seconds
      buttonWasPressed = false;
      Serial.println("BOOT button released");
    }
  }

public:
  ESPSensorCore() :
    mqttClient(espClient),
    everConnectedMQTT(false),
    isBuffering(false),
    lastBufferWrite(0),
    lastPublish(0),
    publishInterval(PUBLISH_INTERVAL_CONNECTED),
    currentLedMode(LED_BOOT),
    lastLedToggle(0),
    ledState(false),
    mqttFailedAttempts(0),
    lastMqttAttempt(0),
    failureNotificationSent(false),
    timeIsSynced(false),
    webServer(nullptr),
    isUploadingBuffer(false),
    uploadIterator(nullptr),
    lastBufferUpload(0),
    lastStatusPublish(0),
    customDeviceName(nullptr),
    customMqttBroker(nullptr) {}

  void begin() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("\n========================================");
    Serial.println("ESP32 Sensor Framework v" + String(FRAMEWORK_VERSION));
    Serial.println("========================================\n");

    setupLED();
    setupWiFi();
    setupMQTT();

    if (!dataBuffer.begin()) {
      Serial.println("WARNING: Data buffering disabled");
    }

    setupWebServer();

    currentLedMode = LED_NORMAL;
    lastLedToggle = millis();

    Serial.println("\n========================================");
    Serial.println("Setup complete - framework ready");
    Serial.println("========================================\n");
  }

  void update() {
    updateLED();

    if (!mqttClient.connected()) {
      reconnectMQTT();
    } else {
      mqttClient.loop();

      // Upload buffered data if available
      if (isUploadingBuffer) {
        uploadBufferedData();
      }

      // Publish WiFi signal status periodically
      unsigned long now = millis();
      if (now - lastStatusPublish >= STATUS_PUBLISH_INTERVAL) {
        publishWiFiSignal();
        lastStatusPublish = now;
      }
    }

    // Handle web server requests
    if (webServer) {
      webServer->handleClient();
    }

    // Check for BOOT button held (continuous monitoring)
    checkBootButton();
  }

  bool shouldPublish() {
    unsigned long now = millis();
    unsigned long interval = mqttClient.connected() ? PUBLISH_INTERVAL_CONNECTED : PUBLISH_INTERVAL_BUFFERING;

    if (now - lastPublish >= interval) {
      lastPublish = now;
      return true;
    }
    return false;
  }

  void publish(String measurement, float value) {
    publish("", measurement, value);
  }

  void publish(String channel, String measurement, float value) {
    String timestamp = getCurrentTimestamp();
    String valueStr = String(value, 2);

    // Build topic: {device}/{channel}/{measurement} or {device}/{measurement}
    String topic = deviceName;
    if (channel.length() > 0) {
      topic += "/" + channel;
    }
    topic += "/" + measurement;

    if (mqttClient.connected() && !isUploadingBuffer) {
      // Publish live data
      mqttClient.publish(topic.c_str(), valueStr.c_str());
      mqttClient.publish((deviceName + "/timestamp").c_str(), timestamp.c_str());

      Serial.println("Published: " + topic + " = " + valueStr + " at " + timestamp);
    } else {
      // Buffer data locally
      dataBuffer.writeReading(timestamp, topic.substring(deviceName.length() + 1), valueStr);
    }
  }

  String getDeviceName() { return deviceName; }
  bool isConnected() { return mqttClient.connected(); }
  String getTimestamp() { return getCurrentTimestamp(); }
};

#endif // ESP_SENSOR_CORE_H
