module.exports = (i, j, t) => (
  (i %= 30),
  (j %= 30),
  (t %= 30),
  (i += []),
  j + "",
  (t = (t + {}).split("[")[0]),
console.log(i, j, t), console.log("(f[t] -= f[j]),"),   (f[t] -= f[j]),
console.log(i, j, t), console.log("(f[t] &= 0xff)"),   (f[t] &= 0xff)
);