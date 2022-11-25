function pushToCalendar() {

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
    
    // xmlPOSTHttp.setRequestHeader("Content-Type", "application/json");
    xmlPOSTHttp.setRequestHeader("Access-Control-Allow-Orgin","*");
    // xmlPOSTHttp.setRequestHeader("Access-Control-Allow-Credentials", "true");
    // xmlPOSTHttp.setRequestHeader("Access-Control-Allow-Methods","POST");
    // xmlPOSTHttp.setRequestHeader("Access-Control-Allow-Headers", "Access-Control-Allow-Headers, Origin,Accept, X-Requested-With, Content-Type, Access-Control-Request-Method, Access-Control-Request-Headers");

    // xmlPOSTHttp.onreadystatechange = () => {
    //     if (this.readyState == xmlPOSTHttp.DONE && this.status == 200) {
    //         console.log("hello");
    //     }
    // };
    // xmlPOSTHttp.send(JSON.stringify(quizCreateCalendarJson));



    xmlPOSTHttp.setRequestHeader("Accept", "application/json");
    xmlPOSTHttp.setRequestHeader("Content-Type", "application/json;charset=utf8");
    
    xmlPOSTHttp.onreadystatechange = function () {
      if (xmlPOSTHttp.readyState === 4) {
        console.log(xmlPOSTHttp.status);
        console.log(xmlPOSTHttp.responseText);
      }};
    
    xmlPOSTHttp.send(JSON.stringify(quizCreateCalendarJson));

}