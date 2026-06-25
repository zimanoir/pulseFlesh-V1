# Documentation

# pulseFlesh V1

This is a small experimental project that turns body signals into control voltages for analog synthesizers. It reads heart activity via ECG, picks up muscle noise, and tracks physical hits using a regular piezo element. All this data is mixed together and sent out as CV to modulate parameters on a Moog Werkstatt-01.

Right now, it works more like a chaotic noise machine and a vibe generator rather than a strict rhythmic sequencer.

## How it was built and the upcycling idea

Most of the connectors and parts for this build were unsalvaged from old broken electronics instead of buying new ones. For example, two output jacks were desoldered from dead portable Bluetooth speakers, the main bio-signal input connector was taken from an old 2.1 PC subwoofer system, and the third jack for the piezo channel was pulled from the front panel of obsolete computer speakers where it used to be a headphone output. It is a good way to reuse old parts and give e-waste a second life.

## Fixes after a short circuit

During the initial testing, the battery was accidentally connected backward, which caused a short circuit that burned out the original charging module and the main chip. While rebuilding it from scratch, a few simple protection steps were added to keep the synth and the new board safe:

* Three 1 kOhm resistors were added right before the output jacks. They act as a shield to protect the Moog from static and accidental reverse currents.
* A regular LED was soldered directly across the piezo sensor in reverse-parallel. When you hit the piezo hard, it can generate a huge voltage spike that could kill the microcontroller pins. The LED just clips those dangerous spikes and keeps the signal safe.
* All grounds from the power supply, sensors, and jacks are tied together into a single solid ground line to prevent unwanted hum and noise loops.

## Where to plug it in the Moog

* Jack 1 (Mix 1, controlled by the pot) goes into VCO LIN FM IN to modulate the oscillator pitch.
* Jack 2 (Mix 2, controlled by the pot) goes into VCF IN to control the filter cutoff.
* Jack 3 (Direct Piezo) goes into LFO RATE or PWM IN to warp the waveform shapes using physical impacts.

## How the code handles the signal

The microcontroller runs a very fast loop to make sure there is no noticeable delay between your movement and the sound from the synth. The main steps in the sketch are quite straightforward:

* It filters out random hardware glitches. If the electrodes lose good skin contact for a millisecond, the code drops that sudden massive spike so it does not hurt your ears.
* It extracts muscle noise. By comparing the current frame with the previous one, the code calculates how fast the signal changes. This gives a "chaos index" representing muscle tension, which adds some grit to the output.
* It uses a quadratic curve. The clean bio-signal gets multiplied by itself. This compresses small baseline drifts but makes actual heartbeats or sharp muscle flexes stand out much more dynamically.

## Future plans

The goal is to expand this setup. It started as a dual-channel ECG and muscle tracker, then got a dedicated third channel for the piezo sensor. The next step is to add a proper low-noise power circuit, write a step-sequencer engine based on internal timers, and eventually add standard MIDI over USB and a classic 5-pin MIDI output alongside the analog CV jacks.
