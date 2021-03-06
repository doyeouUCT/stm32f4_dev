/*
******************************************************************************
File:		main.c
Info:		Generated by Atollic TrueSTUDIO(R) 9.0.0   2018-03-12
Author:		Ku, Do Yeou
******************************************************************************
*/

#include "main.h"

int main(void)
{
	/* Initialize LEDs */
	STM_EVAL_LEDInit(LED3);	STM_EVAL_LEDInit(LED4);	STM_EVAL_LEDInit(LED5);	STM_EVAL_LEDInit(LED6);
	/* Turn off LEDs */
	STM_EVAL_LEDOff(LED3);	STM_EVAL_LEDOff(LED4);	STM_EVAL_LEDOff(LED5);	STM_EVAL_LEDOff(LED6);

	/* Initialize GNSS */
	gnss_initialize();
	exti_initialize();

	STM_EVAL_LEDOn(LED3);

	/* Default set-up of Sensor FLAGS */
	gnss_log_on = 0;

	/* FATFS */
	FATFS file_system;
	FIL file_pointer;
	UINT bytes_written;
	FRESULT f_err_code;

	/* Default set-up of FLAG. See memory.h/c to understand. */
	file_flag.log_enabled = 1;
	file_flag.file_opened = 0;
	file_flag.filename_ok = PASS;
	char status = 0;
	char filename[13] = "g_test.bin\0";
	char dummy [] = "end";
	/* Check if SD is okay and accessible */
	while(status != SD_CARD_OK){
		status = check_memory (
				&file_system,
				&file_pointer,
				f_err_code);
	}

	/* Infinite loop */
	while (	file_flag.log_enabled == 1)
	{
		if ((volatile int) gnss_log_on == 1) {
			STM_EVAL_LEDOn(LED5);
			status = write_to_memory (
					&file_system,
					&file_pointer,
					f_err_code,
					filename,
					&bytes_written,
					GNSS_LOG_Buffer,
					gnss_Length,
					&file_flag);
			gnss_log_on = 0;
			STM_EVAL_LEDOff(LED5);
		}
	}
	if (file_flag.log_enabled == 0){
		status = write_to_memory (
				&file_system,
				&file_pointer,
				f_err_code,
				filename,
				&bytes_written,
				dummy,
				sizeof(dummy),
				&file_flag);
		STM_EVAL_LEDOff(LED6);
	}

	/* Infinite loop */
	while(1){

	}
}
