var fs = require('fs');

function IP(string){
    this.val = string;
    this.counter = 1;
}

IP.prototype.tab = [];

function getIPfromLog(string){
    return (string.split(' '))[1];
}

function getLogs(){
    var array = fs.readFileSync('./log.txt', 'utf8').split('\n');
    for(let i = 0; i < array.length; i++){
        var pom = array[i];
        array[i] = getIPfromLog(pom);
    }
    return array;
};

function searchThroughIPs(IPtab){
    if(IPtab != null){
        var pomIP = new IP(IPtab[0]);
        pomIP.tab.push(pomIP);
    }

    for(let i = 1; i < IPtab.length; i++){
        let __IP = IPtab[i];
        var p; var exists = false;
        var p = new IP(__IP);

        for(let j = 0; j < p.tab.length; j++){
            var created = p.tab[j];

            if( created.val == __IP ){
                exists = true;
                created.counter++;
            }
        }

        if(!exists){
            p.tab.push(p);
        }
    }
}

function print3(){
    searchThroughIPs(getLogs());
    var setIP = (new IP('')).tab;

    function compare(a, b){
        if(a.counter == b.counter) return 0;
        return a.counter < b.counter ? -1 : 1;
    }

    setIP.sort( compare );

    for(let i = setIP.length - 3; i < setIP.length; i++){
        console.log(setIP[i].val);
    }
}

print3();