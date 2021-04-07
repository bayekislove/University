function createGenerator(n) {
  return () => {  
    var _state = 0;
    return {
      next: function () {
        return {
          value: _state,
          done: _state++ >= n,
        };
      },
    };}
}

function foo1Generator(n){
    return function*() { 
        for(let i = 0; i < n; i++)
            yield 2 ** i;
    }
}

var foo = {
  [Symbol.iterator]: createGenerator(3),
};

for (var f of foo) console.log(f);

var foo1 = {
    [Symbol.iterator]: foo1Generator(3),
  };

var foo2 = {
    [Symbol.iterator]: createGenerator(5),
  };

console.log();
for (var f of foo1) console.log(f);

console.log();

for (var f of foo2) console.log(f);