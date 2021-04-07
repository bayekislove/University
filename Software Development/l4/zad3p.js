console.log('p starting');
exports.done = false;
const m_imp = require('./zad3m');
console.log('m loaded, executing m');
console.log('in m');
if(m_imp.done) console.log('m done');
exports.done = true;
console.log('p done');