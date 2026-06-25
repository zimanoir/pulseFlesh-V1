# Building pulseFlesh V1

This guide will walk you through assembling the hardware for pulseFlesh V1. The build requires basic soldering skills and takes approximately 2-3 hours.

## Components List

### Power & Control
- 1× ESP32 Development Board
- 1× 18650 Battery
- 1× USB Power Bank Charging Module (TP4056 or similar)
- 1× Power Switch (ON/OFF)
- 1× Blue LED (3mm, for electrode disconnection indicator)
- 1× 220Ω Resistor (for LED)

### Sensors & Signal Processing
- 1× AD8232 ECG Sensor Module (Red Board)
- 1× Piezo Disc Sensor (mechanical impact detection)
- 1× Regular LED (reverse-parallel protection for piezo)
- 1× 1MΩ Resistor (optional, for piezo damping)

### Audio & Output
- 3× 3.5mm Mono Jack Sockets (for CV outputs)
- 3× 1kΩ Resistors (protection/impedance matching)

### Mechanical
- Enclosure or 3D-printed case
- Electrode pads or ECG lead connectors
- Conductive rubber cords or wires for body contact
- Soldering iron & solder
- Wire strippers
- Breadboard or PCB for prototyping

## Pin Configuration

| Component | ESP32 Pin | Function |
|-----------|-----------|----------|
| ECG Output | 36 (VP) | Analog input from AD8232 |
| ECG LO+ | 21 (D21) | Electrode disconnection check |
| ECG LO- | 15 (D15) | Electrode disconnection check |
| CV DAC Out | 25 (D25) | Analog output to Jack #1 |
| Piezo Input | 32 (D32) | Analog input from piezo |
| Blue LED | 2 (D2) | Status indicator |
| Power | 3.3V / GND | Supply voltage |

## Assembly Steps

### Step 1: Prepare the Power Supply

1. Connect the 18650 battery to the TP4056 charging module:
   - **B+ (Red)** → Positive terminal
   - **B- (Black)** → Negative terminal

2. Add a power switch between **VOUT+** and the main circuit:
   ```
   Battery → Charging Module → [Power Switch] → ESP32 VCC
   Battery GND → Charging Module GND → ESP32 GND
   ```

3. Add a 220Ω resistor in series with the Blue LED, connected to GPIO 2 and GND:
   ```
   [Blue LED] → [220Ω Resistor] → GND
   (other end of LED to GPIO 2)
   ```

### Step 2: Connect ECG Sensor (AD8232)

1. Wire the AD8232 Red Board:
   ```
   AD8232 3.3V   → ESP32 3.3V
   AD8232 GND    → ESP32 GND (common ground bus)
   AD8232 OUTPUT → ESP32 GPIO 36 (VP)
   AD8232 LO+    → ESP32 GPIO 21 (D21)
   AD8232 LO-    → ESP32 GPIO 15 (D15)
   ```

2. Connect ECG electrode pads to the AD8232 board:
   - Two chest electrodes to the sensor inputs
   - One reference electrode to the board ground

### Step 3: Connect Piezo Sensor

1. Connect the piezo disc:
   ```
   [Piezo +] → [Reverse LED] → [Optional 1MΩ] → ESP32 GPIO 32 (D32)
   [Piezo -] → ESP32 GND
   ```

2. The reverse LED protects against high voltage spikes from mechanical impacts.

### Step 4: Wire Output Jacks

1. Each jack gets a 1kΩ protection resistor:
   ```
   ESP32 GPIO 25 (DAC) → [1kΩ] → Jack #1 (MIX 1)
   Potentiometer Pin 2 → [1kΩ] → Jack #2 (MIX 2)
   Potentiometer Pin 3 → [1kΩ] → Jack #3 (PIEZO)
   ```

2. Connect all jack grounds to the common ground bus.

### Step 5: Create a Common Ground Bus

Solder together all ground wires from:
- Power supply
- ESP32
- ECG sensor
- Piezo sensor
- Jacks

This prevents ground loops and hum.

### Step 6: Flash the Firmware

1. Install the Arduino IDE and ESP32 board package
2. Open `software/pulseFlesh v1.ino`
3. Select **Board: ESP32 Dev Module**
4. Upload the sketch to your ESP32
5. Check the Serial Monitor (115200 baud) for initialization message

### Step 7: Test & Calibration

1. **Power on** the device using the power switch
2. **Verify the Blue LED:**
   - Should be **OFF** when electrodes are connected
   - Should be **ON** when electrodes are disconnected
3. **Check ECG input:**
   - Open Serial Plotter (Tools → Serial Plotter)
   - You should see a waveform representing your heartbeat
4. **Test outputs:**
   - Connect a multimeter to each jack
   - Move around and flex muscles to see CV changes
   - Tap the piezo to trigger sharp spikes

## Troubleshooting

**No ECG signal?**
- Check electrode contact with skin
- Verify ECG sensor connections to GPIO 36, 21, 15
- Ensure 3.3V power to the AD8232 board

**Blue LED always on?**
- Check LO+ (GPIO 21) and LO- (GPIO 15) connections
- Verify electrode pads are making good contact

**No CV output?**
- Test GPIO 25 (DAC) with a multimeter
- Check resistor values (should be exactly 1kΩ)
- Verify jack connections

**High noise on outputs?**
- Ensure all grounds are connected to the common bus
- Add ferrite beads around power wires if needed
- Check for loose connections

## Next Steps

- Calibrate **BIOMIN** and **BIOMAX** values in the code for your body
- Experiment with **smoothing factors** to change responsiveness
- Add a potentiometer to mix between different signal sources
- Design a custom enclosure with recessed jacks

---

**Happy building! 🎛️**
