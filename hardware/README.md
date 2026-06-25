# Hardware Prototype

## pulseFlesh V1 System Schematic

```mermaid
graph TD
    Battery["🔋 18650 Battery<br/>Positive/Negative"] --> Charging["⚡ Charging Board<br/>VOUT+ / GND"]
    Charging --> PowerSwitch["Power Switch"]
    PowerSwitch --> ESP32["ESP32<br/>Microcontroller<br/>VN / GND<br/>D21, D15, D25, D32"]
    
    ESP32 -->|Pin D36/VP| ADCOutput["ADC Output"]
    ESP32 -->|Pin D21| LOPlus["LO+ Signal"]
    ESP32 -->|Pin D15| LOMinus["LO- Signal"]
    
    LOPlus --> ECG["AD8232 ECG<br/>Red Board"]
    LOMinus --> ECG
    
    ECG -->|Output| Potentiometer["B10K Potentiometer<br/>Splitter"]
    
    Potentiometer -->|Pin 1| Jack1["Jack #1: MIX 1<br/>ECG DAC from D25"]
    Potentiometer -->|Pin 2| Jack2["Jack #2: MIX 2<br/>Piezo Plus to D32"]
    Potentiometer -->|Pin 3| Jack3["Jack #3: PIEZO<br/>from PC Speaker"]
    
    Jack1 --> ExtSynth1["External Synth<br/>CV Modulation<br/>Pitch/Pitch FM"]
    Jack2 --> ExtSynth2["External Synth<br/>CV Modulation<br/>VCF/Cutoff"]
    Jack3 --> ExtSynth3["External Synth<br/>Trigger/Clock<br/>Gate/LFO/PWM"]
    
    ECG -->|3.3v| Power["Power Distribution"]
    Power -->|GND| GroundBus["Common Ground Bus"]
    GroundBus -->|Protection LED| Protection["Protection LED<br/>Reverse"]
    Protection --> PiezoSensor["Piezo Sensor<br/>Mechanics"]
    
    Jack1 --> Resistor1["Resistor<br/>1 kOhm"]
    Jack2 --> Resistor2["Resistor<br/>1 kOhm"]
    Jack3 --> Resistor3["Resistor<br/>1 kOhm"]
    
    style ESP32 fill:#4da6ff
    style ECG fill:#ff6b6b
    style Battery fill:#ffd700
    style Charging fill:#90ee90
```

## Компоненты

| Компонент | Функция | Пины |
|-----------|---------|------|
| 18650 Battery | Питание | B+/B- |
| Charging Board | Управление питанием | VOUT+/GND |
| ESP32 | Микроконтроллер | D21, D15, D25, D32, D36 |
| AD8232 ECG | ЭКГ датчик | LO+/LO-/Output |
| B10K Potentiometer | Сплиттер сигнала | 1/2/3 |
| Resistors (1kΩ) | Защита/согласование | - |

## Выходы

- **Jack #1 (MIX 1)** → External Synth (CV Modulation: Pitch/Pitch FM)
- **Jack #2 (MIX 2)** → External Synth (CV Modulation: VCF/Cutoff)
- **Jack #3 (PIEZO)** → External Synth (Trigger/Clock: Gate/LFO/PWM)
