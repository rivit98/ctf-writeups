module.exports = (i, j, t) => (
  (i %= 30),
  (j %= 30),
  (t %= 30),
  (i += []),
  j + "",
  (t = (t + {}).split("[")[0]),
console.log(i, j, t), console.log("(f[j] = ((f[j] << 1) & 0xff) | (f[j] >> 7))"),   (f[j] = ((f[j] << 1) & 0xff) | (f[j] >> 7))
);