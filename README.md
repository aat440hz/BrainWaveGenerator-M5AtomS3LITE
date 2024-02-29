# BrainWave Generator

The BrainWave Generator is an innovative project that transforms the M5AtomS3LITE microcontroller into an interactive device, leveraging its capabilities to generate binaural beats and isochronic tones through a web interface. The device acts as a Wi-Fi hotspot, serving the BrainWave Generator's interface on 192.168.4.1, allowing users to access and interact with the generator directly through their web browsers. This project uses the Web Audio API for sound generation and offers real-time oscilloscope visualization of the audio waveform, enhancing user engagement.

## Key Features

- **Microcontroller as Wi-Fi Hotspot**: The M5AtomS3LITE microcontroller serves the web interface as a Wi-Fi hotspot, accessible at 192.168.4.1.
- **Adjustable Frequencies**: Users can control two separate frequencies to explore different auditory experiences.
- **Pulse Rate Control**: Adjust the pulse rate to modulate the sound, creating isochronic tones for various mental states.
- **Real-time Oscilloscope Visualization**: Provides a visual feedback mechanism via an oscilloscope view, enriching the user's interaction.
- **Dynamic Frequency Variance**: Automatically introduces slight variations to the frequencies, simulating a more natural listening experience.
- **Browser Compatibility**: For optimal audio rendering, Mozilla Firefox is recommended due to its superior handling of the Web Audio API.

## How It Works

The generator uses the ESP32-S3 chip within the M5AtomS3LITE to create a Wi-Fi access point, through which users can connect and interact with the generator's interface. It employs oscillators for sound generation, a gain node for volume control, an LFO (Low Frequency Oscillator) for pulse modulation, and an analyser node for waveform visualization, all managed through a user-friendly, terminal-like interface inspired by classic computing aesthetics.

## Usage

1. **Connect to the Wi-Fi Hotspot**: Search for the Wi-Fi network named "M5AtomS3LITE" and connect to it. The default password, if set, will be provided in the documentation.
2. **Access the Interface**: Open a web browser and navigate to 192.168.4.1 to access the BrainWave Generator.
3. **Adjust Frequencies and Pulse Rate**: Use the sliders on the web interface to set the desired audio parameters.
4. **Start the Audio**: Click "Play" to begin sound generation. The button toggles to "Stop" for easy control.
5. **Experience the Visualization**: Watch the real-time oscilloscope visualization for visual feedback of the audio output.

## Customization

This project invites customization to suit various needs. Users can fork the project to adjust frequency ranges, change the UI, or introduce new features like preset brainwave states for specific applications such as meditation, focus, or relaxation.

## Technologies Used

- HTML
- CSS
- JavaScript
- Web Audio API
- ESP32-S3 (for the microcontroller programming)

## Running the Generator

To activate the BrainWave Generator, power up the M5AtomS3LITE microcontroller. The device automatically creates a Wi-Fi hotspot. Simply connect to this network and navigate to 192.168.4.1 on a web browser to interact with the generator.

## Browser Compatibility Note

The experience and sound quality of the BrainWave Generator may vary across different web browsers due to the handling of the Web Audio API. For the best auditory experience, it is recommended to use Mozilla Firefox.

## Science-Based Frequency Combinations

Here are some frequency combinations based on known brainwave states. These are intended for use with binaural or monaural beat generators to encourage the brain to "tune in" to a specific state.

### 1. Deep Relaxation
- **Frequency 1:** 100 Hz
- **Frequency 2:** 104 Hz
- **Pulse:** 4 Hz (Theta range)
- **Explanation:** Aims for Theta range to encourage deep relaxation, meditation, and creativity.

### 2. Focus and Concentration
- **Frequency 1:** 200 Hz
- **Frequency 2:** 215 Hz
- **Pulse:** 15 Hz (Beta range)
- **Explanation:** Utilizes Beta range to enhance focus, alertness, and problem-solving.

### 3. Deep Sleep Induction
- **Frequency 1:** 150 Hz
- **Frequency 2:** 154 Hz
- **Pulse:** 4 Hz (Delta range)
- **Explanation:** Delta range is used to induce deep sleep or restfulness.

### 4. Meditation and Mindfulness
- **Frequency 1:** 200 Hz
- **Frequency 2:** 210 Hz
- **Pulse:** 10 Hz (Alpha range)
- **Explanation:** Alpha range to aid in relaxation, calmness, and meditative states.

### 5. Quick Mental Refresh
- **Frequency 1:** 500 Hz
- **Frequency 2:** 520 Hz
- **Pulse:** 20 Hz (Beta range)
- **Explanation:** Beta range for a quick mental refresh during sustained tasks.

### 6. Creativity Boost
- **Frequency 1:** 300 Hz
- **Frequency 2:** 308 Hz
- **Pulse:** 8 Hz (Alpha/Theta border)
- **Explanation:** Border of Alpha and Theta for a mix of relaxation and alert awareness conducive to creativity.

### Notes on Usage
- **Range Considerations:** Actual frequencies are higher than brainwave frequencies, but the difference (pulse) is in the intended range.
- **Volume and Duration:** Use a comfortable volume and start with shorter periods to gauge reaction.
- **Consult Professionals:** If seeking therapeutic effects or have health concerns, consult a healthcare professional before use.

Use these combinations as tools for relaxation, focus, or creativity, not as medical treatment. Individual results may vary.
