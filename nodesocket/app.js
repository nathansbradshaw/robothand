const express = require("express");
const http = require("http");
const socketIo = require("socket.io");
const SerialPort = require('serialport');
const e = require("express");
const SERIALPORT = 'com20'
const serialport = new SerialPort(SERIALPORT, {
  baudRate: 57600
})
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

//Setting up a socket with the namespace "connection" for new sockets
io.on("connection", socket => {
    console.log("New client connected");

    // //Here we listen on a new namespace called "incoming data"
    // socket.on("incoming data", (data)=>{
    //     //Here we broadcast it out to all other sockets EXCLUDING the socket which sent us the data
    //    socket.broadcast.emit("outgoing data", {num: data});
    // });
    socket.on('hand data', (data)=> {
      let cmd = dataToString(data)
      console.log(cmd)
      if(serialport){
        serialport.write(cmd)
      }
    })

    //A special namespace "disconnect" for when a client disconnects
    socket.on("disconnect", () => console.log("Client disconnected"));
});

const dataToString = (data) => {
  if(data === 'undefined' || data === null) {
    return 'NODATA'
  }
  let commandString = 'h'
  data.forEach(element => {
    if(element === 'No Curl'){
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
server.listen(port, () => console.log(`Listening on port ${port}`));
