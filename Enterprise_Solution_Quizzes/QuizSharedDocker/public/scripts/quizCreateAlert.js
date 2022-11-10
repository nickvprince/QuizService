function sendAlert(alertString) {
    alert(alertString);
    console.log("Alert Sent: " + alertString);
}   


function setMenuOptions() {
    
    var select = document.getElementById("quizPool");

    options = ["pool1", "pool2", "pool3", "pool4", "pool5", "pool6"]

    for (var i = 0; i < options.length; i++) {
        var opt = options[i];
        var el = document.createElement("option");
        el.textContent = opt;
        el.value = opt;
        select.appendChild(el);
    }


}