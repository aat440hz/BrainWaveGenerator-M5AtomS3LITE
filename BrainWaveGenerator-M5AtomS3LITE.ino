#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char *ssid = "Brainwave Generator";
const char *password = NULL;

WebServer server(80);

const char *html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>BrainWave Generator</title>
    <style>
        body {
            text-align: center;
            font-family: 'Courier New', Courier, monospace;
            background-color: #000;
            color: #0f0;
            margin: 0;
            padding: 20px;
        }
        .slider {
            width: 80%;
            -webkit-appearance: none;
            appearance: none;
            height: 10px;
            background: #222;
            outline: none;
            opacity: 0.7;
            -webkit-transition: .2s;
            transition: opacity .2s;
        }
        .slider:hover {
            opacity: 1;
        }
        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: #0f0;
            cursor: pointer;
        }
        .slider::-moz-range-thumb {
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: #0f0;
            cursor: pointer;
        }
        #oscilloscope {
            width: 90%;
            height: 200px;
            background-color: #000;
            display: block;
            margin: 20px auto;
            border: 1px solid #0f0;
        }
        button {
            background-color: #333;
            color: #0f0;
            border: 1px solid #0f0;
            padding: 10px;
            font-family: 'Courier New', Courier, monospace;
            cursor: pointer;
            transition: background-color 0.3s ease;
        }
        button:hover {
            background-color: #555;
        }
    </style>
</head>
<body>
    <h1>Brainwave Generator</h1>
    <div>
        Frequency 1: <input type="range" id="freq1Slider" class="slider" min="20" max="2000" value="20">
        <span id="freq1Value">20</span>Hz
    </div>
    <div>
        Frequency 2: <input type="range" id="freq2Slider" class="slider" min="20" max="2000" value="60">
        <span id="freq2Value">60</span>Hz
    </div>
    <div>
        Pulse Rate: <input type="range" id="pulseRateSlider" class="slider" min="0.1" max="30" value="1" step="0.1">
        <span id="pulseRateValue">1</span>Hz
    </div>
    <button id="playButton">Play</button>
    <canvas id="oscilloscope"></canvas>

    <script>
        var audioCtx = new (window.AudioContext || window.webkitAudioContext)();
        var oscillator1, oscillator2, gainNode, lfo, analyser;
        var isPlaying = false;
        var varianceInterval;

        function updateValues() {
            document.getElementById('freq1Value').textContent = document.getElementById('freq1Slider').value;
            document.getElementById('freq2Value').textContent = document.getElementById('freq2Slider').value;
            document.getElementById('pulseRateValue').textContent = document.getElementById('pulseRateSlider').value;
        }

        function createAudioComponents() {
            oscillator1 = audioCtx.createOscillator();
            oscillator2 = audioCtx.createOscillator();
            gainNode = audioCtx.createGain();
            lfo = audioCtx.createOscillator();
            analyser = audioCtx.createAnalyser();

            oscillator1.connect(gainNode);
            oscillator2.connect(gainNode);
            gainNode.connect(analyser);
            analyser.connect(audioCtx.destination);
            lfo.connect(gainNode.gain);
        }

        function startSound() {
            createAudioComponents();

            var freq1 = parseFloat(document.getElementById('freq1Slider').value);
            var freq2 = parseFloat(document.getElementById('freq2Slider').value);
            var pulseRate = parseFloat(document.getElementById('pulseRateSlider').value);

            oscillator1.frequency.setValueAtTime(freq1, audioCtx.currentTime);
            oscillator2.frequency.setValueAtTime(freq2, audioCtx.currentTime);
            lfo.frequency.setValueAtTime(pulseRate, audioCtx.currentTime);

            oscillator1.start();
            oscillator2.start();
            lfo.start();

            isPlaying = true;
            document.getElementById('playButton').textContent = 'Stop';

            introduceVariance();
            draw();
        }

        function stopSound() {
            oscillator1.stop();
            oscillator2.stop();
            lfo.stop();

            isPlaying = false;
            clearInterval(varianceInterval);
            document.getElementById('playButton').textContent = 'Play';
        }

        function toggleSound() {
            if (isPlaying) {
                stopSound();
            } else {
                startSound();
            }
        }

        function introduceVariance() {
            const varianceAmount = 4.5; // How much the frequency can vary
            varianceInterval = setInterval(() => {
                var baseFreq1 = parseFloat(document.getElementById('freq1Slider').value);
                var baseFreq2 = parseFloat(document.getElementById('freq2Slider').value);
                const variance1 = (Math.random() * 2 - 1) * varianceAmount;
                const variance2 = (Math.random() * 2 - 1) * varianceAmount;
                oscillator1.frequency.setValueAtTime(baseFreq1 + variance1, audioCtx.currentTime);
                oscillator2.frequency.setValueAtTime(baseFreq2 + variance2, audioCtx.currentTime);
            }, 5000); // Adjust every 5 seconds
        }

        function draw() {
            if (!isPlaying) return;
            requestAnimationFrame(draw);
            const canvas = document.getElementById('oscilloscope');
            const canvasCtx = canvas.getContext('2d');
            const bufferLength = analyser.frequencyBinCount;
            const dataArray = new Uint8Array(bufferLength);
            analyser.getByteTimeDomainData(dataArray);

            canvasCtx.fillStyle = 'rgb(0, 0, 0)';
            canvasCtx.fillRect(0, 0, canvas.width, canvas.height);
            canvasCtx.lineWidth = 2;
            canvasCtx.strokeStyle = 'rgb(0, 255, 0)';
            canvasCtx.beginPath();

            const sliceWidth = canvas.width * 1.0 / bufferLength;
            let x = 0;

            for (let i = 0; i < bufferLength; i++) {
                const v = dataArray[i] / 128.0;
                const y = v * canvas.height / 2;
                if (i === 0) {
                    canvasCtx.moveTo(x, y);
                } else {
                    canvasCtx.lineTo(x, y);
                }
                x += sliceWidth;
            }

            canvasCtx.lineTo(canvas.width, canvas.height / 2);
            canvasCtx.stroke();
        }

        document.getElementById('playButton').addEventListener('click', function() {
            toggleSound();
        });

        document.querySelectorAll('.slider').forEach(item => {
            item.addEventListener('input', function() {
                updateValues();
                if (isPlaying) {
                    var freq1 = parseFloat(document.getElementById('freq1Slider').value);
                    var freq2 = parseFloat(document.getElementById('freq2Slider').value);
                    var pulseRate = parseFloat(document.getElementById('pulseRateSlider').value);
                    oscillator1.frequency.setValueAtTime(freq1, audioCtx.currentTime);
                    oscillator2.frequency.setValueAtTime(freq2, audioCtx.currentTime);
                    lfo.frequency.setValueAtTime(pulseRate, audioCtx.currentTime);
                }
            });
        });

        updateValues(); // Initialize display values
    </script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  // Set up the ESP32 as an access point
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Route for root / web page
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
