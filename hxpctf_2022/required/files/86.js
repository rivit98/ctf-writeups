module.exports = (i, j, t) => (
  (i %= 30),
  (j %= 30),
  (t %= 30),
  (i += []),
  j + "",
  (t = (t + {}).split("[")[0]),
console.log(i, j, t), console.log("(f[i] = ((f[i] << 7) & 0xff) | (f[i] >> 1))"),   (f[i] = ((f[i] << 7) & 0xff) | (f[i] >> 1))
);