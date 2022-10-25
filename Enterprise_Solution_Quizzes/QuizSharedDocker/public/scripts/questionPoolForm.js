var formID = 0;
var buttonID = 0;
var optionID = 0;
function AddQuestion(i) {
    var t = String(i);
    var b = document.createElement('input');
    var d = document.createElement('input');
var z = document.createElement('br');
    d.setAttribute("type", "text");
    d.setAttribute("value", "question"+formID);
    d.setAttribute("id", "Q"+formID);
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
 document.getElementById("insertHere").insertAdjacentElement("afterend",z);
 document.getElementById((formID-1) + "Q").insertAdjacentElement("beforebegin",z);

}

function Enter() {
  var query = "?";
  var ids = document.querySelectorAll('[id]');
    Array.prototype.forEach.call(ids, function (el, i) {
        // "el" is your element
        if (el.id.toString().includes("Q")) {
query+=el.id.toString();
query+= "=";
var f = document.getElementById(el.id).value
query+=f;
query+="&&";
           
        }
	else if (el.id.toString().includes("-")) {
var f = document.getElementById(el.id).checked
var d = el.id.toString().split('-');
if(f == true) { 
query+=("Q"+d[0]+"A"+d[1]+"C")
query+= "=";
query+=f;
query+="&&";
}
            
        }
else if (el.id.toString().includes(":")) {
var f = document.getElementById(el.id).value
var d = el.id.toString().split(':');
	  query+= ("Q"+d[0]+"A"+d[1]);
query+= "=";
query+=f;
query+="&&";	
            
        }
       

    });

var tmp = query.slice(0,-2);
var currentHost = window.location.host;
window.location.replace('/savepool'+tmp);
}
function option(i, c) {
var n = document.createElement('br');
    var b = String(i);
    var i = document.createElement('input');
    var z = document.createElement('input');
    i.setAttribute("id", b + "-" + optionID);
    i.setAttribute("name", b);
    z.setAttribute("type", "text");
    z.setAttribute("value", "answer");
z.setAttribute("id", b + ":" + optionID);
    optionID++;
    if (c == 0) {
        i.setAttribute("type", "radio")
       
        document.getElementById(b).insertAdjacentElement("afterend", i);
        document.getElementById(b).insertAdjacentElement("afterend", z);
 document.getElementById(b).insertAdjacentElement("afterend", n);
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