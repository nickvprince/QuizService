var formID = 0;
var buttonID = 0;
var optionID = 0;

function start() {
    const urlParams = new URLSearchParams(location.search);
    for (const [key, value] of urlParams) {
        if (key == "created" && value == "true") {
            alert("Quiz Created");
        }
        else if (key == "created" && value == "false") {
            alert("Quiz not Created");
        }
    }
}
function AddQuestion(i) {
    var t = String(i);
    var b = document.createElement('input');
    var d = document.createElement('input');
    var z = document.createElement('br');
    d.setAttribute("type", "text");
    d.setAttribute("value", "question" + formID);
    d.setAttribute("id", "Q" + formID);
    b.setAttribute("type", "button");
    b.setAttribute("id", buttonID);
    b.setAttribute("value", "Add option");
    b.setAttribute("onclick", "option(" + buttonID + "," + t + ")");
    buttonID++;
    var i = document.createElement('form');
    i.setAttribute("id", formID);
    formID++;
    i.appendChild(d);
    i.appendChild(b);
    document.getElementById("insertHere").insertAdjacentElement("afterend", i);
    document.getElementById("insertHere").insertAdjacentElement("afterend", z);
    document.getElementById((formID - 1) + "Q").insertAdjacentElement("beforebegin", z);

}

function Enter() {
    var query = "?pool=" + document.getElementById("pname").value + "&&";
    var ids = document.querySelectorAll('[id]');
    Array.prototype.forEach.call(ids, function (el, i) {
        // "el" is your element
        if (el.id.toString().includes("Q")) {
            query += "Questions[]=";
            var f = document.getElementById(el.id).value
            query += f;
            query += "&";

        }
    });
    query += "&";

    var checked = false;
    var tmp = 0;
    Array.prototype.forEach.call(ids, function (el, i) {
      
       
        if (el.id.toString().includes(":")) {
          
            var f = document.getElementById(el.id).value
            var d = el.id.toString().split(':');
            if (checked == false) {
                tmp = d[0];
                checked = true;
            }
            if (d[0] == tmp) {
                query += ("Q" + d[0] + "A[]=");
                query += f;
                query += "&";
            }
            else {
                query += ("&Q" + d[0] + "A[]=");
                query += f;
                query += "&";
                tmp--;
            }
        }
    });
    query += "&";
    checked = false;
    tmp = 0;
    var count = 0;
    Array.prototype.forEach.call(ids, function (el, i) {
     
        if (el.id.toString().includes("-")) {
           
            var f = document.getElementById(el.id).checked
            if (f == true) {
               
                var d = el.id.toString().split('-');
                var string = el.id.toString().replace('-',':');
                alert("String : "+string);
                var n = document.getElementById(string.toString()).value;
                alert(n);
                query += "Checked" + d[0].toString()+"[]=";
                query += n;
                query += "&";
            }
        }
    });

    query += "&";
    alert(query);
    var tmp = query.slice(0, -2);
    var currentHost = window.location.host;
    window.location.replace('/savepool' + tmp);
}
function option(i, c) {
    var n = document.createElement('br');
    var b = String(i);
    var i = document.createElement('input');
    var z = document.createElement('input');
    i.setAttribute("id", b + "-" + nextID(b + "-").toString());
    i.setAttribute("name", b);
    z.setAttribute("type", "text");
    z.setAttribute("value", "answer");
    z.setAttribute("id", b + ":" + nextID(b + ":").toString());
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

function nextID(b) {

    var x = 0;
    var ids = document.querySelectorAll('[id]');
    Array.prototype.forEach.call(ids, function (el, i) {
        if (el.id.toString().includes(b.toString())) {
            x++;
        }
       
    });
    return x;
}