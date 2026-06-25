# Hardware Prototype

======================================================================================
                               pulseFlesh V1 SYSTEM SCHEMATIC
======================================================================================

 [ 18650 BATTERY ] 
   (+) Positive (Red)   ----> [ B+ ]  CHARGING BOARD 
   (-) Negative (Black) ----> [ B- ]  (Power Bank Module)
                                      [ VOUT+ ]    [ GND ]
                                          |           |
                                     [ POWER SWITCH ] |
                                          |           |
                                          V           |
+------------------------------------+    |           |
|             pulseFlesh             |    |           |
|              (ESP32)               |    |           |
|                                    |    |           |
|  [ VN ] <---------------------------+----+           |
|  [GND ] <-------------------------------------------+---+ (COMMON GROUND BUS)
|                                    |                |   |
|  [ 36 / VP ] <--- (Output) ------+ |                |   |
|  [ 21 / D21] <--- (LO+) -------+ | |                |   |
|  [ 15 / D15] <--- (LO-) -----+ | | |                |   |
|                                | | |                |   |
|  [ 25 / D25] ----+             | | |                |   |
|  [ 32 / D32] --+ |             | | |                |   |
+----------------|-|-------------|-|-|----------------+   |
                 | |             | | |                |   |
                 | |   +---------|-|-|----------------+   |
                 | |   |         | | |                    |
                 | |   |       [ AD8232 ECG ]             |
                 | |   |       (Red Board)                |
                 | |   |                                  |
                 | |   +-----> [ 3.3v ]                   |
                 | |           [ GND  ] <-----------------+
                 | +---------> [ LO-  ]                   |
                 +-----------> [ LO+  ]                   |
                               [OUTPUT]                   |
                                                          |
                                                          |
                       [ B10K POTENTIOMETER ]             |
                             ( Splitter )                 |
                             /    |    \                  |
                            /     |     \                 |
                        [ 1 ]   [ 2 ]   [ 3 ] <-----------+----------+
                          |       |       |               |          |
                      (ECG DAC)   |  (Piezo Plus)   [PROTECTION]  [PIEZO SENSOR]
                      from pin    |     to pin          LED         (Mechanics)
                        D25       |      D32         (Reverse)       |
                                  |                       |          |
                                  |                       +----------+
                                  |                                  |
         +------------------------+------------------------+         |
         |                        |                        |         V
     [Resistor]               [Resistor]               [Resistor]  (GND)
       1 kOhm                   1 kOhm                   1 kOhm
         |                        |                        |
         V                        V                        V
   [JACK #1: MIX 1]         [JACK #2: MIX 2]        [JACK #3: PIEZO]
  (from BT speaker)        (from BT speaker)        (from PC speaker)
         |                        |                        |
         V                        V                        V
  External Synth           External Synth           External Synth
   CV Modulation            CV Modulation            CV Trigger / Clock
  (e.g., Pitch/Pitch FM)    (e.g., VCF/Cutoff)       (e.g., Gate/LFO/PWM)
