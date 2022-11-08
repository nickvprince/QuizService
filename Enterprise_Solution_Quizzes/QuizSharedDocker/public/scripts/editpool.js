function load() {
    var pool;
    //get pool being edited
    const urlParams = new URLSearchParams(location.search);
    for (const [key, value] of urlParams) {
        pool = value;
    }
    //add the pool being edited
    document.getElementById("pname").value = pool.toString();
   
    var addTitle = document.createElement("h1");
    addTitle.textContent = "Editing : " + pool.toString();
    document.getElementById("title").insertAdjacentElement("afterbegin", addTitle);
    document.getElementById("title").insertAdjacentElement("beforebegin", poolname);
    document.getElementById('pname').style.display = 'none';
    // http request for pool data
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "/getPool/" + pool.toString(), false);
    xmlHttp.send(null);
    // if file doesnt exist or fails to load go back to selectpool after alerting the user
    if (xmlHttp.responseText.toString() == "fail") {
        alert("Error : Failed to find question pool");
        window.location.replace('/selectPool.html?type=edit');
    }
    var data = xmlHttp.responseText.toString();
    // parse information from data || use questionPoolForm.js functions, modify to input values
    
}




