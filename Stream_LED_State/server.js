const express = require('express');
const app = express();

// Allow Express to parse incoming JSON data from the ESP32
app.use(express.json()); 
let currentLedState = "OFF";

// 1. The Web Interface
app.get('/', (req, res) => {
    res.send(`
        <!DOCTYPE html>
        <html>
        <head><title>ESP32 Stream</title></head>
        <body style="font-family: sans-serif; text-align: center; margin-top: 50px;">
            <h1>ESP32 Built-in LED is: <strong id="state" style="color: #007bff;">Unknown</strong></h1>
            <script>
                // Poll the server every 1 second for the latest state
                setInterval(() => {
                    fetch('/status')
                        .then(res => res.json())
                        .then(data => {
                            document.getElementById('state').innerText = data.state;
                        });
                }, 1000);
            </script>
        </body>
        </html>
    `);
});

// 2. The endpoint where the ESP32 sends data
app.post('/update', (req, res) => {
    currentLedState = req.body.state;
    console.log("ESP32 reported state:", currentLedState);
    res.sendStatus(200);
});

// 3. The endpoint where the browser fetches data
app.get('/status', (req, res) => {
    res.json({ state: currentLedState });
});

// Listen on all network interfaces so the ESP32 can connect
app.listen(3000, '0.0.0.0', () => console.log('Server running on port 3000'));