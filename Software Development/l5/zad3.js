var fs = require('fs');
var http = require('http');

(async function() {
    let html = await fs.promises.readFile('zad3.html');
    
    var server = http.createServer(
    (req, res) => { 
        res.setHeader('Content-type', 'text/html; charset=utf-8');
        res.setHeader('Content-disposition', 'attachment; ');
        res.end(html);
    });

    server.listen(3000);
    console.log("I'm on!");
})

