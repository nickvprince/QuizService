function sendAlert(alertString) {
    alert(alertString);
    console.log("Alert Sent: " + alertString);
}   


function setMenuOptions() {

    console.log("TELL ME I GOT HERE");

    // Look for the corresponding GET request
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "../json/pools.json", false);
    xmlHttp.send(null);

    // Parse the services json file
    const json = xmlHttp.responseText;
    const obj = JSON.parse(json);
    
    var select = document.getElementById("quizPool");
    for (var i = 0; i < obj.length; i++) {
        var opt = obj[i];
        var el = document.createElement("option");
        el.textContent = opt;
        el.value = opt;
        select.appendChild(el);
    }

    window.location.replace("createQuiz.html");

}