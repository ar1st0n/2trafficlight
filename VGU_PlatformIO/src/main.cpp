/*#include "software_timer.h"
#include "scheduler.h"
#include "state_machine.h"
#include <Arduino.h>
*/
#include <Arduino.h>
#include "scheduler.h"
#include "software_timer.h"
#include "state_machine.h"

#define LED_PIN 48
#define D3 6
#define D4 7
#define D5 8
#define D6 9



int led_status = 0;
void test_blinky(){
  led_status = 1 - led_status;
  digitalWrite(LED_PIN, led_status);
}


void TIMER_ISR(void *pvParameters) {
  
  while(1) {
    SCH_Update();
    vTaskDelay(10);
  }
}


void setup() {
  SCH_Init();
  pinMode(LED_PIN, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, LOW);
  xTaskCreate(TIMER_ISR, "TIMER_ISR", 2048, NULL, 2, NULL);
  Set_Timer(0, 3);
  SCH_Add_Task(Timer_Run, 0, 100);
  SCH_Add_Task(task, 0, 100);
  SCH_Add_Task(test_blinky, 0, 100);
}


void loop() {
  SCH_Dispatch_Tasks();
}
