import React, { Component } from "react";
import "./App.css";
import FreehandsAPI from "./components/FreehandsAPI"
import Freehand_class from "./components/Freehand_class"
import socketIOClient from "socket.io-client";

class App extends Component {
  state = { message: "" }
callbackFunction = (childData) => {
      this.setState({message: childData})
}
  constructor() {
    super();
    this.state = {
      response: 0,
      endpoint: "http://127.0.0.1:8000"
    };
  }

  componentDidMount() {
    const { endpoint } = this.state;
    //Very simply connect to the socket
    console.log('Connect to server')
    const socket = socketIOClient(endpoint);
    //Listen for data on the "outgoing data" namespace and supply a callback for what to do when we get one. In this case, we set a state variable
    socket.on("outgoing data", data => this.setState({ response: data.num }));
  }

  render() {
    const { response } = this.state;
    console.log(this.state.message);

    return (
      <div style={{ textAlign: "center" }}>
        <link
          rel="stylesheet"
          href="https://unpkg.com/handsfree@8.1.1/build/lib/assets/handsfree.css" />
        {/* <FreehandsAPI  parentCallback = {this.callbackFunction}/> */}
        <Freehand_class  parentCallback = {this.callbackFunction}/>
          <p> {this.state.message} </p>
      </div>
    )
  }
}

export default App;