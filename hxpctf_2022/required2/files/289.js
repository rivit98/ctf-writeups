module.exports = (i, j, t) => (
  (i += []),
  j + "",
  (t = (t + {}).split("[")[0]),
  JSON.parse(
    `{"__proto__":{"data":{"name":"./${i}","exports":{".": "./${j}.js"}},"path": "./"}}`
  )
);