import React, {Component, } from 'react'
import "./App.css";
import Freehand_class from "./components/Freehand_class"
import socketIOClient from "socket.io-client";
import { socket } from './context/socket';

class App extends Component {
  state = { message: "" }
  callbackFunction = (childData) => {
    this.setState({ message: childData })
  }
  constructor() {
    super();
    this.state = {
    };
    this.counter = 0;

  }
  
  sendData = (data) => {
    socket.emit('hand data', (data));
  
  }

  componentDidMount() {
    const { endpoint } = this.state;
    //Very simply connect to the socket
    console.log('Connect to server')
    // const socket = socketIOClient(endpoint);
    const interval = setInterval(this.sendData(this.state.message), 1000)
    // //Listen for data on the "outgoing data" namespace and supply a callback for what to do when we get one. In this case, we set a state variable
    // // socket.on("outgoing data", data => this.setState({ response: data.num }));
    // socket.emit('hand data', ('Heeloo'));
  }

  componentWillUnmount() {
    clearInterval(this.interval);
  }


  render() {
    const { response } = this.state;
    console.log(this.state.message);
    // const interval = setInterval(this.sendData(this.state.message), 10000)
    clearInterval(this.interval);
    if (this.counter > 15) {
      this.sendData(this.state.message)
      this.counter = 0;
      console.log('SENDING DATA')
    }
    this.counter++;
    console.log(this.counter)


    return (
      <div style={{ textAlign: "center" }}>
        <link
          rel="stylesheet"
          href="https://unpkg.com/handsfree@8.1.1/build/lib/assets/handsfree.css" />
        {/* <FreehandsAPI  parentCallback = {this.callbackFunction}/> */}
        <Freehand_class parentCallback={this.callbackFunction} />
        <p> {this.state.message} </p>
        {/* TODO: SEND MESSAGE TO NODE SERVER THROUGH SOCKETS */}
      </div>
    )
  }
}

export default App;