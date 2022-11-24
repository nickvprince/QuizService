import {redirectToAddr} from "redirect.js";

function getMode(){

    // Look for the corresponding GET request
    var xmlHttpIP = new XMLHttpRequest();
    xmlHttpIP.open("GET", "../json/serviceips.json", false);
    xmlHttpIP.send(null);

    // Parse the services json file
    const serviceJson = xmlHttpIP.responseText;
    const serviceObj = JSON.parse(serviceJson);

    var ip = serviceObj["adminactivities"].ip;
    var port = serviceObj["adminactivities"].port;

    var professor;

    //get request mode
    try {
        var xmlHttpMODE = new XMLHttpRequest();
        xmlHttpMODE.open("GET", "http://" + ip + ":" + port + "/modeofoperation", false);
        xmlHttpMODE.send(null);
    
        // Parse the services json file
        professor = xmlHttpMODE.responseText;
    } catch (e) {
        professor = true;
    }

    if(professor == "true") {
        redirectToAddr("../professorIndex.html")
    } else {
        redirectToAddr("../studentIndex.html")
    }
}