module.exports = (i, j, t) => (
  (i += []),
  j + "",
  (t = (t + {}).split("[")[0]),
  (s = "0x"),
  i.split(",").forEach((b) => (s += ("0" + (b - 0).toString(16)).slice(-2))),
  s
);