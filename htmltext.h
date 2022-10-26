/**
 * based on code by Niel Cameron
 * this page forms the text for the HTML
 * Now it is one continous piece because there are no variables
 * Store array (page) data in flash (program) memory instead of SRAM, 
 * qualifeid by the PROGMEM modifier.
 * R"()" is a raw literal string.
 * 
 * This page is returned to client, on the client side, the javascript will
 * execute. THe JS/AJAX code is at end of the file
 */



char page[] PROGMEM = R"(
  <!DOCTYPE html><html><head>
  <title>Local network</title>
  <style>
  
  .on {background-color:red}
  .off {background-color:blue}
  </style></head>
  <body>
  <h1>ESP32 as server, but also connects to web</h1>
  <p> Working in STA mode </p>
  
  <table style='width:100%'><tr>
  <td>Green LED is <span id='LEDG'>OFF</span> now</td>
  <td>Red LED is <span id='LEDR'>OFF</span> now</td>
  </tr></table>
  
  <table style='width:100%'><tr>
  <td><button class = 'btn off' id='Green LED'
       onclick = 'sendData(id)'>Press to control the motor
       </button></td>
       <td><button class = 'btn off' id='Red LED'
     onclick = 'sendData(id)'>Press to turn MANUAL ON
     </button></td>
</tr></table>

<button class = 'current' id='currentLevel'
     onclick = 'sendData(id)'> current water level
     </button>

<div id="extText"> </div>
     
<script>
function sendData(butn)
{
  var URL, variab, text;
  if(butn == 'Red LED')
  {
    URL = 'LEDRurl';
    variab = 'LEDR';
  }
  else if(butn == 'Green LED')
  {
    URL = 'LEDGurl';
    variab = 'LEDG';
  }
  else if(butn == 'currentLevel')
  {
    URL = 'zeroUrl';
    variab = 'extText';
  }
  if(butn == 'Red LED' || butn == 'Green LED')
{ // change button class and text 
  var state = document.getElementById(butn).className;
  state = (state == 'btn on' ? 'btn off' : 'btn on');
  text = (state == 'btn on' ? butn + ' OFF' : butn + ' ON');
    document.getElementById(butn).className = state;
    document.getElementById(butn).innerHTML = 'Press to turn ' + text;
  }
  var xhr = new XMLHttpRequest();
  xhr.onload = function(){
    document.getElementById(variab).innerHTML = this.responseText;
  }
  xhr.open('GET', URL, true);
  xhr.send();
}



</script>
</body></html>
)";

//char page[] PROGMEM = R"(
//  <!DOCTYPE html><html><head>
//  <title>Local network</title>
//  <style>
//  
//  .on {background-color:red}
//  .off {background-color:blue}
//  </style></head>
//  <body>
//  <h1>ESP32 as server, but also connects to web</h1>
//  <p> Working in STA mode </p>
//  
//  <table style='width:100%'><tr>
//  <td>Green LED is <span id='LEDG'>OFF</span> now</td>
//  <td>Red LED is <span id='LEDR'>OFF</span> now</td>
//  </tr></table>
//  
//  <table style='width:100%'><tr>
//  <td>
//  <p>Enter a customer_number <input type="text" id="theText">  </p>
//
//  <button class = 'btn off' id='Green LED'
//       onclick = 'sendData(id)'>Press to turn Green LED ON
//       </button>
//       </td> 
//
//       
//       
//       <td><button class = 'btn off' id='Red LED'
//     onclick = 'sendData(id)'>Press to turn Red LED ON
//     </button></td>
//</tr></table>
//<p>Counter is <span id='counter'>0</span> now</p>
//<button class = 'btn zero' id = 'zero'
//     onclick = 'sendData(id)'>Press to zero counter</button>
//
//<div id="extText"> </div>
//     
//<script>
//function sendData(butn)
//{
//  var URL, variab, text;
//  if(butn == 'Red LED')
//  {
//    URL = 'LEDRurl';
//    variab = 'LEDR';
//  }
//  else if(butn == 'Green LED')
//  {
//    URL = 'LEDGurl';
//    variab = 'LEDG';
//  }
//  else if(butn == 'zero')
//  {
//    URL = 'zeroUrl';
//    variab = 'counter';
//  }
//  if(butn == 'Red LED' || butn == 'Green LED')
//{ // change button class and text 
//  var state = document.getElementById(butn).className;
//  state = (state == 'btn on' ? 'btn off' : 'btn on');
//  text = (state == 'btn on' ? butn + ' OFF' : butn + ' ON');
//    document.getElementById(butn).className = state;
//    document.getElementById(butn).innerHTML = 'Press to turn ' + text;
//  }
//  var xhr = new XMLHttpRequest();
//  id=document.getElementById("theText").value;
//  xhr.onload = function(){
//    document.getElementById().innerHTML = this.responseText;
//  }
//  xhr.open('GET',"http://192.168.230.13:80/sensorproject/retrieve.php?customer_number="+id, true);
//  xhr.send();
//}
//
//
//<!-- not needed, but enables periodic update of count -->
//setInterval(reload, 1000);
//function reload()
//{
//  var xhr = new XMLHttpRequest();
//  
//  xhr.onload = function(){
//    document.getElementById('counter').innerHTML = this.responseText;
//  }
//  xhr.open('GET', 'countUrl', true);
//  xhr.send();
//}
//</script>
//</body></html>
//)";



//char page[] PROGMEM = R"(
//
//<!DOCTYPE html>
//<HTML>
//<head>
//    <title>Page title</title>
//</head>
//<body>
//
//
//    <h1>Illustrating AJAX fetch of dynamic content</h1>
//    <p> we will fetch details of one particular record in the db. You can enter an ID if you know one (eg id=1,...,6) </p>
//
//    <p>Enter a customer_number <input type="text" id="theText">  </p>
//    <p> <button id="fff">fetche the newest water level value by customer number</button></p>
//    <p> returned data is <div id="dbdata"></div></p>
//
//        
//
//    <script type="text/javascript">
//
//
//var btn = document.getElementById("fff");
//btn.addEventListener("click", function() {
//    
//    const xhttp=new XMLHttpRequest();
//            
//            id=document.getElementById("theText").value;
//            xhttp.onload=function(){
//                document.getElementById("dbdata").innerText=this.responseText;
//            }
//            console.log(id);
////            xhttp.open("GET", "http://localhost/sensorproject/retrieve.php?customer_number="+id);
//xhttp.open("GET", "ttp://localhost/sensorproject/retrieve.php?customer_number=1");
//            h
//            xhttp.send();
//
//            
//}, false);
//
//
//        var counter=0;
//        function updateByJS(){
//            counter++;
//            document.getElementById("js_update").innerText="This is the New Text, number of times pressed ="+counter;
//        }
//
//        function updateByAJAX_static(){
//            const xhttp=new XMLHttpRequest();
//            xhttp.onload=function(){
//                document.getElementById("statictext").innerText=this.responseText;
//            }
//            xhttp.open("GET", "/iot/AJAX/someText.txt");
//            xhttp.send();
//        }
//
//        function updateByAJAX_dbData(){
//            const xhttp=new XMLHttpRequest();
//            
//            id=document.getElementById("theText").value;
//            console.log(id);
//            xhttp.open("GET", "/retrieve.php?water_level=99&status=high&customer_number=1");
//            xhttp.send();
//            xhttp.onload=function(){
//                document.getElementById("dbdata").innerText=this.responseText;
//            }
//        }
//        function deff(){
//            document.write("Amen")
//        }
//
//    </script>
//
//</body>
//
//</HTML>
//
//
//
//)";
