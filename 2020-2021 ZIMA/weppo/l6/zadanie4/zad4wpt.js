//załozmy, ze nasza aplikacja dziala tak, ze kiedy sprobujemy wpisac w URL /admin, to przenosi nas to czesci administracyjnej aplikacji
//czyli kazdy wpisujac /admin jest w stanie dostac sie do czesci dla adminow
const http = require('http');
const express = require('express');
const url = require('url');

app = express();

/*app.use('/:id', (req, res) => {
    if(req.params.id.includes('admin')){ //zapewniamy odpowiednia walidacje -> jesli w url wpisanym przez uzytkownika znajduje sie admin,
                                        //to zapobiegamy wejsciu na czesc dla administracji serwera
        res.end("Chyba zbladziles ;)"); 
    } else{
        res.end(req.params.id);
    }
})*/

http.createServer(app).listen(3000);