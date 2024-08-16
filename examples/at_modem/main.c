// Copyright (c) 2020, Myriota Pty Ltd, All Rights Reserved
// SPDX-License-Identifier: BSD-3-Clause-Attribution
//
// This file is licensed under the BSD with attribution  (the "License"); you
// may not use these files except in compliance with the License.
//
// You may obtain a copy of the License here:
// LICENSE-BSD-3-Clause-Attribution.txt and at
// https://spdx.org/licenses/BSD-3-Clause-Attribution.html
//
// See the License for the specific language governing permissions and
// limitations under the License.

// This example demonstrates how to use Myriota module as satellite modem
// controlled by AT commands.

#include "at.h"

#define LED_DELAY 100               // ms
#define WAIT_FOR_TEST_TIMEOUT 3000  // ms

static char RX[UART_MAX_RX_SIZE] = {0};

static time_t ModemReceive() {
  //Ver RX antes y desp de leer
  printf("--- RX antes de leer ---\n");
  printf("IOF RX antes de leer = %c", RX[i]);
  for (int i = 0; i < UART_MAX_RX_SIZE; i++) {
    printf("[IOF] RX antes de leer = %c", RX[i]);
  }
  printf("\n");

  int len = ATReceive(RX, UART_MAX_RX_SIZE);
  if (len > 0) {
    ATProcess(RX, len);
  } else {
    printf("No data received\n");
  }

  printf("--- RX antes de leer ---\n");
  for (int i = 0; i < UART_MAX_RX_SIZE; i++) {
    printf("[IOF] RX antes de leer = %c", RX[i]);
  }
  printf("\n");

  return OnLeuartReceive();
}

static time_t UARTReady() {
  if (HasValidGNSSFix()) {
    ATSetState(SYS_STATE_READY);
    printf("State = READY\n");
  } else {
    ATSetState(SYS_STATE_GNSS_ACQ);
    printf("State = GNSS_ACQ\n");
  }
  LedTurnOn();
  Delay(LED_DELAY);
  LedTurnOff();
  return Never();
}

void AppInit() {
  ScheduleJob(UARTReady, ASAP());
  ScheduleJob(ModemReceive, OnLeuartReceive());
}

int BoardStart(void) {
  GPIOSetModeOutput(MODEM_BUSY);
  GPIOSetHigh(MODEM_BUSY);
  if (ATInit())
    printf("Failed to init modem\n");
  else {
    ATSetState(SYS_STATE_INIT);
    printf("Myriota modem example\n");
    LedTurnOn();
    if (IsTestMode(WAIT_FOR_TEST_TIMEOUT)) HardwareTest();
    LedTurnOff();
  }
  return 0;
}

void BoardSleepEnter(void) { GPIOSetLow(MODEM_BUSY); }

void BoardSleepExit(void) { GPIOSetHigh(MODEM_BUSY); }
