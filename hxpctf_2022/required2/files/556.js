module.exports = (i, j, t) => (
  (i += []),
  j + "",
  (t = (t + {}).split("[")[0]),
  Object.keys(require.cache).forEach((i) => {
    delete require.cache[i];
  })
);