function getExecutionMode(){

    // Look for the corresponding GET request
    var xmlHttpIP = new XMLHttpRequest();
    xmlHttpIP.open("GET", "../json/serviceips.json", false);
    xmlHttpIP.send(null);

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
        xmlHttpMODE
        xmlHttpMODE.send(null);
    
        // Parse the services json file
        professorJson = xmlHttpIP.responseText;
        professorObj = JSON.parse(professorJson);
    } catch (error) {
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

