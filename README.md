# Robot hand
## How to use

Running the node server 
 ```sh
cd nodesocket
npm i
npm start
```
Running the react client
 ```sh
cd react
npm i
npm start
```

### How to connect to the correct com port?
Open nodesocket folder
in app.js change the value of `SERIALPORT` to the port that the device is connected to
#### How to change the Baudrate?
Open nodesocket folder
in app.js change the value of `BAUDRATE` to the desired buaddrate.

### What does this program do?
The react app part of this app uses two node module called handsfree and fingerpose.
Handsfree uses mediapipe to gather information based on the location of the users hand, Fingerpose calculates the position that a finger is in. 
The react app then sends the finger data to the nodesocket app using socket.io, We have to send the data to a node server because our frontend react app cannont access our serial ports. 
The nodesocket Server then recieves the data through the socket and then sends the data recieved through the socket to our Arduino through our COM port
