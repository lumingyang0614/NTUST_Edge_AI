#include <EloquentTinyML.h>
#include "model_1.h"

#include <Arduino_LPS22HB.h>

#include <Arduino_HS300x.h>

#define NUMBER_OF_INPUTS 3
#define NUMBER_OF_OUTPUTS 4
#define TENSOR_ARENA_SIZE 8*1024
#define WINDOW_LENGTH 4

Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;
// Create a buffer to store past readings
float window[WINDOW_LENGTH][NUMBER_OF_INPUTS];

// Keep track of the number of readings in the window
int count = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Communication started");

  if (!HS300x.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }
  Serial.println("HTS sensor initialized");

  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }
  Serial.println("BARO sensor initialized");

  ml.begin(model);
  Serial.println("Model initialized");
}

void loop() {
  // Collect new readings
  window[count][0] = HS300x.readTemperature();
  window[count][1] = HS300x.readHumidity();
  window[count][2] = BARO.readPressure() * 10;

  // Increment count
  count++;

  // If the window is full
  if (count == WINDOW_LENGTH) {
    // Create input array from window
    float input[NUMBER_OF_INPUTS * WINDOW_LENGTH];
    for(int i = 0; i < WINDOW_LENGTH; i++) {
      for(int j = 0; j < NUMBER_OF_INPUTS; j++) {
        input[i * NUMBER_OF_INPUTS + j] = window[i][j];
        if(j==0){
          Serial.print("Temperature: ");
          Serial.print(window[i][j]);
          Serial.print(", ");
        }
        else if(j==1){
          Serial.print("Humidity: ");
          Serial.print(window[i][j]);
          Serial.print(", ");
        }
        else if(j==2){
          Serial.print("Pressure: ");
          Serial.print(window[i][j]);
          Serial.print(", ");
        }
          
      }
      Serial.print("     ");
    }
    
    float output[NUMBER_OF_OUTPUTS] = {0, 0};  // 修改為兩個數值
    ml.predict(input, output);  // 預測兩個輸出

    // Print results
    Serial.print("The predicted values are: ");
    Serial.print(output[0]);
    Serial.print(", ");
    Serial.println(output[1]);
    
    // Move the window forward
    for(int i = 0; i < WINDOW_LENGTH - 1; i++) {
      for(int j = 0; j < NUMBER_OF_INPUTS; j++) {
        window[i][j] = window[i + 1][j];
      }
    }
    
    // Decrement count
    count--;
  }
  
  delay(1000);
}