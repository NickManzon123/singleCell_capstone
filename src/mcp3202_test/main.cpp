/**
 * Basic ADC reading example.
 * - connects to ADC
 * - reads value from channel
 * - converts value to analog voltage
 */

#include <SPI.h>
#include <Mcp320x.h>

#define SPI_CLK     21
#define SPI_MOSI    22
#define SPI_MISO    19
#define SPI_CS      12
#define ADC_VREF    5000     // 3.3V Vref
#define ADC_CLK     1000000  // SPI clock 1.6MHz


MCP3202 adc(ADC_VREF, SPI_CS);

void setup() {

  // configure PIN mode
  pinMode(SPI_CS, OUTPUT);

  // set initial PIN state
  digitalWrite(SPI_CS, HIGH);

  // initialize serial
  Serial.begin(115200);

  // initialize SPI interface for MCP3208
  SPISettings settings(ADC_CLK, MSBFIRST, SPI_MODE0);
  SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, SPI_CS);
  SPI.beginTransaction(settings);
}

void loop() {

  uint32_t t1;
  uint32_t t2;

  // start sampling
  Serial.println("Reading...");

  t1 = micros();
  uint16_t raw = adc.read(MCP3202::Channel::SINGLE_1);
  t2 = micros();

  // get analog value
  uint16_t val = adc.toAnalog(raw);

  // readed value
  Serial.print("value: ");
  Serial.print(raw);
  Serial.print(" (");
  Serial.print(val);
  Serial.println(" mV)");

  // sampling time
  Serial.print("Sampling time: ");
  Serial.print(static_cast<double>(t2 - t1) / 1000, 4);
  Serial.println("ms");

  delay(2000);
}
