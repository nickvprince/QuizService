function load() {

    const urlParams = new URLSearchParams(location.search);
    var b = document.createElement('input');
    b.setAttribute("type", "button");
    b.setAttribute("class", "main_btn");
    b.setAttribute("role", "button");
    b.setAttribute("id", "Submit");
    
    for (const [key, value] of urlParams) {
        if (key == "type" && value == "edit") {
            b.setAttribute("value", "Edit");
          
            b.setAttribute("onclick", "out(0)");
        }
        else if (key == "type" && value == "delete") {
            b.setAttribute("value", "Delete");
            b.setAttribute("onclick", "out(1)");
            
        }
    }
       
    document.getElementById("pname").insertAdjacentElement("afterend", b);

     
        
}
function out(i) {
    var n =document.getElementById("pname").value;
    if (i == 0) {
        window.location.replace("editPool.html?pool=" + n.toString());
    }
    else if (i == 1) {
        window.location.replace("deletePool.html?pool=" + n.toString());
    }
}