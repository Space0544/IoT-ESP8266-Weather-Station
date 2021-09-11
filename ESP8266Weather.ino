// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

// Include Libraries and Config.h
#include "config.h"
#include <Wire.h>
#include <Adafruit_AM2315.h>

// Set up Feeds
AdafruitIO_Feed *temperature1 = io.feed("Temperature_AM2315");
AdafruitIO_Feed *humidity1 = io.feed("Humidity_AM2315");
Adafruit_AM2315 am2315;
void setup() {

  // start the serial connection
  Serial.begin(115200);

  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  am2315.begin();
  
  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
  // Keep alive Adafruit IO connection
  io.run();
  // Make a float for temperature and humidity
  float temperature, humidity;

  // Read the temperature and humidity and export them to their respective floats
  am2315.readTemperatureAndHumidity(&temperature, &humidity);

  // Print the temperature and humidity to the serial monitor
  Serial.print("Temp *C: "); Serial.println(temperature);
  Serial.print("Hum %: "); Serial.println(humidity);

  delay(2000);
  // Send the data to Adafruit IO
  Serial.print("sending -> ");
  humidity1->save(humidity);
  temperature1->save(temperature);

  // Wait 15 minutes before sending another reading
  delay(900000);

}
