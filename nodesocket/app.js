const http = require('http');
const express = require('express');
const app = express();

const PORT = process.env.PORT || 8000 // So we can run on heroku || (OR) localhost:5000

app.set('view engine', 'ejs');
app.set('views', 'views');

const server = app.listen(PORT);
const io = require('socket.io')(server);
io.on('connection', socket => {
   console.log('Client Connected');
});