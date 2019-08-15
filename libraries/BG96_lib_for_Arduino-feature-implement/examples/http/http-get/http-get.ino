#include <NectisCellular.h>

#define WEBURL       "https://httpbin.org/ip"

NectisCellular Nectis;

void setup() {
  char data[3000];  // レスポンスを格納できるだけの容量が必要！
  int status;

  delay(4000);

  Serial.begin(115200);
  Serial.println("");
  Serial.println("--- START ---------------------------------------------------");

  Serial.println("### I/O Initialize.");
  Nectis.Init();
  delay(100);
  Serial.println("### Power supply cellular ON.");
  Nectis.PowerSupplyCellular(true);
  delay(100);

  Nectis.Bg96Begin();
  Nectis.InitLteM();

  Serial.println("### Setup completed.");

  Serial.println("GET " WEBURL);
  status = Nectis.HttpGet(WEBURL, data, sizeof(data));
  
  Serial.print("RecvBytes:");
  Serial.println(status);

  if(status > 0)
  {
    data[status] = 0x0;
    Serial.println(data);
  }
  Serial.print("Status:");
  Serial.println(status);
}

void loop() {
}
