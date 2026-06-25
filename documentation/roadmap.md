# project development roadmap

## phase 1 hardware evolution
* redesigning the main board into a standard eurorack format module
* implementing a dedicated low noise power stage running on eurorack rails
* adding hardware protection loops for all analog inputs and outputs
* replacing temporary sockets with high quality thonkiconn jack connectors

## phase 2 sequencer engine
* writing a native 16 step sequencer engine using internal hardware timers
* implementing independent clock dividers and multipliers per channel
* creating customizable voltage scales and quantization modes for cv outputs
* optimizing data processing to keep latency under 2 milliseconds

## phase 3 connectivity and expansion
* implementing stable midi over usb and a classic 5 pin din midi port
* building a mobile companion app connecting via onboard esp32 wi fi for mapping custom bio signals to midi cc
* adding wireless sequence editing and pattern control from a smartphone
