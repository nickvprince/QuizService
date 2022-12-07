function addButton() {
    var xmlHttpGetMode = new XMLHttpRequest();
    xmlHttpGetMode.open("GET", "/timeout", false);
    xmlHttpGetMode.send(null);
    if (xmlHttpGetMode.responseText == "1") {
        //set prof
   
    }
    else {
        //make button invisible
        document.getElementById("switchBtn").hidden = true;
    }
}