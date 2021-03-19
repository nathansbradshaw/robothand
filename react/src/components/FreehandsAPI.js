import React from "react";
import Handsfree from 'handsfree'

function FreehandsAPI() {
const handsfree = new Handsfree({ showDebug: true, hands: true })
let thumb =  '';
let index =  '';
let middle =  '';
let ring =  '';
let pinky =  '';


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
    console.log(data);
    //  // Show a log whenever the left hand is visible
    //  if (data.hands.landmarksVisible[0]) {
    //    if(typeof(data.hands.gesture) !== 'undefined'){
    //       thumb = data.hands.gesture[0].pose[0][1];
    //       index = data.hands.gesture[0].pose[1][1];
    //       middle = data.hands.gesture[0].pose[2][1];
    //       ring = data.hands.gesture[0].pose[3][1];
    //       pinky = data.hands.gesture[0].pose[4][1];
    //       document.getElementById('thumb').innerHTML = 'Thumb:' + thumb;
    //       document.getElementById('index').innerHTML = 'index:' + index;
    //       document.getElementById('middle').innerHTML = 'middle:' + middle;
    //       document.getElementById('ring').innerHTML = 'ring:' + ring;
    //       document.getElementById('pinky').innerHTML = 'pinky:' + pinky;
    //       console.log(thumb)
    //    }
    //  }
   })

   
   return(
      <div>
        {/* <p id='thumb'>thumb: </p>
        <p id='index'>index: </p>
        <p id='middle'>middle: </p>
        <p id='ring'>ring: </p>
        <p id='pinky'>pinky: </p> */}

      </div>
   )

}

export default FreehandsAPI