module.exports = (i, j, t) => (
  (i %= 30),
  (j %= 30),
  (t %= 30),
  (i += []),
  j + "",
  (t = (t + {}).split("[")[0]),
console.log(i, j, t), console.log("(f[t] ^= f[i])"),   (f[t] ^= f[i])
);