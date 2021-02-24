function fib_rec(n){
    return n == 0 || n == 1 ? n : fib_rec(n-1) + fib_rec(n-2);
}

function fib_iter(n){
    if(n == 0 || n == 1){
        return n;
    }
    let n1 = 1, n2 = 0;
    for(let i = 2; i <= n; i++){ //we have two first series elements, thus we start iterating from the third one
        let npom = n1;
        n1 = n2 + npom;
        n2 = npom;
    }
    return n1;
}

function compare(){
    for(let n = 10; n < 44; n++){
        console.time("iter")
        fib_iter(n)
        time_iter = console.timeEnd("iter")

        console.time("rec")
        fib_rec(n)
        time_rec = console.timeEnd("rec")

        console.log(n)
    }
}

//dla n większego niż 44 bez sensu jest dalsze sprawdzanie, bo zajmuje to za długo
//różnica między n = 40 a n = 41 dla rekurencji jest duża i jako jedyna zauważalna, czas wykonania wzrasta o prawie 2 razy (i 1,6s)
//różnice dla node.js i przeglądarki Chrome są ogromne, dla n około 40 w Chromie wywołanie tej funkcji zajmuje około 100 razy dłużej!

//przeglądarka Vivaldi wypada jeszcze wolniej od Chrome'a -> około 1,3 raza dłużej zajmuje wywołanie się tej funkcji

console.log(compare());