function redirectToAddr (addr) {
    window.location.replace(addr);
}
function changeUrl(name){
    window.history.replaceState(null, "", name);
}