function* fibGen() {
    let n_1 = 0, n_2 = 1;
    while (true) {
        yield n_1;
        [n_1, n_2] = [n_2, n_2 + n_1];
    }
}

function fibIte(){
    let n_1 = 0, n_2 = 1, _value = 0; 
    return {
      next: function () {
        [_value, n_1, n_2] = [n_1, n_2, n_2 + n_1]
        return {
            value: _value,
            done: false,
          };
      },
    };
}

var foo = {
    [Symbol.iterator]: fibGen,
  };

var foo2 = {
    [Symbol.iterator]: fibIte,
}

for(var k of foo2) { 
    console.log( k ); 
    if(k > 100) break; };

console.log(); console.log(); console.log();

for(var k of foo) { 
    console.log( k ); 
    if(k > 100) break; };
