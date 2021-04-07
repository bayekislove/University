var http = require('http');
var express = require('express');

var app = express();

app.use(express.urlencoded({extended:true}));

app.set('view engine', 'ejs');
app.set('views', __dirname + '/views');

app.get('/', (req, res) => {
    res.render('index', { przm: '', imie: '', nazw: '', punkty: ''});
});

app.post('/', (req, res) => {
    let przmm = req.body.przm;
    let imiee = req.body.imie;
    let nazww = req.body.nazw;
    let pkt = req.body.punkty;

    let message = "Błędy są w polach:";
    let formCorrect = true;
    if (przmm.length == 0) {
        message += ' Nazwa przedmiotu';
        formCorrect = false;
    }
    if (imiee.length == 0) {
        message += ' Imię';
        formCorrect = false;
    }
    if (nazww.length == 0) {
        message += ' Nazwisko';
        formCorrect = false;
    }

    let pktt = pkt.split(',');
    if (pktt.length != 10) {
        message += ' Deklarowane zadania';
        formCorrect = false;
    }

    if (!formCorrect){
        res.render('index', { przm: przmm, imie: imiee, nazw: nazww, punkty: pkt, message : message})
    } else {
        pktt = pktt.map((x) => {return x == '' ? 0 : x} );
        res.render('print', { przm: przmm, imie: imiee, nazw: nazww, pkt: pktt})
    }
})

http.createServer(app).listen(3000);
console.log('I"m on!');