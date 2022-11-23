function setMenuOptions() {
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

function redirectToAddr (addr) {
    window.location.replace(addr);
}