function* fibGen() {
    let n_1 = 0, n_2 = 1;
    while (true) {
        yield n_1;
        [n_1, n_2] = [n_2, n_2 + n_1];
    }
}

function* take(it, top){
    for(let i = 0; i < top; i++){
        yield it.next().value;
    }
}

// zwróć dokładnie 10 wartości z potencjalnie
// "nieskończonego" iteratora/generatora
for (let num of take( fibGen(), 10 ) ) {
    console.log(num);
}