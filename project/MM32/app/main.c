#define __MAIN_C__

#include "system_mm32.h"

#include "bsp_led.h"

#include "FreeRTOS.h"
#include "task.h"

#define mainLED1_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define mainLED2_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define mainDELAY_LOOP_COUNT                50000
void app_tick(void)
{
    static u32 cnt = 0;
    
    cnt ++;
}

void vLED1Task( void *pvParameters )
{
    const TickType_t xDelay250ms = pdMS_TO_TICKS( 500 );
	
    for( ;; )
	{
        LD1_on();
        vTaskDelay( xDelay250ms );
        
        LD1_off();
        vTaskDelay( xDelay250ms );
        
	}
}

void vLED2Task( void *pvParameters )
{
    const TickType_t xDelay250ms = pdMS_TO_TICKS( 500 );
    
	for( ;; )
	{
        LD2_on();
        vTaskDelay( xDelay250ms );
        
        LD2_off();
        vTaskDelay( xDelay250ms );
	}
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

void vApplicationTickHook( void )
{
	/* This function will be called by each tick interrupt if
	configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
	added here, but the tick hook is called from an interrupt context, so
	code must not attempt to block, and only the interrupt safe FreeRTOS API
	functions can be used (those that end in FromISR()). */
}

void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}

int main()
{
    ////////////////////////////////////////////////////////////////////////////
    // Hardware initialization                                                //
    ////////////////////////////////////////////////////////////////////////////
    EM_MCUID mcu_id;
    
    SystemClock_TypeDef sys_tick = {
        .clk_src    = 0,            // 0: HSI, >0: HSE frequency
        .clk_target = 72000000,     // clk_src -> clk_target
        .ahb1_div   = 1,            // div 2^(n-1), n: 1 ~ 10, 0: not exist
        .ahb2_div   = 0,            // div 2^(n-1), n: 1 ~ 10, 0: not exist
        .apb1_div   = 1,            // div 2^(n-1), n: 1 ~ 5, 0: not exist
        .apb2_div   = 1,            // div 2^(n-1), n: 1 ~ 5, 0: not exist
        .sys_tick_enable = true,
        .app_tick_ptr = app_tick,
    };
    
    mcu_id = SetSystemClock(&sys_tick);
    
    if (mcu_id == emMCUID_MM32L073) OpenLED();
    if (mcu_id == emMCUID_MM32L373) OpenLED();
    
    bsp_led_init();
    
    ////////////////////////////////////////////////////////////////////////////
    // FreeRTOS                                                               //
    ////////////////////////////////////////////////////////////////////////////
    xTaskCreate( vLED1Task, "LED1", configMINIMAL_STACK_SIZE, NULL, mainLED1_TASK_PRIORITY, NULL );
    xTaskCreate( vLED2Task, "LED2", configMINIMAL_STACK_SIZE, NULL, mainLED2_TASK_PRIORITY, NULL );
    
    vTaskStartScheduler();
    
    while(1) {
        
    }
}