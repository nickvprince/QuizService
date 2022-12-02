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

    var xmlHttpSetMode = new XMLHttpRequest(); // used to set mode in server
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
        xmlHttpSetMode.open("GET", '/setMode/'+responseText, false);
        xmlHttpSetMode.send(null);
        professorJson = xmlHttpIP.responseText;
        professorObj = JSON.parse(professorJson);
    } catch (error) {
        //set mode to na
        
        xmlHttpSetMode.open("GET", '/setMode/na', false);
        xmlHttpSetMode.send(null);

        xmlHttpLog.open("POST", '../log/admin%20is%20not%20online%20at '+ip+':'+port+'/2', false);
        xmlHttpLog.send(null);

        addButtons();
    }

 
}
    
function redirectToAddr(addr) {
   
    window.location.replace(addr);
}

function addButtons() {
    
    //init buttons
    var buttonProf = document.createElement("input");
    var buttonStudent = document.createElement("input");

    // professor button
   buttonProf.setAttribute("onclick", "alterAddr('./index.html')");
    buttonProf.setAttribute("value", "professor");
    buttonProf.setAttribute("type", "button");

    //Student button
    buttonStudent.setAttribute("onclick", "alterAddr('./studentIndex.html')");
    buttonStudent.setAttribute("value", "student");
    buttonStudent.setAttribute("type", "button");

    // add buttons to page
    document.getElementById("insertHere").insertAdjacentElement("afterend", buttonProf);
    document.getElementById("insertHere").insertAdjacentElement("afterend", buttonStudent);
}

function alterAddr(addr) {

    var xmlHttpSetMode = new XMLHttpRequest(); // used to set mode in server
    if (addr == './index.html') {
        xmlHttpSetMode.open("GET", '/setMode/prof', false);
        xmlHttpSetMode.send(null);
 
    }
    else {
        xmlHttpSetMode.open("GET", '/setMode/stud', false);
        xmlHttpSetMode.send(null);
       
    }
    window.location.replace(addr);
}
