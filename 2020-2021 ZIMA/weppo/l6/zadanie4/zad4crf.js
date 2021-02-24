const http = require('http');
const express = require('express');

app = express();

function wykonaj_przelew(dokad, kwota) {}; //funkcja ktroa robi przelew, nieistotne

app.use('/', (req, res) => {
    console.log(req.query.acc);
    console.log(req.query.am);
    wykonaj_przelew(req.query.acc, req.query.am); //znajdujemy w url skad i dokad mamy wykonac przelew i to robimy 
}) //czyli niepozadanym zachowaniem byloby, kiedy osoba klika w podstawiony przez przestepce link i robi sie przelew na wskazane
//przez niego w linku konto

//mozemy rozwiazac to za pomoca csurfa, ktory tworzy token na walidacje, ktory powinnismy dodawac do requestow ktore zmieniaja stan /
// robia cos waznego w urlu albo w jakims ukrytym polu formularza

//ten problem mozna rozwiazac tez np wysylajac na telefon sms z kodem do wpisania albo brac jakis token z aplikacji mobilnej

http.createServer(app).listen(3000);