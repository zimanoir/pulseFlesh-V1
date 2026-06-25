#  project development roadmap


phase 1: hardware evolution
eurorack adaptation: redesigning the PCB into a standard Eurorack module format.
power stage: implementing a dedicated low-noise power circuit running on standard Eurorack rails (±12V), with DC-DC regulation to isolate digital noise.
input/output protection: adding hardware protection loops for all analog inputs and outputs to prevent damage from patching errors.
high-quality connectivity: replacing temporary components with professional Thonkiconn jack connectors.

phase 2: cv precision and sequencing
voltage scaling: using Rail-to-Rail Operational Amplifiers (TL072/OPA2134) to boost 3.3V logic to the standard Eurorack 10V CV range.
precision buffering: integrating low-impedance output buffers for signal stability.
bi-polar control: adding analog bias circuits for manual range shifting (offset) of bio-signals.
16-step sequencer engine: developing a hardware-timed sequencer with a built-in quantizer to map chaotic heart/muscle spikes to musical semitones (V/Oct).
latency optimization: tuning data processing for sub-2ms response time.



phase 3: connectivity and expansion
midi integration: implementing stable MIDI over USB and a classic 5-pin DIN MIDI port.
mobile companion: building an ESP32 Wi-Fi app for mapping bio-signals to MIDI CC and remote pattern editing.
wireless workflow: enabling real-time sequence and pattern control directly from a smartphone during live performances.
