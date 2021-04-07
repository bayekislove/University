function Tree(val, left, right) {
    this.left = left;
    this.right = right;
    this.val = val;
}

Tree.prototype[Symbol.iterator] = function*() {
    var queque=[this];

    while(queque.length != 0){
        var get = queque.splice(0,1);
        
        if ( get[0].left )  queque.splice(0, 0, get[0].left);
        if ( get[0].right ) queque.splice(0, 0, get[0].right);
        yield get[0].val;
    }
}


var root = new Tree(1,
    new Tree(2, new Tree(3)), new Tree(4));

for(var e of root){
    console.log(e);
}