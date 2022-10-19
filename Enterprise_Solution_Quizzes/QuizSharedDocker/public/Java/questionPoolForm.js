var formID = 0;
var buttonID = 0;
var optionID = 0;
function AddQuestion(i) {
    var t = String(i);
    var b = document.createElement('input');
    var d = document.createElement('input');
    d.setAttribute("type", "text");
    d.setAttribute("value", "question"+formID);
    d.setAttribute("id", formID + "Q");
    b.setAttribute("type", "button");
    b.setAttribute("id", buttonID);
    b.setAttribute("value", "Add option");
    b.setAttribute("onclick", "option(" + buttonID + ","+t+")");
    buttonID++;
    var i = document.createElement('form');
    i.setAttribute("id", formID);
    formID++;
    i.appendChild(d);
    i.appendChild(b);
    document.getElementById("insertHere").insertAdjacentElement("afterend",i);

}

function submit() {

}
function option(i, c) {
    var b = String(i);
    var i = document.createElement('input');
    var z = document.createElement('input');
    i.setAttribute("id", b + "-" + optionID);
    i.setAttribute("name", b);
    z.setAttribute("type", "text");
    z.setAttribute("value", "answer")
    optionID++;
    if (c == 0) {
        i.setAttribute("type", "radio")
       
        document.getElementById(b).insertAdjacentElement("afterend", i);
        document.getElementById(b).insertAdjacentElement("afterend", z);
    }
    else if (c == 1) {
        i.setAttribute("type", "checkbox")
        document.getElementById(b).insertAdjacentElement("afterend", i);
        document.getElementById(b).insertAdjacentElement("afterend", z);
    }
    else {
        alert("Unexpected input");
    }
    
}