import React, { Component } from "react";
import Handsfree from 'handsfree'
class Freehand_class extends React.Component {
   videotoggle = false;
   sendData = () => {
      this.props.parentCallback("Hey Popsie, How’s it going?");
   };



   callVideoFeed = () => {
      let thumb = '';
      let index = '';
      let middle = '';
      let ring = '';
      let pinky = '';

      const handsfree = new Handsfree({ showDebug: true, hands: true })
      handsfree.enablePlugins('browser')
      handsfree.start()
      handsfree.useGesture({
         "name": "untitled",
         "algorithm": "fingerpose",
         "models": "hands",
         "confidence": 7.5,
         "description": []
      })

      // From inside a plugin
      handsfree.use('logger', data => {
         if (!data.hands) return
         // console.log(data);
         // Show a log whenever the left hand is visible
         if (data.hands.landmarksVisible[0]) {
            if (typeof (data.hands.gesture) !== 'undefined') {
               thumb = data.hands.gesture[0].pose[0][1];
               index = data.hands.gesture[0].pose[1][1];
               middle = data.hands.gesture[0].pose[2][1];
               ring = data.hands.gesture[0].pose[3][1];
               pinky = data.hands.gesture[0].pose[4][1];
               this.props.parentCallback([thumb,index,middle,ring,pinky])

               // console.log(thumb)
            }
         }
      })
   }


   toggleState() {
      if (this.videotoggle == false) {
         this.videotoggle = true;
      } else {
         this.videotoggle = false;
      }
   }

   render() {


      //Any time you wish to send data from child to parent component, call the sendData function.
      return (
         <div>
            <button onClick={this.callVideoFeed.bind(this)}>Start Video</button>
            {/* <button onClick={this.toggleState.bind(this)}>Console Log Data </button> */}

         </div>
      )

   }
};

export default Freehand_class