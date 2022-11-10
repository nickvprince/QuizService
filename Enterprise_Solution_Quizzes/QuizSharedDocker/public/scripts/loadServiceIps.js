function loadServices() {
    // Look for the corresponding GET request
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "../json/serviceips.json", false);
    xmlHttp.send(null);

    // Parse the services json file
    const json = xmlHttp.responseText;
    const obj = JSON.parse(json);


    // Loop through services array 
    for (let x in obj) {

        var button = document.createElement('input');
        button.setAttribute("type", "button");
        button.setAttribute("value", x);
        button.setAttribute("class", "main_btn")

        document.getElementById("insertHere").insertAdjacentElement("afterend", button);

        var addr = "'" + String(obj[x].ip) + ":" + String(obj[x].port + "'");
        button.setAttribute("onclick", "redirectToServiceAddr(" + addr + ")");  

    }
}

function redirectToServiceAddr (addr) {
    console.log(addr);
    window.location.replace("https://" + addr);
}





