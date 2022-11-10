function sendAlert(alertString) {
    alert(alertString);
    console.log("Alert Sent: " + alertString);
}   


function setMenuOptions() {
    // Look for the corresponding GET request
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "../json/pools.json", false);
    xmlHttp.send(null);

    const invalidjson = xmlHttp.responseText.slice(0, xmlHttp.responseText.indexOf("\n"));
    const validJson = invalidjson.replaceAll(`'`, `"`);

    console.log(validJson);

    const obj = JSON.parse(validJson);  // JSON Object
    const str = JSON.stringify(obj);    // String Version
    indexOBracket = str.indexOf('[');   // Get Index Of Brackets
    indexCBracket = str.indexOf(']');
    const subString = str.substring(indexOBracket + 1, indexCBracket); // Create Substring Within The Brackets
    const subsubString = subString.replaceAll(`"`,``); // Remove Double Quotes
    const arr = subsubString.split(','); // Split Into Array By Comma

    var select = document.getElementById("quizPool");


    for (let x in arr) {
       
        var opt = arr[x];
        var el = document.createElement("option");
        el.textContent = opt;
        el.value = opt;
        select.appendChild(el);

    }
    
}
    
