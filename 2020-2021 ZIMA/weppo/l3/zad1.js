var object = {
    a : "coś",

    get a() {
        return this.a;
    },

    set a(x){
        this.a = x;
    },

    capitalize : () => {return 1; }
}

Object.defineProperty(object, b, {
    b = "nie",
    get() { return b; },
    set(x) { b = x; },
});

Object.defineProperty(object, metodka, () => {
    return 2;
})

Object.define(object, c, {
    value : 5,
} )
