# Documentation

# pulseFlesh V1

This is a small experimental project that turns body signals into control voltages for analog synthesizers. It reads heart activity via ECG, picks up muscle noise, and tracks physical hits using a regular piezo element. All this data is mixed together and sent out as CV (Control Voltage) to modulate parameters on any semi-modular or modular analog synthesizer.

Right now, it works more like a chaotic noise machine and a vibe generator rather than a strict rhythmic sequencer.

## How it was built and the upcycling idea

Most of the connectors and parts for this build were unsalvaged from old broken electronics instead of buying new ones. For example, two output jacks were desoldered from dead portable Bluetooth speakers, the main bio-signal input connector was taken from an old 2.1 PC subwoofer system, and the third jack for the piezo channel was pulled from the front panel of obsolete computer speakers where it used to be a headphone output. It is a good way to reuse old parts and give e-waste a second life.

## Fixes after a short circuit

During the initial testing, the battery was accidentally connected backward, which caused a short circuit that burned out the original charging module and the main chip. While rebuilding it from scratch, a few simple protection steps were added to keep both the microcontroller and the connected synths safe:

* Three 1 kOhm resistors were added right before the output jacks. They act as a buffer to protect external synthesizer inputs from static and accidental reverse currents.
* A regular LED was soldered directly across the piezo sensor in reverse-parallel. When you hit the piezo hard, it can generate a huge voltage spike that could kill the microcontroller pins. The LED just clips those dangerous spikes and keeps the signal safe.
* All grounds from the power supply, sensors, and jacks are tied together into a single solid ground line to prevent unwanted hum and noise loops.

## Patching and connectivity

The device provides three independent outputs that can be patched into any synth gear that accepts standard CV signals:

* Jack 1 (Mix 1, controlled by the pot): Perfect for modulating oscillator pitch (VCO FM) or filter cutoff (VCF IN) with a blended bio-signal.
* Jack 2 (Mix 2, controlled by the pot): Sends a secondary mix of the bio-data, great for controlling envelope times, resonance, or VCA.
* Jack 3 (Direct Piezo): Sends out sharp voltage spikes from physical impacts. Best used for triggering clocks, altering LFO rates, or modulating PWM.

## How the code handles the signal

The microcontroller runs a very fast loop to make sure there is no noticeable delay between your movement and the sound from the synth. The main steps in the sketch are quite straightforward:

* It filters out random hardware glitches. If the electrodes lose good skin contact for a millisecond, the code drops that sudden massive spike so it does not cause harsh audio clicks.
* It extracts muscle noise. By comparing the current frame with the previous one, the code calculates how fast the signal changes. This gives a "chaos index" representing muscle tension, which adds some grit to the output.
* It uses a quadratic curve. The clean bio-signal gets multiplied by itself. This compresses small baseline drifts but makes actual heartbeats or sharp muscle flexes stand out much more dynamically.

## Future plans

The goal is to expand this setup into a fully featured performance tool. The current roadmap includes:

* Designing a proper Eurorack format module with an integrated low-noise power circuit running on standard synth rails.
* Developing a full 16-step sequencer engine based on internal hardware timers.
* Implementing stable CV outputs alongside native MIDI over USB and a classic 5-pin MIDI output port to sequence external hardware and software instruments simultaneously.
