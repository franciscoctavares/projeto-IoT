#include <stdio.h>
#include "contiki.h"
#include "sys/etimer.h"
#include "dev/button-sensor.h"
#include "dev/leds.h"
#include "dev/dht22.h"
#include "dev/i2c.h"
#include "dev/tsl256x.h"

static struct etimer et;

PROCESS(test_process, "test process");

AUTOSTART_PROCESSES(&test_process);

void light_interrupt_callback(uint8_t value)
{
  printf("* Light sensor interrupt!\n");
  leds_toggle(LEDS_PURPLE);
}

PROCESS_THREAD(test_process, ev, data) {
	PROCESS_BEGIN();

	/*
	if(TSL256X_REF == TSL2561_SENSOR_REF) {
    	printf("Light sensor test --> TSL2561\n");
  	} else if(TSL256X_REF == TSL2563_SENSOR_REF) {
    	printf("Light sensor test --> TSL2563\n");
  	} else {
    	printf("Unknown light sensor reference, aborting\n");
    	PROCESS_EXIT();
  	}
  	*/

	SENSORS_ACTIVATE(button_sensor);
	SENSORS_ACTIVATE(dht22);
	SENSORS_ACTIVATE(tsl256x);

	static uint16_t light;
	static uint32_t ticks = 0;

	int16_t temperature[3], humidity[3];
	int16_t temp_mean, hum_mean;

	ticks = 0;

	tsl256x.configure(TSL256X_INT_OVER, 0x15B8);

	while(1) {
		etimer_set(&et, CLOCK_SECOND * 2);

  		ticks++;
  		PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);

  	    if(dht22_read_all(&temperature[0], &humidity[0]) != DHT22_ERROR) {
  	    	dht22_read_all(&temperature[1], &humidity[1]);
  	    	dht22_read_all(&temperature[2], &humidity[2]);
  	    	temp_mean = (temperature[0] + temperature[1] + temperature[2]) / 3;
  	    	hum_mean = (humidity[0] + humidity[1] + humidity[2]) / 3;
      		printf("Temperature(3 sample mean) %02d.%02d ºC, ", temp_mean / 10, temp_mean % 10);
      		printf("Humidity(3 sample mean) %02d.%02d RH\n", hum_mean / 10, hum_mean % 10);
    	} else {
      		printf("Failed to read the sensor\n");
    	}

  		/* // Sensor de luz digital(ir ao laboratório buscar o cabo de 5 pinos)
      	light = tsl256x.value(TSL256X_VAL_READ);
        if(light != TSL256X_ERROR) {
      		printf("Light = %u\n", (uint16_t)light);
    	} else {
      		printf("Error, enable the DEBUG flag in the tsl256x driver for info, ");
      		printf("or check if the sensor is properly connected\n");
      		PROCESS_EXIT();
    	}
  		*/
	}

	PROCESS_END();
}