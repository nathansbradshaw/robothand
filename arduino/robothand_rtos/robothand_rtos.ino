/*
   Example of a basic FreeRTOS queue
   https://www.freertos.org/Embedded-RTOS-Queues.html
*/

// Include Arduino FreeRTOS library
#include <Arduino_FreeRTOS.h>

// Include queue support
#include <queue.h>

// Include Servo library
#include <Servo.h>
Servo fingerServos[5];  // create servo object to control a servo

// Define a Array
int FingerPositions[5] = {0, 0, 0, 0, 0};
//This will store the data from the serial connection
String serial_cmd = "";
//Function Declaration
void TaskThumbFinger(void *pvParameters);
void TaskIndexFinger(void *pvParameters);
void TaskMiddleFinger(void *pvParameters);
void TaskRingFinger(void *pvParameters);
void TaskPinkyFinger(void *pvParameters);
void TaskSerial(void *pvParameters);

/*
   Declaring a global variable of type QueueHandle_t

*/
QueueHandle_t arrayQueue;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Program");
  delay(1000);
  fingerServos[0].attach(7);  // attaches the servo on pin 9 to the servo object
  fingerServos[1].attach(8);  // attaches the servo on pin 9 to the servo object
  fingerServos[2].attach(9);  // attaches the servo on pin 9 to the servo object
  fingerServos[3].attach(10);  // attaches the servo on pin 9 to the servo object
  fingerServos[4].attach(11);  // attaches the servo on pin 9 to the servo object

  /**
      Create a queue.
      https://www.freertos.org/a00116.html
  */
  arrayQueue = xQueueCreate(10, //Queue length
                            sizeof(int)); //Queue item size
  if (arrayQueue != NULL) {

    // Create task that reads the serial data
    xTaskCreate(TaskSerial,// Task function
                "Read Serial",// Task name
                64,// Stack size
                NULL,
                2,// Priority
                NULL);

    // Create task that publish data in the queue if it was created.
    xTaskCreate(TaskThumbFinger, // Task function
                "thumb Finger",// Task name
                64,// Stack size
                NULL,
                1,// Priority
                NULL);

    // Create task that publish data in the queue if it was created.
    xTaskCreate(TaskIndexFinger, // Task function
                "index Finger",// Task name
                128,// Stack size
                NULL,
                1,// Priority
                NULL);


    // Create task that publish data in the queue if it was created.
    xTaskCreate(TaskMiddleFinger, // Task function
                "middle Finger",// Task name
                64,// Stack size
                NULL,
                1,// Priority
                NULL);

    // Create task that publish data in the queue if it was created.
    xTaskCreate(TaskRingFinger, // Task function
                "ring Finger",// Task name
                64,// Stack size
                NULL,
                1,// Priority
                NULL);
    // Create task that publish data in the queue if it was created.
    xTaskCreate(TaskPinkyFinger, // Task function
                "pinky Finger",// Task name
                64,// Stack size
                NULL,
                1,// Priority
                NULL);

  }
}

void loop() {}

/**
   Thumb Task
   Move Thumb to location according to FingerPositions[0]
*/
void TaskThumbFinger(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    Serial.println("Thumb Task");
    if (FingerPositions[0] == 1) {
      fingerServos[0].write(90);
    } else if (FingerPositions[0] == 2) {
      fingerServos[0].write(180);
    } else {
      fingerServos[0].write(0);
    }
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}


/**
   Index Task
   Move Index to location according to FingerPositions[1]
*/
void TaskIndexFinger(void *pvParameters) {
  Serial.println("Running Index Finger Task");
  (void) pvParameters;
  for (;;) {
    Serial.println("Finger Task");
    if (xQueueReceive(arrayQueue, &FingerPositions, portMAX_DELAY) == pdPASS ) {
      if (FingerPositions[1] == 1) {
        fingerServos[1].write(90);
      } else if (FingerPositions[1] == 2) {
        fingerServos[1].write(180);
      } else {
        fingerServos[1].write(0);
      }

      vTaskDelay(200 / portTICK_PERIOD_MS);
    }
  }
}



/**
   Middle Task
   Move Middle Finger to location according to FingerPositions[5]
*/
void TaskMiddleFinger(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    Serial.println("Middle Task");
    if (FingerPositions[2] == 1) {
      fingerServos[2].write(90);
    } else if (FingerPositions[2] == 2) {
      fingerServos[2].write(180);
    } else {
      fingerServos[2].write(0);
    }
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}



/**
   Ring Task
   Move Ring Finger to location according to FingerPositions[5]
*/
void TaskRingFinger(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    Serial.println("Ring Task");
    if (FingerPositions[3] == 1) {
      fingerServos[3].write(90);
    } else if (FingerPositions[3] == 2) {
      fingerServos[3].write(180);
    } else {
      fingerServos[3].write(0);
    }
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

/**
   Pinky Task
   Move Pinky Finger to location according to FingerPositions[5]
*/
void TaskPinkyFinger(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    Serial.println("Pinky Task");
    if (FingerPositions[4] == 1) {
      fingerServos[4].write(90);
    } else if (FingerPositions[4] == 2) {
      fingerServos[4].write(180);
    } else {
      fingerServos[4].write(0);
    }
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}





/*** TODO----------------------------------------------------------------------TODO
    Write serial reader task
    - Read in serial input from computer
    - place data from serial input in FingerPositions
    -

 *** END TODO --------------------------------------------------------------END TODO
  /**
   Serial task.
   Prints the received items from the queue to the serial monitor.
*/
void TaskSerial(void *pvParameters) {
  (void) pvParameters;

  // Init Arduino serial

  Serial.println("Running serial task");
  // Wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  while (!Serial) {
    Serial.println("Waiting for Serial Data");
    vTaskDelay(1);
  }

  for (;;) {
    Serial.println("Runnning Serial Main Loop");

    // Serial data should come in as 'h00000x
    if (Serial) {
      serial_cmd = Serial.readString();
      //Get start if serial
      int start = serial_cmd.indexOf("h");
      //Get end of serial
      int end = serial_cmd.indexOf("x");
      if (serial_cmd != "waiting" && serial_cmd != "" && serial_cmd != "NODATA") {
        FingerPositions[0] = (serial_cmd.substring((start + 1), (start + 2))).toInt();
        FingerPositions[1] = (serial_cmd.substring((start + 2), (start + 3))).toInt();
        FingerPositions[2] = (serial_cmd.substring((start + 3), (start + 4))).toInt();
        FingerPositions[3] = (serial_cmd.substring((start + 4), (start + 5))).toInt();
        FingerPositions[4] = (serial_cmd.substring((start + 5), (start + 6))).toInt();
        Serial.print("Recieved Data------");
        Serial.print(serial_cmd);
        Serial.print("------Finger States: ");
        Serial.print(FingerPositions[0]);
        Serial.print(FingerPositions[1]);
        Serial.print(FingerPositions[2]);
        Serial.print(FingerPositions[3]);
        Serial.println(FingerPositions[4]);

        serial_cmd = "waiting";
      }
      xQueueSend(arrayQueue, &FingerPositions, portMAX_DELAY);
      vTaskDelay(50 / portTICK_PERIOD_MS);
    }
  }
}
