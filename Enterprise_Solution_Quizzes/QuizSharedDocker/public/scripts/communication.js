function pushToCalendar() {
  const urlParams = new URLSearchParams(location.search);
  console.log(location.search);

  for (const [key, value] of urlParams) {
    if(key == "quizTitle"){

      // Look for the corresponding GET request
      var xmlGETHttp = new XMLHttpRequest();
      xmlGETHttp.open("GET", "../json/serviceips.json", false);
      xmlGETHttp.send(null);

      // Parse the services json file
      const serviceJson = xmlGETHttp.responseText;
      const serviceObj = JSON.parse(serviceJson);

      var ip = serviceObj["calendar"].ip;
      var port = serviceObj["calendar"].port;

      // Look for the corresponding GET request
      var xmlGETHttpCreateQuizCalendar = new XMLHttpRequest();
      xmlGETHttpCreateQuizCalendar.open("GET", "../json/createQuizInCalendar.json", false);
      xmlGETHttpCreateQuizCalendar.send(null);

      const quizCreateCalendarJson = JSON.parse(xmlGETHttpCreateQuizCalendar.responseText);
      //const quizCreateCalendarObj = JSON.parse(quizCreateCalendarJson);

      console.log(quizCreateCalendarJson);

      const xmlPOSTHttp = new XMLHttpRequest();
      xmlPOSTHttp.open("POST", "http://" + ip + ":" + port + "/event", true);
      xmlPOSTHttp.setRequestHeader("Access-Control-Allow-Origin","*");
      xmlPOSTHttp.setRequestHeader("Accept", "application/json");
      xmlPOSTHttp.setRequestHeader("Content-Type", "application/json;charset=utf8");

      xmlPOSTHttp.onreadystatechange = function () {
        if (xmlPOSTHttp.readyState === 4) {
          console.log(xmlPOSTHttp.status);
          console.log(xmlPOSTHttp.responseText);
      }};

      xmlPOSTHttp.send(JSON.stringify(quizCreateCalendarJson));
    }
  }
}
function putToCalendar() {

  const urlParams = new URLSearchParams(location.search);
  console.log(location.search);

  for (const [key, value] of urlParams) {
    if(key == "quizTitle"){

      // Look for the corresponding GET request
      var xmlGETHttp = new XMLHttpRequest();
      xmlGETHttp.open("GET", "../json/serviceips.json", false);
      xmlGETHttp.send(null);
    
      // Parse the services json file
      const serviceJson = xmlGETHttp.responseText;
      const serviceObj = JSON.parse(serviceJson);
    
      var ip = serviceObj["calendar"].ip;
      var port = serviceObj["calendar"].port;
    
      // Look for the corresponding GET request
      var xmlGETHttpCreateQuizCalendar = new XMLHttpRequest();
      xmlGETHttpCreateQuizCalendar.open("GET", "../json/createQuizInCalendar.json", false);
      xmlGETHttpCreateQuizCalendar.send(null);
    
      const quizCreateCalendarJson = JSON.parse(xmlGETHttpCreateQuizCalendar.responseText);
      //const quizCreateCalendarObj = JSON.parse(quizCreateCalendarJson);
    
      console.log(quizCreateCalendarJson);
    
      const selected = document.getElementById('quizID');
    
      const xmlPOSTHttp = new XMLHttpRequest();
      xmlPOSTHttp.open("PUT", "http://" + ip + ":" + port + "/event?enterpriseID = " + document.getElementById("quizID").value, true);
      xmlPOSTHttp.setRequestHeader("Access-Control-Allow-Origin","*");
      xmlPOSTHttp.setRequestHeader("Accept", "application/json");
      xmlPOSTHttp.setRequestHeader("Content-Type", "application/json;charset=utf8");
    
      xmlPOSTHttp.onreadystatechange = function () {
        if (xmlPOSTHttp.readyState === 4) {
          console.log(xmlPOSTHttp.status);
          console.log(xmlPOSTHttp.responseText);
      }};
    
      xmlPOSTHttp.send(JSON.stringify(quizCreateCalendarJson));
      }
    }
  }


function deleteFromCalendar() {

  // Look for the corresponding GET request
  var xmlGETHttp = new XMLHttpRequest();
  xmlGETHttp.open("GET", "../json/serviceips.json", false);
  xmlGETHttp.send(null);

  // Parse the services json file
  const serviceJson = xmlGETHttp.responseText;
  const serviceObj = JSON.parse(serviceJson);

  var ip = serviceObj["calendar"].ip;
  var port = serviceObj["calendar"].port;

  const selected = document.getElementById('quizID');
  console.log(selected.value);

  const xmlPOSTHttp = new XMLHttpRequest();
  xmlPOSTHttp.open("DELETE", "http://" + ip + ":" + port + "/event?enterpriseID = " + selected.value, true);
  xmlPOSTHttp.send(null);

}

function pushToGrades(){
  // Look for the corresponding GET request
  var xmlGETHttp = new XMLHttpRequest();
  xmlGETHttp.open("GET", "../json/serviceips.json", false);
  xmlGETHttp.send(null);

  // Parse the services json file
  const serviceJson = xmlGETHttp.responseText;
  const serviceObj = JSON.parse(serviceJson);

  var ip = serviceObj["grades"].ip;
  var port = serviceObj["grades"].port;

  // Look for the corresponding GET request
  const xmlPOSTHttp = new XMLHttpRequest();
  xmlPOSTHttp.open("POST", "http://" + ip + ":" + port + "?grade=100", true);
  xmlPOSTHttp.send(null);
}