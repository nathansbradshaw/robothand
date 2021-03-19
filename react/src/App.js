import React, { Component } from "react";
import logo from "./logo.svg";
import "./App.css";
import FreehandsAPI from "./components/FreehandsAPI"
// Inside your app
// import Handsfree from 'Freehands'
// import FreehandsAPI from "./components/FreehandsAPI";
// Let's use handtracking and enable the plugins tagged with "browser"
// const handsfree = new Handsfree({ showDebug: true, hands: true })



class App extends Component {
  constructor(props) {
    super(props);
    this.state = { apiResponse: "" };
    // handsfree.enablePlugins('browser')
    // handsfree.start()
    // // From inside a plugin
    // handsfree.use('logger', data => {
    //   if (!data.hands) return

    //   // Show a log whenever the left hand is visible
    //   if (data.hands.landmarksVisible[0]) {
    //     console.log(data.hands.gesture[0].pose)
    //   }
    // })
    // handsfree.useGesture({
    //   "name": "untitled",
    //   "algorithm": "fingerpose",
    //   "models": "hands",
    //   "confidence": 7.5,
    //   "description": []
    // })


  }

  callAPI() {
    fetch("http://localhost:9000/testAPI")
      .then(res => res.text())
      .then(res => this.setState({ apiResponse: res }))
      .catch(err => err);
  }

  componentDidMount() {
    this.callAPI();
  }

  render() {
    return (
      <div className="App">
        <link
    rel="stylesheet"
    href="https://unpkg.com/handsfree@8.1.1/build/lib/assets/handsfree.css" />
        {/* <header className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <h1 className="App-title">Welcome to React</h1>
        </header> */}
        <p className="App-intro">{this.state.apiResponse}</p>
        <FreehandsAPI/>
      </div>
    );
  }
}

export default App;