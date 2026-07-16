let inputmessage = document.getElementById("inputmessage");

document.getElementById("sendbutton").onclick = function send()
{
    fetch("/chat?msg=" + inputmessage.value);
};
