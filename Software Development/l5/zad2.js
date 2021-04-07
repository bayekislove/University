const fs = require('fs');
const https = require('https');

(async function() {
    const pfx = await fs.promises.readFile('zad2.pfx');
    let server = https.createServer({
        pfx: pfx,
        passphrase: '123'
    },
    (req, res) => {
        res.setHeader('Content-type', 'text/html; charset=utf-8');
        res.end('zad2');
    })

    server.listen(443);
    console.log("I'm on!");
})();