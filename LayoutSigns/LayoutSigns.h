#include <Arduino.h>
#include <Adafruit_PCF8574.h>

#pragma once
class Svetofor{
private:
	bool pcf_mode;
	Adafruit_PCF8574* pcfs[6];
	uint8_t pcfs_pins[6];
	uint8_t ard_pins[6];
	int8_t blink[2];
	int8_t sets[6][2];
	int8_t def_blink[2];
	int8_t def_sets[6][2];
	uint16_t blink_delay = 500;
	uint64_t t1 = 0;
public:
	Svetofor();
	Svetofor(bool _pcf_mode);
	void set(uint8_t signal, uint8_t st);
	bool is_light(uint8_t signal);
	bool is_blink(uint8_t signal);
	void blink_on(uint8_t signal);
	void blink_off();
	void work();
	void set_ard_pin(uint8_t linz, uint8_t ard_pin);
	void set_pcf_pin(uint8_t linz, Adafruit_PCF8574* pcf, uint8_t pcf_pin);
	void save_default();
	void get_default();
	void set_blink_delay(uint16_t d);
};