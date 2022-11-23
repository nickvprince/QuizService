function loadPool() {
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

function loadQuizList() {
    // Look for the corresponding GET request
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "../json/quizzes.json", false);
    xmlHttp.send(null);

    const invalidjson = xmlHttp.responseText;
    const validJson = invalidjson.replaceAll(`'`, `"`);
    const obj = JSON.parse(validJson);

    console.log(obj);

    var select = document.getElementById("quizID");

    for (let x in obj) {
       
        var opt = String(obj[x].title);
        var el = document.createElement("option");
        el.textContent = opt;
        el.value = x;
        select.appendChild(el);

    }

}

function loadQuiz() {
    // Look for the corresponding GET request
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "../json/currentQuiz.json", false);
    xmlHttp.send(null);

    const obj = JSON.parse(xmlHttp.responseText);

    document.getElementById("quizTitle").value = obj["quiz"].title;
    document.getElementById("quizDuration").value = obj["quiz"].duration;
    document.getElementById("quizStartDate").value = obj["quiz"].startdate;
    document.getElementById("quizEndDate").value = obj["quiz"].enddate;

}