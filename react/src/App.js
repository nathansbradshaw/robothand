import React, { Component } from "react";
import "./App.css";
import FreehandsAPI from "./components/FreehandsAPI"
import openSocket from "socket.io-client"

class App extends Component {
  componentDidMount() {

    openSocket('http://localhost:8000');
  }

  render() {
    return (
      <div className="App">
        <link
    rel="stylesheet"
    href="https://unpkg.com/handsfree@8.1.1/build/lib/assets/handsfree.css" />
        <button id='send'>Send Message to Server</button>
        <FreehandsAPI/>
      </div>
    );
  }
}

export default App;