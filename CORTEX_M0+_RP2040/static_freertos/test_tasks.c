/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/* Library includes. */
#include <stdio.h>
#include "pico/stdlib.h"

int i1 = 0;
int i2 = 0;
int i3 = 0;

void Task1(void* nothing)
{
    ( void ) nothing;
    printf("Task1\n");
    while(1)
    {
        printf("%d %d %d\n", i1, i2, i3);
        i1++;
        sleep_ms(200);
    }
}

void Task2(void* nothing)
{
    ( void ) nothing;
    printf("Task2\n");
    while(1)
    {
        i2++;
        sleep_ms(270);
    }
}

#define staticCREATOR_TASK_STACK_SIZE  (configMINIMAL_STACK_SIZE * 2)
#define staticTASK_PRIORITY            ( tskIDLE_PRIORITY + 2 )

void TestTasks()
{
    stdio_init_all();
    sleep_ms(4000);

    printf("\n\nTestTasks()\n");

    static StackType_t stack0[staticCREATOR_TASK_STACK_SIZE ];
    static StackType_t stack1[staticCREATOR_TASK_STACK_SIZE ];

    static StaticTask_t task0, task1;

    TaskHandle_t ret1 = xTaskCreateStatic(Task1, "Task1",
                                          staticCREATOR_TASK_STACK_SIZE,
                                          NULL,
                                          staticTASK_PRIORITY,
                                          &(stack0[ 0 ]),
                                          &task0);
  
    // Code never reaches here

    if (ret1 != NULL)   printf("Task 1 created OK\n");
    else                printf("Task 1 failed\n");

    TaskHandle_t ret2 = xTaskCreateStatic(Task2, "Task2",
                                          staticCREATOR_TASK_STACK_SIZE,
                                          NULL, staticTASK_PRIORITY,
                                          &(stack1[0]),
                                          &task1);

    if (ret2 != NULL)   printf("Task 2 created OK\n");
    else                printf("Task 2 failed\n");

    vTaskStartScheduler();

    printf("Shouldn't be here");
    while(1)
    {
        i3++;
        sleep_ms(444);
    }
}
