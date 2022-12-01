function getExecutionMode(){
    //log startup
    var xmlHttpLog = new XMLHttpRequest();
   
    xmlHttpLog.open("POST", "../log/gettingMode/0", false);
    xmlHttpLog.send(null);
  


    // Look for the corresponding GET request
    var xmlHttpIP = new XMLHttpRequest();
    xmlHttpIP.open("GET", "../json/serviceips.json", false);
    xmlHttpIP.send(null);
    if (xmlHttpIP.status != 200) {
        xmlHttpLog.open("POST", "../log/get Service Ips failed/2", false);
        xmlHttpLog.send(null);
    }
    // Parse the services json file
    const serviceJson = xmlHttpIP.responseText;
    const serviceObj = JSON.parse(serviceJson);

    var ip = serviceObj["adminactivities"].ip;
    var port = serviceObj["adminactivities"].port;

    var professor = false;
    var professorObj;
    //get request mode
    try {
        var xmlHttpMODE = new XMLHttpRequest();
        xmlHttpMODE.open("GET", "http://" + ip + ":" + port + "/modeofoperation", false);
        xmlHttpMODE.timeout();
        xmlHttpMODE.send(null);
        if (xmlHttpMODE.status != 200) {
            xmlHttpLog.open("POST", "../log/Get mode failed"+xmlHttpMODE.status+"/2", false);
            xmlHttpLog.send(null);
        }
        alert(xmlHttpMODE.status);
        // Parse the services json file
        professorJson = xmlHttpIP.responseText;
        professorObj = JSON.parse(professorJson);
    } catch (error) {
        xmlHttpLog.open("POST", '../log/Professor mode defaulted... admin is not online at '+ip+':'+port+'/2', false);
        xmlHttpLog.send(null);
        professor = true;
    }

    if(professor == false) {
        if(professorObj["modeofoperation"] == true) {
            redirectToAddr("../index.html");
        } else {
            redirectToAddr("../studentIndex.html");
        }
    } else {
        redirectToAddr("../index.html");
    }
}
    
function redirectToAddr (addr) {
    window.location.replace(addr);
}

