console.log('m starting');
exports.done = false;
const p_imp = require('./zad3p');
console.log('p loaded, executing p');
console.log('in p');
if(p_imp.done) console.log('p done');
exports.done = true;
console.log('m done');