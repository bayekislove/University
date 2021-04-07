var pesel = document.getElementById('PESEL');
var konto = document.getElementById('konto');
var data_ur = document.getElementById('data_ur');
var mail = document.getElementById('mail');
var submit = document.getElementById('submit');

submit.onclick = () => {
    if(konto.checkValidity() && data_ur.checkValidity() && pesel.checkValidity() && mail.checkValidity())
        alert("Formularz wypełniono poprawnie");
    else
        alert("Formularz wypełniono niepoprawnie");
}

konto.onchange = konto_ok;
pesel.onchange = pesel_ok;
mail.onchange = mail_ok;

function konto_ok(){
    konto.setCustomValidity(String(konto.value).length == 26 ? "" : "wrong number of numbers");
}

function pesel_ok(){
    if(String(pesel.value).length != 11){
        pesel.setCustomValidity("wrong number of numbers");
        return;
    }
    let numbers = Array.from(String(pesel.value), Number);
    let suma = 9*numbers[0] + 7*numbers[1] + 3*numbers[2] + numbers[3] + 9*numbers[4] + 7*numbers[5] + 3*numbers[6] + 
                         numbers[7] + 9*numbers[8] + 7*numbers[9];
    pesel.setCustomValidity(suma % 10 === numbers[10] ? "" : "inserted numbers are wrong");
}

function mail_ok(){
    var reggie = /\S+@\S+\.\S+/;
    mail.setCustomValidity(reggie.test(mail.value) ? "" : "incorrect mail");
}