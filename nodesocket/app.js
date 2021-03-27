const express = require("express");
const http = require("http");
const socketIo = require("socket.io");
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline')
const e = require("express");
const SERIALPORT = 'COM6'
const BAUDRATE = 115200
const serialport = new SerialPort(SERIALPORT, {
  baudRate: BAUDRATE
})

serialport.on("open", () => {
  console.log('serial port open on ' + SERIALPORT + ' At baudrate: ' + BAUDRATE);
});

const parser = new Readline()
serialport.pipe(parser)
//Port from environment variable or default - 4001
const port = process.env.PORT || 8000;

//Setting up express and adding socketIo middleware
const app = express();
const server = http.createServer(app);
const io = socketIo(server, {
  cors: {
    origin: '*',
  }
});

let command = 'NODATA';

//Setting up a socket with the namespace "connection" for new sockets
io.on("connection", socket => {
  console.log("-----------------------------New client connected");

  // //Here we listen on a new namespace called "incoming data"
  // socket.on("incoming data", (data)=>{
  //     //Here we broadcast it out to all other sockets EXCLUDING the socket which sent us the data
  //    socket.broadcast.emit("outgoing data", {num: data});
  // });

    socket.on('hand data', (data) => {
      let cmd = dataToString(data)
      command = cmd;
      console.log(cmd)
      
    })


  //A special namespace "disconnect" for when a client disconnects
  socket.on("disconnect", () => console.log("--------------------Client disconnected"));
});

const dataToString = (data) => {
  if (data === 'undefined' || data === null) {
    return 'NODATA'
  }
  let commandString = 'h'
  data.forEach(element => {
    if (element === 'No Curl') {
      commandString += '0'
    } else if (element === 'Half Curl') {
      commandString += '1'
    } else {
      commandString += '2'
    }
  });
  commandString += 'x'
  return commandString;

}

parser.on('data', data => {
  console.log('got word from arduino:', data);
});

setInterval(function(){ 
  if (serialport) {
    serialport.write(command)
    console.log(command)

  }
},1000) //logs hi every second


server.listen(port, () => console.log(`Listening on port ${port}`));
