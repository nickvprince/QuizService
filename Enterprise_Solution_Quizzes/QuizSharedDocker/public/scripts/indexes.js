

function addButton() {
    var xmlHttpGetMode = new XMLHttpRequest();
    xmlHttpGetMode.open("GET", "/getMode", false);
    xmlHttpGetMode.send(null);
    if (xmlHttpGetMode.responseText == "na" || xmlHttpGetMode.responseText == "") {
        //set prof
        xmlHttpGetMode.open("GET", "/setMode/prof", false);
        xmlHttpGetMode.send(null);
    }
    else {
        //make button invisible
        document.getElementById("switchBtn").hidden = true;
    }
}