const express = require('express');
const app = express();
const port = 3000;

const ipStore = new Map();

function generateMatchCode() {
  return Math.floor(100000 + Math.random() * 900000).toString();
}

app.use(express.json());

app.post('/create', (req, res) => {
  const ip = req.ip;
  const matchCode = generateMatchCode();
  ipStore.set(matchCode, ip);
  res.json({ matchCode });
});

app.post('/join', (req, res) => {
  const { matchCode } = req.body;
  const ip = ipStore.get(matchCode);
  if (ip) {
    res.json({ ip });
  } else {
    res.status(404).json({ error: 'Match code not found' });
  }
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
