const origFloor = Math.floor

Math.floor = (val) => {
	let a = origFloor(val);
	console.log(a)
	return a;
  }

const dumper = require('./code')
dumper()


