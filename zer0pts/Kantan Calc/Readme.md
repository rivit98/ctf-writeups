# zer0pts CTF 2021, kantan calc, web

## Description
"Kantan" means simple or easy in Japanese.

## Solution
```js
const result = vm.runInNewContext(`'use strict'; (function () { return ${code}; /* ${FLAG} */ })()`, Object.create(null), { timeout: 100 });
```
we are controlling code variable (it cannot be longer than 29 characters). We want to somehow display comment with a flag. The idea is - close function and start new one, cast function to string and return it. Our payload was: `},this.a=()=>{return(a+0)[30]` (30 means string index). After that function looks like this:

```js
'use strict'; (function () { return },this.a=()=>{return(a+0)[30]; /* ${FLAG} */ })()
```
now it is enough to send sequence of indexes and extract flag characters from responses.
