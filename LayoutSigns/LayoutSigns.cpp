#include <Arduino.h>
#include <Adafruit_PCF8574.h>
#include <LayoutSigns.h>

Svetofor::Svetofor(){
	blink[0] = -1;
	blink[1] = 0;
	def_blink[0] = -1;
	def_blink[1] = 0;
	for(int i = 0; i < 6; i++){
	    sets[i][0] = -1;
	    sets[i][1] = -1;
	}
	for(int i = 0; i < 6; i++){
	    def_sets[i][0] = -1;
	    def_sets[i][1] = -1;
	}
	pcf_mode = false;
}
Svetofor::Svetofor(bool _pcf_mode){
	blink[0] = -1;
	blink[1] = 0;
	def_blink[0] = -1;
	def_blink[1] = 0;
	for(int i = 0; i < 6; i++){
	    sets[i][0] = -1;
	    sets[i][1] = -1;
	}
	for(int i = 0; i < 6; i++){
	    def_sets[i][0] = -1;
	    def_sets[i][1] = -1;
	}
	pcf_mode = _pcf_mode;
	Serial.begin(115200);
}
void Svetofor::set(uint8_t signal, uint8_t st){
	if(!pcf_mode){
		sets[signal][0] = signal;
		sets[signal][1] = st;
	}
	else{
		sets[signal][0] = signal;
		sets[signal][1] = st;
	}
}
bool Svetofor::is_light(uint8_t signal){
	return sets[signal][1] == 1;
}
bool Svetofor::is_blink(uint8_t signal){
	return blink[0] == signal;
}
void Svetofor::blink_on(uint8_t signal){
	blink[0] = signal;
}
void Svetofor::blink_off(){
	blink[0] = -1;
	blink[1] = 0;
}
void Svetofor::set_pcf_pin(uint8_t linz, Adafruit_PCF8574* pcf, uint8_t pcf_pin){
	pcfs[linz] = pcf;
	pcfs_pins[linz] = pcf_pin;
}
void Svetofor::set_ard_pin(uint8_t linz, uint8_t ard_pin){
	ard_pins[linz] = ard_pin;
}
void Svetofor::save_default(){
	for(int i = 0; i < 6; i++){
		def_sets[i][0] = sets[i][0];
		def_sets[i][1] = sets[i][1];
		def_blink[0] = blink[0];
		def_blink[1] = blink[1];
	}
}
void Svetofor::get_default(){
	for(int i = 0; i < 6; i++){
		sets[i][0] = def_sets[i][0];
		sets[i][1] = def_sets[i][1];
		blink[0] = def_blink[0];
		blink[1] = def_blink[1];
	}
}
void Svetofor::set_blink_delay(uint16_t d){blink_delay = d;}
void Svetofor::work(){
	if(millis() - t1 >= blink_delay){
		if (blink[0] != -1){
			if(!pcf_mode){
				digitalWrite(ard_pins[blink[0]], blink[1]);
			}
			else{
				pcfs[blink[0]]->digitalWrite(pcfs_pins[blink[0]], blink[1]);
			}
			blink[1] = (int)(!(bool)blink[1]);
		}
		t1 = millis();
	}
	delay(20);
	for(int i = 0; i < 6; i++){
        if (sets[i][0] != -1){
            if(!pcf_mode){
                digitalWrite(ard_pins[sets[i][0]], sets[i][1]);
            }
            else{
                pcfs[i]->digitalWrite(pcfs_pins[i], sets[i][1]);
                delay(20);
            }
        }
    }
	// Clear data
	for(int j = 0; j < 6; j++){
	    sets[j][0] = -1;
	    sets[j][1] = -1;
	}
}