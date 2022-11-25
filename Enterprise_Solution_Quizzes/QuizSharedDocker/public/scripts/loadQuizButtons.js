function loadQuizButtons() {

    // Look for the corresponding GET request
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "../json/quizzes.json", false);
    xmlHttp.send(null);

    const invalidjson = xmlHttp.responseText;
    const validJson = invalidjson.replaceAll(`'`, `"`);
    const obj = JSON.parse(validJson);

    console.log(obj);

    var select = document.getElementById("selectQuiz");
    for (let x in obj) {
    
        var opt = String(obj[x].title);
        var listitem = document.createElement("li");
        var el = document.createElement("BUTTON");
        el.innerHTML = opt;
        el.addEventListener("click", () => {
            var addr = "../takeQuiz.html?quizID=" + x;
            el.value = redirectToAddr(addr);
            
        });
        listitem.appendChild(el);
        select.appendChild(listitem);

    }

}

function redirectToAddr (addr) {
    window.history.pushState(window.history.state, "");
    window.location.replace(addr);
}