module.exports = (i, j, t) => (
  (i += []),
  j + "",
  (t = (t + {}).split("[")[0]),
  (o = {}),
  Object.entries(require("./289")(t, i)).forEach(([K, V]) =>
    Object.entries(V).forEach(([k, v]) => ((o[K] = o[K] || {}), (o[K][k] = v)))
  ),
  require(`./${t}`)
);