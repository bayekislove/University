function Foo() {}
function Bar(string){
    function Qux(){
        return 'asda';
    }
    if(string === 'qux') return Qux();
}

Foo.prototype.Bar = Bar;

var foo = new Foo();

console.log( foo.Bar('qux') );
console.log( foo.Qux());