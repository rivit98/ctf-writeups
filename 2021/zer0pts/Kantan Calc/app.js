const vm = require('vm');
const FLAG = "zeropts{sadgeflag}"

// const payload = "},function a(){return a+''"
const payload = "},this.a=()=>{return(a+0)[30]"

let output = '';
const code = payload + '';

if (code && code.length < 30) {
	try {
		console.log(29-payload.length)
		console.log(`'use strict'; (function () { return ${code}; /* ${FLAG} */ })()`)
		const result = vm.runInNewContext(`'use strict'; (function () { return ${code}; /* ${FLAG} */ })()`, Object.create(null), { timeout: 100 });
		output = result + '';
		console.log("")
		console.log(output)
		if (output.includes('zer0pts')) {
			output = 'Error: please do not exfiltrate the flag';
		}
	} catch (e) {
		console.log(e)
		output = 'Error: error occurred';
	}
} else {
	output = 'Error: invalid code';
}

console.log(output)
