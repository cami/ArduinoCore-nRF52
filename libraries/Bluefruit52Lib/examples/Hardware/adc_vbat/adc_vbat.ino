#include <NectisCellular.h>

NectisCellular Nectis;

void setup() {
    Serial.begin(115200);
    Serial.println("setup");
}

void loop() {
    float LipoVoltageLevelMv;
    LipoVoltageLevelMv = Nectis.ReadVbat();
    
    Serial.printf("%f[mV]\n", LipoVoltageLevelMv);
    
    delay(5000);
}
