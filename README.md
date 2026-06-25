# pulseFlesh V1

A bio-interface NIME that transforms body signals into control voltages for analog synthesizers.

## What is pulseFlesh V1?

**pulseFlesh V1** is an experimental digital musical instrument (NIME) designed to create live sound through embodied interaction. It reads your body signals — heart activity via ECG, muscle tension, and physical impacts — and converts them into control voltages that modulate analog synthesizer parameters like pitch, filter cutoff, and trigger signals.

Rather than a strict rhythmic sequencer, it functions more like a **chaotic noise machine and vibe generator**, blending structured heartbeat data with unpredictable muscle activity to create expressive, organic sound.

## Quick Links

- 📖 **[Full Documentation](documentation/)** – Technical overview, architecture, and signal processing
- 🔧 **[Building Instructions](documentation/BUILDING.md)** – How to assemble the hardware
- ⚙️ **[Hardware Specs](hardware/)** – Schematics and component details
- 💾 **[Firmware](software/)** – ESP32 Arduino sketches

## Key Features

- **ECG Input** – Reads heart rate and converts to smooth CV modulation
- **Muscle Sensing** – Detects muscle tension as a "chaos index" for expressive control
- **Impact Detection** – Piezo sensor captures physical hits for sharp CV triggers
- **Three Independent Outputs** – Jack 1 (Mix 1), Jack 2 (Mix 2), Jack 3 (Direct Piezo)
- **Low-Latency Processing** – ~450 Hz loop speed for responsive real-time performance
- **Upcycled Design** – Built from salvaged components from broken electronics

## Specifications

| Aspect | Details |
|--------|--------|
| **Microcontroller** | ESP32 |
| **ECG Sensor** | AD8232 Red Board |
| **Power** | 18650 Battery + Charging Board |
| **Outputs** | 3× CV (1kΩ buffered) |
| **Loop Speed** | ~450 Hz |
| **ADC Resolution** | 12-bit |

## Get Started

<img src="Images/prototype-eurorack%201.0.png" alt="pulseFlesh V1 prototype" width="300" style="float: left; margin-right: 20px; margin-bottom: 20px;"/>

Здесь ты пишешь свой текст. Благодаря `float: left` картинка прижимается к левому краю, а текст автоматически начинает обтекать её с правой стороны. 

Не забудь добавить `margin-right`, чтобы текст не прилипал к картинке, и `margin-bottom` для отступа снизу.

1. **Read the [Building Guide](documentation/BUILDING.md)** – Solder components and assemble the enclosure
2. **Upload the [Firmware](software/pulseFlesh%20v1.ino)** – Flash the ESP32 with the provided sketch
3. **Patch & Perform** – Connect your synth and start creating

## Project Structure

```
.
├── README.md                      # This file
├── CITATION.cff                   # Citation metadata
├── hardware/                      # Schematics and component specs
│   └── README.md
├── software/                      # Firmware code
│   └── pulseFlesh v1.ino
├── documentation/                 # Detailed technical docs
│   ├── README.md                 # Full project overview
│   └── BUILDING.md               # Assembly instructions
└── files/                         # Additional resources
```

## Author

**Fëdor Zima** – Conservatorio Maderna-Lettimi Cesena Rimini

## License

MIT License – Feel free to use, modify, and share!

## Citation

If you use pulseFlesh V1 in your work, please cite it using the metadata in [`CITATION.cff`](CITATION.cff).

---

**Status:** Experimental prototype ✨  
**Last Updated:** June 2026
