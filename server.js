const express = require('express');
const app = express();
const port = 3000;

// Serve static files (for blocked.mp3)
app.use(express.static(__dirname));

// Endpoint for the ESP32 to notify detection
app.get('/detect', (req, res) => {
    console.log('Object detected!');
    res.send('Detection received');
});

// Serve an HTML file as the frontend interface
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/index.html');
});

// Update the listen to bind to all IPs (0.0.0.0)
app.listen(port, '0.0.0.0', () => {
    console.log(`Server running at http://localhost:${port}`);
});
